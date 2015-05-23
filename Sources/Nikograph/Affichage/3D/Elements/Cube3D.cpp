#include "Cube3D.hpp"

ng::Cube3D::Cube3D(const glm::vec3& position, const glm::vec3& taille) :
	m_position(position),
	m_taille(taille),
	m_couleur(glm::vec4(1, 1, 1, 1)),
	m_identifiantTexturesFaces({-1, -1, -1, -1, -1, -1})
{
	/*
	 * identifiantTexturesFaces : tableau de 6 identifiants de texture, un pour chaque face (dans l'ordre +z, -z, -x, +x, -y, +y)
	*/
}

const glm::vec3& ng::Cube3D::position() const
{
	return m_position;
}

const glm::vec3& ng::Cube3D::vitesse() const
{
	return m_vitesse;
}

const glm::vec3& ng::Cube3D::acceleration() const
{
	return m_acceleration;
}

const glm::vec3& ng::Cube3D::taille() const
{
	return m_taille;
}

const glm::vec3& ng::Cube3D::angles() const
{
	return m_angles;
}

std::vector<float> ng::Cube3D::coordonneesSommets(const std::vector<bool>& facesAffichees, bool positionPrisEnCompte) const
{
	std::vector<float> decalage = {
		-0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5,
		-0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5,
		0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, -0.5,
		0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5,
		-0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5, -0.5,
		0.5, -0.5, 0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5,
		0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5,
		-0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5,
		-0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, 0.5, -0.5,
		0.5, -0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5,
		0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5,
		-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5
	};

	std::vector<float> coordonneesSommets;
	for (int i = 0; i < 36; ++i)
	{
		
		if (facesAffichees[int(i / 6)])
		{
			glm::vec3 positionSommet(decalage[3 * i] * m_taille.x, decalage[3 * i + 1] * m_taille.y, decalage[3 * i + 2] * m_taille.z);
			positionSommet = glm::rotateX(positionSommet, glm::radians(m_angles.x));
			positionSommet = glm::rotateY(positionSommet, glm::radians(m_angles.y));
			positionSommet = glm::rotateZ(positionSommet, glm::radians(m_angles.z));

			coordonneesSommets.push_back(positionSommet.x + (positionPrisEnCompte ? m_position.x : 0));
			coordonneesSommets.push_back(positionSommet.y + (positionPrisEnCompte ? m_position.y : 0));
			coordonneesSommets.push_back(positionSommet.z + (positionPrisEnCompte ? m_position.z : 0));
		}
	}

	return coordonneesSommets;
}

const glm::vec4& ng::Cube3D::couleur() const
{
	return m_couleur;
}

std::vector<float> ng::Cube3D::couleurs(const std::vector<bool>& facesAffichees, bool ajoutLuminosite) const
{
	std::vector<float> couleurs;

	float identifiantsFaces[6] = { 4, 1, 3, 2, 5, 0 };
	float coefficientLuminosite = 0.1;
	std::vector<float> intensiteLumiere = {1, 1, 1, 1, 1, 1};
	if (ajoutLuminosite)
		intensiteLumiere = std::vector<float>({ 1 - identifiantsFaces[0] * coefficientLuminosite, 1 - identifiantsFaces[1] * coefficientLuminosite, 1 - identifiantsFaces[2] * coefficientLuminosite, 1 - identifiantsFaces[3] * coefficientLuminosite, 1 - identifiantsFaces[4] * coefficientLuminosite, 1 - identifiantsFaces[5] * coefficientLuminosite });

	for (int i = 0; i < 6; ++i)
	{
		if (facesAffichees[i])
		{
			std::vector<float> couleur = {
				m_couleur.r * intensiteLumiere[i], m_couleur.g * intensiteLumiere[i], m_couleur.b * intensiteLumiere[i], m_couleur.a, m_couleur.r * intensiteLumiere[i], m_couleur.g * intensiteLumiere[i], m_couleur.b * intensiteLumiere[i], m_couleur.a, m_couleur.r * intensiteLumiere[i], m_couleur.g * intensiteLumiere[i], m_couleur.b * intensiteLumiere[i], m_couleur.a,
				m_couleur.r * intensiteLumiere[i], m_couleur.g * intensiteLumiere[i], m_couleur.b * intensiteLumiere[i], m_couleur.a, m_couleur.r * intensiteLumiere[i], m_couleur.g * intensiteLumiere[i], m_couleur.b * intensiteLumiere[i], m_couleur.a, m_couleur.r * intensiteLumiere[i], m_couleur.g * intensiteLumiere[i], m_couleur.b * intensiteLumiere[i], m_couleur.a
			};

			for (int i = 0; i < 24; ++i)
				couleurs.push_back(couleur[i]);
		}
	}

	return couleurs;
}

