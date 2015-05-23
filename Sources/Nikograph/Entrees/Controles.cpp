#include "Controles.hpp"

ng::Controles::Controles(const sf::Window* fenetre, glm::vec2& taillePixelsFenetre, ng::GrandeurMetrique grandeurMetrique, int nombreDoigts) :
	m_fenetre(fenetre),
	m_taillePixelsFenetre(taillePixelsFenetre),
	m_grandeurMetrique(grandeurMetrique),
	m_caractereEntre(0),
	m_tactileActive(false)
{
	for (int i = 0; i < nombreDoigts; ++i)
	{
		m_doigts.push_back(Doigt());
		m_doigts[i].position = glm::vec2(-1, -1);
	}

	m_souris.boutonGaucheAppuye = false;
	m_souris.boutonDroiteAppuye = false;
}

int ng::Controles::identifiantDoigtDansRectangle(const Rectangle2D& rectangle) const
{
	for (int i = 0; i < m_doigts.size() && m_tactileActive; ++i)
	{
		if (ng::rayonTriangle3DEnCollision(glm::vec3(m_doigts[i].position, 1), glm::vec3(0, 0, -1), glm::vec3(rectangle.coordonneesSommet(0), 0), glm::vec3(rectangle.coordonneesSommet(1), 0), glm::vec3(rectangle.coordonneesSommet(2), 0))
			|| ng::rayonTriangle3DEnCollision(glm::vec3(m_doigts[i].position, 1), glm::vec3(0, 0, -1), glm::vec3(rectangle.coordonneesSommet(3), 0), glm::vec3(rectangle.coordonneesSommet(4), 0), glm::vec3(rectangle.coordonneesSommet(5), 0)))
			return i;
	}

	return -1;
}

bool ng::Controles::doigtPose(int identifiantDoigt) const
{
	if (identifiantDoigt >= 0 && identifiantDoigt < m_doigts.size() && m_tactileActive)
		return m_doigts[identifiantDoigt].pose;
	return false;
}

bool ng::Controles::doigtRetire(int identifiantDoigt) const
{
	if (identifiantDoigt >= 0 && identifiantDoigt < m_doigts.size() && m_tactileActive)
		return m_doigts[identifiantDoigt].retire;
	return false;
}

bool ng::Controles::doigtBouge(int identifiantDoigt) const
{
	if (identifiantDoigt >= 0 && identifiantDoigt < m_doigts.size() && m_tactileActive)
		return (m_doigts[identifiantDoigt].deplacement != glm::vec2(0, 0));
	return false;
}

bool ng::Controles::ecranToucheParDoigt(int identifiantDoigt) const
{
	if (identifiantDoigt >= 0 && identifiantDoigt < m_doigts.size() && m_tactileActive)
		return m_doigts[identifiantDoigt].ecranTouche;
	return false;
}

glm::vec2 ng::Controles::positionDoigt(int identifiantDoigt) const
{
	if (identifiantDoigt >= 0 && identifiantDoigt < m_doigts.size() && m_tactileActive)
		return m_doigts[identifiantDoigt].position;
	return glm::vec2();
}

glm::vec2 ng::Controles::deplacementDoigt(int identifiantDoigt) const
{
	if (identifiantDoigt >= 0 && identifiantDoigt < m_doigts.size() && m_tactileActive)
		return m_doigts[identifiantDoigt].deplacement;
	return glm::vec2();
}

bool ng::Controles::sourisDansRectangle(const Rectangle2D& rectangle) const
{
	return (ng::rayonTriangle3DEnCollision(glm::vec3(m_souris.position, 1), glm::vec3(0, 0, -1), glm::vec3(coordonneesSommetRectangleAvecRatio(rectangle.coordonneesSommet(0), rectangle.position()), 0), glm::vec3(coordonneesSommetRectangleAvecRatio(rectangle.coordonneesSommet(1), rectangle.position()), 0), glm::vec3(coordonneesSommetRectangleAvecRatio(rectangle.coordonneesSommet(2), rectangle.position()), 0))
		|| ng::rayonTriangle3DEnCollision(glm::vec3(m_souris.position, 1), glm::vec3(0, 0, -1), glm::vec3(coordonneesSommetRectangleAvecRatio(rectangle.coordonneesSommet(3), rectangle.position()), 0), glm::vec3(coordonneesSommetRectangleAvecRatio(rectangle.coordonneesSommet(4), rectangle.position()), 0), glm::vec3(coordonneesSommetRectangleAvecRatio(rectangle.coordonneesSommet(5), rectangle.position()), 0)));
}

const glm::vec2& ng::Controles::positionSouris() const
{
	return m_souris.position;
}

const glm::vec2& ng::Controles::deplacementSouris() const
{
	return m_souris.deplacement;
}

bool ng::Controles::boutonSourisGaucheAppuye() const
{
	return m_souris.boutonGaucheAppuye;
}

bool ng::Controles::boutonSourisDroiteAppuye() const
{
	return m_souris.boutonDroiteAppuye;
}

bool ng::Controles::boutonSourisMilieuAppuye() const
{
	return m_souris.boutonMilieuAppuye;
}

bool ng::Controles::boutonSourisGaucheRelache() const
{
	return m_souris.boutonGaucheRelache;
}

bool ng::Controles::boutonSourisDroiteRelache() const
{
	return m_souris.boutonDroiteRelache;
}

bool ng::Controles::boutonSourisMilieuRelache() const
{
	return m_souris.boutonMilieuRelache;
}

