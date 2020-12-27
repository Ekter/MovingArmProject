#ifndef MODEL_SETTING_PC_CONTROLLER_H
#define MODEL_SETTING_PC_CONTROLLER_H

#include <QString>
#include <QStringList>

#include "include_define.h"
#include "model_singleton.h"

class model_setting_PC_controller : public Singleton<model_setting_PC_controller>
{
	friend class Singleton<model_setting_PC_controller>;

	public:
		void init(void);

		double k1_get(void) const;
		void k1_set(const double);

		double k2_get(void) const;
		void k2_set(const double);

		double a1_get(void) const;
		void a1_set(const double);

		double a2_get(void) const;
		void a2_set(const double);

		double b1_get(void) const;
		void b1_set(const double);

		double b2_get(void) const;
		void b2_set(const double);

		double b3_get(void) const;
		void b3_set(const double);

		QString controller_type_string_get(void) const;
		bool controller_type_get(void) const;
		void controller_type_set(const bool);

//			void show(const System::String*);

	private:
		model_setting_PC_controller(void);
		~model_setting_PC_controller(void);

		double k1;
		double k2;

		double a1;
		double a2;
		double b1;
		double b2;
		double b3;
		QString controller_type_name;
		bool controller_type;
		QStringList controllers_types;
};
#endif
