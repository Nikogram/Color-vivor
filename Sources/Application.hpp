#ifndef _APPLICATION
#define _APPLICATION

#include "Nikograph\Nikograph.hpp"
#include "Jeu/Jeu.hpp"
#include "Jeu/Serveur.hpp"

class Application
{
	public :
		Application();
		~Application();
		bool initialiser();
		bool lancerServeur(Jeu& jeu, Serveur& serveur);
		bool rejoindreServeur(std::string adresseIp, Jeu& jeu);
		void lancer();

	protected :
		ng::Fenetre m_fenetre;
};

#endif
