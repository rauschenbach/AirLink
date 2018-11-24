#include <stdio.h>
#include "proto.h"
#include "my_cmd.h"
#include "utils.h"
#include "globdefs.h"
#include "ComPort.h"
#include "main.h"
#include "com_cmd.h"



#define SLEEP_MODEM_RX           350
#define SLEEP_MODEM_TIMEOUT      500


static CComPort *CommPort = NULL;
static PORT_COUNT_STRUCT my_count;
static CRITICAL_SECTION cs;
static XCHG_ERR_COUNT xchg_count;
////////////////////////////////////////////////////////////////////////////////

/**
 * �������� ��������
 */
void PortGetXchgErr(XCHG_ERR_COUNT * err)
{
    err->tx_ok = xchg_count.tx_ok;
    err->rx_err = xchg_count.rx_err;

    // �������� �������
    memset(&xchg_count, 0, sizeof(xchg_count));
}




////////////////////////////////////////////////////////////////////////////////
// ����� ������� ������ � ������ ��� � �����������������
static void LogOutStr(char *txt)
{
    frmMain->LogOut(txt);
}


static void PrintModemCmd(char *txt, bool req = false)
{
    int i;
    char buf[1024];
    String s;

    // ��������� � �����
    memset(buf, 0, sizeof(buf));
    memcpy(buf, txt, strlen(txt));

    // ������ ������� ������
    for (i = 0; i < strlen(txt); i++) {
	if (buf[i] == '\x0D' || buf[i] == '\x0A') {
	    buf[i] = 0;
	    break;
	}
    }
    if(!req)
       s = "Send modem command: " + String(buf);
    else
       s = "Read modem answer: " + String(buf);
    LogOutStr(s.c_str());
}




static void PrintCommandResult(char* cmd, int res) 
{
  char buf[128];

  sprintf(buf, "%s %s", res == 0? "Tx OK:" : "Tx Err:", cmd);
  LogOutStr(buf);
}

// ����������� ����
bool PortInit(int num, u32 baud)
{
    AnsiString temp;
    struct CONNECTION_PARAMETERS params;

    temp = "COM" + IntToStr(num);

    //��������� ���� � ���������� ���������
    params.COMPort = num;
    params.PortSpeed = baud;
    params.MaxFullRetrains = 5;
    params.MaxTimeout = 50;
    memset(&my_count, 0, sizeof(my_count));

    // ������� ���� ���� �� ����
    if (CommPort != NULL) {
	delete CommPort;
	CommPort = NULL;
    }

    CommPort = new CComPort(params);
    Sleep(1);
    CommPort->Init();

    // ����������� ������
    InitializeCriticalSection(&cs);
    return true;
}

// ������� ����
bool PortClose(void)
{
    // ������� ����
    if (CommPort != NULL) {
	delete CommPort;
        CommPort = NULL;
    }
    DeleteCriticalSection(&cs);
    return true;
}


// ������ � ����
static int PortWrite(char *buf, int len)
{
    int num;
    if (CommPort != NULL) {
	num = CommPort->Write(buf, len);
	my_count.tx_pack++;	//��������
    } else {
	return -1;
    }
    return num;
}


// ������ �� �����
static int PortRead(char *buf, int len)
{
    int num;

    // ������ ����� ������� �� �� �������� ������
    num = CommPort->Read(buf, len);
    if (num < len && num != 5) {


    	my_count.rx_cmd_err++;	//�������
	CommPort->Reset();
    }

    my_count.rx_pack++;
    return num;
}


// ������ �� �����
static int PortReadToTimeout(char *buf, int t)
{
    int num;

    num = CommPort->ReadUntilTimeout(buf, t);
    if (num < 0) {		// ��� �������� ������
      	my_count.rx_cmd_err++;	//�������
	CommPort->Reset();
	return -1;		// ��� �����
    }

    CommPort->Reset();
    my_count.rx_pack++;		//�������
    return num;
}

////////////////////////////////////////////////////////////////////////////////
// ����� � ������ ������
////////////////////////////////////////////////////////////////////////////////

// ������ �������� ������
void PortGetXchgCounts(void *p)
{
    if (p != NULL) {
	memcpy(p, &my_count, sizeof(my_count));
    }
}

/**
 * ������� ����� �������. �������� data �� ���������
 */
bool SendSomeCommand(u8 cmd, void *data, int data_len)
{
    u8 buf[255];
    int num;
    bool res = false;

    do {
	if (data_len > 255 || data_len < 0)
	    break;		// ������������ ����� �������

	buf[0] = 0xff;		// �����
	buf[1] = 0;
	buf[2] = data_len + 1;	// �� ������� ������ ����� ������
	buf[3] = cmd;		// �������

	// � ������� ���� ������
	if (data != NULL && data_len > 0) {
	    memcpy(buf + 4, (u8 *) data, data_len);
	}
	add_crc16(buf);		// ����������� �����

	num = PortWrite(buf, buf[2] + 5);
	if (num != buf[2] + 5) {
	    break;		// ���� �� ������
	}
        if(cmd == UART_CMD_DEV_START)
        frmMain->PrintLog("�����: ", buf, buf[2] + 5);
	res = true;		// ��� ��
    } while (0);

    return res;
}

/**
 * �������� ����� �� �����
 */
