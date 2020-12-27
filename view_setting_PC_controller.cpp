#include "view_setting_PC_controller.h"
#include "ui_view_setting_PC_controller.h"

view_setting_PC_controller::view_setting_PC_controller(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::view_setting_PC_controller)
{
	ui->setupUi(this);

	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowCloseButtonHint);

	this->myController_read_setting_PC_controller = controller_read_setting_PC_controller::getInstance();
	this->myController_write_setting_PC_controller = controller_write_setting_PC_controller::getInstance();

	this->data_load();
}

view_setting_PC_controller::~view_setting_PC_controller()
{
	delete ui;
}

void view_setting_PC_controller::on_apply_button_clicked()
{
	bool error = false;

	if(this->ui->cascade_controller_checkBox->checkState() == Qt::Checked)
	{
		this->controller_type = CASCADE_CONTROLLER;

		if(!this->myController_write_setting_PC_controller->k1_set(this->ui->k1_textBox->text()))
		{
			this->ui->k1_textBox->setText(this->myController_read_setting_PC_controller->k1_string_get());
			error = true;
		}

		if(!this->myController_write_setting_PC_controller->k2_set(this->ui->k2_textBox->text()))
		{
			this->ui->k2_textBox->setText(this->myController_read_setting_PC_controller->k2_string_get());
			error = true;
		}
	}

	else
	{
		this->controller_type = LEADLAG_CONTROLLER;

		if(!this->myController_write_setting_PC_controller->a1_set(this->ui->a1_textBox->text()))
		{
			this->ui->a1_textBox->setText(this->myController_read_setting_PC_controller->a1_string_get());
			error = true;
		}

		if(!this->myController_write_setting_PC_controller->a2_set(this->ui->a2_textBox->text()))
		{
			this->ui->a2_textBox->setText(this->myController_read_setting_PC_controller->a2_string_get());
			error = true;
		}

		if(!this->myController_write_setting_PC_controller->b1_set(this->ui->b1_textBox->text()))
		{
			this->ui->b1_textBox->setText(this->myController_read_setting_PC_controller->b1_string_get());
			error = true;
		}

		if(!this->myController_write_setting_PC_controller->b2_set(this->ui->b2_textBox->text()))
		{
			this->ui->b2_textBox->setText(this->myController_read_setting_PC_controller->b2_string_get());
			error = true;
		}

		if(!this->myController_write_setting_PC_controller->b3_set(this->ui->b3_textBox->text()))
		{
			this->ui->b3_textBox->setText(this->myController_read_setting_PC_controller->b3_string_get());
			error = true;
		}
	}
	this->myController_write_setting_PC_controller->controller_type_set(this->controller_type);

	if(!error)
		this->close();
}

void view_setting_PC_controller::on_cancel_button_clicked()
{
	this->close();
}

void view_setting_PC_controller::on_reset_button_clicked()
{
	this->myController_write_setting_PC_controller->init_setting_PC_controller();
	this->data_load();
}

void view_setting_PC_controller::on_cascade_controller_checkBox_stateChanged(int arg1)
{
	if(arg1 == Qt::Checked)
	{
		this->ui->cascade_controller_checkBox->setCheckState(Qt::Checked);
		this->ui->leadlag_controller_checkBox->setCheckState(Qt::Unchecked);
		this->data_load_cascade_controller();
	}
}

void view_setting_PC_controller::on_leadlag_controller_checkBox_stateChanged(int arg1)
{
	if(arg1 == Qt::Checked)
	{
		this->ui->cascade_controller_checkBox->setCheckState(Qt::Unchecked);
		this->ui->leadlag_controller_checkBox->setCheckState(Qt::Checked);
		this->data_load_leadlag_controller();
	}
}

void view_setting_PC_controller::data_load(void)
{
	this->controller_type = this->myController_read_setting_PC_controller->controller_type_get();

	// cascade controller
	if (this->controller_type == CASCADE_CONTROLLER)
	{
		 this->ui->cascade_controller_checkBox->setCheckState(Qt::Checked);
		 this->ui->leadlag_controller_checkBox->setCheckState(Qt::Unchecked);
		 this->data_load_cascade_controller();
	}
	// leadlag controller
	else
	{
		 this->ui->cascade_controller_checkBox->setCheckState(Qt::Unchecked);
		 this->ui->leadlag_controller_checkBox->setCheckState(Qt::Checked);
		 this->data_load_leadlag_controller();
	}
}

void view_setting_PC_controller::data_load_cascade_controller(void)
{
	this->ui->k1_textBox->setText(this->myController_read_setting_PC_controller->k1_string_get());
	this->ui->k2_textBox->setText(this->myController_read_setting_PC_controller->k2_string_get());
	this->ui->a1_textBox->setText("");
	this->ui->a2_textBox->setText("");
	this->ui->b1_textBox->setText("");
	this->ui->b2_textBox->setText("");
	this->ui->b3_textBox->setText("");
}

void view_setting_PC_controller::data_load_leadlag_controller(void)
{
	this->ui->a1_textBox->setText(this->myController_read_setting_PC_controller->a1_string_get());
	this->ui->a2_textBox->setText(this->myController_read_setting_PC_controller->a2_string_get());
	this->ui->b1_textBox->setText(this->myController_read_setting_PC_controller->b1_string_get());
	this->ui->b2_textBox->setText(this->myController_read_setting_PC_controller->b2_string_get());
	this->ui->b3_textBox->setText(this->myController_read_setting_PC_controller->b3_string_get());
	this->ui->k1_textBox->setText("");
	this->ui->k2_textBox->setText("");
}
