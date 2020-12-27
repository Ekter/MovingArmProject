#include "model_file_setting.h"

void model_file_setting::init(void)
{
	this->myTime = model_time::getInstance();
	this->myController_read_setting_PC_controller = controller_read_setting_PC_controller::getInstance();
	this->myController_write_setting_PC_controller = controller_write_setting_PC_controller::getInstance();
	this->myController_read_setting_sample_time = controller_read_setting_sample_time::getInstance();
	this->myController_write_setting_sample_time = controller_write_setting_sample_time::getInstance();
}
//
// file_read
//
void model_file_setting::file_read(void)
{
	QFile fichier("file_setting.txt");

	if (fichier.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&fichier);
		this->texte = in.readAll();
		fichier.close();

		this->file_analyse(&(this->texte));

		this->texte.clear();
	}
	else
		this->myMessage.show_information("File 'file_setting.txt' not find");
}
//
// file_write
//
void model_file_setting::file_write(void)
{
	QFile fichier("file_setting.txt");
	QString texte_a_ecrire;

	texte_a_ecrire.append("PC CONTROLLER");
	texte_a_ecrire.append("\ncontroller_type = ");
	texte_a_ecrire.append(this->myController_read_setting_PC_controller->controller_type_string_get());
	texte_a_ecrire.append("\nk1 = ");
	texte_a_ecrire.append(this->myController_read_setting_PC_controller->k1_string_get());
	texte_a_ecrire.append("\nk2 = ");
	texte_a_ecrire.append(this->myController_read_setting_PC_controller->k2_string_get());
	texte_a_ecrire.append("\na1 = ");
	texte_a_ecrire.append(this->myController_read_setting_PC_controller->a1_string_get());
	texte_a_ecrire.append("\na2 = ");
	texte_a_ecrire.append(this->myController_read_setting_PC_controller->a2_string_get());
	texte_a_ecrire.append("\nb1 = ");
	texte_a_ecrire.append(this->myController_read_setting_PC_controller->b1_string_get());
	texte_a_ecrire.append("\nb2 = ");
	texte_a_ecrire.append(this->myController_read_setting_PC_controller->b2_string_get());
	texte_a_ecrire.append("\nb3 = ");
	texte_a_ecrire.append(this->myController_read_setting_PC_controller->b3_string_get());
	texte_a_ecrire.append("\n\nSAMPLE TIME");
	texte_a_ecrire.append("\ntime_step = ");
	texte_a_ecrire.append(QString::number(this->myController_read_setting_sample_time->step_get()));
	texte_a_ecrire.append("\nsimulation_step = ");
	texte_a_ecrire.append(QString::number(this->myController_read_setting_sample_time->simulator_step_get()));
	texte_a_ecrire.append("\ncontroller_step = ");
	texte_a_ecrire.append(QString::number(this->myController_read_setting_sample_time->controller_step_get()));
	texte_a_ecrire.append("\ngraph_step = ");
	texte_a_ecrire.append(QString::number(this->myController_read_setting_sample_time->graph_step_get()));
	texte_a_ecrire.append("\n\nTIME");
	texte_a_ecrire.append("\ntime_desired = ");
	texte_a_ecrire.append(QString::number(this->myTime->time_desired_get()));

	if (fichier.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&fichier);
		out << texte_a_ecrire;
		fichier.close();
	}
	else
		this->myMessage.show_information("File 'file_setting.txt' not find");
}
//
// file_analyse
//
void model_file_setting::file_analyse(QString* texte)
{
	QStringList lignes;
	QStringList donnees;
	QStringList ligne;
	QString temp_donnee;
	QString temp_valeur;
	int index_donnee;
	bool temp_bool;

	donnees.append(" NOT FIND in File 'file_setting.txt'");
	donnees.append("controller_type");
	donnees.append("k1");
	donnees.append("k2");
	donnees.append("a1");
	donnees.append("a2");
	donnees.append("b1");
	donnees.append("b2");
	donnees.append("b3");
	donnees.append("time_step");
	donnees.append("simulation_step");
	donnees.append("controller_step");
	donnees.append("graph_step");
	donnees.append("time_desired");

	index_donnee = 1;

	lignes = texte->split("\n");

	for(int index = 0; index < lignes.count(); index++)
	{
		if(lignes.at(index).contains("="))
		{
			ligne = lignes.at(index).split("=");
			temp_donnee = ligne.at(0).trimmed();
			temp_valeur = ligne.at(1).trimmed();
			if(temp_donnee == donnees.at(index_donnee))
			{
//				qDebug() << temp_donnee << " = " << temp_valeur;
				switch(index_donnee)
				{
					case 1:
						temp_bool = temp_valeur == "cascade" ? true: false;
						this->myController_write_setting_PC_controller->controller_type_set(temp_bool);
						break;
					case 2:
						this->myController_write_setting_PC_controller->k1_set(temp_valeur);
						break;
					case 3:
						this->myController_write_setting_PC_controller->k2_set(temp_valeur);
						break;
					case 4:
						this->myController_write_setting_PC_controller->a1_set(temp_valeur);
						break;
					case 5:
						this->myController_write_setting_PC_controller->a2_set(temp_valeur);
						break;
					case 6:
						this->myController_write_setting_PC_controller->b1_set(temp_valeur);
						break;
					case 7:
						this->myController_write_setting_PC_controller->b2_set(temp_valeur);
						break;
					case 8:
						this->myController_write_setting_PC_controller->b3_set(temp_valeur);
						break;
					case 9:
						this->myController_write_setting_sample_time->step_set(temp_valeur);
						break;
					case 10:
						this->myController_write_setting_sample_time->simulator_step_set(temp_valeur);
						break;
					case 11:
						this->myController_write_setting_sample_time->controller_step_set(temp_valeur);
						break;
					case 12:
						this->myController_write_setting_sample_time->graph_step_set(temp_valeur);
						break;
					case 13:
						this->myTime->time_desired_set(temp_valeur.toInt());
						break;
					default:
						break;
				}
				index_donnee++;
			}
			else
			{
				if(index_donnee < 9)
				{
					this->texte_erreur_reinitialisation = "SETTING PC CONTROLLER";
					this->myController_write_setting_PC_controller->init_setting_PC_controller();
				}
				else if(index_donnee < 13)
				{
					this->texte_erreur_reinitialisation = "SETTING SAMPLE TIME";
					this->myController_write_setting_sample_time->init_setting_sample_time();
				}
				else
				{
					this->texte_erreur_reinitialisation = "TIME";
					this->myTime->init();
				}
				this->myMessage.show_information(donnees.at(index_donnee) + donnees.at(0) + "\n\nREINITIALISATION " + this->texte_erreur_reinitialisation);
				break;
			}
		}
	}
}
//
// model_file_setting
//
model_file_setting::model_file_setting(void)
{
}
//
// ~model_file_setting
//
model_file_setting::~model_file_setting(void)
{
}
