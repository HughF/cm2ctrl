
//starting phases
#define STR_SP_ENERGIZING 1
#define STR_SP_CONNECTING 2
#define STR_SP_RUNNING 3
#define STR_SP_FAILED 4
#define STR_SP_TIMEOUT 5
#define STR_SP_READY 6


//towfish range frequency codes
#define RFC_12EF 0
#define RFC_25EF 1
#define RFC_25HF 2
#define RFC_50HF 3
#define RFC_75HF 4
#define RFC_100HF 5
#define RFC_150HF 6
#define RFC_100LF 7
#define RFC_150LF 12
#define RFC_200LF 8
#define RFC_300LF 9
#define RFC_400LF 10
#define RFC_500LF 11
#define RFC_37EF 13
#define RFC_50EF 14
#define RFC_200HF 15

//towfish variant codes
#define TFV_EF 0
#define TFV_EDF 1
#define TFV_HF 2
#define TFV_HF2 3
#define TFV_DF 4
#define TFV_LF 5

//custom message values
#define STM_NEWDATA 0
#define STM_FISHSTOPPED 1
#define STM_OVERFLOW 2

//towfish status flags
#define TFS_GAINHOLD	0x1
#define TFS_MUTED		0x2
#define TFS_MAXALT		0x4
#define TFS_SHALLOW		0x8
#define TFS_LOWPOWER	0x10
#define TFS_ISDEPTH		0x20
#define TFS_DEPTHIS1K	0x40

//start dialog return values
#define SFD_RUNNING 0
#define SFD_ABORTED 1
#define SFD_TIMEOUT 2
#define SFD_FAILED 3

//force altitude values
#define FORCE_DOWN -1
#define FORCE_UP 1

//gain adjust values
#define GAIN_DOWN -1
#define GAIN_UP 1

//getechodata formats
#define FMT_BY_TIME 1
#define FMT_BY_POSITION 2

//counters
#define STC_RXCOUNT 1
#define STC_TXCOUNT 2
#define STC_ERRORS  3
#define STC_PINGS	4

//RF code masks
#define RM_EF 0x2003
#define RM_HF 0x007c
#define RM_LF 0x1F80

//structs
struct PINGHEAD
{
	int iRangeFreq;
	DWORD dwTotalSamples;
	float dAltitude;
	int iFishType;
	int iVersionMajor;
	int iVersionMinor;
	int iGain;
	int iHeading;
	int iDepth;
	int iTemperature;
};


struct STRPING
{
	PINGHEAD ph;
	SYSTEMTIME st;
	unsigned char cEcho[12800];
};

#define SONAD sizeof(PINGHEAD)+sizeof(SYSTEMTIME)


//exported functions
extern "C"
{
	__declspec(dllexport) int CALLBACK STRSetSimulation(bool fSimulate, int iVariant, bool fTick);

	//STR functions
	__declspec(dllexport) int CALLBACK STRIsSTRConnected();
	__declspec(dllexport) int CALLBACK STRGetSTRVersion(char* lpcVer, int cchMax);

	//towfish power functions
	__declspec(dllexport) int CALLBACK STRStartTowfish(int iTimeOut);
	__declspec(dllexport) int CALLBACK STRStopTowfish();
	__declspec(dllexport) int CALLBACK STRGetStartPhase();

	//towfish control functions
	__declspec(dllexport) int CALLBACK STRSelectRange(int iRFCode, bool fChange);
	__declspec(dllexport) int CALLBACK STRMuteTowfish(bool fMute);
	__declspec(dllexport) int CALLBACK STRSetShallowMode(bool fShallow);
	__declspec(dllexport) int CALLBACK STRForceAltitude(int iForceAlt);
	__declspec(dllexport) int CALLBACK STRSetGainHold(bool fGainHold);
	__declspec(dllexport) int CALLBACK STRSetTestMode();
	__declspec(dllexport) int CALLBACK STRAdjustGain(int iAdjGain);
	__declspec(dllexport) int CALLBACK STRCycleTestMode();
	__declspec(dllexport) int CALLBACK STRCancelTestMode();

	//towfish status functions
	__declspec(dllexport) int CALLBACK STRGetTelemetry(PINGHEAD* lpph);
	__declspec(dllexport) int CALLBACK STRSetMessage(HWND hwnd, DWORD dwSTRMsg);
	__declspec(dllexport) int CALLBACK STRGetStatus(int* lpiStatus);

	//towfish data functions
	__declspec(dllexport) int CALLBACK STRGetQueueSize(bool fFlush);
	__declspec(dllexport) int CALLBACK STRGetEchoData(STRPING* lpstrp, int iFormat);
	__declspec(dllexport) int CALLBACK STRGetMagString(char* lpcMag, int cchMax);

	//diagnostic functions
	__declspec(dllexport) int CALLBACK STRGetCounter(int iCounter);
	__declspec(dllexport) int CALLBACK STRCalibCompass();

	//STR dialogs
	__declspec(dllexport) int CALLBACK CM2StartTowfishDlg(HWND hWnd, char* szTitle,bool fCentre);
	__declspec(dllexport) int CALLBACK CM2PickRangeDlg(HWND hWnd, char* szTitle,
														int iFishType, int iFishRange,
														bool fCentre);
}
