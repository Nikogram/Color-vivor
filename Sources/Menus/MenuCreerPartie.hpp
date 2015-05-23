#ifndef _MENUCREERPARTIE
#define _MENUCREERPARTIE

#include "../Nikograph/Nikograph.hpp"

class MenuCreerPartie
{
	public :
		MenuCreerPartie(ng::Fenetre& fenetre);
		bool boutonCreerClique() const;
		bool boutonRetourClique() const;
		std::string pseudo() const;
		void afficher();
		void mettreAJour();

	protected :
		ng::Fenetre& m_fenetre;
		ng::Affichage2D m_affichage;
		ng::Texte2D m_titre;
		ng::Texte2D m_labelPseudo;
		ng::ZoneTexte2D m_zonePseudo;
		ng::Bouton2D m_boutonCreer;
		ng::Bouton2D m_boutonRetour;
};

#endif