bool ReadAnyData(void *data, int len)
{
    int num;
    bool res = false;


    do {
	if (len == 0 || data == NULL)
	    break;

	// ���� ������
	num = PortRead((u8 *) data, len);
	if (num < len && num != 5) {
	    break;
	}

	if (test_crc16((c8 *) data)) {
	    break;
	} else {
	    res = true;
	}
    } while (0);


    return res;
}


/**
 * �������� ����� �� �����
 */
bool ReadAnyDataToTimeout(void *data, int time)
{
    int num;
    bool res = false;

    do {
	if (time == 0 || data == NULL)
	    break;

	// ���� ������
	num = PortReadToTimeout((u8 *) data, time);
	if (num <= 0) {
	    break;
	}

	if (test_crc16((c8 *) data)) {
	    break;
	} else {
	    res = true;
	}

    } while (0);

    return res;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                          ���� �������                                     						//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������� ����� - new
int TimeSync(long *t)
{
    int res = -1;
    char buf[255];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_SYNC_RTC_CLOCK, (u8 *) t, 4) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);

    PrintCommandResult("������������� RTC GNS110 � �������� PC!", res);

    return res;
}

//---------------------------------------------------------------------------
// ����� ����� - new
int TimeGet(RTC_TIME_STRUCT * rtc)
{
    int res = -1;
    char str[255];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_GET_RTC_CLOCK, NULL, 0) == false) {
	    break;
	}
	// ������
	if (ReadAnyData((u8 *) str, sizeof(RTC_TIME_STRUCT)) == true) {
	    memcpy(rtc, str, sizeof(RTC_TIME_STRUCT));
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);

    if (res == 0)
	xchg_count.tx_ok++;
    else
	xchg_count.rx_err++;	//� �������

    return res;
}

//---------------------------------------------------------------------------
// �������� �������� - new
int CountsGet(PORT_COUNT_STRUCT * cnt)
{
    int res = -1;
    char str[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_GET_COUNTS, NULL, 0) == false) {
	    break;
	}
	// ������
	if (ReadAnyData((u8 *) str, sizeof(PORT_COUNT_STRUCT)) == true) {
	    memcpy(cnt, str, sizeof(PORT_COUNT_STRUCT));
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);

    if (res == 0)
	xchg_count.tx_ok++;
    else
	xchg_count.rx_err++;	//� �������

    return res;
}

//---------------------------------------------------------------------------
// ����� ������ ��������
int GetWorkTime(DEV_WORK_TIME_STRUCT * wt)
{
    int res = -1;
    char str[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_GET_WORK_TIME, NULL, 0) == false) {
	    break;
	}
	// ������
	if (ReadAnyData((u8 *) str, sizeof(DEV_WORK_TIME_STRUCT)) == true) {
	    memcpy(wt, str, sizeof(DEV_WORK_TIME_STRUCT));
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);

    if (res == 0)
	xchg_count.tx_ok++;
    else
	xchg_count.rx_err++;	//� �������

    return res;
}

//---------------------------------------------------------------------------
// ����� ������ �������� (�������)
int SetWorkTime(DEV_WORK_TIME_STRUCT * wt)
{
    int res = -1;
    char str[256];

    memset(str, 0, sizeof(str));

    EnterCriticalSection(&cs);
    do {
//    FF 00 0D C9 00 00 00 00 00 00 00 00 00 00 00 00 2E 4A
	if (SendSomeCommand(UART_CMD_SET_WORK_TIME, str, sizeof(u32) * 3) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(str, 5) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);

    if (res == 0)
	xchg_count.tx_ok++;
    else
	xchg_count.rx_err++;	//� �������
    PrintCommandResult("����� ������ ������", res);
    return res;
}

//---------------------------------------------------------------------------
// �������� ������ - new
int StatusGet(DEV_STATUS_STRUCT * st)
{
    int res = -1;
    char str[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_GET_DSP_STATUS, NULL, 0) == false) {
	    break;
	}
	// ������
	if (ReadAnyData((u8 *) str, sizeof(DEV_STATUS_STRUCT)) == true) {
	    memcpy(st, str, sizeof(DEV_STATUS_STRUCT));
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);

    if (res == 0)
	xchg_count.tx_ok++;
    else
	xchg_count.rx_err++;	//� �������

    return res;
}

//---------------------------------------------------------------------------
// ������� ����� ������ ��������� ��� ������ 5 ����
int DataGet(void *p)
{
    int res = -1;
    int len;
    ADS1282_PACK_STRUCT *pack;

    if (p == NULL)
	return -1;

    pack = (ADS1282_PACK_STRUCT *) p;

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_GET_DATA, NULL, 0) == false) {
	    break;
	}
	// ������
	res = ReadAnyData((u8 *) pack, sizeof(ADS1282_PACK_STRUCT));
	if (res == true) {
	    len = pack->len;
	    if (len == 0xF9)	// ������
		res = 0;
	    else if (len == 0x02)	//��� ������?
		res = 1;
	    else
		res = -1;
	} else {
	    res = -1;
	}
    } while (0);
    LeaveCriticalSection(&cs);
    return res;
}

//---------------------------------------------------------------------------
//  �������: ���� ��������� - new
int StopDevice(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_DEV_STOP, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	} 
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("���� ���������!", res);
    return res;
}


//---------------------------------------------------------------------------
//  �������: �������� ����� ������
int ClearBuf(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_CLR_BUF, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	} 
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("������� ���������� ������!", res);
    return res;
}

//---------------------------------------------------------------------------
// ������ ������������ - new
int InitTest(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_INIT_TEST, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	} 
    } while (0);
    LeaveCriticalSection(&cs);
    if(res)
     PrintCommandResult("T�����������!", res);
    return res;
}

