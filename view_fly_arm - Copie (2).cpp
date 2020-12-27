#include "view_fly_arm.h"
#include "ui_view_fly_arm.h"

view_fly_arm::view_fly_arm(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::view_fly_arm)
{
	ui->setupUi(this);

	// INIT
	this->objects_init();
	this->sample_time_init();
	this->timer_init();
	this->graph_init();
	this->attributs_init();
	this->widgets_hide();
}

view_fly_arm::~view_fly_arm()
{
	this->myModel_file_setting->file_write();

	delete ui;
}

void view_fly_arm::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event)

//	qDebug() << "resize event";
	this->ui->view_panel->resize(this->ui->groupBox_6->width(), this->ui->groupBox_6->height());
	this->ui->terminal_groupBox->resize(this->ui->terminal_panel->width() - 320, this->ui->terminal_groupBox->height());

	this->nouvelles_dimensions = this->ui->graph_theta_temps_legend_label->geometry();
//	qDebug() << "label dimensions = " << this->nouvelles_dimensions;
	this->nouvelles_dimensions.setTop(this->ui->graph_theta_legend->height() - HAUTEUR_A_ENLEVER);
//	qDebug() << "graph dimensions = " << this->ui->graph_theta_legend->geometry();
	this->ui->graph_theta_temps_legend_label->setGeometry(this->nouvelles_dimensions);
//	qDebug() << "graph_theta_temps_legend_label = " << this->ui->graph_theta_temps_legend_label->geometry();

	this->nouvelles_dimensions = this->ui->graph_thrust_temps_legend_label->geometry();
	this->nouvelles_dimensions.setTop(this->ui->graph_thrust_legend->height() - HAUTEUR_A_ENLEVER);
	this->ui->graph_thrust_temps_legend_label->setGeometry(this->nouvelles_dimensions);

	this->nouvelles_dimensions = this->ui->graph_theta_dot_temps_legend_label->geometry();
	this->nouvelles_dimensions.setTop(this->ui->graph_theta_dot_legend->height() - HAUTEUR_A_ENLEVER);
	this->ui->graph_theta_dot_temps_legend_label->setGeometry(this->nouvelles_dimensions);

	this->nouvelles_dimensions = this->ui->graph_theta_dotdot_temps_legend_label->geometry();
	this->nouvelles_dimensions.setTop(this->ui->graph_theta_dotdot_legend->height() - HAUTEUR_A_ENLEVER);
	this->ui->graph_theta_dotdot_temps_legend_label->setGeometry(this->nouvelles_dimensions);

	this->myDraw->adapte_la_taille(this->ui->view_panel->size());
}

// ------------------------------------------------------
//                      MENU FILE: EXIT + SAVE
// ------------------------------------------------------
void view_fly_arm::on_actionSave_triggered()
{
	QPixmap image = this->graph_theta.donne_le_qchartview()->grab();
	image.save("..\\Theta-Time.png", "PNG");

	image = this->graph_thrust.donne_le_qchartview()->grab();
	image.save("..\\Thrust-Time.png", "PNG");

	image = this->graph_theta_dot.donne_le_qchartview()->grab();
	image.save("..\\Theta_dot-Time.png", "PNG");

	image = this->graph_theta_dotdot.donne_le_qchartview()->grab();
	image.save("..\\Theta_dotdot-Time.png", "PNG");
}

void view_fly_arm::on_actionExit_triggered()
{
	this->close();
}

// ------------------------------------------------------
//                      MENU MODE
// ------------------------------------------------------
void view_fly_arm::on_actionPC_Controleur_triggered()
{
	this->theta_desired = true;
	this->ui->theta_OR_thrust_desired_label->setText("Desired Theta:");
	this->ui->theta_desired_unite_label->setText("deg");
	this->ui->theta_OR_thrust_desired_value_label->setText("0");
	this->ui->theta_OR_thrust_desired_trackBar->setValue(0);
	this->ui->theta_OR_thrust_desired_trackBar->setMaximum(179);

	this->myView_setting_PC_controller.show();

	if (this->myController_read_setting_PC_controller->controller_type_get() == CASCADE_CONTROLLER)
	{
		this->controller_type_name = "(Cascade)";
	}
	else // LEADLAG_CONTROLLER
	{
		this->controller_type_name = "(Leadlag)";
	}
	//this->modes_infos_communes(sender, e, true, false, false, true, L"Mode: PC control " + this->controller_type_name, HILS_MODE_PC_CONTROLLER);
	this->modes_infos_communes(true, false, false, true, "Mode: PC control " + this->controller_type_name, HILS_MODE_PC_CONTROLLER);
}

