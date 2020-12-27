#include "controller_read_setting_sample_time.h"

void controller_read_setting_sample_time::init(void)
{
	this->my_model_setting_sample_time = model_setting_sample_time::getInstance();
}

QString controller_read_setting_sample_time::step_string_get(void) const
{
	return QString::number(this->my_model_setting_sample_time->step_get());
}

int controller_read_setting_sample_time::step_get(void) const
{
	return this->my_model_setting_sample_time->step_get();
}

QString controller_read_setting_sample_time::simulator_step_string_get(void) const
{
	return QString::number(this->my_model_setting_sample_time->simulator_step_get());
}

int controller_read_setting_sample_time::simulator_step_get(void) const
{
	return this->my_model_setting_sample_time->simulator_step_get();
}

QString controller_read_setting_sample_time::controller_step_string_get(void) const
{
	return QString::number(this->my_model_setting_sample_time->controller_step_get());
}

int controller_read_setting_sample_time::controller_step_get(void) const
{
	return this->my_model_setting_sample_time->controller_step_get();
}

QString controller_read_setting_sample_time::graph_step_string_get(void) const
{
	return QString::number(this->my_model_setting_sample_time->graph_step_get());
}

int controller_read_setting_sample_time::graph_step_get(void) const
{
	return this->my_model_setting_sample_time->graph_step_get();
}

double controller_read_setting_sample_time::sample_time_simulator_get(void) const
{
	return this->my_model_setting_sample_time->sample_time_simulator_get();
}

double controller_read_setting_sample_time::sample_time_controller_get(void) const
{
	return this->my_model_setting_sample_time->sample_time_controller_get();
}

controller_read_setting_sample_time::controller_read_setting_sample_time()
{
}
