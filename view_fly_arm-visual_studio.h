#pragma once

#include <iostream>
#include "arm_prop_simulator.h"
#include "arm_prop_controller.h"
#include "hilsModeSerialCommunicator.h"
#include "threadSimulatorController.h"

#include "model_time.h"
#include "model_setting_PC_controller.h"
#include "model_openGL.h"

#include "view_openGL.h"
#include "view_setting_sample_time.h"
#include "view_setting_PC_controller.h"
#include "view_about.h"

namespace MovingArmProject {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
	using namespace System::IO::Ports;
//    using namespace OpenGLForm;

    /// <summary>
    /// Summary for view_fly_arm
    ///
    /// WARNING: If you change the name of this class, you will need to change the
    ///    'Resource File Name' property for the managed resource compiler tool
    ///    associated with all .resx files this class depends on.  Otherwise,
    ///    the designers will not be able to interact properly with localized
    ///    resources associated with this form.
    /// </summary>
    public ref class view_fly_arm : public System::Windows::Forms::Form
    {
        public:
            view_fly_arm()
            {
                InitializeComponent();
                //
                //TODO: Add the constructor code here
                //

				this->objects_init();

				this->sample_time_init();

				this->timer_init();

				this->graph_init();

				this->attributs_init();
		}

        protected:
            /// <summary>
            /// Clean up any resources being used.
            /// </summary>
            ~view_fly_arm()
            {
                if (components)
                {
                    delete components;
                }
            }

        private: System::ComponentModel::IContainer^  components;
        private: System::Windows::Forms::Button^  connect_button;
        private: System::Windows::Forms::Button^  disconnect_button;
        private: System::Windows::Forms::Button^  play_button;
        private: System::Windows::Forms::Button^  pause_button;
        private: System::Windows::Forms::Button^  stop_button;

        private: System::Windows::Forms::DataVisualization::Charting::Chart^  graph_theta;
        private: System::Windows::Forms::DataVisualization::Charting::Chart^  graph_thrust;
        private: System::Windows::Forms::GroupBox^  status_groupBox;
        private: System::Windows::Forms::GroupBox^  terminal_groupBox;
        private: System::Windows::Forms::Label^  status_label;
        private: System::Windows::Forms::Label^  terminal_info_label;
	private: System::Windows::Forms::Label^  terminal_signal_value_label;


        private: System::Windows::Forms::Label^  consol_label;
        private: System::Windows::Forms::Label^  graph_thrust_value_label;
        private: System::Windows::Forms::Label^  graph_theta_value_label;
        private: System::Windows::Forms::Label^  graph_y_theta_label;
        private: System::Windows::Forms::Label^  graph_x_theta_time_label;
        private: System::Windows::Forms::Label^  graph_x_thrust_time_label;
        private: System::Windows::Forms::Label^  graph_y_thrust_label;
        private: System::Windows::Forms::Label^  theta_label;
        private: System::Windows::Forms::Label^  thrust_label;
        private: System::Windows::Forms::Label^  thrust_value_label;
        private: System::Windows::Forms::Label^  theta_value_label;
        private: System::Windows::Forms::Label^  mode_label;
        private: System::Windows::Forms::Label^  time_label;
        private: System::Windows::Forms::Label^  theta_OR_thrust_desired_label;
        private: System::Windows::Forms::Label^  theta_OR_thrust_desired_value_label;

        private: System::Windows::Forms::Label^  time_unite_label;
        private: System::Windows::Forms::Label^  thrust_unite_label;
        private: System::Windows::Forms::Label^  theta_unite_label;
        private: System::Windows::Forms::Label^  theta_desired_unite_label;
		private: System::Windows::Forms::Label^  graph_theta_time_label;
		private: System::Windows::Forms::Label^  graph_thrust_time_label;
		private: System::Windows::Forms::Label^  graph_theta_dotdot_time_label;
		private: System::Windows::Forms::Label^  graph_theta_dot_time_label;
		private: System::Windows::Forms::Label^  graph_x_theta_dot_time_label;
		private: System::Windows::Forms::Label^  graph_x_theta_dotdot_time_label;
		private: System::Windows::Forms::Label^  graph_theta_dot_value_label;
		private: System::Windows::Forms::Label^  graph_theta_dotdot_value_label;
		private: System::Windows::Forms::Label^  graph_y_theta_dot_label;
		private: System::Windows::Forms::Label^  graph_y_theta_dotdot_label;
		private: System::Windows::Forms::Label^  baud_rate_label;


        private: System::Windows::Forms::MenuStrip^  menu;
        private: System::Windows::Forms::ToolStripMenuItem^  help_about_MenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  help_MenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  howToDoToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  setting_PC_controller_MenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  setting_sample_time_MenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  mode_MenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  mode_PC_controller_MenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  mode_hils_mode_1_MenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  mode_PC_display_real_angle_MenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  mode_hilsMode3ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  demoManuelThrustCommandToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  onlineToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  setting_MenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  file_MenuItem;
        private: System::Windows::Forms::Panel^  terminal_panel;
        private: System::Windows::Forms::Panel^  status_panel;
        private: System::Windows::Forms::Panel^  consol_panel;
        private: System::Windows::Forms::Panel^  consol_panel_panel;
		private: System::Windows::Forms::Panel^  modes_panel;
		private: System::Windows::Forms::ComboBox^  baud_rate_comboBox;
		private: System::Windows::Forms::ComboBox^  com_port_comboBox;
        private: System::Windows::Forms::ProgressBar^  signal_value_progressBar;
        private: System::Windows::Forms::TrackBar^  theta_OR_thrust_desired_trackBar;
        private: System::Windows::Forms::ListBox^  angle_unite_listBox;
        private: System::Windows::Forms::TextBox^  time_textBox;
        private: System::Windows::Forms::Timer^  timer1;
		private: System::IO::Ports::SerialPort^  serialPort1;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  graph_theta_dot;
		private: System::Windows::Forms::DataVisualization::Charting::Chart^  graph_theta_dotdot;
		private: System::Windows::Forms::RadioButton^  com_port_radioButton;
		private: System::Windows::Forms::RadioButton^  usb_port_radioButton;

        protected:

        private:
            /// <summary>
            /// Required designer variable.
            /// </summary>
			ArmPropSimulator* myArmPropSimulator;
			ArmPropController* myArmPropController;
			hilsModeSerialCommunicator* my_hilsModeSerialCommunicator;
			threadSimulatorController* myThreadSimulatorController;

			Cmodel_time* myTime;
			Cmodel_openGL* myOpenGL;
			Cmodel_setting_PC_controller* my_setting_PC_controller;
			model_setting_sample_time* my_setting_sample_time;
			String^ controller_type_name;

			bool myThreadSimulatorController_is_create;
			int time_desired;

            view_openGL^ my_view_openGL;

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

            // variables for resize window
            int opengl_y;

            int window_opengl_width;
            int window_opengl_height;
            int window_opengl_x;
            int window_opengl_y;

            int zoom_width;
            int zoom_height;

            int zoom_width_opengl;
            int zoom_height_opengl;

            int zoom_x_opengl;
            int zoom_y_opengl;

            int zoom_width_modulo;
            int zoom_height_modulo;

            int zoom_width_panel;
            int zoom_height_panel;

            int increment_height_theta;
            int increment_height_thrust;
            int increment_height_theta_dot;

            int window_panel_location_left;
            int window_panel_size_width;
            int window_panel_size_height;

            int window_panel_thrust_top;

            bool consol_is_show;
private: System::Windows::Forms::Label^  graph_theta_dot_controlleur_value_label;

private: System::Windows::Forms::Label^  graph_theta_dot_controlleur_time_label;
private: System::Windows::Forms::Panel^  graph_theta_dot_color;





private: System::Windows::Forms::Panel^  graph_theta_dot_controlleur_color;








		 bool theta_desired_is_show;

// ********************* START REGION *********************
#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void)
        {
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(view_fly_arm::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->theta_OR_thrust_desired_trackBar = (gcnew System::Windows::Forms::TrackBar());
			this->graph_y_thrust_label = (gcnew System::Windows::Forms::Label());
			this->graph_thrust = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->graph_y_theta_label = (gcnew System::Windows::Forms::Label());
			this->graph_theta = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->menu = (gcnew System::Windows::Forms::MenuStrip());
			this->file_MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mode_MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mode_PC_controller_MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mode_hils_mode_1_MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mode_PC_display_real_angle_MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mode_hilsMode3ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->demoManuelThrustCommandToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->setting_MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->setting_sample_time_MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->setting_PC_controller_MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->help_MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->howToDoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->onlineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->help_about_MenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->graph_x_thrust_time_label = (gcnew System::Windows::Forms::Label());
			this->graph_thrust_value_label = (gcnew System::Windows::Forms::Label());
			this->graph_x_theta_time_label = (gcnew System::Windows::Forms::Label());
			this->graph_theta_value_label = (gcnew System::Windows::Forms::Label());
			this->terminal_panel = (gcnew System::Windows::Forms::Panel());
			this->consol_panel = (gcnew System::Windows::Forms::Panel());
			this->consol_panel_panel = (gcnew System::Windows::Forms::Panel());
			this->consol_label = (gcnew System::Windows::Forms::Label());
			this->com_port_radioButton = (gcnew System::Windows::Forms::RadioButton());
			this->usb_port_radioButton = (gcnew System::Windows::Forms::RadioButton());
			this->terminal_signal_value_label = (gcnew System::Windows::Forms::Label());
			this->baud_rate_label = (gcnew System::Windows::Forms::Label());
			this->baud_rate_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->signal_value_progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->com_port_comboBox = (gcnew System::Windows::Forms::ComboBox());
			this->disconnect_button = (gcnew System::Windows::Forms::Button());
			this->connect_button = (gcnew System::Windows::Forms::Button());
			this->terminal_groupBox = (gcnew System::Windows::Forms::GroupBox());
			this->terminal_info_label = (gcnew System::Windows::Forms::Label());
			this->status_groupBox = (gcnew System::Windows::Forms::GroupBox());
			this->status_panel = (gcnew System::Windows::Forms::Panel());
			this->status_label = (gcnew System::Windows::Forms::Label());
			this->theta_label = (gcnew System::Windows::Forms::Label());
			this->thrust_label = (gcnew System::Windows::Forms::Label());
			this->thrust_value_label = (gcnew System::Windows::Forms::Label());
			this->theta_value_label = (gcnew System::Windows::Forms::Label());
			this->mode_label = (gcnew System::Windows::Forms::Label());
			this->play_button = (gcnew System::Windows::Forms::Button());
			this->pause_button = (gcnew System::Windows::Forms::Button());
			this->stop_button = (gcnew System::Windows::Forms::Button());
			this->time_label = (gcnew System::Windows::Forms::Label());
			this->time_textBox = (gcnew System::Windows::Forms::TextBox());
			this->theta_OR_thrust_desired_label = (gcnew System::Windows::Forms::Label());
			this->theta_OR_thrust_desired_value_label = (gcnew System::Windows::Forms::Label());
			this->time_unite_label = (gcnew System::Windows::Forms::Label());
			this->thrust_unite_label = (gcnew System::Windows::Forms::Label());
			this->theta_unite_label = (gcnew System::Windows::Forms::Label());
			this->theta_desired_unite_label = (gcnew System::Windows::Forms::Label());
			this->angle_unite_listBox = (gcnew System::Windows::Forms::ListBox());
			this->graph_theta_dot = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->graph_theta_dotdot = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->graph_theta_time_label = (gcnew System::Windows::Forms::Label());
			this->graph_thrust_time_label = (gcnew System::Windows::Forms::Label());
			this->graph_theta_dotdot_time_label = (gcnew System::Windows::Forms::Label());
			this->graph_theta_dot_time_label = (gcnew System::Windows::Forms::Label());
			this->graph_x_theta_dot_time_label = (gcnew System::Windows::Forms::Label());
			this->graph_x_theta_dotdot_time_label = (gcnew System::Windows::Forms::Label());
			this->graph_theta_dot_value_label = (gcnew System::Windows::Forms::Label());
			this->graph_theta_dotdot_value_label = (gcnew System::Windows::Forms::Label());
			this->modes_panel = (gcnew System::Windows::Forms::Panel());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->graph_y_theta_dot_label = (gcnew System::Windows::Forms::Label());
			this->graph_y_theta_dotdot_label = (gcnew System::Windows::Forms::Label());
			this->graph_theta_dot_controlleur_value_label = (gcnew System::Windows::Forms::Label());
			this->graph_theta_dot_controlleur_time_label = (gcnew System::Windows::Forms::Label());
			this->graph_theta_dot_color = (gcnew System::Windows::Forms::Panel());
			this->graph_theta_dot_controlleur_color = (gcnew System::Windows::Forms::Panel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->theta_OR_thrust_desired_trackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->graph_thrust))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->graph_theta))->BeginInit();
			this->menu->SuspendLayout();
			this->terminal_panel->SuspendLayout();
			this->consol_panel->SuspendLayout();
			this->terminal_groupBox->SuspendLayout();
			this->status_groupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->graph_theta_dot))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->graph_theta_dotdot))->BeginInit();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &view_fly_arm::timer1_Tick);
			// 
			// theta_OR_thrust_desired_trackBar
			// 
			this->theta_OR_thrust_desired_trackBar->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->theta_OR_thrust_desired_trackBar->Location = System::Drawing::Point(556, 175);
			this->theta_OR_thrust_desired_trackBar->Maximum = 179;
			this->theta_OR_thrust_desired_trackBar->Name = L"theta_OR_thrust_desired_trackBar";
			this->theta_OR_thrust_desired_trackBar->Size = System::Drawing::Size(161, 45);
			this->theta_OR_thrust_desired_trackBar->TabIndex = 43;
			this->theta_OR_thrust_desired_trackBar->Visible = false;
			this->theta_OR_thrust_desired_trackBar->Scroll += gcnew System::EventHandler(this, &view_fly_arm::theta_OR_thrust_desired_trackBar_Scroll);
			// 
			// graph_y_thrust_label
			// 
			this->graph_y_thrust_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->graph_y_thrust_label->AutoSize = true;
			this->graph_y_thrust_label->BackColor = System::Drawing::Color::White;
			this->graph_y_thrust_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->graph_y_thrust_label->ForeColor = System::Drawing::Color::Green;
			this->graph_y_thrust_label->Location = System::Drawing::Point(735, 193);
			this->graph_y_thrust_label->Name = L"graph_y_thrust_label";
			this->graph_y_thrust_label->Size = System::Drawing::Size(93, 17);
			this->graph_y_thrust_label->TabIndex = 42;
			this->graph_y_thrust_label->Text = L"Thrust ( N )";
			// 
			// graph_thrust
			// 
			this->graph_thrust->BackImageTransparentColor = System::Drawing::Color::Black;
			this->graph_thrust->BackSecondaryColor = System::Drawing::Color::Black;
			this->graph_thrust->BorderlineColor = System::Drawing::Color::Black;
			this->graph_thrust->BorderSkin->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_thrust->BorderSkin->BackHatchStyle = System::Windows::Forms::DataVisualization::Charting::ChartHatchStyle::Cross;
			this->graph_thrust->BorderSkin->BackSecondaryColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_thrust->BorderSkin->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_thrust->BorderSkin->PageColor = System::Drawing::Color::Yellow;
			chartArea1->BackImageTransparentColor = System::Drawing::Color::Transparent;
			chartArea1->BackSecondaryColor = System::Drawing::Color::Black;
			chartArea1->Name = L"ChartArea1";
			this->graph_thrust->ChartAreas->Add(chartArea1);
			legend1->BackColor = System::Drawing::Color::Black;
			legend1->BackSecondaryColor = System::Drawing::Color::Yellow;
			legend1->BorderColor = System::Drawing::Color::Transparent;
			legend1->ForeColor = System::Drawing::Color::White;
			legend1->HeaderSeparatorColor = System::Drawing::Color::Yellow;
			legend1->InterlacedRowsColor = System::Drawing::Color::White;
			legend1->ItemColumnSeparatorColor = System::Drawing::Color::Yellow;
			legend1->Name = L"Legend1";
			legend1->ShadowColor = System::Drawing::Color::Yellow;
			legend1->TitleBackColor = System::Drawing::Color::Yellow;
			legend1->TitleForeColor = System::Drawing::Color::Yellow;
			legend1->TitleSeparatorColor = System::Drawing::Color::Yellow;
			this->graph_thrust->Legends->Add(legend1);
			this->graph_thrust->Location = System::Drawing::Point(726, 204);
			this->graph_thrust->Name = L"graph_thrust";
			series1->BackImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			series1->BackSecondaryColor = System::Drawing::Color::Yellow;
			series1->BorderColor = System::Drawing::Color::Yellow;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Color = System::Drawing::Color::Red;
			series1->EmptyPointStyle->BackSecondaryColor = System::Drawing::Color::Yellow;
			series1->EmptyPointStyle->BorderColor = System::Drawing::Color::Yellow;
			series1->EmptyPointStyle->Color = System::Drawing::Color::Yellow;
			series1->EmptyPointStyle->LabelBackColor = System::Drawing::Color::Yellow;
			series1->EmptyPointStyle->LabelBorderColor = System::Drawing::Color::Yellow;
			series1->EmptyPointStyle->LabelForeColor = System::Drawing::Color::Yellow;
			series1->EmptyPointStyle->MarkerBorderColor = System::Drawing::Color::Yellow;
			series1->EmptyPointStyle->MarkerColor = System::Drawing::Color::Yellow;
			series1->EmptyPointStyle->MarkerImageTransparentColor = System::Drawing::Color::Yellow;
			series1->LabelBackColor = System::Drawing::Color::Yellow;
			series1->LabelBorderColor = System::Drawing::Color::Yellow;
			series1->LabelForeColor = System::Drawing::Color::Yellow;
			series1->Legend = L"Legend1";
			series1->MarkerBorderColor = System::Drawing::Color::Red;
			series1->MarkerColor = System::Drawing::Color::Maroon;
			series1->MarkerImageTransparentColor = System::Drawing::Color::Black;
			series1->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series1->Name = L"T2";
			series1->SmartLabelStyle->CalloutBackColor = System::Drawing::Color::Yellow;
			series1->SmartLabelStyle->CalloutLineColor = System::Drawing::Color::Yellow;
			this->graph_thrust->Series->Add(series1);
			this->graph_thrust->Size = System::Drawing::Size(778, 180);
			this->graph_thrust->TabIndex = 38;
			this->graph_thrust->Text = L"graph_thrust";
			// 
			// graph_y_theta_label
			// 
			this->graph_y_theta_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->graph_y_theta_label->AutoSize = true;
			this->graph_y_theta_label->BackColor = System::Drawing::Color::White;
			this->graph_y_theta_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->graph_y_theta_label->ForeColor = System::Drawing::Color::Green;
			this->graph_y_theta_label->Location = System::Drawing::Point(735, 15);
			this->graph_y_theta_label->Name = L"graph_y_theta_label";
			this->graph_y_theta_label->Size = System::Drawing::Size(132, 17);
			this->graph_y_theta_label->TabIndex = 33;
			this->graph_y_theta_label->Text = L"Theta (             )";
			// 
			// graph_theta
			// 
			this->graph_theta->BackImageTransparentColor = System::Drawing::Color::Black;
			this->graph_theta->BackSecondaryColor = System::Drawing::Color::Black;
			this->graph_theta->BorderlineColor = System::Drawing::Color::Black;
			this->graph_theta->BorderSkin->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_theta->BorderSkin->BackHatchStyle = System::Windows::Forms::DataVisualization::Charting::ChartHatchStyle::Cross;
			this->graph_theta->BorderSkin->BackSecondaryColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_theta->BorderSkin->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_theta->BorderSkin->PageColor = System::Drawing::Color::Yellow;
			chartArea2->BackImageTransparentColor = System::Drawing::Color::Transparent;
			chartArea2->BackSecondaryColor = System::Drawing::Color::Black;
			chartArea2->Name = L"graph_theta_chartArea";
			this->graph_theta->ChartAreas->Add(chartArea2);
			legend2->BackColor = System::Drawing::Color::Black;
			legend2->BackSecondaryColor = System::Drawing::Color::Yellow;
			legend2->BorderColor = System::Drawing::Color::Transparent;
			legend2->ForeColor = System::Drawing::Color::White;
			legend2->HeaderSeparatorColor = System::Drawing::Color::Yellow;
			legend2->InterlacedRowsColor = System::Drawing::Color::White;
			legend2->ItemColumnSeparatorColor = System::Drawing::Color::Yellow;
			legend2->Name = L"graph_theta_legend";
			legend2->ShadowColor = System::Drawing::Color::Yellow;
			legend2->TitleBackColor = System::Drawing::Color::Yellow;
			legend2->TitleForeColor = System::Drawing::Color::Yellow;
			legend2->TitleSeparatorColor = System::Drawing::Color::Yellow;
			this->graph_theta->Legends->Add(legend2);
			this->graph_theta->Location = System::Drawing::Point(726, 24);
			this->graph_theta->Name = L"graph_theta";
			series2->BackImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			series2->BackSecondaryColor = System::Drawing::Color::Yellow;
			series2->BorderColor = System::Drawing::Color::Yellow;
			series2->ChartArea = L"graph_theta_chartArea";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Color = System::Drawing::Color::Red;
			series2->EmptyPointStyle->BackSecondaryColor = System::Drawing::Color::Yellow;
			series2->EmptyPointStyle->BorderColor = System::Drawing::Color::Yellow;
			series2->EmptyPointStyle->Color = System::Drawing::Color::Yellow;
			series2->EmptyPointStyle->LabelBackColor = System::Drawing::Color::Yellow;
			series2->EmptyPointStyle->LabelBorderColor = System::Drawing::Color::Yellow;
			series2->EmptyPointStyle->LabelForeColor = System::Drawing::Color::Yellow;
			series2->EmptyPointStyle->MarkerBorderColor = System::Drawing::Color::Yellow;
			series2->EmptyPointStyle->MarkerColor = System::Drawing::Color::Yellow;
			series2->EmptyPointStyle->MarkerImageTransparentColor = System::Drawing::Color::Yellow;
			series2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			series2->LabelBackColor = System::Drawing::Color::Yellow;
			series2->LabelBorderColor = System::Drawing::Color::Yellow;
			series2->LabelForeColor = System::Drawing::Color::Yellow;
			series2->Legend = L"graph_theta_legend";
			series2->MarkerBorderColor = System::Drawing::Color::Red;
			series2->MarkerColor = System::Drawing::Color::Maroon;
			series2->MarkerImageTransparentColor = System::Drawing::Color::Black;
			series2->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series2->Name = L"T1";
			series2->SmartLabelStyle->CalloutBackColor = System::Drawing::Color::Yellow;
			series2->SmartLabelStyle->CalloutLineColor = System::Drawing::Color::Yellow;
			this->graph_theta->Series->Add(series2);
			this->graph_theta->Size = System::Drawing::Size(778, 180);
			this->graph_theta->TabIndex = 31;
			this->graph_theta->Text = L"graph_theta";
			// 
			// menu
			// 
			this->menu->BackColor = System::Drawing::Color::White;
			this->menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->file_MenuItem, this->mode_MenuItem, 
				this->setting_MenuItem, this->help_MenuItem});
			this->menu->Location = System::Drawing::Point(0, 0);
			this->menu->Name = L"menu";
			this->menu->Size = System::Drawing::Size(1504, 24);
			this->menu->TabIndex = 32;
			this->menu->Text = L"menu";
			// 
			// file_MenuItem
			// 
			this->file_MenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->openToolStripMenuItem, 
				this->saveToolStripMenuItem, this->exitToolStripMenuItem});
			this->file_MenuItem->Name = L"file_MenuItem";
			this->file_MenuItem->Size = System::Drawing::Size(37, 20);
			this->file_MenuItem->Text = L"File";
			this->file_MenuItem->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &view_fly_arm::file_MenuItem_Paint);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->openToolStripMenuItem->Text = L"Open";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &view_fly_arm::saveToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &view_fly_arm::exitToolStripMenuItem_Click);
			// 
			// mode_MenuItem
			// 
			this->mode_MenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->mode_PC_controller_MenuItem, 
				this->mode_hils_mode_1_MenuItem, this->mode_PC_display_real_angle_MenuItem, this->mode_hilsMode3ToolStripMenuItem, this->demoManuelThrustCommandToolStripMenuItem});
			this->mode_MenuItem->Name = L"mode_MenuItem";
			this->mode_MenuItem->Size = System::Drawing::Size(50, 20);
			this->mode_MenuItem->Text = L"Mode";
			// 
			// mode_PC_controller_MenuItem
			// 
			this->mode_PC_controller_MenuItem->Name = L"mode_PC_controller_MenuItem";
			this->mode_PC_controller_MenuItem->Size = System::Drawing::Size(248, 22);
			this->mode_PC_controller_MenuItem->Text = L"PC controller";
			this->mode_PC_controller_MenuItem->Click += gcnew System::EventHandler(this, &view_fly_arm::mode_PC_controller_MenuItem_Click);
			// 
			// mode_hils_mode_1_MenuItem
			// 
			this->mode_hils_mode_1_MenuItem->Name = L"mode_hils_mode_1_MenuItem";
			this->mode_hils_mode_1_MenuItem->Size = System::Drawing::Size(248, 22);
			this->mode_hils_mode_1_MenuItem->Text = L"Hils_Mode 1";
			this->mode_hils_mode_1_MenuItem->Click += gcnew System::EventHandler(this, &view_fly_arm::mode_hils_mode_1_MenuItem_Click);
			// 
			// mode_PC_display_real_angle_MenuItem
			// 
			this->mode_PC_display_real_angle_MenuItem->Name = L"mode_PC_display_real_angle_MenuItem";
			this->mode_PC_display_real_angle_MenuItem->Size = System::Drawing::Size(248, 22);
			this->mode_PC_display_real_angle_MenuItem->Text = L"PC display - real angle";
			this->mode_PC_display_real_angle_MenuItem->Click += gcnew System::EventHandler(this, &view_fly_arm::mode_PC_display_real_angle_MenuItem_Click);
			// 
			// mode_hilsMode3ToolStripMenuItem
			// 
			this->mode_hilsMode3ToolStripMenuItem->Name = L"mode_hilsMode3ToolStripMenuItem";
			this->mode_hilsMode3ToolStripMenuItem->Size = System::Drawing::Size(248, 22);
			this->mode_hilsMode3ToolStripMenuItem->Text = L"Hils_Mode 3";
			this->mode_hilsMode3ToolStripMenuItem->Click += gcnew System::EventHandler(this, &view_fly_arm::mode_hilsMode3ToolStripMenuItem_Click);
			// 
			// demoManuelThrustCommandToolStripMenuItem
			// 
			this->demoManuelThrustCommandToolStripMenuItem->Name = L"demoManuelThrustCommandToolStripMenuItem";
			this->demoManuelThrustCommandToolStripMenuItem->Size = System::Drawing::Size(248, 22);
			this->demoManuelThrustCommandToolStripMenuItem->Text = L"Demo: Manuel Thrust Command";
			this->demoManuelThrustCommandToolStripMenuItem->Click += gcnew System::EventHandler(this, &view_fly_arm::mode_demoManuelThrustCommandToolStripMenuItem_Click);
			// 
			// setting_MenuItem
			// 
			this->setting_MenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->setting_sample_time_MenuItem, 
				this->setting_PC_controller_MenuItem});
			this->setting_MenuItem->Name = L"setting_MenuItem";
			this->setting_MenuItem->Size = System::Drawing::Size(56, 20);
			this->setting_MenuItem->Text = L"Setting";
			// 
			// setting_sample_time_MenuItem
			// 
			this->setting_sample_time_MenuItem->Name = L"setting_sample_time_MenuItem";
			this->setting_sample_time_MenuItem->Size = System::Drawing::Size(241, 22);
			this->setting_sample_time_MenuItem->Text = L"Sample time  --> Configuration";
			this->setting_sample_time_MenuItem->Click += gcnew System::EventHandler(this, &view_fly_arm::setting_sample_time_MenuItem_Click);
			// 
			// setting_PC_controller_MenuItem
			// 
			this->setting_PC_controller_MenuItem->Name = L"setting_PC_controller_MenuItem";
			this->setting_PC_controller_MenuItem->Size = System::Drawing::Size(241, 22);
			this->setting_PC_controller_MenuItem->Text = L"PC controller --> Configuration";
			this->setting_PC_controller_MenuItem->Click += gcnew System::EventHandler(this, &view_fly_arm::setting_PC_controller_MenuItem_Click);
			// 
			// help_MenuItem
			// 
			this->help_MenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->howToDoToolStripMenuItem, 
				this->onlineToolStripMenuItem, this->help_about_MenuItem});
			this->help_MenuItem->Name = L"help_MenuItem";
			this->help_MenuItem->Size = System::Drawing::Size(44, 20);
			this->help_MenuItem->Text = L"Help";
			// 
			// howToDoToolStripMenuItem
			// 
			this->howToDoToolStripMenuItem->Name = L"howToDoToolStripMenuItem";
			this->howToDoToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->howToDoToolStripMenuItem->Text = L"How to do";
			// 
			// onlineToolStripMenuItem
			// 
			this->onlineToolStripMenuItem->Name = L"onlineToolStripMenuItem";
			this->onlineToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->onlineToolStripMenuItem->Text = L"Online";
			// 
			// help_about_MenuItem
			// 
			this->help_about_MenuItem->Name = L"help_about_MenuItem";
			this->help_about_MenuItem->Size = System::Drawing::Size(152, 22);
			this->help_about_MenuItem->Text = L"About";
			this->help_about_MenuItem->Click += gcnew System::EventHandler(this, &view_fly_arm::help_about_MenuItem_Click);
			// 
			// graph_x_thrust_time_label
			// 
			this->graph_x_thrust_time_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_x_thrust_time_label->AutoSize = true;
			this->graph_x_thrust_time_label->BackColor = System::Drawing::Color::White;
			this->graph_x_thrust_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->graph_x_thrust_time_label->ForeColor = System::Drawing::Color::Teal;
			this->graph_x_thrust_time_label->Location = System::Drawing::Point(1398, 355);
			this->graph_x_thrust_time_label->Name = L"graph_x_thrust_time_label";
			this->graph_x_thrust_time_label->Size = System::Drawing::Size(78, 17);
			this->graph_x_thrust_time_label->TabIndex = 51;
			this->graph_x_thrust_time_label->Text = L"Time ( s )";
			// 
			// graph_thrust_value_label
			// 
			this->graph_thrust_value_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_thrust_value_label->AutoSize = true;
			this->graph_thrust_value_label->BackColor = System::Drawing::Color::Black;
			this->graph_thrust_value_label->ForeColor = System::Drawing::Color::White;
			this->graph_thrust_value_label->Location = System::Drawing::Point(1442, 256);
			this->graph_thrust_value_label->MaximumSize = System::Drawing::Size(50, 15);
			this->graph_thrust_value_label->Name = L"graph_thrust_value_label";
			this->graph_thrust_value_label->Size = System::Drawing::Size(22, 13);
			this->graph_thrust_value_label->TabIndex = 50;
			this->graph_thrust_value_label->Text = L"0.0";
			// 
			// graph_x_theta_time_label
			// 
			this->graph_x_theta_time_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_x_theta_time_label->AutoSize = true;
			this->graph_x_theta_time_label->BackColor = System::Drawing::Color::White;
			this->graph_x_theta_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->graph_x_theta_time_label->ForeColor = System::Drawing::Color::Teal;
			this->graph_x_theta_time_label->Location = System::Drawing::Point(1398, 176);
			this->graph_x_theta_time_label->Name = L"graph_x_theta_time_label";
			this->graph_x_theta_time_label->Size = System::Drawing::Size(78, 17);
			this->graph_x_theta_time_label->TabIndex = 48;
			this->graph_x_theta_time_label->Text = L"Time ( s )";
			// 
			// graph_theta_value_label
			// 
			this->graph_theta_value_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_theta_value_label->AutoSize = true;
			this->graph_theta_value_label->BackColor = System::Drawing::Color::Black;
			this->graph_theta_value_label->ForeColor = System::Drawing::Color::White;
			this->graph_theta_value_label->Location = System::Drawing::Point(1442, 76);
			this->graph_theta_value_label->MaximumSize = System::Drawing::Size(50, 15);
			this->graph_theta_value_label->Name = L"graph_theta_value_label";
			this->graph_theta_value_label->Size = System::Drawing::Size(22, 13);
			this->graph_theta_value_label->TabIndex = 47;
			this->graph_theta_value_label->Text = L"0.0";
			// 
			// terminal_panel
			// 
			this->terminal_panel->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->terminal_panel->BackColor = System::Drawing::Color::White;
			this->terminal_panel->Controls->Add(this->consol_panel);
			this->terminal_panel->Controls->Add(this->com_port_radioButton);
			this->terminal_panel->Controls->Add(this->usb_port_radioButton);
			this->terminal_panel->Controls->Add(this->terminal_signal_value_label);
			this->terminal_panel->Controls->Add(this->baud_rate_label);
			this->terminal_panel->Controls->Add(this->baud_rate_comboBox);
			this->terminal_panel->Controls->Add(this->signal_value_progressBar);
			this->terminal_panel->Controls->Add(this->com_port_comboBox);
			this->terminal_panel->Controls->Add(this->disconnect_button);
			this->terminal_panel->Controls->Add(this->connect_button);
			this->terminal_panel->Controls->Add(this->terminal_groupBox);
			this->terminal_panel->Controls->Add(this->status_groupBox);
			this->terminal_panel->Location = System::Drawing::Point(0, 648);
			this->terminal_panel->Name = L"terminal_panel";
			this->terminal_panel->Size = System::Drawing::Size(720, 96);
			this->terminal_panel->TabIndex = 53;
			this->terminal_panel->Visible = false;
			// 
			// consol_panel
			// 
			this->consol_panel->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->consol_panel->BackColor = System::Drawing::Color::Black;
			this->consol_panel->Controls->Add(this->consol_panel_panel);
			this->consol_panel->Controls->Add(this->consol_label);
			this->consol_panel->Location = System::Drawing::Point(5, 6);
			this->consol_panel->Name = L"consol_panel";
			this->consol_panel->Size = System::Drawing::Size(77, 24);
			this->consol_panel->TabIndex = 54;
			this->consol_panel->Visible = false;
			// 
			// consol_panel_panel
			// 
			this->consol_panel_panel->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->consol_panel_panel->BackColor = System::Drawing::Color::Red;
			this->consol_panel_panel->Location = System::Drawing::Point(10, 10);
			this->consol_panel_panel->Name = L"consol_panel_panel";
			this->consol_panel_panel->Size = System::Drawing::Size(25, 2);
			this->consol_panel_panel->TabIndex = 55;
			this->consol_panel_panel->Visible = false;
			// 
			// consol_label
			// 
			this->consol_label->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->consol_label->AutoSize = true;
			this->consol_label->BackColor = System::Drawing::Color::Black;
			this->consol_label->ForeColor = System::Drawing::Color::White;
			this->consol_label->Location = System::Drawing::Point(38, 5);
			this->consol_label->Name = L"consol_label";
			this->consol_label->Size = System::Drawing::Size(39, 13);
			this->consol_label->TabIndex = 54;
			this->consol_label->Text = L"Consol";
			// 
			// com_port_radioButton
			// 
			this->com_port_radioButton->AutoSize = true;
			this->com_port_radioButton->Checked = true;
			this->com_port_radioButton->Location = System::Drawing::Point(5, 54);
			this->com_port_radioButton->Name = L"com_port_radioButton";
			this->com_port_radioButton->Size = System::Drawing::Size(71, 17);
			this->com_port_radioButton->TabIndex = 93;
			this->com_port_radioButton->TabStop = true;
			this->com_port_radioButton->Text = L"COM Port";
			this->com_port_radioButton->UseVisualStyleBackColor = true;
			this->com_port_radioButton->Click += gcnew System::EventHandler(this, &view_fly_arm::com_port_radioButton_Click);
			// 
			// usb_port_radioButton
			// 
			this->usb_port_radioButton->AutoSize = true;
			this->usb_port_radioButton->Location = System::Drawing::Point(5, 34);
			this->usb_port_radioButton->Name = L"usb_port_radioButton";
			this->usb_port_radioButton->Size = System::Drawing::Size(69, 17);
			this->usb_port_radioButton->TabIndex = 92;
			this->usb_port_radioButton->TabStop = true;
			this->usb_port_radioButton->Text = L"USB Port";
			this->usb_port_radioButton->UseVisualStyleBackColor = true;
			this->usb_port_radioButton->Click += gcnew System::EventHandler(this, &view_fly_arm::usb_port_radioButton_Click);
			// 
			// terminal_signal_value_label
			// 
			this->terminal_signal_value_label->AutoSize = true;
			this->terminal_signal_value_label->BackColor = System::Drawing::Color::White;
			this->terminal_signal_value_label->ForeColor = System::Drawing::Color::Black;
			this->terminal_signal_value_label->Location = System::Drawing::Point(85, 12);
			this->terminal_signal_value_label->Name = L"terminal_signal_value_label";
			this->terminal_signal_value_label->Size = System::Drawing::Size(0, 13);
			this->terminal_signal_value_label->TabIndex = 1;
			this->terminal_signal_value_label->Visible = false;
			// 
			// baud_rate_label
			// 
			this->baud_rate_label->AutoSize = true;
			this->baud_rate_label->Location = System::Drawing::Point(9, 75);
			this->baud_rate_label->Name = L"baud_rate_label";
			this->baud_rate_label->Size = System::Drawing::Size(58, 13);
			this->baud_rate_label->TabIndex = 94;
			this->baud_rate_label->Text = L"Baud Rate";
			// 
			// baud_rate_comboBox
			// 
			this->baud_rate_comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->baud_rate_comboBox->FormattingEnabled = true;
			this->baud_rate_comboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"9600", L"19200", L"115200"});
			this->baud_rate_comboBox->Location = System::Drawing::Point(77, 67);
			this->baud_rate_comboBox->Name = L"baud_rate_comboBox";
			this->baud_rate_comboBox->Size = System::Drawing::Size(72, 21);
			this->baud_rate_comboBox->TabIndex = 90;
			this->baud_rate_comboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &view_fly_arm::baud_rate_comboBox_SelectedIndexChanged);
			// 
			// signal_value_progressBar
			// 
			this->signal_value_progressBar->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->signal_value_progressBar->Location = System::Drawing::Point(186, 7);
			this->signal_value_progressBar->MarqueeAnimationSpeed = 1023;
			this->signal_value_progressBar->Maximum = 1023;
			this->signal_value_progressBar->Name = L"signal_value_progressBar";
			this->signal_value_progressBar->Size = System::Drawing::Size(120, 23);
			this->signal_value_progressBar->TabIndex = 57;
			// 
			// com_port_comboBox
			// 
			this->com_port_comboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->com_port_comboBox->FormattingEnabled = true;
			this->com_port_comboBox->Location = System::Drawing::Point(77, 38);
			this->com_port_comboBox->Name = L"com_port_comboBox";
			this->com_port_comboBox->Size = System::Drawing::Size(72, 21);
			this->com_port_comboBox->Sorted = true;
			this->com_port_comboBox->TabIndex = 89;
			this->com_port_comboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &view_fly_arm::com_port_comboBox_SelectedIndexChanged);
			this->com_port_comboBox->Click += gcnew System::EventHandler(this, &view_fly_arm::com_port_comboBox_Click);
			// 
			// disconnect_button
			// 
			this->disconnect_button->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->disconnect_button->Enabled = false;
			this->disconnect_button->Location = System::Drawing::Point(153, 67);
			this->disconnect_button->Name = L"disconnect_button";
			this->disconnect_button->Size = System::Drawing::Size(75, 23);
			this->disconnect_button->TabIndex = 56;
			this->disconnect_button->Text = L"Disconnect";
			this->disconnect_button->UseVisualStyleBackColor = true;
			this->disconnect_button->Visible = false;
			this->disconnect_button->Click += gcnew System::EventHandler(this, &view_fly_arm::disconnect_button_Click);
			// 
			// connect_button
			// 
			this->connect_button->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->connect_button->Enabled = false;
			this->connect_button->Location = System::Drawing::Point(153, 38);
			this->connect_button->Name = L"connect_button";
			this->connect_button->Size = System::Drawing::Size(75, 23);
			this->connect_button->TabIndex = 55;
			this->connect_button->Text = L"Connect";
			this->connect_button->UseVisualStyleBackColor = true;
			this->connect_button->Visible = false;
			this->connect_button->Click += gcnew System::EventHandler(this, &view_fly_arm::connect_button_Click);
			// 
			// terminal_groupBox
			// 
			this->terminal_groupBox->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->terminal_groupBox->BackColor = System::Drawing::Color::Black;
			this->terminal_groupBox->Controls->Add(this->terminal_info_label);
			this->terminal_groupBox->ForeColor = System::Drawing::Color::White;
			this->terminal_groupBox->Location = System::Drawing::Point(312, 7);
			this->terminal_groupBox->Name = L"terminal_groupBox";
			this->terminal_groupBox->Size = System::Drawing::Size(405, 83);
			this->terminal_groupBox->TabIndex = 1;
			this->terminal_groupBox->TabStop = false;
			this->terminal_groupBox->Text = L"Terminal";
			this->terminal_groupBox->Visible = false;
			// 
			// terminal_info_label
			// 
			this->terminal_info_label->AutoSize = true;
			this->terminal_info_label->Location = System::Drawing::Point(6, 13);
			this->terminal_info_label->Name = L"terminal_info_label";
			this->terminal_info_label->Size = System::Drawing::Size(87, 13);
			this->terminal_info_label->TabIndex = 0;
			this->terminal_info_label->Text = L"Press connect ...";
			this->terminal_info_label->Visible = false;
			// 
			// status_groupBox
			// 
			this->status_groupBox->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->status_groupBox->Controls->Add(this->status_panel);
			this->status_groupBox->Controls->Add(this->status_label);
			this->status_groupBox->Location = System::Drawing::Point(232, 33);
			this->status_groupBox->Name = L"status_groupBox";
			this->status_groupBox->Size = System::Drawing::Size(73, 57);
			this->status_groupBox->TabIndex = 0;
			this->status_groupBox->TabStop = false;
			this->status_groupBox->Text = L"Status";
			this->status_groupBox->Visible = false;
			// 
			// status_panel
			// 
			this->status_panel->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->status_panel->BackColor = System::Drawing::Color::Red;
			this->status_panel->Location = System::Drawing::Point(13, 12);
			this->status_panel->Name = L"status_panel";
			this->status_panel->Size = System::Drawing::Size(45, 26);
			this->status_panel->TabIndex = 3;
			// 
			// status_label
			// 
			this->status_label->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->status_label->AutoSize = true;
			this->status_label->Location = System::Drawing::Point(10, 41);
			this->status_label->Name = L"status_label";
			this->status_label->Size = System::Drawing::Size(61, 13);
			this->status_label->TabIndex = 2;
			this->status_label->Text = L"Disconnect";
			this->status_label->Visible = false;
			// 
			// theta_label
			// 
			this->theta_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->theta_label->AutoSize = true;
			this->theta_label->BackColor = System::Drawing::Color::Black;
			this->theta_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->theta_label->ForeColor = System::Drawing::Color::White;
			this->theta_label->Location = System::Drawing::Point(554, 116);
			this->theta_label->Name = L"theta_label";
			this->theta_label->Size = System::Drawing::Size(57, 17);
			this->theta_label->TabIndex = 58;
			this->theta_label->Text = L"Theta : ";
			this->theta_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// thrust_label
			// 
			this->thrust_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->thrust_label->AutoSize = true;
			this->thrust_label->BackColor = System::Drawing::Color::Black;
			this->thrust_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->thrust_label->ForeColor = System::Drawing::Color::White;
			this->thrust_label->Location = System::Drawing::Point(554, 136);
			this->thrust_label->Name = L"thrust_label";
			this->thrust_label->Size = System::Drawing::Size(61, 17);
			this->thrust_label->TabIndex = 59;
			this->thrust_label->Text = L"Thrust : ";
			this->thrust_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// thrust_value_label
			// 
			this->thrust_value_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->thrust_value_label->BackColor = System::Drawing::Color::Black;
			this->thrust_value_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->thrust_value_label->ForeColor = System::Drawing::Color::White;
			this->thrust_value_label->Location = System::Drawing::Point(612, 136);
			this->thrust_value_label->Name = L"thrust_value_label";
			this->thrust_value_label->Size = System::Drawing::Size(70, 17);
			this->thrust_value_label->TabIndex = 60;
			this->thrust_value_label->Text = L"0.0";
			this->thrust_value_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// theta_value_label
			// 
			this->theta_value_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->theta_value_label->BackColor = System::Drawing::Color::Black;
			this->theta_value_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->theta_value_label->ForeColor = System::Drawing::Color::White;
			this->theta_value_label->Location = System::Drawing::Point(612, 116);
			this->theta_value_label->Name = L"theta_value_label";
			this->theta_value_label->Size = System::Drawing::Size(70, 17);
			this->theta_value_label->TabIndex = 61;
			this->theta_value_label->Text = L"0.0";
			this->theta_value_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// mode_label
			// 
			this->mode_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->mode_label->BackColor = System::Drawing::Color::Lime;
			this->mode_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->mode_label->ForeColor = System::Drawing::SystemColors::ControlText;
			this->mode_label->Location = System::Drawing::Point(534, 33);
			this->mode_label->Name = L"mode_label";
			this->mode_label->Size = System::Drawing::Size(186, 23);
			this->mode_label->TabIndex = 63;
			this->mode_label->Text = L"Mode:";
			this->mode_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// play_button
			// 
			this->play_button->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->play_button->Enabled = false;
			this->play_button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"play_button.Image")));
			this->play_button->Location = System::Drawing::Point(550, 59);
			this->play_button->Name = L"play_button";
			this->play_button->Size = System::Drawing::Size(52, 28);
			this->play_button->TabIndex = 64;
			this->play_button->UseVisualStyleBackColor = true;
			this->play_button->Click += gcnew System::EventHandler(this, &view_fly_arm::play_button_Click);
			// 
			// pause_button
			// 
			this->pause_button->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->pause_button->Enabled = false;
			this->pause_button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pause_button.Image")));
			this->pause_button->Location = System::Drawing::Point(601, 59);
			this->pause_button->Name = L"pause_button";
			this->pause_button->Size = System::Drawing::Size(52, 28);
			this->pause_button->TabIndex = 65;
			this->pause_button->UseVisualStyleBackColor = true;
			this->pause_button->Click += gcnew System::EventHandler(this, &view_fly_arm::pause_button_Click);
			// 
			// stop_button
			// 
			this->stop_button->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->stop_button->Enabled = false;
			this->stop_button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"stop_button.Image")));
			this->stop_button->Location = System::Drawing::Point(652, 59);
			this->stop_button->Name = L"stop_button";
			this->stop_button->Size = System::Drawing::Size(52, 28);
			this->stop_button->TabIndex = 66;
			this->stop_button->UseVisualStyleBackColor = true;
			this->stop_button->Click += gcnew System::EventHandler(this, &view_fly_arm::stop_button_Click);
			// 
			// time_label
			// 
			this->time_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->time_label->AutoSize = true;
			this->time_label->BackColor = System::Drawing::Color::Black;
			this->time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->time_label->ForeColor = System::Drawing::Color::White;
			this->time_label->Location = System::Drawing::Point(552, 95);
			this->time_label->Name = L"time_label";
			this->time_label->Size = System::Drawing::Size(59, 17);
			this->time_label->TabIndex = 68;
			this->time_label->Text = L"Time   : ";
			this->time_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// time_textBox
			// 
			this->time_textBox->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->time_textBox->BackColor = System::Drawing::Color::Black;
			this->time_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->time_textBox->ForeColor = System::Drawing::Color::White;
			this->time_textBox->Location = System::Drawing::Point(613, 92);
			this->time_textBox->Name = L"time_textBox";
			this->time_textBox->Size = System::Drawing::Size(59, 23);
			this->time_textBox->TabIndex = 70;
			this->time_textBox->TextChanged += gcnew System::EventHandler(this, &view_fly_arm::time_textBox_textChanged);
			// 
			// theta_OR_thrust_desired_label
			// 
			this->theta_OR_thrust_desired_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->theta_OR_thrust_desired_label->AutoSize = true;
			this->theta_OR_thrust_desired_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->theta_OR_thrust_desired_label->ForeColor = System::Drawing::Color::White;
			this->theta_OR_thrust_desired_label->Location = System::Drawing::Point(555, 156);
			this->theta_OR_thrust_desired_label->Name = L"theta_OR_thrust_desired_label";
			this->theta_OR_thrust_desired_label->Size = System::Drawing::Size(110, 17);
			this->theta_OR_thrust_desired_label->TabIndex = 40;
			this->theta_OR_thrust_desired_label->Text = L"Desired Theta : ";
			this->theta_OR_thrust_desired_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->theta_OR_thrust_desired_label->Visible = false;
			// 
			// theta_OR_thrust_desired_value_label
			// 
			this->theta_OR_thrust_desired_value_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->theta_OR_thrust_desired_value_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->theta_OR_thrust_desired_value_label->ForeColor = System::Drawing::Color::White;
			this->theta_OR_thrust_desired_value_label->Location = System::Drawing::Point(659, 157);
			this->theta_OR_thrust_desired_value_label->Name = L"theta_OR_thrust_desired_value_label";
			this->theta_OR_thrust_desired_value_label->Size = System::Drawing::Size(32, 17);
			this->theta_OR_thrust_desired_value_label->TabIndex = 45;
			this->theta_OR_thrust_desired_value_label->Text = L"180";
			this->theta_OR_thrust_desired_value_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->theta_OR_thrust_desired_value_label->Visible = false;
			// 
			// time_unite_label
			// 
			this->time_unite_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->time_unite_label->AutoSize = true;
			this->time_unite_label->BackColor = System::Drawing::Color::Black;
			this->time_unite_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->time_unite_label->ForeColor = System::Drawing::Color::White;
			this->time_unite_label->Location = System::Drawing::Point(687, 95);
			this->time_unite_label->Name = L"time_unite_label";
			this->time_unite_label->Size = System::Drawing::Size(15, 17);
			this->time_unite_label->TabIndex = 71;
			this->time_unite_label->Text = L"s";
			this->time_unite_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// thrust_unite_label
			// 
			this->thrust_unite_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->thrust_unite_label->AutoSize = true;
			this->thrust_unite_label->BackColor = System::Drawing::Color::Black;
			this->thrust_unite_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->thrust_unite_label->ForeColor = System::Drawing::Color::White;
			this->thrust_unite_label->Location = System::Drawing::Point(687, 136);
			this->thrust_unite_label->Name = L"thrust_unite_label";
			this->thrust_unite_label->Size = System::Drawing::Size(18, 17);
			this->thrust_unite_label->TabIndex = 72;
			this->thrust_unite_label->Text = L"N";
			this->thrust_unite_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// theta_unite_label
			// 
			this->theta_unite_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->theta_unite_label->AutoSize = true;
			this->theta_unite_label->BackColor = System::Drawing::Color::Black;
			this->theta_unite_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->theta_unite_label->ForeColor = System::Drawing::Color::White;
			this->theta_unite_label->Location = System::Drawing::Point(687, 116);
			this->theta_unite_label->Name = L"theta_unite_label";
			this->theta_unite_label->Size = System::Drawing::Size(32, 17);
			this->theta_unite_label->TabIndex = 73;
			this->theta_unite_label->Text = L"deg";
			this->theta_unite_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// theta_desired_unite_label
			// 
			this->theta_desired_unite_label->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->theta_desired_unite_label->AutoSize = true;
			this->theta_desired_unite_label->BackColor = System::Drawing::Color::Black;
			this->theta_desired_unite_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->theta_desired_unite_label->ForeColor = System::Drawing::Color::White;
			this->theta_desired_unite_label->Location = System::Drawing::Point(687, 157);
			this->theta_desired_unite_label->Name = L"theta_desired_unite_label";
			this->theta_desired_unite_label->Size = System::Drawing::Size(32, 17);
			this->theta_desired_unite_label->TabIndex = 74;
			this->theta_desired_unite_label->Text = L"deg";
			this->theta_desired_unite_label->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->theta_desired_unite_label->Visible = false;
			// 
			// angle_unite_listBox
			// 
			this->angle_unite_listBox->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->angle_unite_listBox->BackColor = System::Drawing::Color::White;
			this->angle_unite_listBox->DisplayMember = L"0";
			this->angle_unite_listBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
			this->angle_unite_listBox->ForeColor = System::Drawing::Color::Green;
			this->angle_unite_listBox->FormattingEnabled = true;
			this->angle_unite_listBox->ItemHeight = 16;
			this->angle_unite_listBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"deg", L"rad"});
			this->angle_unite_listBox->Location = System::Drawing::Point(794, 15);
			this->angle_unite_listBox->Name = L"angle_unite_listBox";
			this->angle_unite_listBox->Size = System::Drawing::Size(60, 20);
			this->angle_unite_listBox->TabIndex = 75;
			// 
			// graph_theta_dot
			// 
			this->graph_theta_dot->BackImageTransparentColor = System::Drawing::Color::Black;
			this->graph_theta_dot->BackSecondaryColor = System::Drawing::Color::Black;
			this->graph_theta_dot->BorderlineColor = System::Drawing::Color::Black;
			this->graph_theta_dot->BorderSkin->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_theta_dot->BorderSkin->BackHatchStyle = System::Windows::Forms::DataVisualization::Charting::ChartHatchStyle::Cross;
			this->graph_theta_dot->BorderSkin->BackSecondaryColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_theta_dot->BorderSkin->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_theta_dot->BorderSkin->PageColor = System::Drawing::Color::Yellow;
			chartArea3->BackImageTransparentColor = System::Drawing::Color::Transparent;
			chartArea3->BackSecondaryColor = System::Drawing::Color::Black;
			chartArea3->Name = L"ChartArea1";
			this->graph_theta_dot->ChartAreas->Add(chartArea3);
			legend3->BackColor = System::Drawing::Color::Black;
			legend3->BackSecondaryColor = System::Drawing::Color::Yellow;
			legend3->BorderColor = System::Drawing::Color::Transparent;
			legend3->ForeColor = System::Drawing::Color::White;
			legend3->HeaderSeparatorColor = System::Drawing::Color::Yellow;
			legend3->InterlacedRowsColor = System::Drawing::Color::White;
			legend3->ItemColumnSeparatorColor = System::Drawing::Color::Yellow;
			legend3->Name = L"Legend1";
			legend3->ShadowColor = System::Drawing::Color::Yellow;
			legend3->TitleBackColor = System::Drawing::Color::Yellow;
			legend3->TitleForeColor = System::Drawing::Color::Yellow;
			legend3->TitleSeparatorColor = System::Drawing::Color::Yellow;
			this->graph_theta_dot->Legends->Add(legend3);
			this->graph_theta_dot->Location = System::Drawing::Point(726, 384);
			this->graph_theta_dot->Name = L"graph_theta_dot";
			series3->BackImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			series3->BackSecondaryColor = System::Drawing::Color::Yellow;
			series3->BorderColor = System::Drawing::Color::Yellow;
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Color = System::Drawing::Color::Red;
			series3->EmptyPointStyle->BackSecondaryColor = System::Drawing::Color::Yellow;
			series3->EmptyPointStyle->BorderColor = System::Drawing::Color::Yellow;
			series3->EmptyPointStyle->Color = System::Drawing::Color::Yellow;
			series3->EmptyPointStyle->LabelBackColor = System::Drawing::Color::Yellow;
			series3->EmptyPointStyle->LabelBorderColor = System::Drawing::Color::Yellow;
			series3->EmptyPointStyle->LabelForeColor = System::Drawing::Color::Yellow;
			series3->EmptyPointStyle->MarkerBorderColor = System::Drawing::Color::Yellow;
			series3->EmptyPointStyle->MarkerColor = System::Drawing::Color::Yellow;
			series3->EmptyPointStyle->MarkerImageTransparentColor = System::Drawing::Color::Yellow;
			series3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			series3->LabelBackColor = System::Drawing::Color::Yellow;
			series3->LabelBorderColor = System::Drawing::Color::Yellow;
			series3->LabelForeColor = System::Drawing::Color::Yellow;
			series3->Legend = L"Legend1";
			series3->MarkerBorderColor = System::Drawing::Color::Red;
			series3->MarkerColor = System::Drawing::Color::Maroon;
			series3->MarkerImageTransparentColor = System::Drawing::Color::Black;
			series3->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series3->Name = L"T3";
			series3->SmartLabelStyle->CalloutBackColor = System::Drawing::Color::Yellow;
			series3->SmartLabelStyle->CalloutLineColor = System::Drawing::Color::Yellow;
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Color = System::Drawing::Color::Blue;
			series4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			series4->Legend = L"Legend1";
			series4->MarkerBorderColor = System::Drawing::Color::Blue;
			series4->MarkerColor = System::Drawing::Color::Blue;
			series4->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series4->Name = L"T5";
			this->graph_theta_dot->Series->Add(series3);
			this->graph_theta_dot->Series->Add(series4);
			this->graph_theta_dot->Size = System::Drawing::Size(778, 180);
			this->graph_theta_dot->TabIndex = 76;
			this->graph_theta_dot->Text = L"graph_theta_dot";
			// 
			// graph_theta_dotdot
			// 
			this->graph_theta_dotdot->BackImageTransparentColor = System::Drawing::Color::Black;
			this->graph_theta_dotdot->BackSecondaryColor = System::Drawing::Color::Black;
			this->graph_theta_dotdot->BorderlineColor = System::Drawing::Color::Black;
			this->graph_theta_dotdot->BorderSkin->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_theta_dotdot->BorderSkin->BackHatchStyle = System::Windows::Forms::DataVisualization::Charting::ChartHatchStyle::Cross;
			this->graph_theta_dotdot->BorderSkin->BackSecondaryColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_theta_dotdot->BorderSkin->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->graph_theta_dotdot->BorderSkin->PageColor = System::Drawing::Color::Yellow;
			chartArea4->BackImageTransparentColor = System::Drawing::Color::Transparent;
			chartArea4->BackSecondaryColor = System::Drawing::Color::Black;
			chartArea4->Name = L"ChartArea1";
			this->graph_theta_dotdot->ChartAreas->Add(chartArea4);
			legend4->BackColor = System::Drawing::Color::Black;
			legend4->BackSecondaryColor = System::Drawing::Color::Yellow;
			legend4->BorderColor = System::Drawing::Color::Transparent;
			legend4->ForeColor = System::Drawing::Color::White;
			legend4->HeaderSeparatorColor = System::Drawing::Color::Yellow;
			legend4->InterlacedRowsColor = System::Drawing::Color::White;
			legend4->ItemColumnSeparatorColor = System::Drawing::Color::Yellow;
			legend4->Name = L"Legend1";
			legend4->ShadowColor = System::Drawing::Color::Yellow;
			legend4->TitleBackColor = System::Drawing::Color::Yellow;
			legend4->TitleForeColor = System::Drawing::Color::Yellow;
			legend4->TitleSeparatorColor = System::Drawing::Color::Yellow;
			this->graph_theta_dotdot->Legends->Add(legend4);
			this->graph_theta_dotdot->Location = System::Drawing::Point(726, 564);
			this->graph_theta_dotdot->Name = L"graph_theta_dotdot";
			series5->BackImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			series5->BackSecondaryColor = System::Drawing::Color::Yellow;
			series5->BorderColor = System::Drawing::Color::Yellow;
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series5->Color = System::Drawing::Color::Red;
			series5->EmptyPointStyle->BackSecondaryColor = System::Drawing::Color::Yellow;
			series5->EmptyPointStyle->BorderColor = System::Drawing::Color::Yellow;
			series5->EmptyPointStyle->Color = System::Drawing::Color::Yellow;
			series5->EmptyPointStyle->LabelBackColor = System::Drawing::Color::Yellow;
			series5->EmptyPointStyle->LabelBorderColor = System::Drawing::Color::Yellow;
			series5->EmptyPointStyle->LabelForeColor = System::Drawing::Color::Yellow;
			series5->EmptyPointStyle->MarkerBorderColor = System::Drawing::Color::Yellow;
			series5->EmptyPointStyle->MarkerColor = System::Drawing::Color::Yellow;
			series5->EmptyPointStyle->MarkerImageTransparentColor = System::Drawing::Color::Yellow;
			series5->LabelBackColor = System::Drawing::Color::Yellow;
			series5->LabelBorderColor = System::Drawing::Color::Yellow;
			series5->LabelForeColor = System::Drawing::Color::Yellow;
			series5->Legend = L"Legend1";
			series5->MarkerBorderColor = System::Drawing::Color::Red;
			series5->MarkerColor = System::Drawing::Color::Maroon;
			series5->MarkerImageTransparentColor = System::Drawing::Color::Black;
			series5->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series5->Name = L"T4";
			series5->SmartLabelStyle->CalloutBackColor = System::Drawing::Color::Yellow;
			series5->SmartLabelStyle->CalloutLineColor = System::Drawing::Color::Yellow;
			this->graph_theta_dotdot->Series->Add(series5);
			this->graph_theta_dotdot->Size = System::Drawing::Size(778, 180);
			this->graph_theta_dotdot->TabIndex = 77;
			this->graph_theta_dotdot->Text = L"graph_theta_dotdot";
			// 
			// graph_theta_time_label
			// 
			this->graph_theta_time_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_theta_time_label->BackColor = System::Drawing::Color::Black;
			this->graph_theta_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->graph_theta_time_label->ForeColor = System::Drawing::Color::White;
			this->graph_theta_time_label->Location = System::Drawing::Point(1399, 29);
			this->graph_theta_time_label->Name = L"graph_theta_time_label";
			this->graph_theta_time_label->Size = System::Drawing::Size(96, 38);
			this->graph_theta_time_label->TabIndex = 78;
			this->graph_theta_time_label->Text = L"Theta\r\nTime";
			this->graph_theta_time_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// graph_thrust_time_label
			// 
			this->graph_thrust_time_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_thrust_time_label->BackColor = System::Drawing::Color::Black;
			this->graph_thrust_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->graph_thrust_time_label->ForeColor = System::Drawing::Color::White;
			this->graph_thrust_time_label->Location = System::Drawing::Point(1399, 209);
			this->graph_thrust_time_label->Name = L"graph_thrust_time_label";
			this->graph_thrust_time_label->Size = System::Drawing::Size(96, 38);
			this->graph_thrust_time_label->TabIndex = 79;
			this->graph_thrust_time_label->Text = L"Thrust\r\nTime";
			this->graph_thrust_time_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// graph_theta_dotdot_time_label
			// 
			this->graph_theta_dotdot_time_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_theta_dotdot_time_label->BackColor = System::Drawing::Color::Black;
			this->graph_theta_dotdot_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->graph_theta_dotdot_time_label->ForeColor = System::Drawing::Color::White;
			this->graph_theta_dotdot_time_label->Location = System::Drawing::Point(1399, 569);
			this->graph_theta_dotdot_time_label->Name = L"graph_theta_dotdot_time_label";
			this->graph_theta_dotdot_time_label->Size = System::Drawing::Size(96, 38);
			this->graph_theta_dotdot_time_label->TabIndex = 80;
			this->graph_theta_dotdot_time_label->Text = L"Theta DotDot\r\nTime";
			this->graph_theta_dotdot_time_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// graph_theta_dot_time_label
			// 
			this->graph_theta_dot_time_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_theta_dot_time_label->BackColor = System::Drawing::Color::Black;
			this->graph_theta_dot_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->graph_theta_dot_time_label->ForeColor = System::Drawing::Color::White;
			this->graph_theta_dot_time_label->Location = System::Drawing::Point(1399, 389);
			this->graph_theta_dot_time_label->Name = L"graph_theta_dot_time_label";
			this->graph_theta_dot_time_label->Size = System::Drawing::Size(96, 38);
			this->graph_theta_dot_time_label->TabIndex = 81;
			this->graph_theta_dot_time_label->Text = L"Theta Dot\r\nTime";
			this->graph_theta_dot_time_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// graph_x_theta_dot_time_label
			// 
			this->graph_x_theta_dot_time_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_x_theta_dot_time_label->AutoSize = true;
			this->graph_x_theta_dot_time_label->BackColor = System::Drawing::Color::White;
			this->graph_x_theta_dot_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->graph_x_theta_dot_time_label->ForeColor = System::Drawing::Color::Teal;
			this->graph_x_theta_dot_time_label->Location = System::Drawing::Point(1398, 536);
			this->graph_x_theta_dot_time_label->Name = L"graph_x_theta_dot_time_label";
			this->graph_x_theta_dot_time_label->Size = System::Drawing::Size(78, 17);
			this->graph_x_theta_dot_time_label->TabIndex = 82;
			this->graph_x_theta_dot_time_label->Text = L"Time ( s )";
			// 
			// graph_x_theta_dotdot_time_label
			// 
			this->graph_x_theta_dotdot_time_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_x_theta_dotdot_time_label->AutoSize = true;
			this->graph_x_theta_dotdot_time_label->BackColor = System::Drawing::Color::White;
			this->graph_x_theta_dotdot_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->graph_x_theta_dotdot_time_label->ForeColor = System::Drawing::Color::Teal;
			this->graph_x_theta_dotdot_time_label->Location = System::Drawing::Point(1398, 717);
			this->graph_x_theta_dotdot_time_label->Name = L"graph_x_theta_dotdot_time_label";
			this->graph_x_theta_dotdot_time_label->Size = System::Drawing::Size(78, 17);
			this->graph_x_theta_dotdot_time_label->TabIndex = 83;
			this->graph_x_theta_dotdot_time_label->Text = L"Time ( s )";
			// 
			// graph_theta_dot_value_label
			// 
			this->graph_theta_dot_value_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_theta_dot_value_label->AutoSize = true;
			this->graph_theta_dot_value_label->BackColor = System::Drawing::Color::Black;
			this->graph_theta_dot_value_label->ForeColor = System::Drawing::Color::White;
			this->graph_theta_dot_value_label->Location = System::Drawing::Point(1442, 436);
			this->graph_theta_dot_value_label->MaximumSize = System::Drawing::Size(50, 15);
			this->graph_theta_dot_value_label->Name = L"graph_theta_dot_value_label";
			this->graph_theta_dot_value_label->Size = System::Drawing::Size(22, 13);
			this->graph_theta_dot_value_label->TabIndex = 85;
			this->graph_theta_dot_value_label->Text = L"0.0";
			// 
			// graph_theta_dotdot_value_label
			// 
			this->graph_theta_dotdot_value_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_theta_dotdot_value_label->AutoSize = true;
			this->graph_theta_dotdot_value_label->BackColor = System::Drawing::Color::Black;
			this->graph_theta_dotdot_value_label->ForeColor = System::Drawing::Color::White;
			this->graph_theta_dotdot_value_label->Location = System::Drawing::Point(1442, 616);
			this->graph_theta_dotdot_value_label->MaximumSize = System::Drawing::Size(50, 15);
			this->graph_theta_dotdot_value_label->Name = L"graph_theta_dotdot_value_label";
			this->graph_theta_dotdot_value_label->Size = System::Drawing::Size(22, 13);
			this->graph_theta_dotdot_value_label->TabIndex = 87;
			this->graph_theta_dotdot_value_label->Text = L"0.0";
			// 
			// modes_panel
			// 
			this->modes_panel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->modes_panel->Location = System::Drawing::Point(525, 28);
			this->modes_panel->Name = L"modes_panel";
			this->modes_panel->Size = System::Drawing::Size(198, 128);
			this->modes_panel->TabIndex = 88;
			// 
			// graph_y_theta_dot_label
			// 
			this->graph_y_theta_dot_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->graph_y_theta_dot_label->AutoSize = true;
			this->graph_y_theta_dot_label->BackColor = System::Drawing::Color::White;
			this->graph_y_theta_dot_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->graph_y_theta_dot_label->ForeColor = System::Drawing::Color::Green;
			this->graph_y_theta_dot_label->Location = System::Drawing::Point(735, 372);
			this->graph_y_theta_dot_label->Name = L"graph_y_theta_dot_label";
			this->graph_y_theta_dot_label->Size = System::Drawing::Size(80, 17);
			this->graph_y_theta_dot_label->TabIndex = 89;
			this->graph_y_theta_dot_label->Text = L"Theta Dot";
			// 
			// graph_y_theta_dotdot_label
			// 
			this->graph_y_theta_dotdot_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->graph_y_theta_dotdot_label->AutoSize = true;
			this->graph_y_theta_dotdot_label->BackColor = System::Drawing::Color::White;
			this->graph_y_theta_dotdot_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->graph_y_theta_dotdot_label->ForeColor = System::Drawing::Color::Green;
			this->graph_y_theta_dotdot_label->Location = System::Drawing::Point(735, 553);
			this->graph_y_theta_dotdot_label->Name = L"graph_y_theta_dotdot_label";
			this->graph_y_theta_dotdot_label->Size = System::Drawing::Size(105, 17);
			this->graph_y_theta_dotdot_label->TabIndex = 90;
			this->graph_y_theta_dotdot_label->Text = L"Theta DotDot";
			// 
			// graph_theta_dot_controlleur_value_label
			// 
			this->graph_theta_dot_controlleur_value_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_theta_dot_controlleur_value_label->AutoSize = true;
			this->graph_theta_dot_controlleur_value_label->BackColor = System::Drawing::Color::Black;
			this->graph_theta_dot_controlleur_value_label->ForeColor = System::Drawing::Color::White;
			this->graph_theta_dot_controlleur_value_label->Location = System::Drawing::Point(1441, 510);
			this->graph_theta_dot_controlleur_value_label->MaximumSize = System::Drawing::Size(50, 15);
			this->graph_theta_dot_controlleur_value_label->Name = L"graph_theta_dot_controlleur_value_label";
			this->graph_theta_dot_controlleur_value_label->Size = System::Drawing::Size(22, 13);
			this->graph_theta_dot_controlleur_value_label->TabIndex = 92;
			this->graph_theta_dot_controlleur_value_label->Text = L"0.0";
			// 
			// graph_theta_dot_controlleur_time_label
			// 
			this->graph_theta_dot_controlleur_time_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_theta_dot_controlleur_time_label->BackColor = System::Drawing::Color::Black;
			this->graph_theta_dot_controlleur_time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->graph_theta_dot_controlleur_time_label->ForeColor = System::Drawing::Color::White;
			this->graph_theta_dot_controlleur_time_label->Location = System::Drawing::Point(1398, 463);
			this->graph_theta_dot_controlleur_time_label->Name = L"graph_theta_dot_controlleur_time_label";
			this->graph_theta_dot_controlleur_time_label->Size = System::Drawing::Size(96, 38);
			this->graph_theta_dot_controlleur_time_label->TabIndex = 91;
			this->graph_theta_dot_controlleur_time_label->Text = L"Theta Dot Controlleur";
			this->graph_theta_dot_controlleur_time_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// graph_theta_dot_color
			// 
			this->graph_theta_dot_color->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_theta_dot_color->BackColor = System::Drawing::Color::Red;
			this->graph_theta_dot_color->Location = System::Drawing::Point(1402, 429);
			this->graph_theta_dot_color->Name = L"graph_theta_dot_color";
			this->graph_theta_dot_color->Size = System::Drawing::Size(90, 5);
			this->graph_theta_dot_color->TabIndex = 93;
			// 
			// graph_theta_dot_controlleur_color
			// 
			this->graph_theta_dot_controlleur_color->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->graph_theta_dot_controlleur_color->BackColor = System::Drawing::Color::Blue;
			this->graph_theta_dot_controlleur_color->Location = System::Drawing::Point(1402, 503);
			this->graph_theta_dot_controlleur_color->Name = L"graph_theta_dot_controlleur_color";
			this->graph_theta_dot_controlleur_color->Size = System::Drawing::Size(90, 5);
			this->graph_theta_dot_controlleur_color->TabIndex = 94;
			// 
			// view_fly_arm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(1504, 744);
			this->Controls->Add(this->graph_y_theta_dotdot_label);
			this->Controls->Add(this->graph_theta_dot_controlleur_color);
			this->Controls->Add(this->graph_theta_dot_color);
			this->Controls->Add(this->graph_theta_dot_controlleur_value_label);
			this->Controls->Add(this->graph_theta_dot_controlleur_time_label);
			this->Controls->Add(this->graph_y_theta_dot_label);
			this->Controls->Add(this->theta_desired_unite_label);
			this->Controls->Add(this->theta_OR_thrust_desired_label);
			this->Controls->Add(this->theta_OR_thrust_desired_trackBar);
			this->Controls->Add(this->theta_OR_thrust_desired_value_label);
			this->Controls->Add(this->graph_theta_dot_value_label);
			this->Controls->Add(this->graph_theta_dotdot_value_label);
			this->Controls->Add(this->graph_x_theta_dot_time_label);
			this->Controls->Add(this->graph_x_theta_dotdot_time_label);
			this->Controls->Add(this->graph_theta_dot_time_label);
			this->Controls->Add(this->graph_theta_dotdot_time_label);
			this->Controls->Add(this->graph_thrust_time_label);
			this->Controls->Add(this->graph_theta_time_label);
			this->Controls->Add(this->angle_unite_listBox);
			this->Controls->Add(this->theta_unite_label);
			this->Controls->Add(this->thrust_unite_label);
			this->Controls->Add(this->time_unite_label);
			this->Controls->Add(this->time_textBox);
			this->Controls->Add(this->time_label);
			this->Controls->Add(this->graph_y_theta_label);
			this->Controls->Add(this->stop_button);
			this->Controls->Add(this->graph_x_theta_time_label);
			this->Controls->Add(this->pause_button);
			this->Controls->Add(this->graph_theta_value_label);
			this->Controls->Add(this->play_button);
			this->Controls->Add(this->mode_label);
			this->Controls->Add(this->menu);
			this->Controls->Add(this->theta_value_label);
			this->Controls->Add(this->thrust_value_label);
			this->Controls->Add(this->graph_x_thrust_time_label);
			this->Controls->Add(this->thrust_label);
			this->Controls->Add(this->theta_label);
			this->Controls->Add(this->graph_thrust_value_label);
			this->Controls->Add(this->graph_y_thrust_label);
			this->Controls->Add(this->graph_theta_dotdot);
			this->Controls->Add(this->graph_theta_dot);
			this->Controls->Add(this->graph_thrust);
			this->Controls->Add(this->graph_theta);
			this->Controls->Add(this->modes_panel);
			this->Controls->Add(this->terminal_panel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(1520, 780);
			this->Name = L"view_fly_arm";
			this->Text = L"Balancing Arm System";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &view_fly_arm::view_fly_arm_Paint);
			this->Activated += gcnew System::EventHandler(this, &view_fly_arm::view_fly_arm_Activated);
			this->Resize += gcnew System::EventHandler(this, &view_fly_arm::view_fly_arm_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->theta_OR_thrust_desired_trackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->graph_thrust))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->graph_theta))->EndInit();
			this->menu->ResumeLayout(false);
			this->menu->PerformLayout();
			this->terminal_panel->ResumeLayout(false);
			this->terminal_panel->PerformLayout();
			this->consol_panel->ResumeLayout(false);
			this->consol_panel->PerformLayout();
			this->terminal_groupBox->ResumeLayout(false);
			this->terminal_groupBox->PerformLayout();
			this->status_groupBox->ResumeLayout(false);
			this->status_groupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->graph_theta_dot))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->graph_theta_dotdot))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
