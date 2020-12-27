#ifndef VIEW_FLY_ARM_H
#define VIEW_FLY_ARM_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QRandomGenerator>
#include <QtMath>
#include <QRect>
#include <QPointF>
#include <QPixmap>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "arm_prop_simulator.h"
#include "arm_prop_controller.h"
#include "hilsModeSerialCommunicator.h"
#include "threadSimulatorController.h"

#include "model_draw.h"
#include "model_file_setting.h"
#include "model_time.h"

#include "controller_read_setting_PC_controller.h"
#include "controller_write_setting_PC_controller.h"
#include "controller_read_setting_sample_time.h"

#include "view_graph.h"
#include "view_about.h"
#include "view_setting_sample_time.h"
#include "view_setting_PC_controller.h"

#define HAUTEUR_A_ENLEVER 27

QT_BEGIN_NAMESPACE
namespace Ui { class view_fly_arm; }
QT_END_NAMESPACE

class view_fly_arm : public QMainWindow
{
	Q_OBJECT

	public:
		view_fly_arm(QWidget *parent = nullptr);
		~view_fly_arm();

	protected:
	  void resizeEvent(QResizeEvent *event);

	private slots:
	  void on_actionSave_triggered();

	  void on_actionExit_triggered();

	  void on_actionPC_Controleur_triggered();

	  void on_actionHils_mode_1_triggered();

	  void on_actionPC_Display_Real_angle_triggered();

	  void on_actionHils_mode_3_triggered();

	  void on_actionDemo_Manuel_Thrust_Command_triggered();

	  void on_actionSample_time_Configuration_triggered();

	  void on_actionPC_controller_Configuration_triggered();

	  void on_actionAbout_triggered();

	  void on_actionRepair_file_setting_txt_triggered();

	  void on_play_button_clicked();

	  void on_pause_button_clicked();

	  void on_stop_button_clicked();

	  void on_usb_port_radioButton_clicked();

	  void on_com_port_radioButton_clicked();

	  void on_com_port_comboBox_currentIndexChanged(int index);

	  void on_baud_rate_comboBox_currentIndexChanged(int index);

	  void on_connect_button_clicked();

	  void on_disconnect_button_clicked();

	  void timer1_Tick(void);

	  void on_theta_OR_thrust_desired_trackBar_actionTriggered(int action);

	  void on_time_textBox_textChanged(const QString &arg1);

	private:
		Ui::view_fly_arm *ui;

		model_draw *myDraw;
		model_file_setting* myModel_file_setting;
		model_time* myTime;

		// CLASSES VUES
		view_graph graph_theta;
		view_graph graph_thrust;
		view_graph graph_theta_dot;
		view_graph graph_theta_dotdot;

		view_about myView_about;
		view_setting_sample_time myView_setting_sample_time;
		view_setting_PC_controller myView_setting_PC_controller;

		ArmPropSimulator* myArmPropSimulator;
		ArmPropController* myArmPropController;
		hilsModeSerialCommunicator* myHilsModeSerialCommunicator;
		threadSimulatorController* myThreadSimulatorController;

		controller_read_setting_PC_controller* myController_read_setting_PC_controller;
		controller_write_setting_PC_controller* myController_write_setting_PC_controller;
		controller_read_setting_sample_time* myController_read_setting_sample_time;
		controller_write_setting_sample_time* myController_write_setting_sample_time;

		QTimer* timer1;
		QSerialPort* serialPort;

		QString controller_type_name;
		QString bouton_gris;
		QString bouton_vert;
		QString bouton_racine;

		bool myThreadSimulatorController_is_create;
		int time_desired;

		double DesiredTheta_Rad;
		double DesiredTheta_Deg;

		// attributs pour 'setting_sample_time
		int step;
		int simulator_step;
		int controller_step;
		int graph_step;
		int simulator_step_count;
		int controller_step_count;
		int graph_step_count;
		double timer_graph;
		double timer_graph_step;

		int signalValue;
		bool theta_desired;             // choice: theta desired OR thrust desired
		double thrust_desired;

		double rad_arm;
		double degree_arm;
		double thrust;
		double theta_dot;
		double theta_dotdot;
		double theta_dot_controlleur;

		bool consol_is_show;
		bool theta_desired_is_show;

		void console_info_update(void);

		void disconnect_method(void);

		void graphs_draw(void);

		void objects_init(void);
		void sample_time_init(void);
		void timer_init(void);
		void graph_init(void);
		void attributs_init(void);
		void widgets_hide(void);

		void modes_infos_communes(bool consol_is_show_bool, bool consol_show_OR_hide_bool, bool theta_OR_thrust_desired_is_show_bool, bool theta_OR_thrust_desired_show_OR_hide_bool, QString texte, int hils_mode_int);

		void buttons_enabled(bool play_state,bool pause_state, bool stop_state);
		void theta_desired_show_OR_hide(bool true_or_false);
		void theta_OR_thrust_desired_save();

		void consol_show_OR_hide(bool true_or_false);
		void connect_disconnect_true_or_false(bool true_or_false);

		void graphs_clear(void);

		void find_ports(void);
		void connect_button_state(void);
		void disconnect_serial_port(void);
// ======================================================

		// AFFICHAGE
		qreal graph_temps_label_top;
		QRect nouvelles_dimensions;

// PARTIE TEMPORAIRE
		void remplir_valeurs(void);

		int nombre_d_elements;
		QPointF valeurs;
		QPointF valeur2;

		QRandomGenerator generateur_nombre_aleatoire;
};
#endif // VIEW_FLY_ARM_H
