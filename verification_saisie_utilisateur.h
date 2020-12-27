#ifndef VERIFICATION_SAISIE_UTILISATEUR_H
#define VERIFICATION_SAISIE_UTILISATEUR_H

#include <QString>
#include <QRegExp>
#include <QDebug>

#include "model_singleton.h"

class verification_saisie_utilisateur : public Singleton<verification_saisie_utilisateur>
{
	friend class Singleton<verification_saisie_utilisateur>;

	public:
		verification_saisie_utilisateur();

		bool saisie_nombre_valide_setting_PC_controller(const QString texte_nombre);
		bool saisie_nombre_valide_setting_sample_time(const QString texte_nombre);

	private:
		QRegExp rx;
};

#endif // VERIFICATION_SAISIE_UTILISATEUR_H