// ********************* END REGION *********************
// ------------------------------------------------------
//                      START EVENTS
// ------------------------------------------------------
// ------------------------------------------------------
//                      MENU FILE: EXIT + SAVE
// ------------------------------------------------------
        //
        // exitToolStripMenuItem_Click
        //
        private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
            Close();
        }
        //
        // saveToolStripMenuItem_Click
        //
        private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
            this->graph_theta->SaveImage("..\\Theta-Time.png",System::Windows::Forms::DataVisualization::Charting::ChartImageFormat::Png);
            this->graph_thrust->SaveImage("..\\Thrust-Time.png",System::Windows::Forms::DataVisualization::Charting::ChartImageFormat::Png);
            this->graph_theta_dot->SaveImage("..\\Theta_dot-Time.png",System::Windows::Forms::DataVisualization::Charting::ChartImageFormat::Png);
            this->graph_theta_dotdot->SaveImage("..\\Theta_dotdot-Time.png",System::Windows::Forms::DataVisualization::Charting::ChartImageFormat::Png);
        }
// ------------------------------------------------------
//                      MENU MODE
// ------------------------------------------------------
        //
        // mode_PC_controller_MenuItem_Click
        //
        private: System::Void mode_PC_controller_MenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			this->theta_desired = true;
            this->theta_OR_thrust_desired_label->Text = L"Desired Theta:";
	        this->theta_desired_unite_label->Text = L"deg";
            this->theta_OR_thrust_desired_value_label->Text = "0";
            this->theta_OR_thrust_desired_trackBar->Value = 0;
            this->theta_OR_thrust_desired_trackBar->Maximum = 179;

            view_setting_PC_controller^ my_view_setting_PC_controller = gcnew view_setting_PC_controller();
			my_view_setting_PC_controller->ShowDialog(this);

			if (this->my_setting_PC_controller->controller_type_get() == CASCADE_CONTROLLER)
			{
				this->controller_type_name = L"(Cascade)";
			}
			else // LEADLAG_CONTROLLER
			{
				this->controller_type_name = L"(Leadlag)";
			}
			//this->modes_infos_communes(sender, e, true, false, false, true, L"Mode: PC control " + this->controller_type_name, HILS_MODE_PC_CONTROLLER);
			this->modes_infos_communes(true, false, false, true, L"Mode: PC control " + this->controller_type_name, HILS_MODE_PC_CONTROLLER);
        }
        //
        // mode_hils_mode_1_MenuItem_Click
        //
        private: System::Void mode_hils_mode_1_MenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
 			this->modes_infos_communes(false, true, true, false, L"Mode: Simulateur PC", HILS_MODE_1_);
        }
        //
        // mode_PC_display_real_angle_MenuItem_Click
        //
        private: System::Void mode_PC_display_real_angle_MenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			//this->modes_infos_communes(sender, e, false, true, true, false, L"Mode: PC display real angle", HILS_MODE_2);
			this->modes_infos_communes(false, true, true, false, L"Mode: PC display real angle", HILS_MODE_REAL_ANGLE);
        }
        //
        // mode_hilsMode3ToolStripMenuItem_Click
        //
		private: System::Void mode_hilsMode3ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
 			this->modes_infos_communes(false, true, true, false, L"Mode: HILS MODE 3", HILS_MODE_3_);
		}
        //
        // mode_demoManuelThrustCommandToolStripMenuItem_Click
        //
		private: System::Void mode_demoManuelThrustCommandToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			this->theta_desired = false; // THRUST DESIRED
            this->theta_OR_thrust_desired_label->Text = L"Desired Thrust:";
            this->theta_desired_unite_label->Text = L"N";
            this->theta_OR_thrust_desired_value_label->Text = "0";
            this->theta_OR_thrust_desired_trackBar->Value = 0;
            this->theta_OR_thrust_desired_trackBar->Maximum = 30;

			this->modes_infos_communes(true, false, false, true, L"Mode: Demo Manuel Thrust", HILS_MODE_MANUAL_THRUST_COMMAND);
         }
