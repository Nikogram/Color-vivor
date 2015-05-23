#include "Modele3D.hpp"

ng::Modele3D::Modele3D(const glm::vec3& position, const glm::vec3& taille) :
	m_position(position),
	m_taille(taille),
	m_identifiantTexture(-1)
{
}

const glm::vec3& ng::Modele3D::position() const
{
	return m_position;
}

const glm::vec3& ng::Modele3D::taille() const
{
	return m_taille;
}

const glm::vec3& ng::Modele3D::angles() const
{
	return m_angles;
}

std::vector<float> ng::Modele3D::coordonneesSommets() const
{
	std::vector<float> coordonneesSommetsTransformees;

	for (int i = 0; i < m_coordonneesSommets.size() / 3; ++i)
	{
		glm::vec3 coordonneeSommet = glm::vec3(m_coordonneesSommets[3 * i], m_coordonneesSommets[3 * i + 1], m_coordonneesSommets[3 * i + 2]) * m_taille;
		coordonneeSommet = glm::rotateX(coordonneeSommet, glm::radians(m_angles.x));
		coordonneeSommet = glm::rotateY(coordonneeSommet, glm::radians(m_angles.y));
		coordonneeSommet = glm::rotateZ(coordonneeSommet, glm::radians(m_angles.z));
		coordonneeSommet += m_position;

		coordonneesSommetsTransformees.push_back(coordonneeSommet.x);
		coordonneesSommetsTransformees.push_back(coordonneeSommet.y);
		coordonneesSommetsTransformees.push_back(coordonneeSommet.z);
	}

	return coordonneesSommetsTransformees;
}

const std::vector<float>& ng::Modele3D::couleurs() const
{
	return m_couleurs;
}

std::vector<float> ng::Modele3D::coordonneesTexture() const
{
	std::vector<float> coordonneesTexture;

	for (int i = 0; i < m_coordonneesTexture.size() / 3; ++i)
	{
		coordonneesTexture.push_back(m_coordonneesTexture[3 * i] * m_taille.x);
		coordonneesTexture.push_back(m_coordonneesTexture[3 * i + 1] * m_taille.y);
		coordonneesTexture.push_back(m_coordonneesTexture[3 * i + 2]);
	}

	return coordonneesTexture;
}

std::vector<float> ng::Modele3D::normales() const
{
	std::vector<float> normalesTransformees;

	for (int i = 0; i < m_normales.size() / 3; ++i)
	{
		glm::vec3 normale = glm::vec3(m_normales[3 * i], m_normales[3 * i + 1], m_normales[3 * i + 2]) * m_taille;
		normale = glm::rotateX(normale, glm::radians(m_angles.x));
		normale = glm::rotateY(normale, glm::radians(m_angles.y));
		normale = glm::rotateZ(normale, glm::radians(m_angles.z));

		normalesTransformees.push_back(normale.x);
		normalesTransformees.push_back(normale.y);
		normalesTransformees.push_back(normale.z);
	}

	return normalesTransformees;
}

void ng::Modele3D::modifierIdentifiantTexture(int identifiantTexture)
{
	m_identifiantTexture = identifiantTexture;

	for (int i = 0; i < m_coordonneesTexture.size(); ++i)
	{
		if (i % 3 == 2)
			m_coordonneesTexture[i] = m_identifiantTexture;
	}
}

void ng::Modele3D::modifierPosition(const glm::vec3& position)
{
	m_position = position;
}

void ng::Modele3D::modifierTaille(const glm::vec3& taille)
{
	m_taille = taille;
}

void ng::Modele3D::modifierAngles(const glm::vec3& angles)
{
	m_angles = angles;
}

void ng::Modele3D::translater(const glm::vec3& deplacement)
{
	m_position += deplacement;
}

void ng::Modele3D::modifierEchelle(const glm::vec3& echelle)
{
	m_taille *= echelle;
}

void ng::Modele3D::tourner(const glm::vec3& angles)
{
	m_angles += angles;
}

void ng::Modele3D::chargerCube()
{
	m_coordonneesSommets = {
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


	m_couleurs = std::vector<float>(36 * 4, 1);


	m_coordonneesTexture = {
		0, 0, (float)m_identifiantTexture, 1, 0, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		1, 0, (float)m_identifiantTexture, 1, 1, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		0, 0, (float)m_identifiantTexture, 1, 0, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		1, 0, (float)m_identifiantTexture, 1, 1, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		0, 0, (float)m_identifiantTexture, 1, 0, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		1, 0, (float)m_identifiantTexture, 1, 1, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		0, 0, (float)m_identifiantTexture, 1, 0, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		1, 0, (float)m_identifiantTexture, 1, 1, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		0, 0, (float)m_identifiantTexture, 1, 0, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		1, 0, (float)m_identifiantTexture, 1, 1, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		0, 0, (float)m_identifiantTexture, 1, 0, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture,
		1, 0, (float)m_identifiantTexture, 1, 1, (float)m_identifiantTexture, 0, 1, (float)m_identifiantTexture
	};


	std::vector<glm::vec3> normalesFaces = { glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1), glm::vec3(0, 0, 1) };
	m_normales.clear();

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 18; ++j)
			m_normales.push_back(normalesFaces[i][j % 3]);
	}
}