void view_fly_arm::on_actionHils_mode_1_triggered()
{
	this->modes_infos_communes(false, true, true, false, "Mode: Simulateur PC", HILS_MODE_1_);
}

void view_fly_arm::on_actionPC_Display_Real_angle_triggered()
{
	//this->modes_infos_communes(sender, e, false, true, true, false, L"Mode: PC display real angle", HILS_MODE_2);
	this->modes_infos_communes(false, true, true, false, "Mode: PC display real angle", HILS_MODE_REAL_ANGLE);
}

void view_fly_arm::on_actionHils_mode_3_triggered()
{
	this->modes_infos_communes(false, true, true, false, "Mode: HILS MODE 3", HILS_MODE_3_);
}

void view_fly_arm::on_actionDemo_Manuel_Thrust_Command_triggered()
{
	this->theta_desired = false; // THRUST DESIRED
	this->ui->theta_OR_thrust_desired_label->setText("Desired Thrust:");
	this->ui->theta_desired_unite_label->setText("N");
	this->ui->theta_OR_thrust_desired_value_label->setText("0");
	this->ui->theta_OR_thrust_desired_trackBar->setValue(0);
	this->ui->theta_OR_thrust_desired_trackBar->setMaximum(30);

	this->modes_infos_communes(true, false, false, true, "Mode: Demo Manuel Thrust", HILS_MODE_MANUAL_THRUST_COMMAND);
}

// ------------------------------------------------------
//                      MENU SETTING: SAMPLE TIME + PC CONTROLLER
// ------------------------------------------------------
void view_fly_arm::on_actionSample_time_Configuration_triggered()
{
	if(this->ui->stop_button->isEnabled() == true)
	{
		this->on_stop_button_clicked();
	}

	this->myView_setting_sample_time.show();

	// mise-à-jour des informations
	this->graphs_clear();
	this->sample_time_init();
	this->timer_init();
	this->graph_init();
}

void view_fly_arm::on_actionPC_controller_Configuration_triggered()
{
	this->myView_setting_PC_controller.show();

	if(this->theta_desired == true && this->ui->theta_OR_thrust_desired_trackBar->isVisible() == true)
	{
		if(this->myController_read_setting_PC_controller->controller_type_get() == CASCADE_CONTROLLER)
			this->ui->mode_label->setText("Mode: PC control (Cascade)");
		else // LEADLAG_CONTROLLER
			this->ui->mode_label->setText("Mode: PC control (Leadlag)");
	}
}

// ------------------------------------------------------
//                      MENU HELP: ABOUT + REPAIR
// ------------------------------------------------------
void view_fly_arm::on_actionAbout_triggered()
{
	this->myView_about.show();
}

void view_fly_arm::on_actionRepair_file_setting_txt_triggered()
{
	this->myController_write_setting_PC_controller->init_setting_PC_controller();
	this->myController_write_setting_sample_time->init_setting_sample_time();
	this->myTime->init();
	this->myModel_file_setting->file_write();
}
// ------------------------------------------------------
//                      PANEL MODE
// ------------------------------------------------------

void view_fly_arm::on_play_button_clicked()
{
	// effacer les graphiques si je ne suis pas en mode pause
	if(this->ui->pause_button->isEnabled() == false && this->ui->stop_button->isEnabled() == false)
	{
		this->graphs_clear();
	}
	this->buttons_enabled(false, true, true); // prevents from clicking twice on play ince ativated but the other get accessible

	if(this->myThreadSimulatorController_is_create == false) // to not create a second class
	{
		this->myThreadSimulatorController_is_create = true; // create class
		this->myThreadSimulatorController->init();
		this->timer_define_function_execute();
		this->timer1->start(); // start timer
	}
}

void view_fly_arm::on_pause_button_clicked()
{
	this->buttons_enabled(true, false, true);
	if(this->myThreadSimulatorController_is_create == true)
	{
		this->timer1->stop();
		this->myThreadSimulatorController_is_create = false;
	}
}