//---------------------------------------------------------------------------
// Modem ON
int ModemOn(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_MODEM_ON, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyDataToTimeout(buf, 250) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);
    if(res)
     PrintCommandResult("��������� ������!", res);
    return res;
}

//---------------------------------------------------------------------------
// Modem OFF
int ModemOff(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_MODEM_OFF, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyDataToTimeout(buf, 250) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("���������� ������!", res);
    return res;
}

//---------------------------------------------------------------------------
// Burn ON
int BurnOn(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_BURN_ON, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyDataToTimeout(buf, 250) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("��������� ���� ��������!", res);
    return res;
}

//---------------------------------------------------------------------------
// Burn OFF
int BurnOff(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_BURN_OFF, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyDataToTimeout(buf, 250) == true) {
	    LogOutStr("Rele BurnOff: OK");
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("���������� ���� ��������!", res);
    return res;
}

//---------------------------------------------------------------------------
// GPS ON
int GpsOn(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_GPS_ON, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("��������� ������ GPS!", res);
    return res;
}

//---------------------------------------------------------------------------
// GPS OFF
int GpsOff(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_GPS_OFF, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("���������� ������ GPS!", res);
    return res;
}

//---------------------------------------------------------------------------
int NmeaGet(void *par)
{
    int res = -1, len;

    NMEA_RX_BUF *rx_pack;

    if (par == NULL)
	return -1;

    rx_pack = (NMEA_RX_BUF *) par;
    memset((u8*)par, 0, 10);//������ ������ �������

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_NMEA_GET, NULL, 0) == false) {
	    break;
	}
	// ������
	res = ReadAnyDataToTimeout((u8 *) rx_pack, sizeof(NMEA_RX_BUF));
	if (res == true) {
	    len = rx_pack->len;
	    if (len == NMEA_PACK_SIZE)	// ������
		res = 0;
	    else if (len == 0x02)	//��� ������?
		res = 1;
	    else
		res = -1;
	} 
    } while (0);
    LeaveCriticalSection(&cs);

    return res;
}
//---------------------------------------------------------------------------
// ����� DSP - new
int ResetDSP(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_DSP_RESET, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	} 
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("����� DSP!", res);
    return res;
}

//---------------------------------------------------------------------------
// ���������� �������� - new
int PowerOff(void *par)
{
    int res = -1;
    u8 buf[256];

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_POWER_OFF, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	} 
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("���������� ������� GNS110!", res);
    return res;
}

//---------------------------------------------------------------------------
// ������ ����� ������� - new
int SetId(void *par)
{
    int res = -1;
    char buf[255];
    u16 num;

    if (par == NULL)
	return -1;

    num = *(u16 *) par;

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_SET_DSP_ADDR, (u8 *) & num, 2) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);

    sprintf(buf, "������� ������ ������� %d!", num);
    PrintCommandResult(buf, res);
    if(res == 0) {
        LogOutStr("��������� ������������ �������!");
    }
    return res;
}

//---------------------------------------------------------------------------
// -- �������� EEPROM
int SetTimesToZero(void *par)
{
    char buf[255];
    int res;

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_ZERO_ALL_EEPROM, NULL, 0) == false) {
	    break;
	}
	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("����� EEPROM", res);
    return res;
}

//---------------------------------------------------------------------------
// �������� ���������  ���� �������
int GetConst(void *in)
{
    int res = -1;
    char buf[256];

    if (in == NULL)
	return res;

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_GET_ADC_CONST, NULL, 0) == false) {
	    break;
	}
	// ������ ���������
	if (ReadAnyData(buf, sizeof(ADS1282_Regs) + 3) == true) {
	    memcpy(in, buf + 1, sizeof(ADS1282_Regs));
	    LogOutStr("GetConst: OK");
	    res = 0;
	} 
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("��������� �������� �� EEPROM!", res);
    return res;
}

