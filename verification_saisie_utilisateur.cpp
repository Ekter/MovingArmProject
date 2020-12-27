#include "verification_saisie_utilisateur.h"

verification_saisie_utilisateur::verification_saisie_utilisateur()
{
}

bool verification_saisie_utilisateur::saisie_nombre_valide_setting_PC_controller(const QString texte_nombre)
{
	if(texte_nombre.contains("."))
		rx.setPattern("^[0-9-]+[0-9.]+[0-9]$");
	else if(texte_nombre.length() == 1)
		rx.setPattern("(\\d)");
	else
		rx.setPattern("^[0-9-]+(\\d+)");

	if (rx.exactMatch(texte_nombre))
		return true;

	return false;
}

bool verification_saisie_utilisateur::saisie_nombre_valide_setting_sample_time(const QString texte_nombre)
{
	rx.setPattern("(\\d+)");

	if (rx.exactMatch(texte_nombre))
		return true;

	return false;
}