void view_fly_arm::on_stop_button_clicked()
{
	this->buttons_enabled(true, false, false);

	if(this->myThreadSimulatorController_is_create == true)
	{
		this->timer1->stop();
		this->myThreadSimulatorController_is_create =false;
	}

	this->myArmPropSimulator->init();
	this->myArmPropController->init();
	this->theta_OR_thrust_desired_save();

	this->graphs_clear();
	// pour avoir en abscisse une graduation de 0 à 2
	this->timer_graph = 0;
	this->graphs_draw();
}

void view_fly_arm::on_theta_OR_thrust_desired_trackBar_actionTriggered(int action)
{
	Q_UNUSED(action)

	this->theta_OR_thrust_desired_save();
}

void view_fly_arm::on_time_textBox_textChanged(const QString &arg1)
{
	int temp;
	temp = this->ui->time_textBox->text().toInt();
	if (temp > 9999999)
	{
		temp = 9999999;
		this->ui->time_textBox->setText(QString::number(temp));
	}
	this->time_desired = temp;
	this->myTime->time_desired_set(temp);
}
// ------------------------------------------------------
//                      CONSOLE
// ------------------------------------------------------
void view_fly_arm::console_info_update(void)
{
	// si la console est active
	if (this->ui->theta_OR_thrust_desired_trackBar->isVisible() == false)
	{
		this->signalValue = this->myHilsModeSerialCommunicator->getSignal();
		this->ui->terminal_signal_value_label->setText("Current Signal:" + QString::number(this->signalValue));
		this->ui->signal_value_progressBar->setValue(signalValue);
	}
}

void view_fly_arm::on_connect_button_clicked()
{
	//this->label2->Text = "";
	//-------------Connect serialcommunication-------------------
	//verify that the Setting PORT USB or COM and BAUD RATE are selected
	//
	QString string_temp;
	// make sure port isn't open
	if(this->myHilsModeSerialCommunicator->myCommunicator->portSuccessfullyOpened() == false)
	{
		if(this->ui->usb_port_radioButton->isChecked())
		{
			// essaie d'ouvrir la connection au port usb
			this->myHilsModeSerialCommunicator->myCommunicator->open_port(0, this->ui->baud_rate_comboBox->currentText().toInt());
			string_temp = this->myHilsModeSerialCommunicator->getMessage_serial_communicator();
			this->ui->terminal_info_label->setText(string_temp);
		}
		else // com_port_radioButton
		{
			// essaie d'ouvrir la connection au port com
			this->myHilsModeSerialCommunicator->myCommunicator->open_port(this->ui->com_port_comboBox->currentText().toInt(), this->ui->baud_rate_comboBox->currentText().toInt());
			string_temp = this->myHilsModeSerialCommunicator->getMessage_serial_communicator();
			this->ui->terminal_info_label->setText(string_temp);
		}
	}

	// vérifier que le port est ouvert
	if(this->myHilsModeSerialCommunicator->myCommunicator->portSuccessfullyOpened() == false)
	{
		if(this->ui->usb_port_radioButton->isChecked())
		{
			string_temp = this->myHilsModeSerialCommunicator->getMessage_serial_communicator();
			string_temp.append("Connect cable USB and press Connect ...");
			this->ui->terminal_info_label->setText(string_temp);
		}
		else // com_port_radioButton
		{
			string_temp = this->myHilsModeSerialCommunicator->getMessage_serial_communicator();
			string_temp.append("Connect cable COM and press Connect ...");
			this->ui->terminal_info_label->setText(string_temp);
		}
	}
	else // SI le port est ouvert
	{
		this->connect_disconnect_true_or_false(false);

		//this->myHilsModeSerialCommunicator->init();
		this->myHilsModeSerialCommunicator->run();

		// écrire les messages d'information
		switch(this->myHilsModeSerialCommunicator->getMessage())
		{
			case 1:
				string_temp.append("Could not open port!\nExiting...\n");
				this->ui->terminal_info_label->setText(string_temp);
				break;
			case 2:
				string_temp.append("Connecting to the board ... \n");
				string_temp.append("Failed to switch into HILS mode ");
				string_temp.append(QString::number(this->myHilsModeSerialCommunicator->getHilsMode()));
				string_temp.append(" - exiting...\n");
				this->ui->terminal_info_label->setText(string_temp);
				break;
			case 3:
				string_temp.append("Connecting to the board ... \n");
				string_temp.append("Successfully switched into HILS mode ");
				string_temp.append(QString::number(this->myHilsModeSerialCommunicator->getHilsMode()));
				string_temp.append(".\n");
				this->ui->terminal_info_label->setText(string_temp);
				break;
		}
	}
}

