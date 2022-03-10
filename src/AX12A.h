#ifndef DYNAMIXELSERIAL_H
#define DYNAMIXELSERIAL_H

#include <HardwareSerial.h>

#define MAX_READ_PARAMS_NUMBER 4

class DynamixelSerial{
public:

	enum RotationDirection{
		Counterclockwise = 0,
		Clockwise = 1
	};

	DynamixelSerial();

	void init(HardwareSerial* sd);

	int reset(unsigned char ID);
	int ping(unsigned char ID);

	int setID(unsigned char ID, unsigned char newID);
	int setBD(unsigned char ID, long baud);

	int move(unsigned char ID, int position);
	int moveSpeed(unsigned char ID, int position, int speed);
	int setEndless(unsigned char ID, bool status);
	int turn(unsigned char ID, RotationDirection direction, int speed);
	int moveRW(unsigned char ID, int position);
	int moveSpeedRW(unsigned char ID, int position, int speed);

	void action(void);

	int setTempLimit(unsigned char ID, unsigned char temperature);
	int setAngleLimit(unsigned char ID, int CWLimit, int CCWLimit);
	int setVoltageLimit(unsigned char ID, unsigned char DVoltage, unsigned char UVoltage);
	int setMaxTorque(unsigned char ID, int maxTorque);
	/*Should not be used with SRL != 2. This library expects the Dynamixels to return a status packet for each command*/
	int setSRL(unsigned char ID, unsigned char SRL);
	int setRDT(unsigned char ID, unsigned char RDT);
	int setLEDAlarm(unsigned char ID, unsigned char LEDAlarm);
	int setShutdownAlarm(unsigned char ID, unsigned char SALARM);
	int setCMargin(unsigned char ID, unsigned char CWCMargin, unsigned char CCWCMargin);
	int setCSlope(unsigned char ID, unsigned char CWCSlope, unsigned char CCWCSlope);
	int setPunch(unsigned char ID, int punch);

	int moving(unsigned char ID);
	int lockRegister(unsigned char ID);
	int RWStatus(unsigned char ID);

	int readTemperature(unsigned char ID);
	int readVoltage(unsigned char ID);
	int readPosition(unsigned char ID);
	int readSpeed(unsigned char ID);
	int readLoad(unsigned char ID);

	int torqueStatus(unsigned char ID, bool status);
	int ledStatus(unsigned char ID, bool status);

	int readResponse(uint8_t *params);

	uint8_t getError() const {
		return error_;
	}

protected:
	void enableOpenDrain(bool enable);
	int sendInstruction(unsigned char ID, unsigned char instruction, unsigned char* params, int paramsLength);

	uint8_t error_;

	enum eStatusReceiveState {
			RECEIVE_IDLE,			//wait for 0xFF
			RECEIVE_GOT_FF_1,		//wait for 0xFF
			RECEIVE_ID,
			RECEIVE_LENGHT,			//wait for lenght
			RECEIVE_ERROR,			//wait for error byte
			RECEIVE_PARAMS,			//wait for params
			RECEIVE_CHK				//wait for checksum
		};

	HardwareSerial* serial_;
//	eStatusReceiveState _receive_state;
//	int _nb_bytes_to_read;
//	size_t _nb_params;

// *********
	// The Dynamixel instructions
	enum eInstruction
	{
	    I_Ping      = 1,
	    I_ReadData  = 2,
	    I_WriteData = 3,
	    I_RegWrite  = 4,
	    I_Action    = 5,
	    I_Reset     = 6,
	    I_SyncWrite = 0x83,
	};

	// The Dynamixel registers
	enum eRegister
	{
	    // ---------- EEPROM ------------

	    R_ModelNumber             = 0x00, // 2 Byte
	    R_FirmwareVersion         = 0x02, //
	    R_ServoID                 = 0x03, //         Write
	    R_BaudRate                = 0x04, //         Write
	    R_ReturnDelayTime         = 0x05, //         Write
	    R_CW_AngleLimit           = 0x06, // 2 Byte  Write
	    R_CCW_AngleLimit          = 0x08, // 2 Byte  Write
	    R_HighestLimitTemperature = 0x0B, //         Write
	    R_LowestLimitVoltage      = 0x0C, //         Write
	    R_HighestLimitVoltage     = 0x0D, //         Write
	    R_MaxTorque               = 0x0E, // 2 Byte  Write
	    R_StatusReturnLevel       = 0x10, //         Write
	    R_AlarmLED                = 0x11, //         Write
	    R_AlarmShutdown           = 0x12, //         Write

	    // ----------- RAM -------------

	    R_TorqueEnable            = 0x18, //         Write
	    R_LED                     = 0x19, //         Write
	    R_CW_ComplianceMargin     = 0x1A, //         Write
	    R_CCW_ComplianceMargin    = 0x1B, //         Write
	    R_CW_ComplianceSlope      = 0x1C, //         Write
	    R_CCW_ComplianceSlope     = 0x1D, //         Write
	    R_GoalPosition            = 0x1E, // 2 Byte  Write
	    R_MovingSpeed             = 0x20, // 2 Byte  Write
	    R_TorqueLimit             = 0x22, // 2 Byte  Write
	    R_PresentPosition         = 0x24, // 2 Byte
	    R_PresentSpeed            = 0x26, // 2 Byte
	    R_PresentLoad             = 0x28, // 2 Byte
	    R_PresentVoltage          = 0x2A, //
	    R_PresentTemperature      = 0x2B, //
	    R_RegisteredInstruction   = 0x2C, //         Write
	    R_Moving                  = 0x2E, //
	    R_Lock                    = 0x2F, //         Write
	    R_Punch                   = 0x30, // 2 Byte  Write
	};

	// Dynamixel errors returned in Status packet
	enum eError
	{
	    E_InputVoltage   = 0x01,
	    E_AngleLimit     = 0x02,
	    E_Overheating    = 0x04,
	    E_ParameterRange = 0x08,
	    E_Checksum       = 0x10,
	    E_Overload       = 0x20,
	    E_Instruction    = 0x40,
	};


};
extern DynamixelSerial AX12As;
#endif /* DYNAMIXELSERIAL_H */