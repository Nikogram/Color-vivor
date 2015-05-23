#include "CreationServeur.hpp"

CreationServeur::CreationServeur(ng::Fenetre& fenetre) :
	m_fenetre(fenetre),
	m_affichage(&m_fenetre.taillePixels(), ng::RelatifRedimensionneX),
	m_information(0, "Création de la partie en cours...", glm::vec2(0.5, 0.4), 0.05),
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

bool CreationServeur::boutonOKClique() const
{
	return partieCreee() && m_boutonOK.estRelache();
}

bool CreationServeur::boutonRetourClique() const
{
	return !partieCreee() && !enChargement() && m_boutonRetour.estRelache();
}

bool CreationServeur::partieCreee() const
{
	return m_information.chaine() == "La partie a été créée avec succès";
}

bool CreationServeur::enChargement() const
{
	return m_information.chaine() == "Création de la partie en cours...";
}

void CreationServeur::modifierEtat(bool cree)
{
	if (cree)
		m_information.modifierChaine("La partie a été créée avec succès");
	else
		m_information.modifierChaine("Problème lors de la création de la partie");
}

void CreationServeur::reinitialiser()
{
	m_information.modifierChaine("Création de la partie en cours...");
}

void CreationServeur::afficher()
{
	m_affichage.afficher();
}

void CreationServeur::mettreAJour()
{
	m_information.mettreAJourAffichage();
	if (partieCreee())
		m_boutonOK.mettreAJourAffichage();
	else if(!enChargement())
		m_boutonRetour.mettreAJourAffichage();

	m_affichage.reinitialiser();
	m_affichage.ajouterSommets(m_information);
	if (partieCreee())
		m_affichage.ajouterSommets(m_boutonOK);
	else if (!enChargement())
		m_affichage.ajouterSommets(m_boutonRetour);
}