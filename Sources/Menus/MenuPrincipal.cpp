#include "MenuPrincipal.hpp"

MenuPrincipal::MenuPrincipal(ng::Fenetre& fenetre) :
	m_fenetre(fenetre),
	m_affichage(&m_fenetre.taillePixels(), ng::RelatifRedimensionneX),
	m_titre(0, "Survivor", glm::vec2(0.5, 0.2), 0.1),
	m_boutonCreerPartie(&m_fenetre.controles(), "Créer une partie", 0.05, 0, glm::vec2(0.5, 0.5)),
	m_boutonRejoindrePartie(&m_fenetre.controles(), "Rejoindre une partie", 0.05, 0, glm::vec2(0.5, 0.7)),
	m_boutonQuitter(&m_fenetre.controles(), "Quitter", 0.05, 0, glm::vec2(0.5, 0.9))
{
	m_affichage.ajouterTexturePolice(0, "Consolas", false, false, false);
	m_boutonCreerPartie.modifierTaille(glm::vec2(0.7, m_boutonCreerPartie.fond().taille().y));
	m_boutonCreerPartie.modifierCouleurPointe(glm::vec4(0.8, 0.8, 0.8, 1));
	m_boutonCreerPartie.modifierCouleurClique(glm::vec4(0.6, 0.6, 0.6, 1));
	m_boutonRejoindrePartie.modifierTaille(glm::vec2(0.7, m_boutonRejoindrePartie.fond().taille().y));
	m_boutonRejoindrePartie.modifierCouleurPointe(glm::vec4(0.8, 0.8, 0.8, 1));
	m_boutonRejoindrePartie.modifierCouleurClique(glm::vec4(0.6, 0.6, 0.6, 1));
	m_boutonQuitter.modifierTaille(glm::vec2(0.7, m_boutonRejoindrePartie.fond().taille().y));
	m_boutonQuitter.modifierCouleurPointe(glm::vec4(0.8, 0.8, 0.8, 1));
	m_boutonQuitter.modifierCouleurClique(glm::vec4(0.6, 0.6, 0.6, 1));
}

bool MenuPrincipal::boutonCreerPartieClique() const
{
	return m_boutonCreerPartie.estRelache();
}

bool MenuPrincipal::boutonRejoindrePartieClique() const
{
	return m_boutonRejoindrePartie.estRelache();
}

bool MenuPrincipal::boutonQuitterClique() const
{
	return m_boutonQuitter.estRelache();
}

void MenuPrincipal::afficher()
{
	m_affichage.afficher();
}

void MenuPrincipal::mettreAJour()
{
	m_titre.mettreAJourAffichage();
	m_boutonCreerPartie.mettreAJourAffichage();
	m_boutonRejoindrePartie.mettreAJourAffichage();
	m_boutonQuitter.mettreAJourAffichage();

	m_affichage.reinitialiser();
	m_affichage.ajouterSommets(m_titre);
	m_affichage.ajouterSommets(m_boutonCreerPartie);
	m_affichage.ajouterSommets(m_boutonRejoindrePartie);
	m_affichage.ajouterSommets(m_boutonQuitter);
}