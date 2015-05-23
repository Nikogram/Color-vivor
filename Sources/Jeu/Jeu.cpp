#include "Jeu.hpp"

Jeu::Jeu(ng::Fenetre& fenetre, const std::string& pseudo) :
	m_fenetre(fenetre),
	m_termine(false),
	m_affichage(&m_fenetre.taillePixels(), ng::Pixels),
	m_joueur(fenetre, m_fenetre.taillePixels() / 2.0f, pseudo, false),
	m_client(nullptr)
{
	m_affichage.ajouterTexturePolice(0, "Consolas", false, false, false);
	m_affichage.ajouterTexture(1, "Textures/Personnage - haut.png", true);
	m_affichage.ajouterTexture(2, "Textures/Arme 0.png", true);
	m_affichage.ajouterTexture(3, "Textures/Arme 0 - etincelles.png", true);
	m_affichage.ajouterTexture(4, "Textures/Arme 0 - balle.png", true);
}

Jeu::~Jeu()
{
	reinitialiser();
	deconnecter();
}

bool Jeu::termine() const
{
	return m_termine;
}

int Jeu::identifiantJoueur(const std::string& pseudo) const
{
	for (int i = 0; i < m_autresJoueurs.size(); ++i)
	{
		if (m_autresJoueurs[i].pseudo() == pseudo)
			return i;
	}

	return -1;
}

bool Jeu::actif() const
{
	return m_client != nullptr;
}

void Jeu::modifierPseudo(const std::string& pseudo)
{
	m_joueur.modifierPseudo(pseudo);
}

bool Jeu::connecter(int port, const std::string& adresseIp)
{
	m_client = new ng::ClientTCP(adresseIp, port);

	if (m_client->port() != 0)
		return true;

	deconnecter();
	return false;
}

void Jeu::deconnecter()
{
	if (actif())
	{
		delete m_client;
		m_client = nullptr;
	}
}

void Jeu::reinitialiser()
{
	m_autresJoueurs.clear();
	m_joueur.mettreAJour("", m_fenetre.taillePixels() / 2.0f, 0, 100, 0, glm::vec2(0, 0));
	m_termine = false;
}

void Jeu::envoyerMessageConnexion()
{
	std::vector<std::string> donneesAEnvoyer = { "|connexion client", m_joueur.pseudo(), "connexion client|" };
	m_client->envoyerDonnees(donneesAEnvoyer);
}

void Jeu::afficher()
{
	m_affichage.afficher();
}

void Jeu::mettreAJour(float tempsFrame)
{
	if (actif())
	{
		// Mise à jour de l'affichage
		m_joueur.mettreAJourAffichage(tempsFrame, true);
		for (int i = 0; i < m_autresJoueurs.size(); ++i)
			m_autresJoueurs[i].mettreAJourAffichage(tempsFrame, false);

		m_affichage.reinitialiser();

		m_joueur.ajouterAAffichage(m_affichage);
		for (int i = 0; i < m_autresJoueurs.size(); ++i)
			m_autresJoueurs[i].ajouterAAffichage(m_affichage);

		m_joueur.ajouterAAffichageSuperieur(m_affichage);
		for (int i = 0; i < m_autresJoueurs.size(); ++i)
			m_autresJoueurs[i].ajouterAAffichageSuperieur(m_affichage);


		if (!m_client->connecte() || (m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::Escape) && m_fenetre.active()))
		{
			m_termine = true;
			return;
		}


		// Envoie des données
		int taillePacketPersonnage = 12;
		std::vector<std::string> donneesAEnvoyer = { "|personnage", m_joueur.pseudo(), std::to_string(m_joueur.position().x), std::to_string(m_joueur.position().y), std::to_string(m_joueur.angle()), std::to_string(m_joueur.vie()), std::to_string(m_joueur.identifiantArmeSelectionne()), std::to_string((int)m_joueur.tire()), std::to_string((int)m_joueur.estEnnemi()), std::to_string(m_joueur.coordonneesViseur().x), std::to_string(m_joueur.coordonneesViseur().y), "personnage|" };
		m_client->envoyerDonnees(donneesAEnvoyer);


		// Recupération des données des autres joueurs
		std::vector<std::string> donneesRecues;
		m_client->recevoirDonnees(donneesRecues);

		// Traitement des données des autres joueurs
		int curseur = 0;
		while (curseur < donneesRecues.size())
		{
			if (donneesRecues.size() > curseur + taillePacketPersonnage - 1 && donneesRecues[curseur] == "|personnage" && donneesRecues[curseur + taillePacketPersonnage - 1] == "personnage|")
			{
				if (identifiantJoueur(donneesRecues[curseur + 1]) < 0 && donneesRecues[curseur + 1] != m_joueur.pseudo())
					m_autresJoueurs.push_back(Joueur(m_fenetre, glm::vec2(), donneesRecues[curseur + 1], std::stoi(donneesRecues[curseur + 8])));

				if (identifiantJoueur(donneesRecues[curseur + 1]) >= 0)
				{
					m_autresJoueurs[identifiantJoueur(donneesRecues[curseur + 1])].mettreAJour(donneesRecues[curseur + 1], glm::vec2(std::stof(donneesRecues[curseur + 2]), std::stof(donneesRecues[curseur + 3])), std::stof(donneesRecues[curseur + 4]), std::stof(donneesRecues[curseur + 5]), std::stoi(donneesRecues[curseur + 6]), glm::vec2(std::stof(donneesRecues[curseur + 9]), std::stof(donneesRecues[curseur + 10])));
					if (std::stoi(donneesRecues[curseur + 7]) == 1)
						m_autresJoueurs[identifiantJoueur(donneesRecues[curseur + 1])].tirer();
				}

				curseur += taillePacketPersonnage;
			}
			else if (donneesRecues.size() > curseur + 2 && donneesRecues[curseur] == "|deconnexion" && donneesRecues[curseur + 2] == "deconnexion|")
			{
				if (identifiantJoueur(donneesRecues[curseur + 1]) >= 0)
					m_autresJoueurs.erase(m_autresJoueurs.begin() + identifiantJoueur(donneesRecues[curseur + 1]));

				curseur += 3;
			}
			else
				curseur += 1;
		}
	}
}