// ------------------------------------------------------
//                      MENU SETTING: SAMPLE TIME + PC CONTROLLER
// ------------------------------------------------------
        //
        // setting_sample_time_MenuItem_Click
        //
		private: System::Void setting_sample_time_MenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			if(this->stop_button->Enabled == true)
			{
				this->stop_button_Click_action();
			}
            view_setting_sample_time^ my_view_setting_sample_time = gcnew view_setting_sample_time();
			my_view_setting_sample_time->ShowDialog(this);
	
			// mise-à-jour des informations
			this->graphs_clear();
			this->sample_time_init();
			this->timer_init();
			this->graph_init();
			}
        //
        // setting_PC_controller_MenuItem_Click
        //
        private: System::Void setting_PC_controller_MenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
            view_setting_PC_controller^ my_view_setting_PC_controller = gcnew view_setting_PC_controller();
			my_view_setting_PC_controller->ShowDialog(this);

			if(this->theta_desired == true && this->theta_OR_thrust_desired_trackBar->Visible == true)
			{
				if(this->my_setting_PC_controller->controller_type_get() == CASCADE_CONTROLLER)
				{
					this->mode_label->Text = L"Mode: PC control (Cascade)";
				}
				else // LEADLAG_CONTROLLER
				{
					this->mode_label->Text = L"Mode: PC control (Leadlag)";
				}
			}
		}
