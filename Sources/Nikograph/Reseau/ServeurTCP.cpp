#include "ServeurTCP.hpp"

ng::ServeurTCP::ServeurTCP(int port)
{
	m_socketEcoute.listen(port == -1 ? sf::Socket::AnyPort : port);
	m_socketEcoute.setBlocking(false);
}

ng::ServeurTCP::~ServeurTCP()
{
	for (int i = 0; i < m_socketClients.size(); ++i)
	{
		m_socketClients[i]->disconnect();
		delete m_socketClients[i];
	}
}

int ng::ServeurTCP::port() const
{
	return m_socketEcoute.getLocalPort();
}

int ng::ServeurTCP::nombreClients() const
{
	return m_socketClients.size();
}

int ng::ServeurTCP::identifiantClient(std::string adresseIp) const
{
	for (int i = 0; i < m_socketClients.size(); ++i)
	{
		if (m_socketClients[i]->getRemoteAddress().toString() == adresseIp)
			return i;
	}

	return -1;
}

std::string ng::ServeurTCP::adresseIpClient(int identifiant) const
{
	if (identifiant >= 0 && identifiant < nombreClients())
		return m_socketClients[identifiant]->getRemoteAddress().toString();
	
	return "";
}

void ng::ServeurTCP::deconnecterClient(int identifiant)
{
	if (identifiant >= 0 && identifiant < m_socketClients.size())
	{
		m_socketClients[identifiant]->disconnect();
		delete m_socketClients[identifiant];
		m_socketClients.erase(m_socketClients.begin() + identifiant);
	}
}

bool ng::ServeurTCP::verifierNouvellesConnexions()
{
	sf::TcpSocket* client = new sf::TcpSocket();
	if (m_socketEcoute.accept(*client) == sf::Socket::Done)
	{
		client->setBlocking(false);
		m_socketClients.push_back(client);
		return true;
	}

	client->disconnect();
	delete client;
	return false;
}

std::vector<std::string> ng::ServeurTCP::adresseIpClientsDeconnectes()
{
	std::vector<std::string> adresseIpClientsDeconnectes;

	for (int i = m_socketClients.size() - 1; i >= 0; --i)
	{
		sf::Packet packet;
		packet << "¤0";

		if (m_socketClients[i]->send(packet) == sf::Socket::Disconnected)
		{
			adresseIpClientsDeconnectes.push_back(m_socketClients[i]->getRemoteAddress().toString());
			m_socketClients[i]->disconnect();
			delete m_socketClients[i];
			m_socketClients.erase(m_socketClients.begin() + i);
		}
	}

	return adresseIpClientsDeconnectes;
}

std::vector<int> ng::ServeurTCP::identifiantClientsDeconnectes()
{
	std::vector<int> identifiantClientsDeconnectes;

	for (int i = m_socketClients.size() - 1; i >= 0; --i)
	{
		sf::Packet packet;
		packet << "¤0";

		if (m_socketClients[i]->send(packet) == sf::Socket::Disconnected)
		{
			identifiantClientsDeconnectes.push_back(i);
			m_socketClients[i]->disconnect();
			delete m_socketClients[i];
			m_socketClients.erase(m_socketClients.begin() + i);
		}
	}

	return identifiantClientsDeconnectes;
}

void ng::ServeurTCP::envoyerDonnees(const std::vector<std::string>& donnees, int identifiantDestinataire, bool envoyerAuServeur)
{
	sf::Packet packet;

	for (int i = 0; i < donnees.size(); ++i)
		packet << donnees[i];

	for (int i = 0; i < m_socketClients.size(); ++i)
	{
		if (identifiantDestinataire == -1 || i == identifiantDestinataire)
			m_socketClients[i]->send(packet);
	}

	if (envoyerAuServeur)
		m_donneesRecuesEnAttente.insert(m_donneesRecuesEnAttente.end(), donnees.begin(), donnees.end());
}

void ng::ServeurTCP::recevoirDonnees(std::vector<std::string>& donnees, int identifiantExpediteur, bool renvoyerAToutLeMonde)
{
	std::vector<std::string> donneesRecuperees;

	for (int i = 0; i < m_socketClients.size(); ++i)
	{
		if (identifiantExpediteur == -1 || i == identifiantExpediteur)
		{
			sf::Packet packet;

			while (m_socketClients[i]->receive(packet) == sf::UdpSocket::Done)
			{
				while (!packet.endOfPacket())
				{
					std::string donnee;
					packet >> donnee;

					if (donnee != "¤0")
						donneesRecuperees.push_back(donnee);
				}
			}
		}
	}

	if (renvoyerAToutLeMonde)
		envoyerDonnees(donneesRecuperees);

	donneesRecuperees.insert(donneesRecuperees.end(), m_donneesRecuesEnAttente.begin(), m_donneesRecuesEnAttente.end());
	m_donneesRecuesEnAttente.clear();
	donnees = donneesRecuperees;
}