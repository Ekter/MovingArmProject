#ifndef MODEL_TIME_H
#define MODEL_TIME_H

#include "model_singleton.h"

class model_time : public Singleton<model_time>
{
	friend class Singleton<model_time>;

	public:
		void init(void);

		int time_desired_get(void);
		void time_desired_set(const int);

	private:
		model_time(void);
		~model_time(void);

		int time_desired;
};

#endif