void view_fly_arm::on_disconnect_button_clicked()
{
	this->disconnect_method();
}

void view_fly_arm::disconnect_method(void)
{
	//-------------Disconnect serialcommunication-------------------
	this->timer1->stop();
	this->myHilsModeSerialCommunicator->stop();
	this->ui->terminal_info_label->setText("Press Connect ...");
	this->ui->terminal_signal_value_label->setText("");
	this->ui->signal_value_progressBar->setValue(0);

	this->connect_disconnect_true_or_false(true);
}
// ------------------------------------------------------
//                      TIMER
// ------------------------------------------------------
//
void view_fly_arm::timer_define_function_execute(void)
{
	//
	if(this->myHilsModeSerialCommunicator->getHilsMode() != HILS_MODE_MANUAL_THRUST_COMMAND)
		this->ptr_functions = &view_fly_arm::no_hils_mode_manual_thrust_command_function;


	// controller: GD: gets executed after some step counts (simulator faster than controller
	if(this->controller_step_count == this->controller_step && this->myHilsModeSerialCommunicator->getHilsMode() != HILS_MODE_MANUAL_THRUST_COMMAND
		&& this->myHilsModeSerialCommunicator->getHilsMode() != HILS_MODE_1)
	{
		this->ptr_functions = &this->controller_step_and_no_hils_mode_manual_thrust_command_function;
	}

	//==>> partie à modifier selon les indications de Guillaume
	// simulator
	//if(this->myHilsModeSerialCommunicator->getHilsMode() != HILS_MODE_REAL_ANGLE && this->simulator_step_count == this->simulator_step)
	if(this->myHilsModeSerialCommunicator->getHilsMode() != HILS_MODE_REAL_ANGLE && this->myHilsModeSerialCommunicator->getHilsMode() != HILS_MODE_1
		&& this->simulator_step_count == this->simulator_step)
	{
		this->ptr_functions = &view_fly_arm::no_hils_mode_real_angle_no_hils_mode_1;
	}
}

void view_fly_arm::no_hils_mode_manual_thrust_command_function(void)
{
	this->myThreadSimulatorController->hils_mode_execute(); //see threadSimulatorController.cpp
	qDebug() << "ptr_functions = no_hils_mode_manual_thrust_command_function";
}

void view_fly_arm::controller_step_and_no_hils_mode_manual_thrust_command_function(void)
{
	this->myThreadSimulatorController->runController();
	this->controller_step_count = 0;
	qDebug() << "ptr_functions = controller_step_and_no_hils_mode_manual_thrust_command_function";
}

void view_fly_arm::no_hils_mode_real_angle_no_hils_mode_1(void)
{
	this->myThreadSimulatorController->runSimulator();
	this->simulator_step_count = 0;
	qDebug() << "ptr_functions = no_hils_mode_real_angle_no_hils_mode_1";
}