//---------------------------------------------------------------------------
// �������� ��������� ���� �������
// � ����������� ������ - 2 ����, �.�. � ��� ���� ��������
// ����� ������ �������� �� ����
int SetConst(void *in)
{
    int res = -1;
    u8 buf[256];
    ADS1282_Regs *regs;

    if (in == NULL)
	return res;

    regs = (ADS1282_Regs *) in;

    EnterCriticalSection(&cs);
    do {
	if (SendSomeCommand(UART_CMD_SET_ADC_CONST, (u8 *) regs, sizeof(ADS1282_Regs)) == false) {
	    break;
	}
	// ���� ������-�������� ������ � ���������!������ 5 ���� �������
	if (ReadAnyDataToTimeout(buf, 1000) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("������ �������� � EEPROM!", res);
    if(res == 0) {
      LogOutStr("��������� ������������ �������!");
    }
    return res;
}

//---------------------------------------------------------------------------
// ������ ������� ��������� ���������
// � ����������� ������ - 2 ����, �.�. � ��� ���� ��������
// ����� ������ �������� �� ����
int StartDevice(START_ADC_STRUCT * start)
{
    u8 buf[1024];
    int num, res = -1;


    EnterCriticalSection(&cs);
    do {
	//������ ������� "������� � ��������� �����������"
	if (SendSomeCommand(UART_CMD_DEV_START, (u8 *) start, sizeof(START_ADC_STRUCT)) == false) {
	    break;
	}
	Sleep(250);	// ���� ������-�������� ������ � ���������!

	// ������ 5 ���� �������
	if (ReadAnyData(buf, 5) == true) {
	    res = 0;
	}
    } while (0);
    LeaveCriticalSection(&cs);
    PrintCommandResult("����� ���������!", res);
    return res;
}

///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//                                   ������� ������
///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// �������� ����� ������
// ������� ���� � ��� ������
int GetModemNumber(void *par)
{
    u8 buf[512];
    u8 temp[128];
    int res = -1;
    char *str = "$RGANM,,*d05c\r\n";
    u16 *num;


    // �������� ��������
    if (par != NULL) {
	num = (u16 *) par;

	do {
	    EnterCriticalSection(&cs);
	    do {
		//������ ������� �������� ����� ������
		PrintModemCmd(str);
		if (SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str)) == false) {
		    res = -1;
		    break;
		}
		// ���� ������-�������� ������ ��� ������� ������: 5 ���� �������
		if (ReadAnyData(buf, 5) == true) {
		    res = 0;
		} else {
//		    res = -1;
		}

	    } while (0);
	    LeaveCriticalSection(&cs);
	    if (res < 0)
		break;

	    Sleep(SLEEP_MODEM_RX);
	    EnterCriticalSection(&cs);
	    do {
		// �������� ����� ������
		if (SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0) == false) {
		    res = -1;
		    break;
		}
		// ������� �����: $AGANM,0015,00*243b\r\n
		res = -1;
		if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		    if (strstr((char*)buf, "$AGANM")!= NULL) {	// ��� �������� ������
			memcpy(temp, buf + 1, buf[0]);
			temp[19] = 0;
			PrintModemCmd(temp, 1);
			*num = am3_get_dev_num(temp);
			frmMain->ShowModemNum(*num);
			res = 0;
		    }
		}
	    } while (0);
	    LeaveCriticalSection(&cs);
	} while (0);
    }
    if (res < 0)
	LogOutStr("GetModemNum: Error");
    return res;
}

//---------------------------------------------------------------------------
// �������� ����� ������
// ������� ���� � ��� ������
int GetModemTime(void *par)
{
    int num;
    u8 buf[512];
    u8 temp[512];
    int res;
    char *str = "$RGACL,,*a13c\r\n";	// �������� ���� ��������� �������

    MODEM_STRUCT *ms;

    // �������� ��������
    if (par != NULL) {
	ms = (MODEM_STRUCT *) par;
	memset(&ms->modem_time, 0, sizeof(SYSTEMTIME));	// ���� ����� �� ������

	do {
	    EnterCriticalSection(&cs);
	    do {
		//������ ������� �������� ����� ������
		res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
		PrintModemCmd(str);
		if (res == false) {
		    res = -1;
		    break;
		}
		// ������ 5 ���� �������
		if (ReadAnyData(buf, 5) == true) {
		    res = 0;
		} else {
//		    res = -1;
		}

	    } while (0);
	    LeaveCriticalSection(&cs);
	    if (res < 0)
		break;

	    Sleep(SLEEP_MODEM_RX);
	    EnterCriticalSection(&cs);
	    do {
		// �������� ����� ������
		res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
		if (res == false) {
		    res = -1;
		    break;
		}
		// ������� �����: $AGACL,00.00.00,00:00,00*7cdd\r\n
		res = -1;
            if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		    if (strstr((char*)buf, "$AGACL")!= NULL) {	// ��� �������� ������
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buf + 1, buf[0]);
			PrintModemCmd(temp, 1);
			if (am3_get_modem_time(temp, &ms->modem_time) > 0) {
			    frmMain->ShowModemTime(&ms->modem_time);
			    res = 0;
			}
		    }
		}
	    } while (0);
	    LeaveCriticalSection(&cs);
	} while (0);
    }
    if (res < 0)
	LogOutStr("GetModemTime: Error");
    return res;
}

//---------------------------------------------------------------------------
// �������� ��������� �����
// ������� ���� � ��� ������
int GetAlarmTime(void *par)
{
    int num;
    u8 buf[512];
    u8 temp[512];
    int res;
    char *str = "$RGAAL,,*cf5c\r\n";	// �������� ��������� ����� ��������

    MODEM_STRUCT *ms;

    // �������� ��������
    if (par != NULL) {
	ms = (MODEM_STRUCT *) par;
	ms->modem_num = -1;	// ���� ����� �� ������

	do {
	    EnterCriticalSection(&cs);
	    do {
		//������ ������� �������� ����� ������
		res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
		PrintModemCmd(str);
		if (res == false) {
		    res = -1;
		    break;
		}
		// ������ 5 ���� �������
		if (ReadAnyData(buf, 5) == true) {
		    res = 0;
		} else {
//		    res = -1;
		}

	    } while (0);

	    LeaveCriticalSection(&cs);
	    if (res < 0)
		break;

	    Sleep(SLEEP_MODEM_RX);
	    EnterCriticalSection(&cs);
	    do {
		// �������� ����� ������
		res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
		if (res == false) {
		    res = -1;
		    break;
		}
		// ������� �����: $AGAAL,21.05.13,11:07,00*7cdd\r\n
		res = -1;
		if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		    if (strstr((char*)buf, "$AGAAL")!= NULL) {	// ��� �������� ������
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buf + 1, buf[0]);
			PrintModemCmd(temp, 1);
			am3_get_alarm_time(temp, &ms->alarm_time);
                        // ���� ����� ��
                        if(ms->alarm_time.wMonth != 0 && ms->alarm_time.wDay != 0)
          		  frmMain->ShowAlarmTime(&ms->alarm_time);
			res = 0;
		    }
		}
	    } while (0);
	    LeaveCriticalSection(&cs);
	} while (0);
    }
    if (res < 0)
	LogOutStr("GetAlarmTime: Error");
    return res;
}

