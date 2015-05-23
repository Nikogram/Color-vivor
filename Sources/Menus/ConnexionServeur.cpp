#include "ConnexionServeur.hpp"

ConnexionServeur::ConnexionServeur(ng::Fenetre& fenetre) :
	m_fenetre(fenetre),
	m_affichage(&m_fenetre.taillePixels(), ng::RelatifRedimensionneX),
	m_information(0, "Connexion à la partie en cours...", glm::vec2(0.5, 0.4), 0.05),
	m_boutonOK(&m_fenetre.controles(), "OK", 0.05, 0, glm::vec2(0.5, 0.8)),
	m_boutonRetour(&m_fenetre.controles(), "OK", 0.05, 0, glm::vec2(0.5, 0.8))
{
	m_affichage.ajouterTexturePolice(0, "Consolas", false, false, false);
	m_boutonOK.modifierTaille(glm::vec2(0.4, m_boutonOK.fond().taille().y));
	m_boutonOK.modifierCouleurPointe(glm::vec4(0.8, 0.8, 0.8, 1));
	m_boutonOK.modifierCouleurClique(glm::vec4(0.6, 0.6, 0.6, 1));
	m_boutonRetour.modifierTaille(glm::vec2(0.4, m_boutonRetour.fond().taille().y));
	m_boutonRetour.modifierCouleurPointe(glm::vec4(0.8, 0.8, 0.8, 1));
	m_boutonRetour.modifierCouleurClique(glm::vec4(0.6, 0.6, 0.6, 1));
}

bool ConnexionServeur::boutonOKClique() const
{
	return partieCreee() && m_boutonOK.estRelache();
}

bool ConnexionServeur::boutonRetourClique() const
{
	return !partieCreee() && !enChargement() && m_boutonRetour.estRelache();
}

bool ConnexionServeur::partieCreee() const
{
	return m_information.chaine() == "La partie a été rejointe avec succès";
}

bool ConnexionServeur::enChargement() const
{
	return m_information.chaine() == "Connexion à la partie en cours...";
}

void ConnexionServeur::modifierEtat(bool connecte)
{
	if (connecte)
		m_information.modifierChaine("La partie a été rejointe avec succès");
	else
		m_information.modifierChaine("Problème lors de la connexion à la partie");
}

void ConnexionServeur::reinitialiser()
{
	m_information.modifierChaine("Connexion à la partie en cours...");
}

void ConnexionServeur::afficher()
{
	m_affichage.afficher();
}

void ConnexionServeur::mettreAJour()
{
	m_information.mettreAJourAffichage();
	if (partieCreee())
		m_boutonOK.mettreAJourAffichage();
	else if (!enChargement())
		m_boutonRetour.mettreAJourAffichage();

	m_affichage.reinitialiser();
	m_affichage.ajouterSommets(m_information);
	if (partieCreee())
		m_affichage.ajouterSommets(m_boutonOK);
	else if (!enChargement())
		m_affichage.ajouterSommets(m_boutonRetour);
}