#include "Camera3D.hpp"

ng::Camera3D::Camera3D(const glm::vec3& position) :
	m_position(position),
	m_pointFixe(0, 0, 0, -1)
{
}

const glm::vec3& ng::Camera3D::position() const
{
	return m_position;
}

const glm::vec3& ng::Camera3D::vitesse() const
{
	return m_vitesse;
}

const glm::vec3& ng::Camera3D::acceleration() const
{
	return m_acceleration;
}
const glm::vec3& ng::Camera3D::angles() const
{
	return m_angles;
}

glm::vec3 ng::Camera3D::directionVue() const
{
	glm::vec3 directionVue(1, 0, 0);

	directionVue = glm::rotateX(directionVue, glm::radians(m_angles.x));
	directionVue = glm::rotateY(directionVue, glm::radians(m_angles.y));
	directionVue = glm::rotateZ(directionVue, glm::radians(m_angles.z));

	return directionVue;
}

glm::mat4 ng::Camera3D::matriceVue() const
{
	if (m_pointFixe.w == -1)
	{
		glm::vec3 directionVue(1, 0, 0);

		directionVue = glm::rotateX(directionVue, glm::radians(m_angles.x));
		directionVue = glm::rotateY(directionVue, glm::radians(m_angles.y));
		directionVue = glm::rotateZ(directionVue, glm::radians(m_angles.z));

		return glm::lookAt(m_position, m_position + directionVue, glm::vec3(0, 0, 1));
	}
	else
		return glm::lookAt(m_position, glm::vec3(m_pointFixe.x, m_pointFixe.y, m_pointFixe.z), glm::vec3(0, 0, 1));
}

void ng::Camera3D::modifierPosition(const glm::vec3& position)
{
	m_position = position;

	if (m_pointFixe.w != -1)
		fixerPoint(glm::vec3(m_pointFixe));
}

void ng::Camera3D::modifierVitesse(const glm::vec3& vitesse)
{
	m_vitesse = vitesse;
}

void ng::Camera3D::modifierAcceleration(const glm::vec3& acceleration)
{
	m_acceleration = acceleration;
}

void ng::Camera3D::modifierAngles(const glm::vec3& angles)
{
	if (m_pointFixe.w == -1)
		m_angles = angles;
}

void ng::Camera3D::translater(const glm::vec3& deplacement, const glm::bvec3& deplacementAFaire, bool prendreEnCompteRotationHauteurCamera)
{
	glm::vec3 deplacementRepereCamera(deplacement);

	if (!prendreEnCompteRotationHauteurCamera)
	{
		if (deplacementAFaire.x || deplacementAFaire.y)
			deplacementRepereCamera = glm::rotateZ(deplacementRepereCamera, glm::radians(m_angles.z));
	}
	else
	{
		if (deplacementAFaire.y && deplacementAFaire.z)
			deplacementRepereCamera = glm::rotateX(deplacementRepereCamera, glm::radians(m_angles.x));
		if (deplacementAFaire.x && deplacementAFaire.z)
			deplacementRepereCamera = glm::rotateY(deplacementRepereCamera, glm::radians(m_angles.y));
		if (deplacementAFaire.x && deplacementAFaire.y)
			deplacementRepereCamera = glm::rotateZ(deplacementRepereCamera, glm::radians(m_angles.z));
	}

	m_position += glm::vec3(deplacementAFaire.x ? deplacementRepereCamera.x : 0, deplacementAFaire.y ? deplacementRepereCamera.y : 0, deplacementAFaire.z ? deplacementRepereCamera.z : 0);

	if (m_pointFixe.w != -1)
		fixerPoint(glm::vec3(m_pointFixe));
}

void ng::Camera3D::tourner(const glm::vec3& angles)
{
	if (m_pointFixe.w == -1)
	{
		if (!(m_angles.y == 89 && angles.y > 0) && !(m_angles.y == 89 && angles.y > 0))
		{
			m_angles += angles;

			if (m_angles.y > 89)
				m_angles.y = 89;
			else if (m_angles.y < -89)
				m_angles.y = -89;
		}
	}
}

void ng::Camera3D::mettreAJourPosition(float tempsFrame, bool anglePrisEnCompte)
{
	m_vitesse += tempsFrame * m_acceleration;

	if (anglePrisEnCompte)
		translater(tempsFrame * m_vitesse);
	else
		modifierPosition(m_position + tempsFrame * m_vitesse);

	if (m_pointFixe.w != -1)
		fixerPoint(glm::vec3(m_pointFixe));
}

void ng::Camera3D::annulerMiseAJourPosition(float tempsFrame, bool anglePrisEnCompte)
{
	if (anglePrisEnCompte)
		translater(-tempsFrame * m_vitesse);
	else
		modifierPosition(m_position - tempsFrame * m_vitesse);

	m_vitesse -= tempsFrame * m_acceleration;

	if (m_pointFixe.w != -1)
		fixerPoint(glm::vec3(m_pointFixe));
}

void ng::Camera3D::fixerPoint(const glm::vec3& positionPoint)
{
	if (positionPoint != m_position)
	{
		m_pointFixe = glm::vec4(positionPoint, 0);

		glm::vec3 determinants(
			glm::determinant(glm::mat2(m_pointFixe.y - m_position.y, m_pointFixe.z - m_position.z, 1, 0)),
			glm::determinant(glm::mat2(m_pointFixe.x - m_position.x, m_pointFixe.z - m_position.z, 1, 0)),
			glm::determinant(glm::mat2(m_pointFixe.x - m_position.x, m_pointFixe.y - m_position.y, 1, 0)));

		m_angles.y = (determinants.y < 0 ? 1 : -1) * glm::degrees(glm::angle(glm::normalize(glm::vec3(m_pointFixe.x - m_position.x, 0, m_pointFixe.z - m_position.z)), glm::vec3(1, 0, 0)));
		m_angles.z = (determinants.z < 0 ? 1 : -1) * glm::degrees(glm::angle(glm::normalize(glm::vec3(m_pointFixe.x - m_position.x, m_pointFixe.y - m_position.y, 0)), glm::vec3(1, 0, 0)));
	}
}

void ng::Camera3D::arreterFixerPoint()
{
	m_pointFixe = glm::vec4(0, 0, 0, -1);
}