// timer1_Tick : GD: period of execution is specified in Sample time Settings see in GUI
//
void view_fly_arm::timer1_Tick(void)
{
	// incrémenter les compteurs
	this->simulator_step_count++;
	this->controller_step_count++;
	this->graph_step_count++;

	// executer la fonction définie par le pointeur
	(this->*ptr_functions)();

	// graph
	if(this->graph_step_count == this->graph_step)
	{
		this->graph_step_count = 0;
		this->timer_graph += this->timer_graph_step;
		this->graphs_draw();

		this->console_info_update();

//		this->myOpenGL->render();
//		this->my_view_openGL->buffers_swap();
	}


	// tenir compte du temps désiré
	if (this->timer_graph >= double(this->time_desired))
	{
		this->timer1->stop();
		this->myThreadSimulatorController_is_create =false;
		this->buttons_enabled(true, false, true);
	}
}
// ------------------------------------------------------
//                      GRAPHS
// ------------------------------------------------------
void view_fly_arm::graphs_draw(void)
{
	this->rad_arm = this->myArmPropSimulator->GetTheta();
	this->degree_arm = this->rad_arm * 180.0 / MY_PI;
	this->thrust = this->myArmPropSimulator->GetPropThrust();
	this->theta_dot = this->myArmPropSimulator->GetThetaDot();
	this->theta_dotdot = this->myArmPropSimulator->GetThetaDotDot();
	this->theta_dot_controlleur = this->theta_dot + 2;

	this->ui->theta_value_label->setText(QString::number(this->degree_arm));
	this->ui->thrust_value_label->setText(QString::number(this->thrust));

	this->ui->graph_theta_value_label->setText(QString::number(this->degree_arm));
	this->ui->graph_thrust_value_label->setText(QString::number(this->thrust));
	this->ui->graph_theta_dot_value_label->setText(QString::number(this->theta_dot));
	this->ui->graph_theta_dotdot_value_label->setText(QString::number(this->theta_dotdot));
	this->ui->graph_theta_dot_controlleur_value_label->setText(QString::number(this->theta_dot_controlleur));

	// T1 = Theta-Time
	if (this->ui->angle_unite_listBox->currentIndex() == 0) // "deg" -> unité: degré
	{
		this->graph_theta.dessiner_les_points(QPointF(this->timer_graph, this->degree_arm));
	}
	else // "rad" -> unité: radian
	{
		this->graph_theta.dessiner_les_points(QPointF(this->timer_graph, this->rad_arm));
	}

	// T2 = Thrust-Time
	this->graph_thrust.dessiner_les_points(QPointF(this->timer_graph, this->thrust));

	// T3 = Theta_Dot-Time
	this->graph_theta_dot.dessiner_les_points(QPointF(this->timer_graph, this->theta_dot), QPointF(this->timer_graph, this->theta_dot_controlleur));

	// T4 = Theta_DotDot-Time
	this->graph_theta_dotdot.dessiner_les_points(QPointF(this->timer_graph, this->theta_dotdot));

	this->myDraw->definit_la_puissance_et_la_rotation_du_bras(this->thrust, this->degree_arm);
}
// ------------------------------------------------------
//                      WINDOW
// ------------------------------------------------------
// ------------------------------------------------------
//                      SERIAL PORT
// ------------------------------------------------------
void view_fly_arm::on_usb_port_radioButton_clicked()
{
	this->ui->com_port_comboBox->clear();
	this->connect_button_state();

	this->myHilsModeSerialCommunicator->myCommunicator->port_select(PORT_USB);

	this->ui->terminal_info_label->setText("Press Connect ...");
}

void view_fly_arm::on_com_port_radioButton_clicked()
{
	this->find_ports();
	this->connect_button_state();

	this->myHilsModeSerialCommunicator->myCommunicator->port_select(PORT_COM);

	this->ui->terminal_info_label->setText("Press Connect ...");

}

void view_fly_arm::on_com_port_comboBox_currentIndexChanged(int index)
{
	Q_UNUSED(index)
	this->connect_button_state();
}

void view_fly_arm::on_baud_rate_comboBox_currentIndexChanged(int index)
{
	Q_UNUSED(index)
	this->connect_button_state();
}
// ******************************************************
//                      START LOCAL FUNCTIONS
// ******************************************************
// ------------------------------------------------------
//                      INIT
// ------------------------------------------------------
void view_fly_arm::objects_init(void)
{
	this->myArmPropSimulator = ArmPropSimulator::getInstance();
	this->myArmPropController = ArmPropController::getInstance();
	this->myHilsModeSerialCommunicator = hilsModeSerialCommunicator::getInstance();
	this->myThreadSimulatorController = threadSimulatorController::getInstance();
	this->myThreadSimulatorController_is_create = false;

	this->myModel_file_setting = model_file_setting::getInstance();
	this->myTime = model_time::getInstance();
	this->myController_read_setting_PC_controller = controller_read_setting_PC_controller::getInstance();
	this->myController_write_setting_PC_controller = controller_write_setting_PC_controller::getInstance();
	this->myController_read_setting_sample_time = controller_read_setting_sample_time::getInstance();
	this->myController_write_setting_sample_time = controller_write_setting_sample_time::getInstance();

	this->timer1 = new QTimer(this);
	connect(this->timer1, SIGNAL(timeout()), this, SLOT(timer1_Tick()));
}

void view_fly_arm::sample_time_init(void)
{
	this->step = this->myController_read_setting_sample_time->step_get();
	this->simulator_step = this->myController_read_setting_sample_time->simulator_step_get();
	this->controller_step = this->myController_read_setting_sample_time->controller_step_get();
	this->graph_step = this->myController_read_setting_sample_time->graph_step_get();
	this->simulator_step_count = 0;
	this->controller_step_count = 0;
	this->graph_step_count = 0;
}

