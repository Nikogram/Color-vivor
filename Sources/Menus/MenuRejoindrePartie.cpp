#include "MenuRejoindrePartie.hpp"

MenuRejoindrePartie::MenuRejoindrePartie(ng::Fenetre& fenetre) :
	m_fenetre(fenetre),
	m_affichage(&m_fenetre.taillePixels(), ng::RelatifRedimensionneX),
	m_titre(0, "Rejoindre une partie", glm::vec2(0.5, 0.2), 0.1),
	m_labelPseudo(0, "Pseudo", glm::vec2(0.25, 0.4), 0.05),
	m_zonePseudo(&m_fenetre.controles(), 0.05, glm::vec2(20, 1), 0, glm::vec2(0.75, 0.4)),
	m_labelAdresseIpServeur(0, "Adresse IP serveur", glm::vec2(0.25, 0.6), 0.05),
	m_zoneAdresseIpServeur(&m_fenetre.controles(), 0.05, glm::vec2(20, 1), 0, glm::vec2(0.75, 0.6)),
	m_boutonConnexion(&m_fenetre.controles(), "Connexion", 0.05, 0, glm::vec2(0.75, 0.8)),
	m_boutonRetour(&m_fenetre.controles(), "Retour", 0.05, 0, glm::vec2(0.25, 0.8))
{
	m_affichage.ajouterTexturePolice(0, "Consolas", false, false, false);
	m_boutonConnexion.modifierTaille(glm::vec2(0.4, m_boutonConnexion.fond().taille().y));
	m_boutonConnexion.modifierCouleurPointe(glm::vec4(0.8, 0.8, 0.8, 1));
	m_boutonConnexion.modifierCouleurClique(glm::vec4(0.6, 0.6, 0.6, 1));
	m_boutonRetour.modifierTaille(glm::vec2(0.4, m_boutonRetour.fond().taille().y));
	m_boutonRetour.modifierCouleurPointe(glm::vec4(0.8, 0.8, 0.8, 1));
	m_boutonRetour.modifierCouleurClique(glm::vec4(0.6, 0.6, 0.6, 1));
}

bool MenuRejoindrePartie::boutonConnexionClique() const
{
	return m_boutonConnexion.estRelache();
}

bool MenuRejoindrePartie::boutonRetourClique() const
{
	return m_boutonRetour.estRelache();
}

std::string MenuRejoindrePartie::pseudo() const
{
	return m_zonePseudo.chaine();
}

std::string MenuRejoindrePartie::adresseIpServeur() const
{
	return m_zoneAdresseIpServeur.chaine();
}

void MenuRejoindrePartie::afficher()
{
	m_affichage.afficher();
}

void MenuRejoindrePartie::mettreAJour()
{
	m_labelPseudo.modifierPosition(glm::vec2(0.25 + (m_labelAdresseIpServeur.taille().x - m_labelPseudo.taille().x) * m_fenetre.ratio(true) / 2, 0.4));

	m_titre.mettreAJourAffichage();
	m_labelPseudo.mettreAJourAffichage();
	m_zonePseudo.mettreAJourAffichage();
	m_labelAdresseIpServeur.mettreAJourAffichage();
	m_zoneAdresseIpServeur.mettreAJourAffichage();
	m_boutonConnexion.mettreAJourAffichage();
	m_boutonRetour.mettreAJourAffichage();

	m_affichage.reinitialiser();
	m_affichage.ajouterSommets(m_titre);
	m_affichage.ajouterSommets(m_labelPseudo);
	m_affichage.ajouterSommets(m_zonePseudo);
	m_affichage.ajouterSommets(m_labelAdresseIpServeur);
	m_affichage.ajouterSommets(m_zoneAdresseIpServeur);
	m_affichage.ajouterSommets(m_boutonConnexion);
	m_affichage.ajouterSommets(m_boutonRetour);
}