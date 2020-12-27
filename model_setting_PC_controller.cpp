#include "model_setting_PC_controller.h"

// -------- PUBLIC --------
// ++++++++++++++++ A1_GET
void model_setting_PC_controller::init(void)
{
	this->controllers_types.append("cascade");
	this->controllers_types.append("leadlag");

	// cascade controller
	this->k1 = sqrt(2.0) * MY_PI;
	this->k2 = this->k1 * 2;

	// leadlag controller
	this->a1 = 1.0;
	this->a2 = 0.0;
	this->b1 = 5.83;
	this->b2 = -5.33;
	this->b3 = 0.0;
	this->controller_type_set(CASCADE_CONTROLLER);
}

// ++++++++++++++++ K1_GET
double model_setting_PC_controller::k1_get(void) const
{
	return this->k1;
}

// ++++++++++++++++ K1_SET
void model_setting_PC_controller::k1_set(const double k1_new)
{
	this->k1 = k1_new;
}

// ++++++++++++++++ K2_GET
double model_setting_PC_controller::k2_get(void) const
{
	return this->k2;
}

// ++++++++++++++++ K2_SET
void model_setting_PC_controller::k2_set(const double k2_new)
{
	this->k2 = k2_new;
}

// ++++++++++++++++ A1_GET
double model_setting_PC_controller::a1_get(void) const
{
	return this->a1;
}

// ++++++++++++++++ A1_SET
void model_setting_PC_controller::a1_set(const double a1_new)
{
	this->a1 = a1_new;
}

// ++++++++++++++++ A2_GET
double model_setting_PC_controller::a2_get(void) const
{
	return this->a2;
}

// ++++++++++++++++ A2_SET
void model_setting_PC_controller::a2_set(const double a2_new)
{
	this->a2 = a2_new;
}

// ++++++++++++++++ B1_GET
double model_setting_PC_controller::b1_get(void) const
{
	return this->b1;
}

// ++++++++++++++++ B1_SET
void model_setting_PC_controller::b1_set(const double b1_new)
{
	this->b1 = b1_new;
}

// ++++++++++++++++ B2_GET
double model_setting_PC_controller::b2_get(void) const
{
	return this->b2;
}

// ++++++++++++++++ B2_SET
void model_setting_PC_controller::b2_set(const double b2_new)
{
	 this->b2 = b2_new;
}

// ++++++++++++++++ B3_GET
double model_setting_PC_controller::b3_get(void) const
{
	return this->b3;
}

// ++++++++++++++++ B3_SET
void model_setting_PC_controller::b3_set(const double b3_new)
{
	this->b3 = b3_new;
}

// ++++++++++++++++ TYPE_GET
QString model_setting_PC_controller::controller_type_string_get(void) const
{
	return this->controller_type_name;
}

bool model_setting_PC_controller::controller_type_get(void) const
{
	return this->controller_type;
}

// ++++++++++++++++ TYPE_SET
void model_setting_PC_controller::controller_type_set(const bool controller_type_new)
{
	this->controller_type = controller_type_new;

	if(controller_type_new == CASCADE_CONTROLLER)
		this->controller_type_name = "cascade";
	else
		this->controller_type_name = "leadlag";
}

model_setting_PC_controller::model_setting_PC_controller(void)
{
}

model_setting_PC_controller::~model_setting_PC_controller(void)
{
}
