#ifndef _MENUREJOINDREPARTIE
#define _MENUREJOINDREPARTIE

#include "../Nikograph/Nikograph.hpp"

class MenuRejoindrePartie
{
	public :
		MenuRejoindrePartie(ng::Fenetre& fenetre);
		bool boutonConnexionClique() const;
		bool boutonRetourClique() const;
		std::string pseudo() const;
		std::string adresseIpServeur() const;
		void afficher();
		void mettreAJour();

	protected :
		ng::Fenetre& m_fenetre;
		ng::Affichage2D m_affichage;
		ng::Texte2D m_titre;
		ng::Texte2D m_labelPseudo;
		ng::ZoneTexte2D m_zonePseudo;
		ng::Texte2D m_labelAdresseIpServeur;
		ng::ZoneTexte2D m_zoneAdresseIpServeur;
		ng::Bouton2D m_boutonConnexion;
		ng::Bouton2D m_boutonRetour;
};

#endif
