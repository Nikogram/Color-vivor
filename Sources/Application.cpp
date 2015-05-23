#include "Application.hpp"
#include "Menus/MenuPrincipal.hpp"
#include "Menus/MenuRejoindrePartie.hpp"
#include "Menus/MenuCreerPartie.hpp"
#include "Menus/CreationServeur.hpp"
#include "Menus/ConnexionServeur.hpp"

Application::Application() :
	m_fenetre(ng::RelatifRedimensionneX)
{
}

Application::~Application()
{
}

bool Application::initialiser()
{
	srand(time(0));

	return m_fenetre.initialiserAffichage(glm::vec2(800, 600), "Survivor");;
}

bool Application::lancerServeur(Jeu& jeu, Serveur& serveur)
{
	if (serveur.connecter(49000) && jeu.connecter(49000, "localhost"))
		return true;
	
	jeu.deconnecter();
	serveur.deconnecter();
	return false;
}

bool Application::rejoindreServeur(std::string adresseIp, Jeu& jeu)
{
	if (jeu.connecter(49000, adresseIp))
		return true;

	jeu.deconnecter();
	return false;
}

void Application::lancer()
{
	int pageAAfficher = 0;	// 0 : menu principal, 1 : menu "Rejoindre une partie", 2 : menu "Créer une partie", 3 : création du serveur, 4 : connexion au serveur, 5 : jeu
	MenuPrincipal menuPrincipal(m_fenetre);
	MenuRejoindrePartie menuRejoindrePartie(m_fenetre);
	MenuCreerPartie menuCreerPartie(m_fenetre);
	CreationServeur creationServeur(m_fenetre);
	ConnexionServeur connexionServeur(m_fenetre);
	bool doitSeConnecter = false;
	bool doitCreerServeur = false;
	Serveur m_serveur(m_fenetre);
	Jeu m_jeu(m_fenetre, "");

	while (!m_fenetre.fermer()/* && !(m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::Escape) && m_fenetre.active())*/)
	{
		//std::cout << (int)(1 / m_fenetre.tempsDerniereFrame()) << std::endl;

		// Gestion des évenements
		if (doitSeConnecter)
		{
			connexionServeur.modifierEtat(rejoindreServeur(menuRejoindrePartie.adresseIpServeur(), m_jeu));
			doitSeConnecter = false;
		}
		else if (doitCreerServeur)
		{
			creationServeur.modifierEtat(lancerServeur(m_jeu, m_serveur));
			doitCreerServeur = false;
		}

		if (pageAAfficher == 0)	// Menu principal
		{
			if (menuPrincipal.boutonRejoindrePartieClique())
				pageAAfficher = 1;
			else if (menuPrincipal.boutonCreerPartieClique())
				pageAAfficher = 2;
			else if (menuPrincipal.boutonQuitterClique())
				break;
		}
		else if (pageAAfficher == 1)	// menu pour rejoindre une partie
		{
			if (menuRejoindrePartie.boutonRetourClique())
				pageAAfficher = 0;
			else if(menuRejoindrePartie.boutonConnexionClique())
			{
				pageAAfficher = 4;
				doitSeConnecter = true;
				connexionServeur.reinitialiser();
			}
		}
		else if (pageAAfficher == 2)	// menu pour créer une partie
		{
			if (menuCreerPartie.boutonRetourClique())
				pageAAfficher = 0;
			else if (menuCreerPartie.boutonCreerClique())
			{
				pageAAfficher = 3;
				doitCreerServeur = true;
				creationServeur.reinitialiser();
			}
		}
		else if (pageAAfficher == 3)	// création de la partie
		{
			if (creationServeur.boutonRetourClique())
				pageAAfficher = 2;
			else if (creationServeur.boutonOKClique())
			{
				pageAAfficher = 5;
				m_jeu.modifierPseudo(menuCreerPartie.pseudo());
			}
		}
		else if (pageAAfficher == 4)	// connexion à une partie
		{
			if (connexionServeur.boutonRetourClique())
				pageAAfficher = 1;
			else if (connexionServeur.boutonOKClique())
			{
				pageAAfficher = 5;
				m_jeu.modifierPseudo(menuRejoindrePartie.pseudo());
			}
		}
		else if (pageAAfficher == 5)	// écran de jeu
		{
			if (m_jeu.termine())
			{
				pageAAfficher = 0;
				m_jeu.reinitialiser();

				m_jeu.deconnecter();
				m_serveur.deconnecter();
			}
		}


		// Mise à jour de l'affichage
		m_fenetre.recupererEvenements();
		if (pageAAfficher == 0)
			menuPrincipal.mettreAJour();
		else if (pageAAfficher == 1)
			menuRejoindrePartie.mettreAJour();
		else if (pageAAfficher == 2)
			menuCreerPartie.mettreAJour();
		else if (pageAAfficher == 3)
			creationServeur.mettreAJour();
		else if (pageAAfficher == 4)
			connexionServeur.mettreAJour();
		else if (pageAAfficher == 5)
		{
			m_serveur.mettreAJour(m_fenetre.tempsDerniereFrame());
			m_jeu.mettreAJour(m_fenetre.tempsDerniereFrame());
		}


		// Affichage
		m_fenetre.demarrerAffichage();

		if (pageAAfficher == 0)
			menuPrincipal.afficher();
		else if (pageAAfficher == 1)
			menuRejoindrePartie.afficher();
		else if (pageAAfficher == 2)
			menuCreerPartie.afficher();
		else if (pageAAfficher == 3)
			creationServeur.afficher();
		else if (pageAAfficher == 4)
			connexionServeur.afficher();
		else if (pageAAfficher == 5)
			m_jeu.afficher();

		m_fenetre.terminerAffichage();
	}
}