// ------------------------------------------------------
//                      MENU HELP: ABOUT
// ------------------------------------------------------
        //
        // help_about_MenuItem_Click
        //
        private: System::Void help_about_MenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
            view_about^ my_view_about = gcnew view_about();
			my_view_about->ShowDialog(this);
        }
// ------------------------------------------------------
//                      PANEL MODE
// ------------------------------------------------------
        //
        // play_button_Click
        //
        private: System::Void play_button_Click(System::Object^  sender, System::EventArgs^  e) {
			// effacer les graphiques si je ne suis pas en mode pause
			if(this->pause_button->Enabled == false && this->stop_button->Enabled == false)
			{
	            this->graphs_clear();
			}
			this->buttons_enabled(false, true, true); // prevents from clicking twice on play ince ativated but the other get accessible

			if(this->myThreadSimulatorController_is_create == false) // to not create a second class 
			{
				this->myThreadSimulatorController_is_create = true; // create class
				this->myThreadSimulatorController->init();
				this->timer1->Start(); // start timer
			}
        }
        //
        // pause_button_Click
        //
        private: System::Void pause_button_Click(System::Object^  sender, System::EventArgs^  e) {
			this->buttons_enabled(true, false, true);
			if(this->myThreadSimulatorController_is_create == true)
			{
				this->timer1->Stop();
				this->myThreadSimulatorController_is_create =false;
			}
        }
        //
        // stop_button_Click
        //
        private: System::Void stop_button_Click(System::Object^  sender, System::EventArgs^  e) {
            UNREFERENCED_PARAMETER(sender);
            UNREFERENCED_PARAMETER(e);
			
			this->stop_button_Click_action();
        }
        //
        // theta_OR_thrust_desired_trackBar_Scroll
        //
        private: System::Void theta_OR_thrust_desired_trackBar_Scroll(System::Object^  sender, System::EventArgs^  e) {
			this->theta_OR_thrust_desired_save();
        }
        //
        // time_textBox_textChanged
        //
        private: System::Void time_textBox_textChanged(System::Object^  sender, System::EventArgs^  e) {
            int temp;
            int::TryParse(this->time_textBox->Text, temp);
            if (temp > 9999999)
            {
                temp = 9999999;
                this->time_textBox->Text = temp.ToString();
            }
            this->time_desired = temp;
            this->myTime->time_desired_set(temp);
        }
