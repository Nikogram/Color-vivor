#ifndef _MENUPRINCIPAL
#define _MENUPRINCIPAL

#include "../Nikograph/Nikograph.hpp"

class MenuPrincipal
{
	public :
		MenuPrincipal(ng::Fenetre& fenetre);
		bool boutonCreerPartieClique() const;
		bool boutonRejoindrePartieClique() const;
		bool boutonQuitterClique() const;
		void afficher();
		void mettreAJour();

	protected :
		ng::Fenetre& m_fenetre;
		ng::Affichage2D m_affichage;
		ng::Texte2D m_titre;
		ng::Bouton2D m_boutonCreerPartie;
		ng::Bouton2D m_boutonRejoindrePartie;
		ng::Bouton2D m_boutonQuitter;
};

#endif
