#ifndef _SERVEUR
#define _SERVEUR

#include "../Nikograph/Nikograph.hpp"
#include "Joueur.hpp"

class Serveur
{
	public :
		Serveur(ng::Fenetre& fenetre);
		~Serveur();
		bool actif() const;
		int identifiantJoueur(const std::string& pseudo) const;
		bool connecter(int port);
		void deconnecter();
		void mettreAJour(float tempsFrame);

	protected :
		ng::Fenetre& m_fenetre;
		ng::ServeurTCP* m_serveur;
		std::vector<std::string> m_pseudoClients;
		std::vector<Joueur> m_joueurs;
		int dernierIA;
};

#endif