std::vector<float> ng::Cube3D::coordonneesTexture(const std::vector<bool>& facesAffichees) const
{
	std::vector<float> coordonneesTextureCubeEntier;
	std::vector<float> coordonneesTexture;
		
	
	coordonneesTextureCubeEntier = {
		0, 0, m_identifiantTexturesFaces[0], 1, 0, m_identifiantTexturesFaces[0], 0, 1, m_identifiantTexturesFaces[0],
		1, 0, m_identifiantTexturesFaces[0], 1, 1, m_identifiantTexturesFaces[0], 0, 1, m_identifiantTexturesFaces[0],
		0, 0, m_identifiantTexturesFaces[1], 1, 0, m_identifiantTexturesFaces[1], 0, 1, m_identifiantTexturesFaces[1],
		1, 0, m_identifiantTexturesFaces[1], 1, 1, m_identifiantTexturesFaces[1], 0, 1, m_identifiantTexturesFaces[1],
		0, 0, m_identifiantTexturesFaces[2], 1, 0, m_identifiantTexturesFaces[2], 0, 1, m_identifiantTexturesFaces[2],
		1, 0, m_identifiantTexturesFaces[2], 1, 1, m_identifiantTexturesFaces[2], 0, 1, m_identifiantTexturesFaces[2],
		0, 0, m_identifiantTexturesFaces[3], 1, 0, m_identifiantTexturesFaces[3], 0, 1, m_identifiantTexturesFaces[3],
		1, 0, m_identifiantTexturesFaces[3], 1, 1, m_identifiantTexturesFaces[3], 0, 1, m_identifiantTexturesFaces[3],
		0, 0, m_identifiantTexturesFaces[4], 1, 0, m_identifiantTexturesFaces[4], 0, 1, m_identifiantTexturesFaces[4],
		1, 0, m_identifiantTexturesFaces[4], 1, 1, m_identifiantTexturesFaces[4], 0, 1, m_identifiantTexturesFaces[4],
		0, 0, m_identifiantTexturesFaces[5], 1, 0, m_identifiantTexturesFaces[5], 0, 1, m_identifiantTexturesFaces[5],
		1, 0, m_identifiantTexturesFaces[5], 1, 1, m_identifiantTexturesFaces[5], 0, 1, m_identifiantTexturesFaces[5]
	};

	for (int i = 0; i < 36; ++i)
	{
		if (facesAffichees[int(i / 6)])
		{
			coordonneesTexture.push_back(coordonneesTextureCubeEntier[3 * i]);
			coordonneesTexture.push_back(coordonneesTextureCubeEntier[3 * i + 1]);
			coordonneesTexture.push_back(coordonneesTextureCubeEntier[3 * i + 2]);
		}
	}

	return coordonneesTexture;
}

std::vector<float> ng::Cube3D::normales(const std::vector<bool>& facesAffichees) const
{
	std::vector<glm::vec3> normalesFaces = { glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, 1) };
	std::vector<float> normales;

	for (int i = 0; i < 6; ++i)
	{
		normalesFaces[i] = glm::normalize(glm::rotateX(normalesFaces[i], glm::radians(m_angles.x)));
		normalesFaces[i] = glm::normalize(glm::rotateY(normalesFaces[i], glm::radians(m_angles.y)));
		normalesFaces[i] = glm::normalize(glm::rotateZ(normalesFaces[i], glm::radians(m_angles.z)));

		for (int j = 0; j < 18; ++j)
			normales.push_back(normalesFaces[i][j % 3]);
	}

	return normales;
}

void ng::Cube3D::modifierPosition(const glm::vec3& position)
{
	m_position = position;
}

void ng::Cube3D::modifierVitesse(const glm::vec3& vitesse)
{
	m_vitesse = vitesse;
}

void ng::Cube3D::modifierAcceleration(const glm::vec3& acceleration)
{
	m_acceleration = acceleration;
}

void ng::Cube3D::modifierTaille(const glm::vec3& taille)
{
	m_taille = taille;
}

void ng::Cube3D::modifierAngles(const glm::vec3& angles)
{
	m_angles = angles;
}

void ng::Cube3D::modifierIdentifiantTexturesFaces(const std::vector<float>& identifiants)
{
	if (identifiants.size() == 6)
		m_identifiantTexturesFaces = identifiants;
}

void ng::Cube3D::modifierCouleur(const glm::vec4& couleur)
{
	m_couleur = couleur;
}

void ng::Cube3D::translater(const glm::vec3& deplacement)
{
	glm::vec3 deplacementRepereCube = deplacement;

	deplacementRepereCube = glm::rotateX(deplacementRepereCube, glm::radians(m_angles.x));
	deplacementRepereCube = glm::rotateY(deplacementRepereCube, glm::radians(m_angles.y));
	deplacementRepereCube = glm::rotateZ(deplacementRepereCube, glm::radians(m_angles.z));

	m_position += deplacementRepereCube;
}

void ng::Cube3D::modifierEchelle(const glm::vec3& echelle)
{
	m_taille *= echelle;
}

void ng::Cube3D::tourner(const glm::vec3& angles)
{
	m_angles += angles;
}

void ng::Cube3D::mettreAJourPosition(float tempsFrame, bool anglePrisEnCompte)
{
	m_vitesse += tempsFrame * m_acceleration;

	if (anglePrisEnCompte)
		translater(tempsFrame * m_vitesse);
	else
		modifierPosition(m_position + tempsFrame * m_vitesse);
}

void ng::Cube3D::annulerMiseAJourPosition(float tempsFrame, bool anglePrisEnCompte)
{
	if (anglePrisEnCompte)
		translater(-tempsFrame * m_vitesse);
	else
		modifierPosition(m_position - tempsFrame * m_vitesse);

	m_vitesse -= tempsFrame * m_acceleration;
}