void view_fly_arm::timer_init(void)
{
	this->timer1->setInterval(this->step);
}

void view_fly_arm::graph_init(void)
{
	// DESSIN
	this->myDraw = new model_draw(this->ui->view_panel);
	this->myDraw->definit_la_taille(this->ui->view_panel->size());
//	qDebug() << "view_panel->rect = " << this->ui->view_panel->rect();

	// GRAPHIQUES
	this->graph_theta_dot.ajoute_une_deuxieme_ligne();

	this->ui->splitter_2->addWidget(this->graph_theta.donne_le_qchartview());
	this->ui->splitter_2->addWidget(this->graph_thrust.donne_le_qchartview());
	this->ui->splitter_2->addWidget(this->graph_theta_dot.donne_le_qchartview());
	this->ui->splitter_2->addWidget(this->graph_theta_dotdot.donne_le_qchartview());

//	this->remplir_valeurs();
	this->timer_graph_step = double(this->step * this->graph_step / 1000.0);
	this->timer_graph = 0;
	this->graphs_draw();
}

void view_fly_arm::attributs_init(void)
{
	this->bouton_racine = "border-image: url(:/";
	this->bouton_gris = "_gris.jpg);";
	this->bouton_vert = "_green.jpg);";

	this->rad_arm = 0.0;
	this->degree_arm = 0;
	this->thrust = 0.0;
	this->theta_dot = 0.0;
	this->theta_dotdot = 0.0;
	this->theta_dot_controlleur = 0.0;

	this->time_desired = this->myTime->time_desired_get();
	this->ui->time_textBox->setText(QString::number(this->time_desired));

	this->DesiredTheta_Rad = 0.0;
	this->DesiredTheta_Deg = 0.0;

	this->consol_is_show = false;
	this->theta_desired_is_show =false;

	this->ui->angle_unite_listBox->addItem("Deg");
	this->ui->angle_unite_listBox->addItem("Rad");
	this->ui->angle_unite_listBox->setCurrentIndex(0);
}

void view_fly_arm::widgets_hide(void)
{
//	this->ui->theta_OR_thrust_desired_label->setVisible(false);
//	this->ui->theta_OR_thrust_desired_value_label->setVisible(false);
//	this->ui->theta_desired_unite_label->setVisible(false);
	this->ui->modes_panel->setFixedSize(this->ui->modes_panel->width(), 128);

	this->theta_desired_show_OR_hide(false);
	this->consol_show_OR_hide(false);
}
// ------------------------------------------------------
//                      MODES
// ------------------------------------------------------
void view_fly_arm::modes_infos_communes(bool consol_is_show_bool, bool consol_show_OR_hide_bool, bool theta_OR_thrust_desired_is_show_bool, bool theta_OR_thrust_desired_show_OR_hide_bool, QString texte, int hils_mode_int)
{
	this->disconnect_serial_port();
	//UNREFERENCED_PARAMETER(sender);
	//UNREFERENCED_PARAMETER(e);
	this->myArmPropSimulator->init();
	this->myArmPropController->init();
//	this->myOpenGL->render();
	this->myHilsModeSerialCommunicator->setHilsMode(hils_mode_int);
	this->myThreadSimulatorController->hils_mode_update(hils_mode_int);
	// mettre les boutons 'PLAY' 'PAUSE' et 'STOP' avec les valeurs de départ
	this->buttons_enabled(true, false, false);
	// adapter la taille de 'modes_panel' en fonction de hils_mode
	if(this->myHilsModeSerialCommunicator->getHilsMode() == HILS_MODE_PC_CONTROLLER || this->myHilsModeSerialCommunicator->getHilsMode() == HILS_MODE_MANUAL_THRUST_COMMAND)
	{
		this->ui->modes_panel->setFixedSize(this->ui->modes_panel->width(), 180);
		// mettre les controles devant 'modes_panel'
		this->ui->theta_OR_thrust_desired_label->setVisible(true);
		this->ui->theta_OR_thrust_desired_value_label->setVisible(true);
		this->ui->theta_desired_unite_label->setVisible(true);
	}
	else
	{
		this->ui->theta_OR_thrust_desired_label->setVisible(false);
		this->ui->theta_OR_thrust_desired_value_label->setVisible(false);
		this->ui->theta_desired_unite_label->setVisible(false);
		this->ui->modes_panel->setFixedSize(this->ui->modes_panel->width(), 128);
	}
	// afficher les informations nécessaires
	if (this->consol_is_show == consol_is_show_bool)
	{
		this->consol_show_OR_hide(consol_show_OR_hide_bool);
	}

	if (theta_desired_is_show == theta_OR_thrust_desired_is_show_bool)
	{
		this->theta_desired_show_OR_hide(theta_OR_thrust_desired_show_OR_hide_bool);
	}

	this->graphs_clear();
	this->ui->mode_label->setText(texte);
	this->timer_graph = 0;
	this->graphs_draw();
	this->simulator_step_count = 0;
	this->controller_step_count = 0;
	this->graph_step_count = 0;
	this->ui->graph_thrust_value_label->setText("0.0");
	this->ui->graph_theta_value_label->setText("0.0");
	this->ui->theta_value_label->setText("0.0");
	this->ui->thrust_value_label->setText("0.0");
}
// ------------------------------------------------------
//                      PANEL MODE
// ------------------------------------------------------
void view_fly_arm::buttons_enabled(bool play_state,bool pause_state, bool stop_state)
{
	this->ui->play_button->setEnabled(play_state);
	this->ui->pause_button->setEnabled(pause_state);
	this->ui->stop_button->setEnabled(stop_state);

	// CHANGER LES COULEURS DES BOUTONS
	if(play_state)
		this->ui->play_button->setStyleSheet(this->bouton_racine + "play" + this->bouton_vert);
	else
		this->ui->play_button->setStyleSheet(this->bouton_racine + "play" + this->bouton_gris);

	if(pause_state)
		this->ui->pause_button->setStyleSheet(this->bouton_racine + "pause" + this->bouton_vert);
	else
		this->ui->pause_button->setStyleSheet(this->bouton_racine + "pause" + this->bouton_gris);

	if(stop_state)
		this->ui->stop_button->setStyleSheet(this->bouton_racine + "stop" + this->bouton_vert);
	else
		this->ui->stop_button->setStyleSheet(this->bouton_racine + "stop" + this->bouton_gris);
}

