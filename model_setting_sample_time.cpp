#include "model_setting_sample_time.h"

void model_setting_sample_time::init(void)
{
	this->step = 50;//25;
	this->simulator_step = 2;
	this->controller_step = 1;//2;
	this->graph_step = 2;//4;

	this->sample_time_simulator_update();
	this->sample_time_controller_update();
}

int model_setting_sample_time::step_get(void) const
{
	return this->step;
}

void model_setting_sample_time::step_set(const int new_step)
{
//	if(new_step > 0)
//		this->step = new_step;
//	else
//		this->step = 25;
		this->step = new_step;
}

int model_setting_sample_time::simulator_step_get(void) const
{
	return this->simulator_step;
}

void model_setting_sample_time::simulator_step_set(const int new_simulator_step)
{
//	if(new_simulator_step > 0)
//		this->simulator_step = new_simulator_step;
//	else
//		this->simulator_step = 1;
		this->simulator_step = new_simulator_step;

	this->sample_time_simulator_update();
}

int model_setting_sample_time::controller_step_get(void) const
{
	return this->controller_step;
}

void model_setting_sample_time::controller_step_set(const int new_controller_step)
{
//	if(new_controller_step > 0)
//		this->controller_step = new_controller_step;
//	else
//		this->controller_step = 2;
		this->controller_step = new_controller_step;

	this->sample_time_controller_update();
}

int model_setting_sample_time::graph_step_get(void) const
{
	return this->graph_step;
}

void model_setting_sample_time::graph_step_set(const int new_graph_step)
{
//	if(new_graph_step > 0)
//		this->graph_step = new_graph_step;
//	else
//		this->graph_step = 4;
		this->graph_step = new_graph_step;
}

double model_setting_sample_time::sample_time_simulator_get(void) const
{
	return this->sample_time_simulator;
}

double model_setting_sample_time::sample_time_controller_get(void) const
{
	return this->sample_time_controller;
}

void model_setting_sample_time::sample_time_simulator_update(void)
{
	this->sample_time_simulator = double(this->step) * double(this->simulator_step) / double(1000);
}

void model_setting_sample_time::sample_time_controller_update(void)
{
	this->sample_time_controller = double(this->step) * double(this->controller_step) / double(1000);
}

model_setting_sample_time::model_setting_sample_time(void)
	{
	}

model_setting_sample_time::~model_setting_sample_time(void)
	{
	}
