#ifndef _Matrix_Keypad_h
#define _Matrix_Keypad_h


/************************************************************************/
/* Key Definitions                                                      */
/************************************************************************/
//Hardware
#define	ROW1	PB10
#define	ROW2	PB11
#define	ROW3	PB12
#define	COL1	PB13
#define	COL2	PB14

//Bit variables
bool	ParaKey;
bool	RunKey;
bool	StartKey;
bool	StopKey;
bool	UpdateKey;
bool	StoreKey;

//Alternate names
#define EnterKey	StoreKey
#define IncrKey		StartKey
#define DecrKey		StopKey
//////////////////////////////////////////////////////////////////////////
#define debounce_ms 20		//milliseconds to wait between two scan to confirm key press and debounce keys.

void ClearKeys(void);
bool KeyDetected(void);
void Keyconfig(void);
void Keyscan(void);


#endif