// ------------------------------------------------------
//                      CONSOLE
// ------------------------------------------------------
        //
        // console_info_update
        //
		private : System::Void console_info_update(void)
        {
            // si la console est active
            if (this->theta_OR_thrust_desired_trackBar->Visible == false)
            {
				this->signalValue = this->my_hilsModeSerialCommunicator->getSignal();
                this->terminal_signal_value_label->Text = "Current Signal:" + this->signalValue.ToString();
                this->signal_value_progressBar->Value = signalValue;
            }
		}
        //
        // connect_button_Click
        //
        private: System::Void connect_button_Click(System::Object^  sender, System::EventArgs^  e) {
//this->label2->Text = "";
            //-------------Connect serialcommunication-------------------
			//verify that the Setting PORT USB or COM and BAUD RATE are selected
			//
			// make sure port isn't open	
			if(!this->my_hilsModeSerialCommunicator->myCommunicator->portSuccessfullyOpened())
			{
				if(this->usb_port_radioButton->Checked == true)
				{
					// essaie d'ouvrir la connection au port usb
					this->my_hilsModeSerialCommunicator->myCommunicator->open_port(0, Int32::Parse(this->baud_rate_comboBox->Text));
					String^ string_temp = gcnew String(this->my_hilsModeSerialCommunicator->getMessage_serial_communicator());
					this->terminal_info_label->Text = string_temp;
				}
				else // com_port_radioButton
				{
					// essaie d'ouvrir la connection au port com
					this->my_hilsModeSerialCommunicator->myCommunicator->open_port(Int16::Parse(this->com_port_comboBox->Text->Substring(3)), Int32::Parse(this->baud_rate_comboBox->Text));
					String^ string_temp = gcnew String(this->my_hilsModeSerialCommunicator->getMessage_serial_communicator());
					this->terminal_info_label->Text = string_temp;
				}
			}

			// vérifier que le port est ouvert
			if(!this->my_hilsModeSerialCommunicator->myCommunicator->portSuccessfullyOpened())
			{
				if(this->usb_port_radioButton->Checked == true)
				{
					String^ string_temp = gcnew String(this->my_hilsModeSerialCommunicator->getMessage_serial_communicator());
					this->terminal_info_label->Text = string_temp;
		            this->terminal_info_label->Text += "Connect cable USB and press Connect ...";
				}
				else // com_port_radioButton
				{
					String^ string_temp = gcnew String(this->my_hilsModeSerialCommunicator->getMessage_serial_communicator());
					this->terminal_info_label->Text = string_temp;
		            this->terminal_info_label->Text += "Connect cable COM and press Connect ...";
				}
			}
			else // SI le port est ouvert
			{
				this->connect_disconnect_true_or_false(false);

				//this->my_hilsModeSerialCommunicator->init();
				this->my_hilsModeSerialCommunicator->run();

				// écrire les messages d'information
				switch(this->my_hilsModeSerialCommunicator->getMessage())
				{
					case 1:
						this->terminal_info_label->Text += "Could not open port!\nExiting...\n";
						break;
					case 2:
						this->terminal_info_label->Text += "Connecting to the board ... \n";
						this->terminal_info_label->Text += "Failed to switch into HILS mode ";
						this->terminal_info_label->Text += this->my_hilsModeSerialCommunicator->getHilsMode().ToString();
						this->terminal_info_label->Text += " - exiting...\n" ;
						break;
					case 3:
						this->terminal_info_label->Text += "Connecting to the board ... \n";
						this->terminal_info_label->Text += "Successfully switched into HILS mode ";
						this->terminal_info_label->Text += this->my_hilsModeSerialCommunicator->getHilsMode().ToString();
						this->terminal_info_label->Text += ".\n" ;
						break;
				}
			}
        }
        //
        // disconnect_button_Click
        //
        private: System::Void disconnect_button_Click(System::Object^  sender, System::EventArgs^  e) {
			this->disconnect_method();
        }
        //
        // disconnect_method
        //
        private: System::Void disconnect_method(void)
		{
            //-------------Disconnect serialcommunication-------------------
            this->timer1->Stop();
            this->my_hilsModeSerialCommunicator->stop();
            this->terminal_info_label->Text = "Press Connect ...";
            this->terminal_signal_value_label->Text = "";
            this->signal_value_progressBar->Value = 0;

			this->connect_disconnect_true_or_false(true);
        }
