#include "test_controller_write_setting_PC_controller.h"

test_controller_write_setting_PC_controller::test_controller_write_setting_PC_controller(void)
{
	this->myController_write_setting_PC_controller = controller_write_setting_PC_controller::getInstance();
}

test_controller_write_setting_PC_controller::~test_controller_write_setting_PC_controller(void)
{
}

void test_controller_write_setting_PC_controller::test_classe(void)
{
	qDebug() << "controller_type_set";
	this->myController_write_setting_PC_controller->controller_type_set(false);
	qDebug() << "k1_set";
	this->myController_write_setting_PC_controller->k1_set("4.15");
	qDebug() << "k2_set";
	this->myController_write_setting_PC_controller->k2_set("8.30");
	qDebug() << "a1_set";
	this->myController_write_setting_PC_controller->a1_set("10");
	qDebug() << "a2_set";
	this->myController_write_setting_PC_controller->a2_set("AAAA");
	qDebug() << "b1_set";
	this->myController_write_setting_PC_controller->b1_set("5.2222");
	qDebug() << "b2_set";
	this->myController_write_setting_PC_controller->b2_set("-4.8788");
	qDebug() << "b3_set";
	this->myController_write_setting_PC_controller->b3_set("48");
//	this->my_model_setting_sample_time->step_set("2");
//	this->my_model_setting_sample_time->simulator_step_set("2");
//	this->my_model_setting_sample_time->controller_step_set("10");
//	this->my_model_setting_sample_time->graph_step_set("2");
//	this->myTime->time_desired_set("4");
}
