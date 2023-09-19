#ifndef HILSMODESERIALCOMMUNICATOR_H
#define HILSMODESERIALCOMMUNICATOR_H

#include "include_define.h"

#include "arm_prop_simulator.h"
#include "../../v0.2-ressources_communes/Hexa_PC_com/serialCommunicator.h"

class hilsModeSerialCommunicator
{
	public:
		static hilsModeSerialCommunicator* getInstance();

		void init(void);
		void run(void);
		void stop(void);

		SerialCommunicator* myCommunicator;

		// Some Get functions
		int getHilsMode(void);
		int getSignal(void);
		int getMessage(void);
		char* getMessage_serial_communicator(void);
		SerialCommunicator* GetCommunicator(void);

		// Some Set functions
		void setHilsMode(int);
		void SetCommunicator(SerialCommunicator*);
		void setSignal(int);

	private:
		hilsModeSerialCommunicator(void);
		~hilsModeSerialCommunicator(void);

		int hils_mode;
		int	signal;
		int message;

		ArmPropSimulator* myArmPropSimulator;
};

#endif
