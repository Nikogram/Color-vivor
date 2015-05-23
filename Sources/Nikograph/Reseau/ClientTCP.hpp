#ifndef _CLIENTTCP
#define _CLIENTTCP

#include "../BibliothequesExternes.hpp"

namespace ng
{
	class ClientTCP
	{
		public :
			ClientTCP(std::string adresseIp, int port);
			~ClientTCP();
			std::string adresseIp() const;
			int port() const;
			bool connecte();
			void redemarrer(std::string adresseIp, int port);
			void envoyerDonnees(const std::vector<std::string>& donnees);
			void recevoirDonnees(std::vector<std::string>& donnees);

		protected :
			sf::TcpSocket m_socket;
	};
}

#endif