// ------------------------------------------------------
//                      TIMER
// ------------------------------------------------------
        //
        // timer1_Tick : GD: period of execution is specified in Sample time Settings see in GUI
        //
        private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
            UNREFERENCED_PARAMETER(sender);
            UNREFERENCED_PARAMETER(e); // GD: we don't know what's good for but we leave it

			// incrémenter les compteurs
			this->simulator_step_count++;
			this->controller_step_count++;
			this->graph_step_count++;

			// 
			if(this->my_hilsModeSerialCommunicator->getHilsMode() != HILS_MODE_MANUAL_THRUST_COMMAND)
				this->myThreadSimulatorController->hils_mode_execute(); //see threadSimulatorController.cpp
				

			// controller: GD: gets executed after some step counts (simulator faster than controller
			if(this->controller_step_count == this->controller_step && this->my_hilsModeSerialCommunicator->getHilsMode() != HILS_MODE_MANUAL_THRUST_COMMAND
				&& this->my_hilsModeSerialCommunicator->getHilsMode() != HILS_MODE_1)
			{
				this->myThreadSimulatorController->runController();
				this->controller_step_count = 0;
			}

			//==>> partie à modifier selon les indications de Guillaume
			// simulator
			//if(this->my_hilsModeSerialCommunicator->getHilsMode() != HILS_MODE_REAL_ANGLE && this->simulator_step_count == this->simulator_step)
			if(this->my_hilsModeSerialCommunicator->getHilsMode() != HILS_MODE_REAL_ANGLE && this->my_hilsModeSerialCommunicator->getHilsMode() != HILS_MODE_1 
				&& this->simulator_step_count == this->simulator_step)
			{
				this->myThreadSimulatorController->runSimulator();
				this->simulator_step_count = 0;
			}

			// graph
			if(this->graph_step_count == this->graph_step)
			{
				this->graph_step_count = 0;
				this->timer_graph += this->timer_graph_step;
				this->graphs_draw();

				this->console_info_update();

				this->myOpenGL->render();
				this->my_view_openGL->buffers_swap();
			}


            // tenir compte du temps désiré
            if (this->timer_graph >= (double)this->time_desired)
            {
                this->timer1->Stop();
				this->myThreadSimulatorController_is_create =false;
				this->buttons_enabled(true, false, true);
            }
		}
