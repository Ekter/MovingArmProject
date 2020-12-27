#include "model_time.h"

// -------- PUBLIC --------
// ++++++++++++++++ INIT
void model_time::init(void)
{
	this->time_desired = 0;
}

// ++++++++++++++++ TIME_DESIRED_GET
int model_time::time_desired_get(void)
{
	return this->time_desired;
}

// ++++++++++++++++ TIME_DESIRED_SET
void model_time::time_desired_set(const int time_desired_new)
{
	if(time_desired_new >= 0)
		this->time_desired = time_desired_new;
	else
		this->time_desired = 30;
}

// -------- PRIVATE --------

model_time::model_time(void)
{
}

model_time::~model_time(void)
{
}
