#include "threadSimulatorController.h"

//---------------------------------------------------------------------------------------------------
// Select here in which Mode to operate both the GUI and the Board:
//---------------------------------------------------------------------------------------------------
// HILS = 0, In this mode, we are not doing Hardware in the loop, the PC simulator runs on its own
// HILS = 1 if you want to do Hardware in the loop,
// In this mode, we want that the PC sends the Board sensor data
// The board should reply with motor commands, which are treated by the PC simulator and displayed in the 3D animation ...
// HILS = 2: In this mode, the 3D GUI is only used to display the real angle of the balancing arm
// HILS = 3: In this mode, we want the board to send the true angle values and the PC computes the control law and send to the board the
// force that should be generated to control the arm.

//-----------------------------------------
// init
//-----------------------------------------
void threadSimulatorController::init(void)
{
	e_k = 0;
	e_k_1 = 0;
	e_k_2 = 0;
	theta_dotdot_desired_k_1 = 0;
	theta_dotdot_desired_k_2 = 0;
}
//-----------------------------------------------------------------
// hils_mode_update
//-----------------------------------------------------------------
void threadSimulatorController::hils_mode_update(int new_hils_mode)
{
	switch(new_hils_mode)
	{
		case HILS_MODE_PC_CONTROLLER:
			this->ptr_hils_modes_function = &threadSimulatorController::hils_mode_pc_controller_function;
			break;
		case HILS_MODE_1_:
			this->ptr_hils_modes_function = &threadSimulatorController::hils_mode_1_function;
			break;
		case HILS_MODE_REAL_ANGLE:
			this->ptr_hils_modes_function = &threadSimulatorController::hils_mode_real_angle_function;
			break;
		case HILS_MODE_3_:
			this->ptr_hils_modes_function = &threadSimulatorController::hils_mode_3_function;
			break;
		case HILS_MODE_MANUAL_THRUST_COMMAND:
			this->ptr_hils_modes_function = &threadSimulatorController::hils_mode_manual_thrust_command_function;
			break;
		default:
			break;
	}
}
//
// hils_mode_execute
//
void threadSimulatorController::hils_mode_execute(void)
{
	(this->*ptr_hils_modes_function)();
}
//
// runSimulator
//
void threadSimulatorController::runSimulator(void)
{
this->myArmPropSimulator->Run(this->myController_read_setting_sample_time->sample_time_controller_get(), this->myArmPropController->GetThrustCmd());
}
//
// runController
//
void threadSimulatorController::runController(void)
{
	// code de Guillaume
	// this->myArmPropController->RunArmController(this->myArmPropSimulator->GetTheta(), this->myArmPropSimulator->GetThetaDot());
	// code de ses élèves
	this->myArmPropController->RunArmController();
}
//
// hils_mode_pc_controller_function
//
void threadSimulatorController::hils_mode_pc_controller_function(void)
{
	// controller type: "CASCADE_CONTROLLER"
	if(this->myController_read_setting_PC_controller->controller_type_get() == CASCADE_CONTROLLER)
	{
		this->myArmPropController->SetThetaDotdotCmd((((this->myArmPropController->GetThetaCmd() - this->myArmPropSimulator->GetTheta()) * this->myController_read_setting_PC_controller->k1_get()) - this->myArmPropSimulator->GetThetaDot()) * this->myController_read_setting_PC_controller->k2_get());
	}

	// controller type: "LEADLAG_CONTROLLER"
	else
	{
		this->e_k = this->myArmPropController->GetThetaCmd() - this->myArmPropSimulator->GetTheta();
		this->myArmPropController->SetThetaDotdotCmd(
			(this->myController_read_setting_PC_controller->a1_get() * this->theta_dotdot_desired_k_1) +
			(this->myController_read_setting_PC_controller->a2_get() * this->theta_dotdot_desired_k_2) +
			(this->myController_read_setting_PC_controller->b1_get() * e_k) +
			(this->myController_read_setting_PC_controller->b2_get() * this->e_k_1) +
			(this->myController_read_setting_PC_controller->b3_get() * this->e_k_2)
			);
		this->theta_dotdot_desired_k_2 = this->theta_dotdot_desired_k_1;
		this->theta_dotdot_desired_k_1 = this->myArmPropController->GetThetaDotdotCmd();
		this->e_k_2 = this->e_k_1;
		this->e_k_1 = this->e_k;
	}
}

