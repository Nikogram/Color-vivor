#ifndef _JEU
#define _JEU

#include "../Nikograph/Nikograph.hpp"
#include "Joueur.hpp"

class Jeu
{
	public :
		Jeu(ng::Fenetre& fenetre, const std::string& pseudo);
		~Jeu();
		bool termine() const;
		int identifiantJoueur(const std::string& pseudo) const;
		bool actif() const;
		void modifierPseudo(const std::string& pseudo);
		bool connecter(int port, const std::string& adresseIp);
		void deconnecter();
		void reinitialiser();
		void envoyerMessageConnexion();
		void afficher();
		void mettreAJour(float tempsFrame);

	protected :
		ng::Fenetre& m_fenetre;
		bool m_termine;
		ng::Affichage2D m_affichage;
		Joueur m_joueur;
		std::vector<Joueur> m_autresJoueurs;
		ng::ClientTCP* m_client;
};

#endif
