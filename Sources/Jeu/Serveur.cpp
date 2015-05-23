#include "Serveur.hpp"

Serveur::Serveur(ng::Fenetre& fenetre) :
	m_fenetre(fenetre),
	m_serveur(nullptr),
	dernierIA(0)
{
	m_joueurs.push_back(Joueur(m_fenetre, glm::vec2(50, 50), "|" + std::to_string(dernierIA) + "|", true));
	++dernierIA;
}

Serveur::~Serveur()
{
	deconnecter();
}

bool Serveur::actif() const
{
	return m_serveur != nullptr;
}

int Serveur::identifiantJoueur(const std::string& pseudo) const
{
	for (int i = 0; i < m_joueurs.size(); ++i)
	{
		if (m_joueurs[i].pseudo() == pseudo)
			return i;
	}

	return -1;
}

bool Serveur::connecter(int port)
{
	m_serveur = new ng::ServeurTCP(port);

	if (m_serveur->port() != 0)
		return true;

	deconnecter();
	return false;
}

void Serveur::deconnecter()
{
	if (actif())
	{
		delete m_serveur;
		m_serveur = nullptr;
	}

	m_pseudoClients.clear();
	m_joueurs.clear();
	dernierIA = 0;
}

void Serveur::mettreAJour(float tempsFrame)
{
	if (actif())
	{
		// Vérification des nouvelles connexions
		if (m_serveur->verifierNouvellesConnexions())
			m_pseudoClients.push_back("|" + std::to_string(m_pseudoClients.size()));


		// Vérification des déconnexions
		std::vector<int> identifiantMachineDeconnectee = m_serveur->identifiantClientsDeconnectes();
		for (int i = 0; i < identifiantMachineDeconnectee.size(); ++i)
		{
			std::vector<std::string> messageDeconnexion = { "|deconnexion", m_pseudoClients[identifiantMachineDeconnectee[i]], "deconnexion|" };
			m_serveur->envoyerDonnees(messageDeconnexion);
			m_pseudoClients.erase(m_pseudoClients.begin() + identifiantMachineDeconnectee[i]);

			if (identifiantJoueur(m_pseudoClients[identifiantMachineDeconnectee[i]]) >= 0)
				m_joueurs.erase(m_joueurs.begin() + identifiantJoueur(m_pseudoClients[identifiantMachineDeconnectee[i]]));
		}


		// Réception et renvoie des données des clients
		int taillePacketPersonnage = 12;

		for (int i = 0; i < m_serveur->nombreClients(); ++i)
		{
			std::vector<std::string> donneesRecues;
			m_serveur->recevoirDonnees(donneesRecues, i);
			int curseur = 0;
			while (curseur < donneesRecues.size())
			{
				if (donneesRecues.size() > curseur + taillePacketPersonnage - 1 && donneesRecues[curseur] == "|personnage" && donneesRecues[curseur + taillePacketPersonnage - 1] == "personnage|")
				{
					if (identifiantJoueur(donneesRecues[curseur + 1]) < 0)
						m_joueurs.push_back(Joueur(m_fenetre, glm::vec2(), donneesRecues[curseur + 1], false));

					if (identifiantJoueur(donneesRecues[curseur + 1]) >= 0)
					{
						m_joueurs[identifiantJoueur(donneesRecues[curseur + 1])].mettreAJour(donneesRecues[curseur + 1], glm::vec2(std::stof(donneesRecues[curseur + 2]), std::stof(donneesRecues[curseur + 3])), std::stof(donneesRecues[curseur + 4]), std::stof(donneesRecues[curseur + 5]), std::stoi(donneesRecues[curseur + 6]), glm::vec2(std::stof(donneesRecues[curseur + 9]), std::stof(donneesRecues[curseur + 10])));
						if (std::stoi(donneesRecues[curseur + 7]) == 1)
							m_joueurs[identifiantJoueur(donneesRecues[curseur + 1])].tirer();
					}

					std::vector<std::string> donneesEnvoyes;
					donneesEnvoyes.insert(donneesEnvoyes.begin(), donneesRecues.begin() + curseur, donneesRecues.begin() + curseur + taillePacketPersonnage);
					m_serveur->envoyerDonnees(donneesEnvoyes);

					m_pseudoClients[i] = donneesRecues[curseur + 1];
					curseur += taillePacketPersonnage;
				}
				else
					curseur += 1;
			}
		}
	}


	// Envoi des données concernant les ennemis
	for (int i = 0; i < m_joueurs.size(); ++i)
	{
		if (m_joueurs[i].estEnnemi())
		{
			std::vector<std::string> donneesEnnemi = { "|personnage", m_joueurs[i].pseudo(), std::to_string(m_joueurs[i].position().x), std::to_string(m_joueurs[i].position().y), std::to_string(m_joueurs[i].angle()), std::to_string(m_joueurs[i].vie()), std::to_string(m_joueurs[i].identifiantArmeSelectionne()), std::to_string((int)m_joueurs[i].tire()), std::to_string((int)m_joueurs[i].estEnnemi()), std::to_string(m_joueurs[i].coordonneesViseur().x), std::to_string(m_joueurs[i].coordonneesViseur().y), "personnage|" };
			m_serveur->envoyerDonnees(donneesEnnemi);
		}
	}


	// Mise à jour de la position des IA
	for (int i = 0; i < m_joueurs.size(); ++i)
	{
		if (m_joueurs[i].estEnnemi())
		{
			float distanceJoueurLePlusProche = -1;
			int identifiantJoueurLePlusProche = -1;

			for (int j = 0; j < m_joueurs.size(); ++j)
			{
				if (!m_joueurs[j].estEnnemi())
				{
					float distance = glm::length(m_joueurs[i].position() - m_joueurs[j].position());

					if (distance < distanceJoueurLePlusProche || distanceJoueurLePlusProche == -1)
					{
						distanceJoueurLePlusProche = distance;
						identifiantJoueurLePlusProche = j;
					}
				}
			}


			if (identifiantJoueurLePlusProche != -1)
			{
				m_joueurs[i].modifierCoordonneesViseur(m_joueurs[identifiantJoueurLePlusProche].position());

				if (distanceJoueurLePlusProche > 200)
					m_joueurs[i].translater(glm::vec2(0, -100) * tempsFrame);
				if (distanceJoueurLePlusProche < 300)
					m_joueurs[i].tirer();
			}
		}
	}

	for (int i = 0; i < m_joueurs.size(); ++i)
		m_joueurs[i].mettreAJourAffichage(tempsFrame, false);
}