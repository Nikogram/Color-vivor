#include "Rectangle2D.hpp"

ng::Rectangle2D::Rectangle2D(glm::vec2 position, glm::vec2 taille, float angle) :
	m_position(position),
	m_vitesse(0, 0),
	m_acceleration(0, 0),
	m_taille(taille),
	m_angle(angle),
	m_couleur(1, 1, 1, 1),
	m_identifiantTexture(-1),
	m_positionTexture(glm::vec2(0, 0)),
	m_tailleTexture(glm::vec2(0, 0))
{
}

glm::vec2 ng::Rectangle2D::position() const
{
	return m_position;
}

glm::vec2 ng::Rectangle2D::vitesse() const
{
	return m_vitesse;
}

glm::vec2 ng::Rectangle2D::acceleration() const
{
	return m_acceleration;
}

glm::vec2 ng::Rectangle2D::taille() const
{
	return m_taille;
}

float ng::Rectangle2D::angle() const
{
	return m_angle;
}

glm::vec4 ng::Rectangle2D::couleur() const
{
	return m_couleur;
}

int ng::Rectangle2D::identifiantTexture() const
{
	return m_identifiantTexture;
}

glm::vec2 ng::Rectangle2D::positionTexture() const
{
	return m_positionTexture;
}

glm::vec2 ng::Rectangle2D::tailleTexture() const
{
	return m_tailleTexture;
}

glm::vec2 ng::Rectangle2D::coordonneesSommet(int identifiant) const
{
	if (identifiant >= 0 && identifiant < 6)
	{
		float coordonneesBaseRectangle[] = {0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1};
		glm::vec2 coordonneesSommetSansRotation(coordonneesBaseRectangle[2 * identifiant] * m_taille.x - 0.5 * m_taille.x, coordonneesBaseRectangle[2 * identifiant + 1] * m_taille.y - 0.5 * m_taille.y);
		glm::vec2 coordonneesSommet(coordonneesSommetSansRotation.x * glm::cos(glm::radians(m_angle)) + coordonneesSommetSansRotation.y * glm::sin(glm::radians(m_angle)) + m_position.x, -coordonneesSommetSansRotation.x * glm::sin(glm::radians(m_angle)) + coordonneesSommetSansRotation.y * glm::cos(glm::radians(m_angle)) + m_position.y);

		return coordonneesSommet;
	}

	return glm::vec2();
}

std::vector<float> ng::Rectangle2D::coordonneesSommets() const
{
	std::vector<float> coordonneesSommets;

	for (int i = 0; i < 6; ++i)
	{
		glm::vec2 coordonneesSommet(this->coordonneesSommet(i));

		coordonneesSommets.push_back(coordonneesSommet.x);
		coordonneesSommets.push_back(coordonneesSommet.y);
	}

	return coordonneesSommets;
}

std::vector<float> ng::Rectangle2D::coordonneesTexture() const
{
	float coordonneesBaseRectangle[] = {-0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5};
	std::vector<float> coordonneesTexture;
	for (int i = 0; i < 6; ++i)
	{
		coordonneesTexture.push_back(coordonneesBaseRectangle[2 * i] * m_tailleTexture.x + m_positionTexture.x);
		coordonneesTexture.push_back(coordonneesBaseRectangle[2 * i + 1] * m_tailleTexture.y + m_positionTexture.y);
		coordonneesTexture.push_back(m_tailleTexture != glm::vec2(0, 0) ? m_identifiantTexture : -1);
	}

	return coordonneesTexture;
}

void ng::Rectangle2D::modifierPosition(const glm::vec2& position)
{
	m_position = position;
}

void ng::Rectangle2D::modifierVitesse(const glm::vec2& vitesse)
{
	m_vitesse = vitesse;
}

void ng::Rectangle2D::modifierAcceleration(const glm::vec2& acceleration)
{
	m_acceleration = acceleration;
}

void ng::Rectangle2D::modifierTaille(const glm::vec2& taille)
{
	m_taille = taille;
}

void ng::Rectangle2D::modifierAngle(float angle)
{
	m_angle = angle;
}

void ng::Rectangle2D::modifierCouleur(const glm::vec4& couleur)
{
	m_couleur = couleur;
}

void ng::Rectangle2D::modifierTexture(int identifiantTexture, const glm::vec2& positionTexture, const glm::vec2& tailleTexture)
{
	m_identifiantTexture = identifiantTexture;
	m_positionTexture = positionTexture;
	m_tailleTexture = tailleTexture;
}

void ng::Rectangle2D::translater(const glm::vec2& deplacement)
{
	m_position.x += deplacement.x * glm::cos(glm::radians(m_angle)) + deplacement.y * glm::sin(glm::radians(m_angle));
	m_position.y += -deplacement.x * glm::sin(glm::radians(m_angle)) + deplacement.y * glm::cos(glm::radians(m_angle));
}

void ng::Rectangle2D::modifierEchelle(const glm::vec2& echelle)
{
	m_taille *= echelle;
}

void ng::Rectangle2D::tourner(float angle)
{
	m_angle += angle;
}

void ng::Rectangle2D::retirerTexture()
{
	m_identifiantTexture = -1;
	m_positionTexture = glm::vec2(0, 0);
	m_tailleTexture = glm::vec2(0, 0);
}

void ng::Rectangle2D::mettreAJourPosition(float tempsFrame, bool anglePrisEnCompte)
{
	m_vitesse += tempsFrame * m_acceleration;

	if (anglePrisEnCompte)
		translater(tempsFrame * m_vitesse);
	else
		modifierPosition(m_position + tempsFrame * m_vitesse);
}