int threadSimulatorController::convertAngleDegtoADCvalue(double angleinRad)
{
	double angleinDeg = angleinRad * (180/3.14);
	int ADCvalue = 0;
	if ( (0.0 < angleinDeg) &&  (angleinDeg < 105.0))
	{
		ADCvalue = int((angleinDeg + 41.9883)/1.1851 );
	}

	if(angleinDeg > 105.0)
	{
		ADCvalue = int(( angleinDeg - 95.381)/0.1184 );
	}
	return ADCvalue;
}

//
// hils_mode_1_function: see function void hilsModeSerialCommunicator::run(void)
//
void threadSimulatorController::hils_mode_1_function(void)
{	// 18.02.2015
	//GD: in this mode, we wish the Microcontroller to generate motor commands and send it to PC, whereas the PC simulates and returns the angle.
	int PicMotorCmd = this->myHilsModeSerialCommunicator->GetCommunicator()->getLastDebugDataAnalog(0);
	// TODO: use instead getLastDebugDataAnalog(0):  motorCommandsHILS
	if (PicMotorCmd>1023)
	{
		PicMotorCmd = 1023;
	}
	if (PicMotorCmd<0)
	{
		PicMotorCmd = 0;
	}
	this->myHilsModeSerialCommunicator->setSignal(PicMotorCmd);
	double PicThrustCmd = PicMotorCmd/128.0; // in Newton //TODO : /100.0
	this->myArmPropController->SetThrustCmd(PicThrustCmd);
	this->myArmPropSimulator->Run(this->myController_read_setting_sample_time->sample_time_controller_get(),this->myArmPropController->GetThrustCmd());

	double theta_rad = this->myArmPropSimulator->GetTheta();
	double thetadot_rads = this->myArmPropSimulator->GetThetaDot();

	//converts into a integer number ADC equivalent for the uC
	int ADC_theta = this->convertAngleDegtoADCvalue(theta_rad);
	// converts the angular rate [rad/s] into a integer number that the uC can understand
	//int Thetadot_toPic = thetadot_rads * 128;
	// Fills up the HILSSensorData structure and sends it off: 1st arg: angle, 2nd arg: angle rate
	//this->myHilsModeSerialCommunicator->GetCommunicator()->setHILSSensorData(ADC_theta, Thetadot_toPic);

	//this->myHilsModeSerialCommunicator->GetCommunicator()->setHILSSensorData((int)(theta_rad*128.0), (int)(thetadot_rads *128.0));
	this->myHilsModeSerialCommunicator->GetCommunicator()->setHILSSensorData(int(theta_rad*128.0), int(thetadot_rads *128.0), ADC_theta);

}
//
// hils_mode_pc_controller_function
//
void threadSimulatorController::hils_mode_real_angle_function(void)
{
	double ADC_value = double(this->myHilsModeSerialCommunicator->GetCommunicator()->getLastDebugDataAnalog(0));
	this->myHilsModeSerialCommunicator->setSignal(int(ADC_value));
	double arm_real_angle_deg =0.0;

	if (ADC_value<36)
	{
		arm_real_angle_deg = 0.0;
	}

	if (ADC_value<=125)
	{
		arm_real_angle_deg = 1.1851 * ADC_value -41.9883;
	}

	if (ADC_value>125)
	{
		arm_real_angle_deg = 0.1184 * ADC_value + 95.381;
	}

	double real_angle_rad = arm_real_angle_deg *MY_PI/180.0; //- MY_PI/2.0;
	this->myArmPropSimulator->SetTheta(real_angle_rad);
}
//
// hils_mode_3_function
//
void threadSimulatorController::hils_mode_3_function(void)
{
}
//
// hils_mode_manual_thrust_command_function
//
void threadSimulatorController::hils_mode_manual_thrust_command_function(void)
{
this->myArmPropSimulator->Run(this->myController_read_setting_sample_time->sample_time_controller_get(),this->myArmPropController->GetThrustCmd());
}

threadSimulatorController::threadSimulatorController(void)
{
	this->myArmPropSimulator = ArmPropSimulator::getInstance();
	this->myArmPropController = ArmPropController::getInstance();
	this->myHilsModeSerialCommunicator = hilsModeSerialCommunicator::getInstance();
	this->myController_read_setting_sample_time = controller_read_setting_sample_time::getInstance();
	this->myController_read_setting_PC_controller = controller_read_setting_PC_controller::getInstance();
}

//
// ~threadSimulatorController
//
threadSimulatorController::~threadSimulatorController(void)
{
}
