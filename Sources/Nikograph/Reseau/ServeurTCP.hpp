#ifndef _SERVEURTCP
#define _SERVEURTCP

#include "../BibliothequesExternes.hpp"

namespace ng
{
	class ServeurTCP
	{
		public:
			ServeurTCP(int port = -1);
			~ServeurTCP();
			int port() const;
			int nombreClients() const;
			int identifiantClient(std::string adresseIp) const;
			std::string adresseIpClient(int identifiant) const;
			void deconnecterClient(int identifiant);
			bool verifierNouvellesConnexions();
			std::vector<std::string> adresseIpClientsDeconnectes();
			std::vector<int> identifiantClientsDeconnectes();
			void envoyerDonnees(const std::vector<std::string>& donnees, int identifiantDestinataire = -1, bool envoyerAuServeur = false);
			void recevoirDonnees(std::vector<std::string>& donnees, int identifiantExpediteur = -1, bool renvoyerAToutLeMonde = false);

		protected :
			sf::TcpListener m_socketEcoute;
			std::vector<sf::TcpSocket*> m_socketClients;
			std::vector<std::string> m_donneesRecuesEnAttente;
	};
}

#endif


/*
¤0 : vérification de la connexion
*/