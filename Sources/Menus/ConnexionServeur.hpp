#ifndef _CONNEXIONSERVEUR
#define _CONNEXIONSERVEUR

#include "../Nikograph/Nikograph.hpp"

class ConnexionServeur
{
	public :
		ConnexionServeur(ng::Fenetre& fenetre);
		bool boutonOKClique() const;
		bool boutonRetourClique() const;
		bool partieCreee() const;
		bool enChargement() const;
		void modifierEtat(bool connecte);
		void reinitialiser();
		void afficher();
		void mettreAJour();

	protected :
		ng::Fenetre& m_fenetre;
		ng::Affichage2D m_affichage;
		ng::Texte2D m_information;
		ng::Bouton2D m_boutonOK;
		ng::Bouton2D m_boutonRetour;
};

#endif