void view_fly_arm::theta_desired_show_OR_hide(bool true_or_false)
{
	this->theta_desired_is_show = true_or_false;

	this->ui->theta_OR_thrust_desired_label->setVisible(true_or_false);
	this->ui->theta_OR_thrust_desired_value_label->setVisible(true_or_false);
	this->ui->theta_OR_thrust_desired_trackBar->setVisible(true_or_false);
	this->ui->theta_desired_unite_label->setVisible(true_or_false);
}

void view_fly_arm::theta_OR_thrust_desired_save()
{
	// theta_desired
	if (this->theta_desired == true)
	{
		qDebug() << "desired_value_label = " << this->ui->theta_OR_thrust_desired_value_label->text();
//		qDebug() << "desired_trackBar = " << QString::number(action);
		qDebug() << "desired_trackBar = " << QString::number(this->ui->theta_OR_thrust_desired_trackBar->value());
		this->ui->theta_OR_thrust_desired_value_label->setText(QString::number(this->ui->theta_OR_thrust_desired_trackBar->value()));
		this->DesiredTheta_Rad = double(this->ui->theta_OR_thrust_desired_trackBar->value()) * MY_PI / 180.0;
//		this->ui->theta_OR_thrust_desired_value_label->setText(QString::number(action));
//		this->DesiredTheta_Rad = double(action) * MY_PI / 180.0;
		this->myArmPropController->SetThetaCmd(this->DesiredTheta_Rad);
	}
	// thrust_desired
	else
	{
		this->thrust_desired = this->ui->theta_OR_thrust_desired_trackBar->value() / 10.0;
//		this->thrust_desired = action / 10.0;
		this->ui->theta_OR_thrust_desired_value_label->setText(QString::number(this->thrust_desired));
		this->myArmPropController->SetThrustCmd(this->thrust_desired);
	}
}
// ------------------------------------------------------
//                      CONSOLE
// ------------------------------------------------------
void view_fly_arm::consol_show_OR_hide(bool true_or_false)
{
	this->consol_is_show = true_or_false;

	this->ui->terminal_panel->setVisible(true_or_false);

	if(true_or_false == true)
		this->ui->baud_rate_comboBox->setCurrentText("19200");
}