//---------------------------------------------------------------------------
// �������� ������� ����� �����
// ������� ���� � ��� ������
int GetCalTime(void *par)
{
    int num;
    u8 buf[512];
    u8 temp[128];
    int res;
    char *str = "$RGAST,,*6885\r\n";	// �������� ������� ����� �����

    MODEM_STRUCT *ms;

    // �������� ��������
    if (par != NULL) {
	ms = (MODEM_STRUCT *) par;
	ms->am3_h0_time = -1;	// ���� ����� �� ������
	ms->am3_m0_time = -1;	// ���� ����� �� ������
	ms->am3_h1_time = -1;	// ���� ����� �� ������
	ms->am3_h1_time = -1;	// ���� ����� �� ������

	do {
	    EnterCriticalSection(&cs);
	    do {
		//������ ������� �������� ����� ������
		res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
		PrintModemCmd(str);
		if (res == false) {
		    res = -1;
		    break;
		}
		// ������ 5 ���� �������
		if (ReadAnyData(buf, 5) == true) {
		    res = 0;
		} else {
//		    res = -1;
		}

	    } while (0);
	    LeaveCriticalSection(&cs);
	    if (res < 0)
		break;

	    Sleep(SLEEP_MODEM_RX);
	    EnterCriticalSection(&cs);
	    do {
		// �������� ����� ������
		res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
		if (res == false) {
		    res = -1;
		    break;
		}
		// ������� �����
		res = -1;
		if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		    if (strstr((char*)buf, "$AGAST")!= NULL) {
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buf + 1, buf[0]);
			PrintModemCmd(temp, 1);
			am3_get_cal_time(temp, &ms->am3_h0_time, &ms->am3_m0_time, &ms->am3_h1_time, &ms->am3_m1_time);
			frmMain->ShowCalTime(ms->am3_h0_time, ms->am3_m0_time, ms->am3_h1_time, ms->am3_m1_time);
			res = 0;
		    }
		}
	    } while (0);
	    LeaveCriticalSection(&cs);
	} while (0);
    }
    if (res < 0)
	LogOutStr("GetCalTime: Error");
    return res;
}

//---------------------------------------------------------------------------
// �������� ������� ��������
// ������� ���� � ��� ������
int GetTimeForRelease(void *par)
{
    int num;
    u8 buf[512];
    u8 temp[128];
    int res;
    char *str = "$RGATZ,,*ce1a\r\n";	// ����� �� �������� (���)

    MODEM_STRUCT *ms;

    // �������� ��������
    if (par != NULL) {
	ms = (MODEM_STRUCT *) par;
	ms->time_for_release = -1;	// ���� ����� �� ������

	do {
	    EnterCriticalSection(&cs);
	    do {
		//������ ������� �������� ����� ������
		res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
		PrintModemCmd(str);
		if (res == false) {
		    res = -1;
		    break;
		}
		// ������ 5 ���� �������
		if (ReadAnyData(buf, 5) == true) {
		    res = 0;
		} else {
//		    res = -1;
		}

	    } while (0);
	    LeaveCriticalSection(&cs);
	    if (res < 0)
		break;

	    Sleep(SLEEP_MODEM_RX);
	    EnterCriticalSection(&cs);
	    do {
		// �������� ����� ������
		res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
		if (res == false) {
		    res = -1;
		    break;
		}
		// ������� �����
		res = -1;
		if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		    if (strstr((char*)buf, "$AGATZ")!= NULL) {
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buf + 1, buf[0]);
			PrintModemCmd(temp, 1);
			ms->time_for_release = am3_get_time_for_release(temp);
			frmMain->ShowTimeForRelease(ms->time_for_release);
			res = 0;
		    }
		}
	    } while (0);
	    LeaveCriticalSection(&cs);
	} while (0);
    }
    if (res < 0)
	LogOutStr("GetTimeForRelease: Error");
    return res;
}

//---------------------------------------------------------------------------
// �������� ������� ��������
// ������� ���� � ��� ������
int GetBurnLen(void *par)
{
    int num;
    u8 buf[512];
    u8 temp[128];
    int res;
    char *str = "$RGABT,,*1cd6\r\n";	// ����� �� ������� (���)

    MODEM_STRUCT *ms;

    // �������� ��������
    if (par != NULL) {
	ms = (MODEM_STRUCT *) par;
	ms->burn_len = -1;	// ���� ����� �� ������

	do {
	    EnterCriticalSection(&cs);
	    do {
		//������ ������� �������� ����� ������
		res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
		PrintModemCmd(str);
		if (res == false) {
		    res = -1;
		    break;
		}
		// ������ 5 ���� �������
		if (ReadAnyData(buf, 5) == true) {
		    res = 0;
		} else {
//		    res = -1;
		}

	    } while (0);
	    LeaveCriticalSection(&cs);
	    if (res < 0)
		break;

	    Sleep(SLEEP_MODEM_RX);
	    EnterCriticalSection(&cs);
	    do {
		// �������� ����� ������
		res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
		if (res == false) {
		    res = -1;
		    break;
		}
		// ������� �����
		res = -1;
		if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		    if (strstr((char*)buf, "$AGABT")!= NULL) {
			memset(temp, 0, sizeof(temp));
			memcpy(temp, buf + 1, buf[0]);
			PrintModemCmd(temp, 1);
			ms->burn_len = am3_get_burn_len(temp);
			frmMain->ShowBurnLen(ms->burn_len);
			res = 0;
		    }
		}
	    } while (0);
	    LeaveCriticalSection(&cs);
	} while (0);
    }
    if (res < 0)
	LogOutStr("GetBurnLen: Error");
    return res;
}

