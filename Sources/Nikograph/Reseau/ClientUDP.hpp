#ifndef _CLIENTUDP
#define _CLIENTUDP

#include "../BibliothequesExternes.hpp"

namespace ng
{
	class ClientUDP
	{
		public:
			ClientUDP(int port = -1);
			bool connecte() const;
			int port() const;
			void redemarrer(int port);
			void envoyerDonnees(const std::vector<std::string>& donnees, int port, const std::string& adresseIpDestinataire = "");
			std::vector<int> recevoirDonnees(std::vector<std::string>& donnees);

		protected :
			sf::UdpSocket m_socket;
	};
}

#endif