// ------------------------------------------------------
//                      GRAPHS
// ------------------------------------------------------
        //
        // graphs_draw
        //
		private : System::Void graphs_draw(void)
        {
			this->rad_arm = this->myArmPropSimulator->GetTheta();
			this->degree_arm = this->rad_arm * 180.0 / MY_PI;
			this->thrust = this->myArmPropSimulator->GetPropThrust();
			this->theta_dot = this->myArmPropSimulator->GetThetaDot();
			this->theta_dotdot = this->myArmPropSimulator->GetThetaDotDot();
			this->theta_dot_controlleur = this->theta_dot + 2;

            this->theta_value_label->Text = this->degree_arm.ToString();
			this->thrust_value_label->Text = this->thrust.ToString();

			this->graph_theta_value_label->Text = this->degree_arm.ToString();
			this->graph_thrust_value_label->Text = this->thrust.ToString();
			this->graph_theta_dot_value_label->Text = this->theta_dot.ToString();
			this->graph_theta_dotdot_value_label->Text = this->theta_dotdot.ToString();
			this->graph_theta_dot_controlleur_value_label->Text = this->theta_dot_controlleur.ToString();

			// T1 = Theta-Time
			if (this->angle_unite_listBox->GetSelected(0) == true) // "deg" -> unité: degré
			{
				this->graph_theta->Series["T1"]->Points->AddXY(this->timer_graph, this->degree_arm);
			}
			else // "rad" -> unité: radian
			{
				this->graph_theta->Series["T1"]->Points->AddXY(this->timer_graph,  this->degree_arm);
			}

            // T2 = Thrust-Time
			this->graph_thrust->Series["T2"]->Points->AddXY(this->timer_graph, this->thrust);

            // T3 = Theta_Dot-Time
			this->graph_theta_dot->Series["T3"]->Points->AddXY(this->timer_graph, this->theta_dot);

            // T4 = Theta_DotDot-Time
			this->graph_theta_dotdot->Series["T4"]->Points->AddXY(this->timer_graph, this->theta_dotdot);

            // T5 = Theta_Dot_Controlleur-Time
			this->graph_theta_dot->Series["T5"]->Points->AddXY(this->timer_graph, this->theta_dot_controlleur);
		}
// ------------------------------------------------------
//                      WINDOW
// ------------------------------------------------------
        //
        // view_fly_arm_Activated
        //
        private: System::Void view_fly_arm_Activated(System::Object^  sender, System::EventArgs^  e) {
            // draw window openGL
            UNREFERENCED_PARAMETER(sender);
            UNREFERENCED_PARAMETER(e);
            this->myOpenGL->init_scene();
            this->myOpenGL->render();
            this->my_view_openGL->buffers_swap();
        }
        //
        // view_fly_arm_Paint
        //
        private: System::Void view_fly_arm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
            UNREFERENCED_PARAMETER(sender);
            UNREFERENCED_PARAMETER(e);
            this->myOpenGL->init_scene();
            this->myOpenGL->render();
            this->my_view_openGL->buffers_swap();
		}
        //
        // file_MenuItem_Paint
        //
        private: System::Void file_MenuItem_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
            UNREFERENCED_PARAMETER(sender);
            UNREFERENCED_PARAMETER(e);
            this->myOpenGL->render();
            this->my_view_openGL->buffers_swap();
        }
        //
        // view_fly_arm_Resize
        //
        private: System::Void view_fly_arm_Resize(System::Object^  sender, System::EventArgs^  e) {
            // I don't know resize view_opengl_width and view_opengl_height
            // calculate opengl_y
            // this->opengl_y = VIEW_OPENGL_HEIGHT - this->window_opengl_height;

            // ZOOM WIDTH AND HEIGHT
            this->zoom_width = this->Width - VIEW_FLY_ARM_WIDTH;
            this->zoom_height = this->Height - VIEW_FLY_ARM_HEIGHT;

            // OPENGL ZONE LEFT
            // zoom width and height for opengl
            this->zoom_width_opengl = this->zoom_width / 2;
            this->zoom_height_opengl = this->zoom_height;

            // MARGIN
            this->zoom_x_opengl = this->zoom_width_opengl / 2;
            this->zoom_y_opengl = this->zoom_height_opengl / 2;

			// CONSOLE
			this->terminal_panel->Left = this->zoom_width_opengl /2;

// ================================================================
// REVOIR LA TAILLE DE LA FENETRE OPENGL AINSI QUE L'ANGLE DE
// VIEWPORT
// ================================================================
            // IF ZOOM_WIDTH_OPENGL < ZOOM_HEIGHT_OPENGL
            if (this->zoom_width_opengl < this->zoom_height_opengl)
            {
                this->window_opengl_width = OPENGL_WIDTH + this->zoom_width_opengl;
                this->window_opengl_height = this->window_opengl_width;

                this->opengl_y = VIEW_OPENGL_HEIGHT - this->window_opengl_height;

                this->window_opengl_x = 0;
                this->window_opengl_y = this->opengl_y - this->zoom_y_opengl + this->zoom_x_opengl;
            }

            // ELSE IF ZOOM_WIDTH_OPENGL > ZOOM_HEIGHT_OPENGL
            else if (this->zoom_width_opengl > this->zoom_height_opengl)
            {
                this->window_opengl_height = OPENGL_HEIGHT + this->zoom_height_opengl;
                this->window_opengl_width = this->window_opengl_height;

                this->opengl_y = VIEW_OPENGL_HEIGHT - this->window_opengl_height;

                this->window_opengl_x = this->zoom_x_opengl - this->zoom_y_opengl;
                this->window_opengl_y = this->opengl_y;
            }

            // ELSE ZOOM_WIDTH_OPENGL = ZOOM_HEIGHT_OPENGL
            else
            {
                this->window_opengl_width = OPENGL_WIDTH + this->zoom_width_opengl;
                this->window_opengl_height = OPENGL_HEIGHT + this->zoom_height_opengl;

                this->opengl_y = VIEW_OPENGL_HEIGHT - this->window_opengl_height;

                this->window_opengl_x = 0;
                this->window_opengl_y = this->opengl_y - this->zoom_y_opengl;
            }

            // RESIZE WINDOW OPENGL
            this->myOpenGL->openGL_width_set(this->window_opengl_width);
            this->myOpenGL->openGL_height_set(this->window_opengl_height);
            this->myOpenGL->openGL_x_set(this->window_opengl_x);
            this->myOpenGL->openGL_y_set(this->window_opengl_y);

            // PANEL ZONE RIGHT
            // ZOOM WIDTH AND HEIGHT FOR PANEL
            this->zoom_width_panel = this->zoom_width / 2; // number of panel
            this->zoom_height_panel = this->zoom_height / 4; // number of panel

            // ZOOM WIDTH AND HEIGHT MODULO
            this->zoom_width_modulo = this->zoom_width % 2;
            this->zoom_height_modulo =  this->zoom_height % 4;

            // RESIZE WINDOW PANEL LOCATION LEFT
            this->window_panel_location_left = PANEL_LOCATION_LEFT + this->zoom_width_panel - this->zoom_width_modulo;

            // RESIZE WINDOW PANEL SIZE WIDTH
            this->window_panel_size_width = PANEL_WIDTH + this->zoom_width_panel + this->zoom_width_modulo;

            // RESIZE WINDOW PANEL SIZE HEIGHT
            this->window_panel_size_height = PANEL_HEIGHT + this->zoom_height_panel;

            // INCREMENT HEIGHT PANEL
            switch (this->zoom_height_modulo)
            {
                case 0:
                    this->increment_height_theta = 0;
                    this->increment_height_thrust = 0;
                    this->increment_height_theta_dot = 0;
                    break;

                case 1:
                    this->increment_height_theta = 1;
                    this->increment_height_thrust = 0;
                    this->increment_height_theta_dot = 0;
                    break;

                case 2:
                    this->increment_height_theta = 1;
                    this->increment_height_thrust = 1;
                    this->increment_height_theta_dot = 0;
                    break;
                case 3:
                    this->increment_height_theta = 1;
                    this->increment_height_thrust = 1;
                    this->increment_height_theta_dot = 1;
                    break;

                default:
                    break;
            }

            // RESIZE WINDOW PANEL THETA
            this->graph_theta->Left = this->window_panel_location_left;
            this->graph_theta->Top = PANEL_THETA_TOP;
            this->graph_theta->Width = this->window_panel_size_width;
            this->graph_theta->Height = this->window_panel_size_height + this->increment_height_theta;

            // RESIZE WINDOW PANEL THRUST
            this->graph_thrust->Left = this->window_panel_location_left;
            this->graph_thrust->Top =  this->graph_theta->Top + this->graph_theta->Height;
            this->graph_thrust->Width = this->window_panel_size_width;
            this->graph_thrust->Height = this->window_panel_size_height + this->increment_height_thrust;

            // RESIZE WINDOW PANEL THETA_DOT
            this->graph_theta_dot->Left = this->window_panel_location_left;
            this->graph_theta_dot->Top =  this->graph_thrust->Top + this->graph_thrust->Height;
            this->graph_theta_dot->Width = this->window_panel_size_width;
            this->graph_theta_dot->Height = this->window_panel_size_height + this->increment_height_theta_dot;

            // RESIZE WINDOW PANEL THETA_DOTDOT
            this->graph_theta_dotdot->Left = this->window_panel_location_left;
            this->graph_theta_dotdot->Top = this->graph_theta_dot->Top + this->graph_theta_dot->Height;
            this->graph_theta_dotdot->Width = this->window_panel_size_width;
            this->graph_theta_dotdot->Height = this->window_panel_size_height;

			// GRAPHS
			// RELOCATION TITLE + VALUE + LEGENDS
			// GRAPH THETA
			this->graph_theta_time_label->Top = this->graph_theta->Top + MARGE_TITLE;
			this->graph_theta_value_label->Top = this->graph_theta->Top + MARGE_VALUE;
			this->graph_x_theta_time_label->Top = this->graph_theta->Top + this->graph_theta->Height - MARGE_TIME;

			// GRAPH THRUST
			this->graph_y_thrust_label->Top = this->graph_thrust->Top - MARGE_MESURE;
			this->graph_thrust_time_label->Top = this->graph_thrust->Top + MARGE_TITLE;
			this->graph_thrust_value_label->Top = this->graph_thrust->Top + MARGE_VALUE;
			this->graph_x_thrust_time_label->Top = this->graph_thrust->Top + this->graph_thrust->Height - MARGE_TIME;

			// GRAPH THETA_DOT
			this->graph_theta_dot_time_label->Top = this->graph_theta_dot->Top + MARGE_TITLE;
			this->graph_theta_dot_color->Top = this->graph_theta_dot->Top + MARGE_TITLE + 40;
			this->graph_theta_dot_value_label->Top = this->graph_theta_dot->Top + MARGE_VALUE;
			this->graph_x_theta_dot_time_label->Top = this->graph_theta_dot->Top + this->graph_theta_dot->Height - MARGE_TIME;

			// GRAPH THETA_DOT_CONTROLLEUR
			this->graph_theta_dot_controlleur_time_label->Top = this->graph_theta_dot->Top + MARGE_TITLE + 74;
			this->graph_theta_dot_controlleur_color->Top = this->graph_theta_dot->Top + MARGE_TITLE + 114; // 40 + 74
			this->graph_theta_dot_controlleur_value_label->Top = this->graph_theta_dot->Top + MARGE_VALUE + 74;

			// GRAPH THETA_DOTDOT
			this->graph_theta_dotdot_time_label->Top = this->graph_theta_dotdot->Top + MARGE_TITLE;
			this->graph_theta_dotdot_value_label->Top = this->graph_theta_dotdot->Top + MARGE_VALUE;
			this->graph_x_theta_dotdot_time_label->Top = this->graph_theta_dotdot->Top + this->graph_theta_dotdot->Height - MARGE_TIME;
			
			// GRAPH_Y THETA_DOTDOT
			this->graph_y_theta_dotdot_label->Top = this->graph_theta_dotdot->Top - 11;

			// DRAW WINDOW OPENGL
            UNREFERENCED_PARAMETER(sender);
            UNREFERENCED_PARAMETER(e);
            this->myOpenGL->init_scene();
            this->myOpenGL->render();
            this->my_view_openGL->buffers_swap();
        }
