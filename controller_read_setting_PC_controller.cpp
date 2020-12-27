#include "controller_read_setting_PC_controller.h"

void controller_read_setting_PC_controller::init(void)
{
	this->myModel_setting_PC_controller = model_setting_PC_controller::getInstance();
}

// ++++++++++++++++ K1_GET
QString controller_read_setting_PC_controller::k1_string_get(void)
{
	return QString::number(this->myModel_setting_PC_controller->k1_get());
}

double controller_read_setting_PC_controller::k1_get(void)
{
	return this->myModel_setting_PC_controller->k1_get();
}
// ++++++++++++++++ K2_GET
QString controller_read_setting_PC_controller::k2_string_get(void)
{
	return QString::number(this->myModel_setting_PC_controller->k2_get());
}

double controller_read_setting_PC_controller::k2_get(void)
{
	return this->myModel_setting_PC_controller->k2_get();
}
// ++++++++++++++++ A1_GET
QString controller_read_setting_PC_controller::a1_string_get(void)
{
	return QString::number(this->myModel_setting_PC_controller->a1_get());
}

double controller_read_setting_PC_controller::a1_get(void)
{
	return this->myModel_setting_PC_controller->a1_get();
}
// ++++++++++++++++ A2_GET
QString controller_read_setting_PC_controller::a2_string_get(void)
{
	return QString::number(this->myModel_setting_PC_controller->a2_get());
}

double controller_read_setting_PC_controller::a2_get(void)
{
	return this->myModel_setting_PC_controller->a2_get();
}
// ++++++++++++++++ B1_GET
QString controller_read_setting_PC_controller::b1_string_get(void)
{
	return QString::number(this->myModel_setting_PC_controller->b1_get());
}

double controller_read_setting_PC_controller::b1_get(void)
{
	return this->myModel_setting_PC_controller->b1_get();
}
// ++++++++++++++++ B2_GET
QString controller_read_setting_PC_controller::b2_string_get(void)
{
	return QString::number(this->myModel_setting_PC_controller->b2_get());
}

double controller_read_setting_PC_controller::b2_get(void)
{
	return this->myModel_setting_PC_controller->b2_get();
}
// ++++++++++++++++ B3_GET
QString controller_read_setting_PC_controller::b3_string_get(void)
{
	return QString::number(this->myModel_setting_PC_controller->b3_get());
}

double controller_read_setting_PC_controller::b3_get(void)
{
	return this->myModel_setting_PC_controller->b3_get();
}
// ++++++++++++++++ TYPE_GET
QString controller_read_setting_PC_controller::controller_type_string_get(void)
{
	return this->myModel_setting_PC_controller->controller_type_string_get();
}

bool controller_read_setting_PC_controller::controller_type_get(void)
{
		return this->myModel_setting_PC_controller->controller_type_get();
}

controller_read_setting_PC_controller::controller_read_setting_PC_controller()
{
}
