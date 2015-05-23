#include "Fenetre.hpp"

ng::Fenetre::Fenetre(GrandeurMetrique grandeurMetriqueControles) :
	m_fenetre(nullptr),
	m_tempsDerniereFrame(0),
	m_taillePixels(0, 0),
	m_controles(m_fenetre, m_taillePixels, grandeurMetriqueControles),
	m_fermer(false),
	m_active(true)
{
	m_controles.modifierTactileActive(false);
}

ng::Fenetre::~Fenetre()
{
	delete m_fenetre;
}

const glm::vec2& ng::Fenetre::taillePixels() const
{
	return m_taillePixels;
}

float ng::Fenetre::ratio(bool inverse) const
{
	return (inverse ? m_taillePixels.y / m_taillePixels.x : m_taillePixels.x / m_taillePixels.y);
}

float ng::Fenetre::tempsDerniereFrame() const
{
	return m_tempsDerniereFrame;
}

const ng::Controles& ng::Fenetre::controles()
{
	return m_controles;
}

bool ng::Fenetre::fermer() const
{
	return m_fermer;
}

bool ng::Fenetre::active() const
{
	return m_active;
}

bool ng::Fenetre::initialiserAffichage(const glm::vec2& taillePixelsFenetre, const std::string& titreFenetre)
{
	// Initialisation du contexte OpenGL
	m_parametresContexte.depthBits = 32;
	m_parametresContexte.stencilBits = 8;
	m_parametresContexte.antialiasingLevel = 4;
	m_parametresContexte.majorVersion = 3;
	m_parametresContexte.minorVersion = 3;


	// Initialisation de la fenêtre SFML
	m_fenetre = new sf::Window(sf::VideoMode(taillePixelsFenetre.x, taillePixelsFenetre.y), titreFenetre, sf::Style::Default, m_parametresContexte);
	m_fenetre->setFramerateLimit(60);
	m_fenetre->setVerticalSyncEnabled(false);
	m_taillePixels = glm::vec2(m_fenetre->getSize().x, m_fenetre->getSize().y);
	m_controles.modifierFenetre(m_fenetre);


	//Initialize de GLEW
	if (glewInit() != GLEW_OK)
		return false;


	// Configuration de OpenGL
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, m_fenetre->getSize().x, m_fenetre->getSize().y);

	return true;
}

void ng::Fenetre::recupererEvenements()
{
	sf::Event evenement;

	m_controles.reinitialiser();
	m_controles.recupererEntrees();

	while (m_fenetre->pollEvent(evenement))
	{
		m_controles.recupererCaractereEntre(evenement);

		if (evenement.type == sf::Event::Closed)
			m_fermer = true;
		if (evenement.type == sf::Event::Resized)
		{
			glViewport(0, 0, evenement.size.width, evenement.size.height);
			m_taillePixels = glm::vec2(evenement.size.width, evenement.size.height);
		}
		if (evenement.type == sf::Event::LostFocus)
			m_active = false;
		if (evenement.type == sf::Event::GainedFocus)
			m_active = true;
	}
}

void ng::Fenetre::demarrerAffichage()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
}

void ng::Fenetre::terminerAffichage()
{
	m_fenetre->display();

	m_tempsDerniereFrame = m_horloge.restart().asSeconds();
}