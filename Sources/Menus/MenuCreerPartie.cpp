#include "MenuCreerPartie.hpp"

MenuCreerPartie::MenuCreerPartie(ng::Fenetre& fenetre) :
	m_fenetre(fenetre),
	m_affichage(&m_fenetre.taillePixels(), ng::RelatifRedimensionneX),
	m_titre(0, "Créer une partie", glm::vec2(0.5, 0.2), 0.1),
	m_labelPseudo(0, "Pseudo", glm::vec2(0.25, 0.4), 0.05),
	m_zonePseudo(&m_fenetre.controles(), 0.05, glm::vec2(20, 1), 0, glm::vec2(0.75, 0.4)),
	m_boutonCreer(&m_fenetre.controles(), "Créer", 0.05, 0, glm::vec2(0.75, 0.8)),
	m_boutonRetour(&m_fenetre.controles(), "Retour", 0.05, 0, glm::vec2(0.25, 0.8))
{
	m_affichage.ajouterTexturePolice(0, "Consolas", false, false, false);
	m_boutonCreer.modifierTaille(glm::vec2(0.4, m_boutonCreer.fond().taille().y));
	m_boutonCreer.modifierCouleurPointe(glm::vec4(0.8, 0.8, 0.8, 1));
	m_boutonCreer.modifierCouleurClique(glm::vec4(0.6, 0.6, 0.6, 1));
	m_boutonRetour.modifierTaille(glm::vec2(0.4, m_boutonRetour.fond().taille().y));
	m_boutonRetour.modifierCouleurPointe(glm::vec4(0.8, 0.8, 0.8, 1));
	m_boutonRetour.modifierCouleurClique(glm::vec4(0.6, 0.6, 0.6, 1));
}

bool MenuCreerPartie::boutonCreerClique() const
{
	return m_boutonCreer.estRelache();
}

bool MenuCreerPartie::boutonRetourClique() const
{
	return m_boutonRetour.estRelache();
}

std::string MenuCreerPartie::pseudo() const
{
	return m_zonePseudo.chaine();
}

void MenuCreerPartie::afficher()
{
	m_affichage.afficher();
}

void MenuCreerPartie::mettreAJour()
{
	m_titre.mettreAJourAffichage();
	m_labelPseudo.mettreAJourAffichage();
	m_zonePseudo.mettreAJourAffichage();
	m_boutonCreer.mettreAJourAffichage();
	m_boutonRetour.mettreAJourAffichage();

	m_affichage.reinitialiser();
	m_affichage.ajouterSommets(m_titre);
	m_affichage.ajouterSommets(m_labelPseudo);
	m_affichage.ajouterSommets(m_zonePseudo);
	m_affichage.ajouterSommets(m_boutonCreer);
	m_affichage.ajouterSommets(m_boutonRetour);
}