//---------------------------------------------------------------------------
// �������� ����� ������
// ������� ���� � ��� ������
int SetModemNumber(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;
    MODEM_STRUCT *ms;
    u16 num;

    if (par == NULL)
	return -1;

    ms = (MODEM_STRUCT *) par;
    num = ms->modem_num;	// ����� ������

    // �������� ��������
    snprintf(str, sizeof(str), "$RSANM,%04d,*%04x\r\n", num, 0);
    crc16 = check_crc16((u8 *) str + 1, 11);	// ���������� ����������� ����� �� ���������
    snprintf(str, sizeof(str), "$RSANM,%04d,*%04x\r\n", num, crc16);	// ������� � ����������� ������

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ ������� �������� ����� ������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;

	Sleep(SLEEP_MODEM_RX);
	res = -1;
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����: $ASANM,,00*XXXX\r\n
	    res = -1;
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
		PrintModemCmd(str, 1);
		if (strncmp(str, "$ASANM,,00", 10) == 0) {	// ��� �������� ������
		    frmMain->ShowModemNum(num);
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("SetModemNum: Error");
    return res;
}

//---------------------------------------------------------------------------
// ����������� ����� ���������
// ������� ���� � ��� ������
int SetCalTime(void *n)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;
    MODEM_STRUCT *modem;

    if (n == NULL)
	return -1;

    modem = (MODEM_STRUCT *) n;

    // �������� ��������
    snprintf(str, sizeof(str), "$RSAST,%02d:%02d-%02d:%02d,*%04x\r\n", modem->am3_h0_time, modem->am3_m0_time, modem->am3_h1_time, modem->am3_m1_time, 0);
    crc16 = check_crc16((u8 *) str + 1, 18);
    snprintf(str, sizeof(str), "$RSAST,%02d:%02d-%02d:%02d,*%04x\r\n", modem->am3_h0_time, modem->am3_m0_time, modem->am3_h1_time, modem->am3_m1_time, crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ ������� �������� ����� ������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;

	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);
		if (strncmp(str, "$ASAST,,00", 10) == 0) {	// ��� �������� ������
		    frmMain->ShowCalTime(modem->am3_h0_time, modem->am3_m0_time, modem->am3_h1_time, modem->am3_m1_time);
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("SetCalTime: Error");
    return res;
}

//---------------------------------------------------------------------------
// ����� �� ��������
// ������� ���� � ��� ������
int SetTimeForRelease(void *n)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;
    MODEM_STRUCT *modem;


    if (n == NULL)
	return -1;

    modem = (MODEM_STRUCT *) n;

    // �������� ��������
    snprintf(str, sizeof(str), "$RSATZ,%03d,*%04x\r\n", modem->time_for_release, 0);
    crc16 = check_crc16((u8 *) str + 1, 10);
    snprintf(str, sizeof(str), "$RSATZ,%03d,*%04x\r\n", modem->time_for_release, crc16);


    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����: $ASATZ,,00*XXXX\r\n
	    res = -1;
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);
		if (strncmp(str, "$ASATZ,,00", 10) == 0) {	// ��� �������� ������
		    frmMain->ShowTimeForRelease(modem->time_for_release);
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("SetTimeForRelease: Error");
    return res;
}

//---------------------------------------------------------------------------
// ����� ��������
// ������� ���� � ��� ������
int SetBurnLen(void *n)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;
    MODEM_STRUCT *modem;


    if (n == NULL)
	return -1;

    modem = (MODEM_STRUCT *) n;

    // �������� ��������
    snprintf(str, sizeof(str), "$RSABT,%04d,*%04x\r\n", modem->burn_len, 0);
    crc16 = check_crc16((u8 *) str + 1, 11);
    snprintf(str, sizeof(str), "$RSABT,%04d,*%04x\r\n", modem->burn_len, crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ ������� �������� ����� ������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;

	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����: $ASABT,,00*XXXX\r\n
	    res = -1;
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);
		if (strncmp(str, "$ASABT,,00", 10) == 0) {	// ��� �������� ������
		    frmMain->ShowBurnLen(modem->burn_len);
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("SetBurnLen: Error");
    return res;
}

