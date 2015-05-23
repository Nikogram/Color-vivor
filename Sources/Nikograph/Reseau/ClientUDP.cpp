#include "ClientUDP.hpp"

ng::ClientUDP::ClientUDP(int port)
{
	m_socket.bind(port == -1 ? sf::Socket::AnyPort : port);
	m_socket.setBlocking(false);
}

bool ng::ClientUDP::connecte() const
{
	return port() != 0;
}

int ng::ClientUDP::port() const
{
	return m_socket.getLocalPort();
}

void ng::ClientUDP::redemarrer(int port)
{
	m_socket.unbind();
	m_socket.bind(port);
	m_socket.setBlocking(false);
}

void ng::ClientUDP::envoyerDonnees(const std::vector<std::string>& donnees, int port, const std::string& adresseIpDestinataire)
{
	sf::Packet packet;

	for (int i = 0; i < donnees.size(); ++i)
		packet << donnees[i];

	if (adresseIpDestinataire == "")
		m_socket.send(packet, sf::IpAddress::Broadcast, port);
	else
		m_socket.send(packet, adresseIpDestinataire, port);
}

std::vector<int> ng::ClientUDP::recevoirDonnees(std::vector<std::string>& donnees)
{
	sf::Packet packet;
	sf::IpAddress adresseIpExpediteur;
	unsigned short portExpediteur = 0;
	std::vector<int> informationsExpediteurs;

	while (m_socket.receive(packet, adresseIpExpediteur, portExpediteur) == sf::UdpSocket::Done)
	{
		while (!packet.endOfPacket())
		{
			std::string donnee;
			packet >> donnee;
			donnees.push_back(donnee);

			informationsExpediteurs.push_back(adresseIpExpediteur.toInteger());
			informationsExpediteurs.push_back(portExpediteur);
		}
	}

	return informationsExpediteurs;
}
