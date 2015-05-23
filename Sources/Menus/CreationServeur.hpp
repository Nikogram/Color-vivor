#ifndef _CREATIONSERVEUR
#define _CREATIONSERVEUR

#include "../Nikograph/Nikograph.hpp"

class CreationServeur
{
	public :
		CreationServeur(ng::Fenetre& fenetre);
		bool boutonOKClique() const;
		bool boutonRetourClique() const;
		bool partieCreee() const;
		bool enChargement() const;
		void modifierEtat(bool cree);
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
