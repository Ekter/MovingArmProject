#ifndef MODEL_SETTING_SAMPLE_TIME_H
#define MODEL_SETTING_SAMPLE_TIME_H

#include "model_singleton.h"

class model_setting_sample_time : public Singleton<model_setting_sample_time>
{
	friend class Singleton<model_setting_sample_time>;

	public:
		void init(void);

		int step_get(void) const;
		void step_set(const int);

		int simulator_step_get(void) const;
		void simulator_step_set(const int);

		int controller_step_get(void) const;
		void controller_step_set(const int);

		int graph_step_get(void) const;
		void graph_step_set(const int);

		double sample_time_simulator_get(void) const;
		double sample_time_controller_get(void) const;

	private:
		model_setting_sample_time(void);
		~model_setting_sample_time(void);

		int step;
		int simulator_step;
		int controller_step;
		int graph_step;

		double sample_time_simulator;
		double sample_time_controller;

		void sample_time_simulator_update(void);
		void sample_time_controller_update(void);
};

#endif