// ------------------------------------------------------
//                      SERIAL PORT
// ------------------------------------------------------
        //
        // usb_port_radioButton_Click
        //
		private: System::Void usb_port_radioButton_Click(System::Object^  sender, System::EventArgs^  e) {
			this->com_port_comboBox->Items->Clear();
			this->connect_button_state();

			this->my_hilsModeSerialCommunicator->myCommunicator->port_select(PORT_USB);

			this->terminal_info_label->Text = "Press Connect ...";
			 }
        //
        // com_port_radioButton_Click
        //
		private: System::Void com_port_radioButton_Click(System::Object^  sender, System::EventArgs^  e) {
			this->connect_button_state();

			this->my_hilsModeSerialCommunicator->myCommunicator->port_select(PORT_COM);

			this->terminal_info_label->Text = "Press Connect ...";
		}
        //
        // com_port_comboBox_Click
        //
		private: System::Void com_port_comboBox_Click(System::Object^  sender, System::EventArgs^  e) {
			if(this->com_port_radioButton->Checked == true)
				this->find_ports();
			else
				// vider la liste
				this->com_port_comboBox->Items->Clear();
		 }
        //
        // com_port_comboBox_SelectedIndexChanged
        //
		private: System::Void com_port_comboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			this->connect_button_state();
		}
        //
        // baud_rate_comboBox_SelectedIndexChanged
        //
		private: System::Void baud_rate_comboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			this->connect_button_state();
			 }
// ----------------------------------------------------------------------------------------------------
//                      START LOCAL FUNCTIONS
// ----------------------------------------------------------------------------------------------------
// ------------------------------------------------------
//                      INIT
// ------------------------------------------------------
        //
        // objects_init
        //
        private : System::Void objects_init(void)
        {
			this->myArmPropSimulator = ArmPropSimulator::getInstance();
			this->myArmPropController = ArmPropController::getInstance();
			this->my_hilsModeSerialCommunicator = hilsModeSerialCommunicator::getInstance();
			this->myThreadSimulatorController = threadSimulatorController::getInstance();
			this->myThreadSimulatorController_is_create = false;

			this->myTime = Cmodel_time::getInstance();
			this->myOpenGL = Cmodel_openGL::getInstance();
			this->my_setting_PC_controller = Cmodel_setting_PC_controller::getInstance();
			this->my_setting_sample_time = model_setting_sample_time::getInstance();
			
            this->my_view_openGL = gcnew view_openGL(this);
            this->myOpenGL->init();
	
        }
        //
        // sample_time_init
        //
        private : System::Void sample_time_init(void)
        {
			this->step = this->my_setting_sample_time->get_step();
			this->simulator_step = this->my_setting_sample_time->get_simulator_step();
			this->controller_step = this->my_setting_sample_time->get_controller_step();
			this->graph_step = this->my_setting_sample_time->get_graph_step();
			this->simulator_step_count = 0;
			this->controller_step_count = 0;
			this->graph_step_count = 0;
        }
        //
        // timer_init
        //
        private : System::Void timer_init(void)
        {
			this->timer1->Interval = this->step;
            this->timer1->Stop();
        }
        //
        // graph_init
        //
        private : System::Void graph_init(void)
        {
			this->timer_graph_step = (double)this->step * this->graph_step / 1000.0;
			this->timer_graph = 0;
			this->graphs_draw();
        }
        //
        // attributs_init
        //
        private : System::Void attributs_init(void)
        {
			this->rad_arm = 0.0;
            this->degree_arm = 0;
			this->thrust = 0.0;
			this->theta_dot = 0.0;
			this->theta_dotdot = 0.0;
			this->theta_dot_controlleur = 0.0;

			this->time_desired = this->myTime->time_desired_get();
            this->time_textBox->Text = this->time_desired.ToString();

			this->DesiredTheta_Rad = 0.0;
            this->DesiredTheta_Deg = 0.0;

            this->consol_is_show = false;
            this->theta_desired_is_show =false;

			this->angle_unite_listBox->SetSelected(0, true);
		}
// ------------------------------------------------------
//                      MODES
// ------------------------------------------------------
        //
        // modes_infos_communes
        //
		//private: System::Void modes_infos_communes(System::Object^  sender, System::EventArgs^  e, bool consol_is_show_bool, bool consol_show_OR_hide_bool, bool theta_OR_thrust_desired_is_show_bool, bool theta_OR_thrust_desired_show_OR_hide_bool,System::String^ texte, int hils_mode_int) {
		private: System::Void modes_infos_communes(bool consol_is_show_bool, bool consol_show_OR_hide_bool, bool theta_OR_thrust_desired_is_show_bool, bool theta_OR_thrust_desired_show_OR_hide_bool,System::String^ texte, int hils_mode_int) {
			this->disconnect_serial_port();
            //UNREFERENCED_PARAMETER(sender);
            //UNREFERENCED_PARAMETER(e);
            this->myArmPropSimulator->init();
			this->myArmPropController->init();
            this->myOpenGL->render();
            this->my_hilsModeSerialCommunicator->setHilsMode(hils_mode_int);
			this->myThreadSimulatorController->hils_mode_update(hils_mode_int);
			// mettre les boutons 'PLAY' 'PAUSE' et 'STOP' avec les valeurs de départ
			this->buttons_enabled(true, false, false);
			// adapter la taille de 'modes_panel' en fonction de hils_mode
			if(this->my_hilsModeSerialCommunicator->getHilsMode() == HILS_MODE_PC_CONTROLLER || this->my_hilsModeSerialCommunicator->getHilsMode() == HILS_MODE_MANUAL_THRUST_COMMAND)
			{
				this->modes_panel->Height = 199;
				// mettre les controles devant 'modes_panel'
				this->theta_OR_thrust_desired_label->BringToFront();
				this->theta_OR_thrust_desired_value_label->BringToFront();
				this->theta_desired_unite_label->BringToFront();
				this->theta_OR_thrust_desired_trackBar->BringToFront();
			}
			else
			{
				this->modes_panel->Height = 128;
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
            this->mode_label->Text = texte;
            this->timer_graph = 0;
			this->graphs_draw();
			this->simulator_step_count = 0;
			this->controller_step_count = 0;
			this->graph_step_count = 0;
            this->graph_thrust_value_label->Text = "0.0";
            this->graph_theta_value_label->Text = "0.0";
            this->theta_value_label->Text = "0.0";
            this->thrust_value_label->Text = "0.0";
            this->my_view_openGL->buffers_swap();
        }
// ------------------------------------------------------
//                      PANEL MODE
// ------------------------------------------------------
        //
        // buttons_enabled
        //
        private : System::Void buttons_enabled(bool play_state,bool pause_state, bool stop_state)
        {
			this->play_button->Enabled = play_state;
			this->pause_button->Enabled = pause_state;
			this->stop_button->Enabled = stop_state;
        }
        //
        // stop_button_Click_action
        //
        private: System::Void stop_button_Click_action(void)
		{
			this->buttons_enabled(true, false, false);

			if(this->myThreadSimulatorController_is_create == true)
			{
				this->timer1->Stop();
				this->myThreadSimulatorController_is_create =false;
			}

			this->myArmPropSimulator->init();
			this->myArmPropController->init();
			this->theta_OR_thrust_desired_save();

			this->graphs_clear();
			// pour avoir en abscisse une graduation de 0 à 2
			this->timer_graph = 0;
			this->graphs_draw();

			this->myOpenGL->render();
			this->my_view_openGL->buffers_swap();
        }
        //
        // theta_desired_show_OR_hide
        //
        private : System::Void theta_desired_show_OR_hide(bool true_or_false)
        {
            this->theta_desired_is_show = true_or_false;

            this->theta_OR_thrust_desired_label->Visible = true_or_false;
            this->theta_OR_thrust_desired_value_label->Visible = true_or_false;
            this->theta_OR_thrust_desired_trackBar->Visible = true_or_false;
            this->theta_desired_unite_label->Visible = true_or_false;
        }
        //
        // theta_OR_thrust_desired_save
        //
        private: System::Void theta_OR_thrust_desired_save(void)
		{
			// theta_desired
            if (this->theta_desired == true)
			{
                this->theta_OR_thrust_desired_value_label->Text = this->theta_OR_thrust_desired_trackBar->Value.ToString();
				this->DesiredTheta_Rad = (double)this->theta_OR_thrust_desired_trackBar->Value * MY_PI / 180.0;
				this->myArmPropController->SetThetaCmd(this->DesiredTheta_Rad);
			}
			// thrust_desired
            else
            {
                this->thrust_desired = this->theta_OR_thrust_desired_trackBar->Value / 10.0;
                this->theta_OR_thrust_desired_value_label->Text = this->thrust_desired.ToString("c1");
				this->myArmPropController->SetThrustCmd(this->thrust_desired);
            }
		}
// ------------------------------------------------------
//                      CONSOLE
// ------------------------------------------------------
        //
        // consol_show_OR_hide
        //
        private : System::Void consol_show_OR_hide(bool true_or_false)
        {
            this->consol_is_show = true_or_false;

            this->terminal_panel->Visible = true_or_false;
            this->consol_panel->Visible = true_or_false;
            this->consol_panel_panel->Visible = true_or_false;
            this->consol_label->Visible = true_or_false;
            this->status_groupBox->Visible = true_or_false;
            this->terminal_groupBox->Visible = true_or_false;
            this->status_label->Visible = true_or_false;
            this->terminal_info_label->Visible = true_or_false;
            this->terminal_signal_value_label->Visible = true_or_false;
            this->connect_button->Visible = true_or_false;
            this->disconnect_button->Visible = true_or_false;
            this->status_panel->Visible = true_or_false;

			if(true_or_false == true)
				this->baud_rate_comboBox->Text = "19200";
        }
        //
        // connect_disconnect_true_or_false
        //
        private : System::Void connect_disconnect_true_or_false(bool true_or_false)
        {
			this->connect_button->Enabled = true_or_false;
			this->disconnect_button->Enabled = !true_or_false;
			this->usb_port_radioButton->Enabled = true_or_false;
			this->com_port_radioButton->Enabled = true_or_false;
			this->com_port_comboBox->Enabled = true_or_false;
			this->baud_rate_comboBox->Enabled = true_or_false;

			if(true_or_false == false)
			{
				this->status_panel->BackColor = System::Drawing::Color::Lime;
				this->status_label->Text = "Connected";
			}
			else
			{
			this->status_panel->BackColor = System::Drawing::Color::Red;
				this->status_label->Text = "Disconnect";
			}
		}
// ------------------------------------------------------
//                      GRAPHS
// ------------------------------------------------------
        //
        // graphs_clear
        //
        private : System::Void graphs_clear(System::Void)
        {
            this->graph_theta->Series["T1"]->Points->Clear();
            this->graph_thrust->Series["T2"]->Points->Clear();
            this->graph_theta_dot->Series["T3"]->Points->Clear();
            this->graph_theta_dotdot->Series["T4"]->Points->Clear();
            this->graph_theta_dot->Series["T5"]->Points->Clear();
		}
// ------------------------------------------------------
//                      SERIAL PORT
// ------------------------------------------------------
		//
		// find_ports
		// Trouve les ports utilisant la liaison série
		private: System::Void find_ports(void)
		{
			// vider la liste
			this->com_port_comboBox->Items->Clear();
			// obtient le nom des ports utilisant la liaison série
			array<Object^>^ objectArray = SerialPort::GetPortNames();
			// ajoute à la combobox les ports trouvés
			this->com_port_comboBox->Items->AddRange( objectArray );
		}
        //
        // connect_button_state
        //
		private: System::Void connect_button_state(void)
		{
			// enabled SI
			// com port actif ET baud rate valeur sélectionnée ET com port combobox choisi
			// OU usb port actif ET baud rate valeur sélectionnée
			if(this->baud_rate_comboBox->Text != String::Empty && ((this->com_port_radioButton->Checked == true && this->com_port_comboBox->Text != String::Empty) || this->usb_port_radioButton->Checked == true))
				this->connect_button->Enabled = true;
			else
				this->connect_button->Enabled = false;
		}
        //
        // deconnect_serial_port
        //
		private: System::Void disconnect_serial_port(void)
		{
			// déconnecter la liaison série lorsque l'utilisateur change de HilsMode sans avoir déconnecter manuellement
			if(this->disconnect_button->Enabled == true)
				this->disconnect_method();
		}
};
}