//---------------------------------------------------------------------------
// ����� ������ ���������
// ������� ���� � ��� ������
int SetModemTime(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;
    MODEM_STRUCT *ms;

    if (par == NULL)
	return -1;

    ms = (MODEM_STRUCT *) par;

    // ����� RTC ������ �� ���v� UNIX
    snprintf(str, sizeof(str), "$RSACL,%02d.%02d.%02d,%02d:%02d,*%04x\r\n", ms->modem_time.wDay, ms->modem_time.wMonth,
	     ms->modem_time.wYear - 2000, ms->modem_time.wHour, ms->modem_time.wMinute, 0);
    crc16 = check_crc16((u8 *) str + 1, 21);	// ���������� ����������� ����� �� ���������
    snprintf(str, sizeof(str), "$RSACL,%02d.%02d.%02d,%02d:%02d,*%04x\r\n", ms->modem_time.wDay, ms->modem_time.wMonth,
	     ms->modem_time.wYear - 2000, ms->modem_time.wHour, ms->modem_time.wMinute, crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ ������� ����� ������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);
		if (strncmp(str, "$ASACL,,00", 10) == 0) {	// ��� �������� ������
		    frmMain->ShowModemTime(&ms->modem_time);
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("SetModemTime: Error");
    return res;
}

//---------------------------------------------------------------------------
// ����� ������ ���������
// ������� ���� � ��� ������
int SetAlarmTime(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;
    MODEM_STRUCT *ms;

    if (par == NULL)
	return -1;

    ms = (MODEM_STRUCT *) par;

    // ����� Alarm �� ���v� UNIX
    snprintf(str, sizeof(str), "$RSAAL,%02d.%02d.%02d,%02d:%02d,*%04x\r\n", ms->alarm_time.wDay, ms->alarm_time.wMonth,
	     ms->alarm_time.wYear - 2000, ms->alarm_time.wHour, ms->alarm_time.wMinute, 0);
    crc16 = check_crc16((u8 *) str + 1, 21);	// ��� 2
    snprintf(str, sizeof(str), "$RSAAL,%02d.%02d.%02d,%02d:%02d,*%04x\r\n", ms->alarm_time.wDay, ms->alarm_time.wMonth,
	     ms->alarm_time.wYear - 2000, ms->alarm_time.wHour, ms->alarm_time.wMinute, crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ ������� ����� ������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);
		if (strncmp(str, "$ASAAL,,00", 10) == 0) {	// ��� �������� ������
		    frmMain->ShowAlarmTime(&ms->alarm_time);
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("SetModemTime: Error");
    return res;
}

//---------------------------------------------------------------------------
// �������� �����
int RadioOn(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;

    if (par == NULL)
	return -1;

    // �������� �����
    snprintf(str, sizeof(str), "$RSAGR,1,*%04x\r\n");
    crc16 = check_crc16((u8 *) str + 1, 8);	// ��� 2
    snprintf(str, sizeof(str), "$RSAGR,1,*%04x\r\n", crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
            memset(buf, 0, 250);
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);

              //vvvvv:
		if (strncmp(str, "$ASAGR,,00", 8) == 0) {	// ��� �������� ������
		    frmMain->ltRadioOnOff->State = true;
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("Radio ON: Error");
    return res;
}
//---------------------------------------------------------------------------
// ��������� �����
int RadioOff(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;

    if (par == NULL)
	return -1;

    // ��������� �����
    snprintf(str, sizeof(str), "$RSAGR,0,*%04x\r\n");
    crc16 = check_crc16((u8 *) str + 1, 8);	// ��� 2
    snprintf(str, sizeof(str), "$RSAGR,0,*%04x\r\n", crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
 //		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
            memset(buf, 0, 250);
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);

              //vvvvv:
		if (strncmp(str, "$ASAGR,,00", 8) == 0) {	// ��� �������� ������
		    frmMain->ltRadioOnOff->State = true;
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("Radio OFF: Error");
    return res;
}

//---------------------------------------------------------------------------
// ������� ����� ������� � �����
// ������� ���� � ��� ������
int SendAnyCommand(char *n)
{
    c8 buf[512];
    char str[128];
    char str2[8];
    int i;
    int res;
    u16 crc16;

    if (n == NULL)
	return -1;

    if (n[0] != '$') {
	LogOutStr("������������ �������!");
	return -1;
    }
    // ��� ������� ������������ *
    // ������ ������ *
    for (i = 0; i < strlen(n); i++) {
	if (n[i] == '*')
	    break;		// ����� �����
    }
    if (i > 100)
	return -1;

    memcpy(str, n, i + 1);
    crc16 = check_crc16((u8 *) str + 1, i - 1);	// ��� 1
    sprintf(str2, "%04x\r\n", crc16);

    memcpy(buf, str, i + 1);
    memcpy(buf + i + 1, str2, 6);
    buf[i + 1 + 6] = 0;

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, buf, strlen(buf));
	    PrintModemCmd(buf);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;

	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
            memset(buf, 0, 250);
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);
		res = 0;
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("Send Any Command: Error");
    return res;
}

//---------------------------------------------------------------------------
// �������� �����
int LampOn(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;

    if (par == NULL)
	return -1;

    // �������� �����
    snprintf(str, sizeof(str), "$RSALP,1,*%04x\r\n");
    crc16 = check_crc16((u8 *) str + 1, 8);	// ��� 2
    snprintf(str, sizeof(str), "$RSALP,1,*%04x\r\n", crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
            memset(buf, 0, 250);
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);

              //vvvvv:
		if (strncmp(str, "$ASALP,,00", 8) == 0) {	// ��� �������� ������
		    frmMain->ltLampOnOff->State = true;
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("Lamp ON: Error");
    return res;
}
//---------------------------------------------------------------------------
// ��������� �����
int LampOff(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;

    if (par == NULL)
	return -1;

    // ��������� �����
    snprintf(str, sizeof(str), "$RSALP,0,*%04x\r\n");
    crc16 = check_crc16((u8 *) str + 1, 8);	// ��� 2
    snprintf(str, sizeof(str), "$RSALP,0,*%04x\r\n", crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
            memset(buf, 0, 250);
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);

              //vvvvv:
		if (strncmp(str, "$ASALP,,00", 8) == 0) {	// ��� �������� ������
		    frmMain->ltLampOnOff->State = true;
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("Radio OFF: Error");
    return res;
}
//---------------------------------------------------------------------------
// �������� ������
int BurnCmdOn(void *par)
{
    u8 buf[512];
    char str[128];
    int res, i = 5;
    u16 crc16;

    if (par == NULL)
	return -1;

    // �������� �����
    snprintf(str, sizeof(str), "$RSABR,1,*%04x\r\n");
    crc16 = check_crc16((u8 *) str + 1, 8);	// ��� 2
    snprintf(str, sizeof(str), "$RSABR,1,*%04x\r\n", crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
            memset(buf, 0, 250);
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);

		if (strncmp(str, "$ASABR,,00", 8) == 0) {	// ��� �������� ������
		    frmMain->ltBurnCmdOnOff->State = true;
		    res = 0;
		}
	    }
	} while (0);

	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("Burn CMD ON: Error");
    return res;
}
//---------------------------------------------------------------------------
// ��������� ������
int BurnCmdOff(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    u16 crc16;

    if (par == NULL)
	return -1;

    // ��������� �����
    snprintf(str, sizeof(str), "$RSABR,0,*%04x\r\n");
    crc16 = check_crc16((u8 *) str + 1, 8);	// ��� 2
    snprintf(str, sizeof(str), "$RSABR,0,*%04x\r\n", crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
            memset(buf, 0, 250);
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);

              //vvvvv:
		if (strncmp(str, "$ASABR,,00", 8) == 0) {	// ��� �������� ������
		    frmMain->ltBurnCmdOnOff->State = true;
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("Burn OFF: Error");
    return res;
}
//---------------------------------------------------------------------------
// ������� ����
int SendPing11(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    int num;
    u16 crc16;

    if (par == NULL)
	return -1;

    num = *(int*)par;

    // �������� �����
    snprintf(str, sizeof(str), "$RSADT,0-%03d,*%04x\r\n", num);
    crc16 = check_crc16((u8 *) str + 1, 12);	// ��� 2
    snprintf(str, sizeof(str), "$RSADT,0-%03d,*%04x\r\n",num, crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
  //		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
            memset(buf, 0, 250);
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);

              //vvvvv:
		if (strncmp(str, "$ASADT,,00", 10) == 0) {	// ��� �������� ������
		    frmMain->ltPing->State = true;
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("Send PING 11.5 kHz: Error");
    return res;
}
//---------------------------------------------------------------------------
// ������� ����  13
int SendPing13(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    int num;
    u16 crc16;

    if (par == NULL)
	return -1;

    num = *(int*)par;

    // �������� �����
    snprintf(str, sizeof(str), "$RSADT,1-%03d,*%04x\r\n", num);
    crc16 = check_crc16((u8 *) str + 1, 12);	// ��� 2
    snprintf(str, sizeof(str), "$RSADT,1-%03d,*%04x\r\n",num, crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
//		res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)
	    break;


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
            memset(buf, 0, 250);
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);

              //vvvvv:
		if (strncmp(str, "$ASADT,,00", 10) == 0) {	// ��� �������� ������
		    frmMain->ltPing->State = true;
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("Send PING 13 kHz: Error");
    return res;
}
//---------------------------------------------------------------------------
// ������� ����  9
int SendPing9(void *par)
{
    u8 buf[512];
    char str[128];
    int res;
    int num;
    u16 crc16;

    if (par == NULL)
	return -1;

    num = *(int*)par;

    // �������� �����
    snprintf(str, sizeof(str), "$RSADT,2-%03d,*%04x\r\n", num);
    crc16 = check_crc16((u8 *) str + 1, 12);	// ��� 2
    snprintf(str, sizeof(str), "$RSADT,2-%03d,*%04x\r\n",num, crc16);

    do {
	EnterCriticalSection(&cs);
	do {
	    //������ �������
	    res = SendSomeCommand(UART_CMD_MODEM_REQUEST, str, strlen(str));
	    PrintModemCmd(str);
	    if (res == false) {
		res = -1;
		break;
	    }
            
	    // ������ 5 ���� �������
	    if (ReadAnyData(buf, 5) == true) {
		res = 0;
	    } else {
		//res = -1;
	    }

	} while (0);
	LeaveCriticalSection(&cs);
	if (res < 0)  {
	    break;
           }


	Sleep(SLEEP_MODEM_RX);
	EnterCriticalSection(&cs);
	do {
	    // �������� ����� ������
	    res = SendSomeCommand(UART_CMD_GET_MODEM_REPLY, NULL, 0);
	    if (res == false) {
		res = -1;
		break;
	    }
	    // ������� �����
	    res = -1;
            memset(buf, 0, 250);
	    if (ReadAnyDataToTimeout(buf, SLEEP_MODEM_TIMEOUT) == true) {
		memset(str, 0, sizeof(str));
		memcpy(str, buf + 1, buf[0]);
        	PrintModemCmd(str, 1);

              //vvvvv:
		if (strncmp(str, "$ASADT,,00", 10) == 0) {	// ��� �������� ������
		    frmMain->ltPing->State = true;
		    res = 0;
		}
	    }
	} while (0);
	LeaveCriticalSection(&cs);
    } while (0);
    if (res < 0)
	LogOutStr("Send PING 9 kHz: Error");
    return res;
}
//---------------------------------------------------------------------------------
