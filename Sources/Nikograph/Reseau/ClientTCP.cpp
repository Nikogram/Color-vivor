#include "ClientTCP.hpp"

ng::ClientTCP::ClientTCP(std::string adresseIp, int port)
{
	m_socket.connect(adresseIp, port);
	m_socket.setBlocking(false);

	std::vector<std::string> donnees;
	recevoirDonnees(donnees);
}

ng::ClientTCP::~ClientTCP()
{
	m_socket.disconnect();
}

std::string ng::ClientTCP::adresseIp() const
{
	return m_socket.getRemoteAddress().toString();
}

int ng::ClientTCP::port() const
{
	return m_socket.getRemotePort();
}

bool ng::ClientTCP::connecte()
{
	sf::Packet packet;
	packet << "¤0";

	if (m_socket.send(packet) == sf::Socket::Disconnected)
		return false;

	return true;
}

void ng::ClientTCP::redemarrer(std::string adresseIp, int port)
{
	m_socket.disconnect();
	m_socket.connect(adresseIp, port);
	m_socket.setBlocking(false);
}

void ng::ClientTCP::envoyerDonnees(const std::vector<std::string>& donnees)
{
	sf::Packet packet;

	for (int i = 0; i < donnees.size(); ++i)
		packet << donnees[i];

	m_socket.send(packet);
}

void ng::ClientTCP::recevoirDonnees(std::vector<std::string>& donnees)
{
	sf::Packet packet;
	std::vector<int> informationsExpediteurs;

	while (m_socket.receive(packet) == sf::UdpSocket::Done)
	{
		while (!packet.endOfPacket())
		{
			std::string donnee;
			packet >> donnee;

			if (donnee.substr() != "¤0")
				donnees.push_back(donnee);
		}
	}
}