bool ng::Controles::toucheClavierAppuyee(sf::Keyboard::Key touche) const
{
	return sf::Keyboard::isKeyPressed(touche);
}

char ng::Controles::caractereEntre() const
{
	return m_caractereEntre;
}

bool ng::Controles::tactileActive() const
{
	return m_tactileActive;
}

void ng::Controles::modifierFenetre(const sf::Window* fenetre)
{
	m_fenetre = fenetre;
}

void ng::Controles::modifierTactileActive(bool tactileActive)
{
	m_tactileActive = tactileActive;
}

void ng::Controles::recupererEntrees()
{
	// Gestion du tactile
	for (int i = 0; i < m_doigts.size(); ++i)
	{
		if (sf::Touch::isDown(i))
		{
			m_doigts[i].identifiant = i;
			m_doigts[i].ecranTouche = true;
			m_doigts[i].pose = true;
			m_doigts[i].retire = false;

			if (m_grandeurMetrique == Pixels)
			{
				m_doigts[i].deplacement = glm::vec2((sf::Touch::getPosition(i).x - m_doigts[i].position.x) * m_taillePixelsFenetre.x, (sf::Touch::getPosition(i).y - m_doigts[i].position.y) * m_taillePixelsFenetre.y);
				m_doigts[i].position = glm::vec2(sf::Touch::getPosition(i).x * m_taillePixelsFenetre.x, sf::Touch::getPosition(i).y * m_taillePixelsFenetre.y);
			}
			else
			{
				m_doigts[i].deplacement = glm::vec2(sf::Touch::getPosition(i).x - m_doigts[i].position.x, sf::Touch::getPosition(i).y - m_doigts[i].position.y);
				m_doigts[i].position = glm::vec2(sf::Touch::getPosition(i).x, sf::Touch::getPosition(i).y);
			}
		}
		else if (!sf::Touch::isDown(i) && m_doigts[i].ecranTouche)
			m_doigts[i].retire = true;
	}

	// Gestion de la souris
	if (m_souris.position.x != sf::Mouse::getPosition(*m_fenetre).x && m_souris.position.y != sf::Mouse::getPosition(*m_fenetre).y)
	{
		if (m_grandeurMetrique == Pixels)
		{
			m_souris.deplacement = glm::vec2(sf::Mouse::getPosition(*m_fenetre).x - m_souris.position.x, sf::Mouse::getPosition(*m_fenetre).y - m_souris.position.y);
			m_souris.position = glm::vec2(m_souris.position.x, m_souris.position.y);
		}
		else
		{
			m_souris.deplacement = glm::vec2((sf::Mouse::getPosition(*m_fenetre).x - m_souris.position.x) / m_taillePixelsFenetre.x, (sf::Mouse::getPosition(*m_fenetre).y - m_souris.position.y) / m_taillePixelsFenetre.y);
			m_souris.position = glm::vec2(sf::Mouse::getPosition(*m_fenetre).x / m_taillePixelsFenetre.x, sf::Mouse::getPosition(*m_fenetre).y / m_taillePixelsFenetre.y);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_souris.boutonGaucheAppuye = true;
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		m_souris.boutonDroiteAppuye = true;
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		m_souris.boutonMilieuAppuye = true;
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_souris.boutonGaucheAppuye)
	{
		m_souris.boutonGaucheAppuye = false;
		m_souris.boutonGaucheRelache = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && m_souris.boutonDroiteAppuye)
	{
		m_souris.boutonDroiteAppuye = false;
		m_souris.boutonDroiteRelache = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Middle) && m_souris.boutonMilieuAppuye)
	{
		m_souris.boutonMilieuAppuye = false;
		m_souris.boutonMilieuRelache = true;
	}
}

void ng::Controles::recupererCaractereEntre(const sf::Event& evenements)
{
	if (evenements.type == sf::Event::TextEntered)
		m_caractereEntre = evenements.text.unicode;
}

void ng::Controles::reinitialiser()
{
	for (int i = 0; i < m_doigts.size(); ++i)
	{
		if (doigtRetire(i))
		{
			m_doigts[i].identifiant = -1;
			m_doigts[i].ecranTouche = false;
			m_doigts[i].position = glm::vec2(-1, -1);
		}

		m_doigts[i].pose = false;
		m_doigts[i].retire = false;
		m_doigts[i].deplacement = glm::vec2(0, 0);
	}

	m_souris.deplacement = glm::vec2(0, 0);
	m_souris.boutonGaucheRelache = false;
	m_souris.boutonDroiteRelache = false;

	m_caractereEntre = 0;
}

glm::vec2 ng::Controles::coordonneesSommetRectangleAvecRatio(const glm::vec2& coordonnees, const glm::vec2& coordonneesCentreRectangle) const
{
	glm::vec2 ratio((m_grandeurMetrique == RelatifRedimensionneX ? m_taillePixelsFenetre.y / m_taillePixelsFenetre.x : 1),
		(m_grandeurMetrique == RelatifRedimensionneY ? m_taillePixelsFenetre.x / m_taillePixelsFenetre.y : 1));
	glm::vec2 nouvellesCoordonneesSommet;

	nouvellesCoordonneesSommet.x = (coordonnees.x - coordonneesCentreRectangle.x) * ratio.x + coordonneesCentreRectangle.x;
	nouvellesCoordonneesSommet.y = (coordonnees.y - coordonneesCentreRectangle.y) * ratio.y + coordonneesCentreRectangle.y;

	return nouvellesCoordonneesSommet;
}