void view_fly_arm::connect_disconnect_true_or_false(bool true_or_false)
{
	this->ui->connect_button->setEnabled(true_or_false);
	this->ui->disconnect_button->setEnabled(!true_or_false);
	this->ui->usb_port_radioButton->setEnabled(true_or_false);
	this->ui->com_port_radioButton->setEnabled(true_or_false);
	this->ui->com_port_comboBox->setEnabled(true_or_false);
	this->ui->baud_rate_comboBox->setEnabled(true_or_false);

	if(true_or_false == false)
	{
		this->ui->status_panel->setStyleSheet("background-color: rgb(0, 255, 0);"); // Qt::green
		this->ui->status_label->setText("Connected");
	}
	else
	{
		this->ui->status_panel->setStyleSheet("background-color: rgb(255, 0, 0);"); // Qt::red
		this->ui->status_label->setText("Disconnect");
	}
}
// ------------------------------------------------------
//                      GRAPHS
// ------------------------------------------------------
void view_fly_arm::graphs_clear(void)
{
	this->graph_theta.clear();
	this->graph_thrust.clear();
	this->graph_theta_dot.clear();
	this->graph_theta_dotdot.clear();
}
// ------------------------------------------------------
//                      SERIAL PORT
// ------------------------------------------------------
void view_fly_arm::find_ports(void)
{
	// vider la liste
	this->ui->com_port_comboBox->clear();
	// obtient le nom des ports utilisant la liaison série
	QList<QSerialPortInfo> liste_de_ports = QSerialPortInfo::availablePorts();
	// ajoute à la combobox les ports trouvés
	for(int index = 0; index < liste_de_ports.count(); index++)
	{
		this->ui->com_port_comboBox->addItem(liste_de_ports.at(index).portName());
	}
}

void view_fly_arm::connect_button_state(void)
{
	// enabled SI
	// com port actif ET baud rate valeur sélectionnée ET com port combobox choisi
	// OU usb port actif ET baud rate valeur sélectionnée
	if(this->ui->baud_rate_comboBox->currentIndex() >= 0 && ((this->ui->com_port_radioButton->isChecked() && this->ui->com_port_comboBox->currentIndex() >= 0) || this->ui->usb_port_radioButton->isChecked()))
		this->ui->connect_button->setEnabled(true);
	else
		this->ui->connect_button->setEnabled(false);
}

void view_fly_arm::disconnect_serial_port(void)
{
	// déconnecter la liaison série lorsque l'utilisateur change de HilsMode sans avoir déconnecter manuellement
	if(this->ui->disconnect_button->isEnabled())
		this->disconnect_method();
}














// ==========================================================
// ==========================================================
// ==========================================================
// ==========================================================


// FONCTIONS TEMPORAIRES
void view_fly_arm::remplir_valeurs()
{
	for(qreal index = 0.1; index < 15; index += 0.1)
	{
		this->valeurs = QPointF(qreal(index), qreal(this->generateur_nombre_aleatoire.bounded(-23, 42)));
		this->graph_theta.dessiner_les_points(this->valeurs);
		this->graph_thrust.dessiner_les_points(this->valeurs);
		this->valeur2 = this->valeurs;
		this->valeur2.setY(this->valeurs.y() + 4);
		this->graph_theta_dot.dessiner_les_points(this->valeurs, this->valeur2);
//		this->graph_theta_dot.dessiner_les_points(this->valeurs);
		this->graph_theta_dotdot.dessiner_les_points(this->valeurs);
	}
	// VALEURS DIVERSES
//	this->valeurs = {{0.1, 0}, {0.2, 3}, {0.3, 6}, {0.4, -2}, {0.5, -7},
//					{0.6, 10.8}, {0.7, 23}, {0.8, 16}, {0.9, -2.7}, {1, -7.5},
//					{1.1, -0.3}, {1.2, 43}, {1.3, 1.6}, {1.4, 25}, {1.5, -0.7},
//					{1.6, -9.9}, {1.7, -10}, {1.8, 16.8}, {1.9, -2.1}, {2, -5.5}};
	// TEST VALEURS Y > 0 ET Y < 0.1
//	this->valeurs = {{0.1, 0}, {0.2, 0.03}, {0.3, 0.04}, {0.4, 0.01}, {0.5, 0.03},
//					{0.6, 0.099}, {0.7, 0.07}, {0.8, 0.08548}};
}