bool ng::Modele3D::ajouterSommets(std::string nomFichier, const glm::vec2& signeCoordonneesTexture)
{
	std::ifstream fichier(nomFichier.c_str());

	if (!fichier)
		return false;

	std::vector<float> coordonneesSommets;
	std::vector<float> coordonneesTexture;
	std::vector<float> normales;
	std::vector<int> identifiantsCoordonneesSommets;
	std::vector<float> identifiantsCoordonneesTexture;
	std::vector<int> identifiantsNormales;

	std::string ligne;
	while (getline(fichier, ligne))
	{
		if (ligne.substr(0, 2) == "v ")
		{
			std::istringstream flux(ligne.substr(2));

			float coordonnee = 0;
			for (int i = 0; i < 3; ++i)
			{
				flux >> coordonnee;
				coordonneesSommets.push_back(coordonnee);
			}
		}
		else if (ligne.substr(0, 3) == "vt ")
		{
			std::istringstream flux(ligne.substr(3));

			float coordonnee = 0;

			flux >> coordonnee;
			coordonneesTexture.push_back(signeCoordonneesTexture.x * coordonnee);

			flux >> coordonnee;
			coordonneesTexture.push_back(signeCoordonneesTexture.y * coordonnee);
		}
		else if (ligne.substr(0, 3) == "vn ")
		{
			std::istringstream flux(ligne.substr(3));

			float normale = 0;
			for (int i = 0; i < 3; ++i)
			{
				flux >> normale;
				normales.push_back(normale);
			}
		}
		else if (ligne.substr(0, 2) == "f ")
		{
			std::istringstream flux(ligne.substr(2));

			for (int i = 0; i < 3; ++i)
			{
				std::string identifiants;
				flux >> identifiants;

				std::stringstream fluxChaine(identifiants);

				int j = 0;
				std::string identifiant;

				while (std::getline(fluxChaine, identifiant, '/'))
				{
					int identifiantSommet = 0;
					std::istringstream fluxConversion(identifiant);
					fluxConversion >> identifiantSommet;

					if (j == 0)
						identifiantsCoordonneesSommets.push_back(identifiantSommet - 1);
					else if (j == 1)
						identifiantsCoordonneesTexture.push_back(identifiantSommet - 1);
					else if (j == 2)
						identifiantsNormales.push_back(identifiantSommet - 1);

					++j;
				}
			}
		}
	}

	std::vector<float> coordonneesSommetsArranges;
	std::vector<float> coordonneesTextureArranges;
	std::vector<float> normalesArrangees;

	for (int i = 0; i < identifiantsCoordonneesSommets.size(); ++i)
	{
		coordonneesSommetsArranges.push_back(coordonneesSommets[3 * identifiantsCoordonneesSommets[i]]);
		coordonneesSommetsArranges.push_back(coordonneesSommets[3 * identifiantsCoordonneesSommets[i] + 1]);
		coordonneesSommetsArranges.push_back(coordonneesSommets[3 * identifiantsCoordonneesSommets[i] + 2]);

		coordonneesTextureArranges.push_back(coordonneesTexture[2 * identifiantsCoordonneesTexture[i]]);
		coordonneesTextureArranges.push_back(coordonneesTexture[2 * identifiantsCoordonneesTexture[i] + 1]);
		coordonneesTextureArranges.push_back(m_identifiantTexture);

		normalesArrangees.push_back(normales[3 * identifiantsNormales[i]]);
		normalesArrangees.push_back(normales[3 * identifiantsNormales[i] + 1]);
		normalesArrangees.push_back(normales[3 * identifiantsNormales[i] + 2]);
	}

	std::vector<float> couleurs(coordonneesSommetsArranges.size() / 3 * 4, 1);
	
	m_coordonneesSommets.insert(m_coordonneesSommets.end(), coordonneesSommetsArranges.begin(), coordonneesSommetsArranges.end());
	m_couleurs.insert(m_couleurs.end(), couleurs.begin(), couleurs.end());
	m_coordonneesTexture.insert(m_coordonneesTexture.end(), coordonneesTextureArranges.begin(), coordonneesTextureArranges.end());
	m_normales.insert(m_normales.end(), normalesArrangees.begin(), normalesArrangees.end());

	return true;
}
