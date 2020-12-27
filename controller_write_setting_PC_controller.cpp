#include "controller_write_setting_PC_controller.h"

void controller_write_setting_PC_controller::init(void)
{
	this->myModel_setting_PC_controller = model_setting_PC_controller::getInstance();
	this->my_verification_saisie_utilisateur = verification_saisie_utilisateur::getInstance();
}

void controller_write_setting_PC_controller::init_setting_PC_controller()
{
	this->myModel_setting_PC_controller->init();
}

// ++++++++++++++++ K1_SET
bool controller_write_setting_PC_controller::k1_set(const QString k1_new)
{
	if(this->my_verification_saisie_utilisateur->saisie_nombre_valide_setting_PC_controller(k1_new))
	{
		this->myModel_setting_PC_controller->k1_set(k1_new.toDouble());

		return true;
	}

	this->my_view_messages.show_warning("K1 value error");

	return false;
}

// ++++++++++++++++ K2_SET
bool controller_write_setting_PC_controller::k2_set(const QString k2_new)
{
	if(this->my_verification_saisie_utilisateur->saisie_nombre_valide_setting_PC_controller(k2_new))
	{
		this->myModel_setting_PC_controller->k2_set(k2_new.toDouble());

		return true;
	}

	this->my_view_messages.show_warning("K2 value error");

	return false;
}

// ++++++++++++++++ A1_SET
bool controller_write_setting_PC_controller::a1_set(const QString a1_new)
{
	if(this->my_verification_saisie_utilisateur->saisie_nombre_valide_setting_PC_controller(a1_new))
	{
		this->myModel_setting_PC_controller->a1_set(a1_new.toDouble());

		return true;
	}

	this->my_view_messages.show_warning("A1 value error");

	return false;
}

// ++++++++++++++++ A2_SET
bool controller_write_setting_PC_controller::a2_set(const QString a2_new)
{
	if(this->my_verification_saisie_utilisateur->saisie_nombre_valide_setting_PC_controller(a2_new))
	{
		this->myModel_setting_PC_controller->a2_set(a2_new.toDouble());

		return true;
	}

	this->my_view_messages.show_warning("A2 value error");

	return false;
}

// ++++++++++++++++ B1_SET
bool controller_write_setting_PC_controller::b1_set(const QString b1_new)
{
	if(this->my_verification_saisie_utilisateur->saisie_nombre_valide_setting_PC_controller(b1_new))
	{
		this->myModel_setting_PC_controller->b1_set(b1_new.toDouble());

		return true;
	}

	this->my_view_messages.show_warning("B1 value error");

	return false;
}

// ++++++++++++++++ B2_SET
bool controller_write_setting_PC_controller::b2_set(const QString b2_new)
{
	if(this->my_verification_saisie_utilisateur->saisie_nombre_valide_setting_PC_controller(b2_new))
	{
		this->myModel_setting_PC_controller->b2_set(b2_new.toDouble());

		return true;
	}

	this->my_view_messages.show_warning("B2 value error");

	return false;
}

// ++++++++++++++++ B3_SET
bool controller_write_setting_PC_controller::b3_set(const QString b3_new)
{
	if(this->my_verification_saisie_utilisateur->saisie_nombre_valide_setting_PC_controller(b3_new))
	{
		this->myModel_setting_PC_controller->b3_set(b3_new.toDouble());

		return true;
	}

	this->my_view_messages.show_warning("B3 value error");

	return false;
}

// ++++++++++++++++ TYPE_SET
void controller_write_setting_PC_controller::controller_type_set(const bool controller_type_new)
{
	this->myModel_setting_PC_controller->controller_type_set(controller_type_new);
}

controller_write_setting_PC_controller::controller_write_setting_PC_controller()
{
}
