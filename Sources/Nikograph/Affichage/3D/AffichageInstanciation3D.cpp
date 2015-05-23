#include "AffichageInstanciation3D.hpp"

ng::AffichageInstanciation3D::AffichageInstanciation3D(const glm::mat4& matriceProjection, const glm::mat4& matriceVue) :
	m_shader("Shaders/AffichageInstanciation3D.vert", "Shaders/AffichageInstanciation3D.frag"),
	m_matriceProjection(matriceProjection),
	m_matriceVue(matriceVue)
{
	// Initialisation des 8 textures
	for (int i = 0; i < 8; ++i)
		m_textures.push_back(Texture());
}

int ng::AffichageInstanciation3D::nombreSommets() const
{
	return int(m_informationsSommets.size() / 4);
}

glm::vec2 ng::AffichageInstanciation3D::tailleTexture(int identifiantTexture) const
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		return m_textures[identifiantTexture].taille();
	return glm::vec2(0, 0);
}

const glm::mat4& ng::AffichageInstanciation3D::matriceProjection() const
{
	return m_matriceProjection;
}

const glm::mat4& ng::AffichageInstanciation3D::matriceVue() const
{
	return m_matriceVue;
}

int ng::AffichageInstanciation3D::identifiantCoordonneesSommetModele(const glm::vec4& coordonnees) const
{
	for (int i = 0; i < m_coordonneesSommets.size() / 4; ++i)
	{
		if (coordonnees.x == m_coordonneesSommets[4 * i] && coordonnees.y == m_coordonneesSommets[4 * i + 1] && coordonnees.z == m_coordonneesSommets[4 * i + 2] && coordonnees.w == m_coordonneesSommets[4 * i + 3])
			return i;
	}

	return -1;
}

int ng::AffichageInstanciation3D::identifiantCoordonneesTextureModele(const glm::vec3& coordonnees) const
{
	for (int i = 0; i < m_coordonneesTexture.size() / 3; ++i)
	{
		if (coordonnees.x == m_coordonneesTexture[3 * i] && coordonnees.y == m_coordonneesTexture[3 * i + 1] && coordonnees.z == m_coordonneesTexture[3 * i + 2])
			return i;
	}

	return -1;
}

void ng::AffichageInstanciation3D::modifierMatriceProjection(const glm::mat4& matrice)
{
	m_matriceProjection = matrice;
}

void ng::AffichageInstanciation3D::modifierMatriceVue(const glm::mat4& matrice)
{
	m_matriceVue = matrice;
}

void ng::AffichageInstanciation3D::ajouterSommets(const std::vector<float>& coordonneesSommets, const std::vector<float>& coordonneesTexture, const glm::vec3& position, const glm::vec3& taille)
{
	m_positionSommets.push_back(position);
	m_identifiantPremierSommetPosition.push_back(nombreSommets());
	m_nombreSommetsPosition.push_back(coordonneesSommets.size() / 3);

	for (int i = 0; i < coordonneesSommets.size() / 3; ++i)
	{
		int identifiantCoordonneesSommet = identifiantCoordonneesSommetModele(glm::vec4(coordonneesSommets[3 * i], coordonneesSommets[3 * i + 1], coordonneesSommets[3 * i + 2], 10 - 10 * coordonneesTexture[4 * i + 3]));
		int identifiantCoordonneesTexture = identifiantCoordonneesTextureModele(glm::vec3(coordonneesTexture[4 * i], coordonneesTexture[4 * i + 1], coordonneesTexture[4 * i + 2]));

		if (identifiantCoordonneesSommet == -1)
		{
			identifiantCoordonneesSommet = m_coordonneesSommets.size() / 4;
			m_coordonneesSommets.push_back(coordonneesSommets[3 * i]);
			m_coordonneesSommets.push_back(coordonneesSommets[3 * i + 1]);
			m_coordonneesSommets.push_back(coordonneesSommets[3 * i + 2]);
			m_coordonneesSommets.push_back(10 - 10 * coordonneesTexture[4 * i + 3]);
		}
		if (identifiantCoordonneesTexture == -1)
		{
			identifiantCoordonneesTexture = m_coordonneesTexture.size() / 3;
			m_coordonneesTexture.push_back(coordonneesTexture[4 * i]);
			m_coordonneesTexture.push_back(coordonneesTexture[4 * i + 1]);
			m_coordonneesTexture.push_back(coordonneesTexture[4 * i + 2]);
		}

		m_informationsSommets.push_back(taille.x * 1000.0 + position.x);
		m_informationsSommets.push_back(taille.y * 1000.0 + position.y);
		m_informationsSommets.push_back(taille.z * 1000.0 + position.z);
		m_informationsSommets.push_back(identifiantCoordonneesSommet * 1000.0 + identifiantCoordonneesTexture);

		/*m_informationsTailles.push_back(taille.x);
		m_informationsTailles.push_back(taille.y);
		m_informationsTailles.push_back(taille.z);
		m_informationsAutres.push_back(identifiantCoordonneesSommet);
		m_informationsAutres.push_back(identifiantCoordonneesTexture);
		m_informationsAutres.push_back(coordonneesTexture[4 * i + 3]);*/
	}
}

void ng::AffichageInstanciation3D::ajouterSommets(const std::vector<float>& coordonneesSommets, const std::vector<float>& coordonneesTexture, const std::vector<float>& positions, const std::vector<float>& tailleFaces)
{
	int sommetsAjoutes = 0;
	for (int i = 0; i < positions.size() / 3; i += sommetsAjoutes)
	{
		std::vector<float> coordonneesSommetsElement;
		coordonneesSommetsElement.insert(coordonneesSommetsElement.begin(), coordonneesSommets.begin() + 3 * i, coordonneesSommets.begin() + 3 * (i + 1));
		std::vector<float> coordonneesTextureElement;
		coordonneesTextureElement.insert(coordonneesTextureElement.begin(), coordonneesTexture.begin() + 4 * i, coordonneesTexture.begin() + 4 * (i + 1));
		glm::vec3 positionElement(positions[3 * i], positions[3 * i + 1], positions[3 * i + 2]);
		glm::vec3 taille(tailleFaces[3 * i], tailleFaces[3 * i + 1], tailleFaces[3 * i + 2]);

		sommetsAjoutes = 1;

		while (positionElement == glm::vec3(positions[3 * (i + sommetsAjoutes)], positions[3 * (i + sommetsAjoutes) + 1], positions[3 * (i + sommetsAjoutes) + 2]) && taille == glm::vec3(tailleFaces[3 * (i + sommetsAjoutes)], tailleFaces[3 * (i + sommetsAjoutes) + 1], tailleFaces[3 * (i + sommetsAjoutes) + 2]))
		{
			coordonneesSommetsElement.insert(coordonneesSommetsElement.begin(), coordonneesSommets.begin() + 3 * (i + sommetsAjoutes), coordonneesSommets.begin() + 3 * (i + sommetsAjoutes + 1));
			coordonneesTextureElement.insert(coordonneesTextureElement.begin(), coordonneesTexture.begin() + 4 * (i + sommetsAjoutes), coordonneesTexture.begin() + 4 * (i + sommetsAjoutes + 1));

			++sommetsAjoutes;
		}

		ajouterSommets(coordonneesSommetsElement, coordonneesTextureElement, positionElement, taille);
	}
}

void ng::AffichageInstanciation3D::ajouterSommetsCube(const Cube3D& cube, const std::vector<bool>& facesAffichees)
{
	int nombreSommetsCube = 0;
	for (int i = 0; i < 6; ++i)
		nombreSommetsCube += (facesAffichees[i] ? 6 : 0);

	ajouterSommets(cube.coordonneesSommets(facesAffichees, false), cube.coordonneesTexture(facesAffichees), cube.position());
}

void ng::AffichageInstanciation3D::ajouterTexture(int identifiantTexture, std::string cheminTexture, bool textureAdoucie)
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		m_textures[identifiantTexture].charger(cheminTexture, textureAdoucie, GL_LINEAR, (textureAdoucie ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST));
}

void ng::AffichageInstanciation3D::supprimerSommets(int identifiantPremierSommet, int nombreSommets)
{
	m_informationsSommets.erase(m_informationsSommets.begin() + identifiantPremierSommet * 4, m_informationsSommets.begin() + (identifiantPremierSommet + nombreSommets) * 4);
}

bool ng::AffichageInstanciation3D::supprimerSommetsCube(const glm::vec3& positionCube)
{
	int identifiantPosition = -1;;
	for (int i = 0; i < m_positionSommets.size(); ++i)
	{
		if (positionCube == m_positionSommets[i])
			identifiantPosition = i;
	}

	if (identifiantPosition != -1)
	{
		for (int i = identifiantPosition + 1; i < m_identifiantPremierSommetPosition.size(); ++i)
			m_identifiantPremierSommetPosition[i] -= m_nombreSommetsPosition[identifiantPosition];

		supprimerSommets(m_identifiantPremierSommetPosition[identifiantPosition], m_nombreSommetsPosition[identifiantPosition]);
		m_positionSommets.erase(m_positionSommets.begin() + identifiantPosition);
		m_identifiantPremierSommetPosition.erase(m_identifiantPremierSommetPosition.begin() + identifiantPosition);
		m_nombreSommetsPosition.erase(m_nombreSommetsPosition.begin() + identifiantPosition);

		return true;
	}

	return false;
}

void ng::AffichageInstanciation3D::supprimerSommetsCube(const glm::vec3& positionCubeMini, const glm::vec3& positionCubeMaxi)
{
	for (int i = 0; i < m_positionSommets.size(); ++i)
	{
		if (m_positionSommets[i].x >= positionCubeMini.x && m_positionSommets[i].y >= positionCubeMini.y && m_positionSommets[i].z >= positionCubeMini.z && m_positionSommets[i].x <= positionCubeMaxi.x && m_positionSommets[i].y <= positionCubeMaxi.y && m_positionSommets[i].z <= positionCubeMaxi.z)
		{
			for (int j = i + 1; j < m_identifiantPremierSommetPosition.size(); ++j)
				m_identifiantPremierSommetPosition[j] -= m_nombreSommetsPosition[i];

			supprimerSommets(m_identifiantPremierSommetPosition[i], m_nombreSommetsPosition[i]);
			m_positionSommets.erase(m_positionSommets.begin() + i);
			m_identifiantPremierSommetPosition.erase(m_identifiantPremierSommetPosition.begin() + i);
			m_nombreSommetsPosition.erase(m_nombreSommetsPosition.begin() + i);
			--i;
		}
	}
}

void ng::AffichageInstanciation3D::supprimerTexture(int identifiantTexture)
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		m_textures[identifiantTexture] = Texture();
}

void ng::AffichageInstanciation3D::reinitialiser()
{
	m_coordonneesSommets.clear();
	m_coordonneesTexture.clear();
	m_informationsSommets.clear();

	m_positionSommets.clear();
	m_identifiantPremierSommetPosition.clear();
	m_nombreSommetsPosition.clear();
}

void ng::AffichageInstanciation3D::afficher(int identifiantPremierSommet, int nombreSommets)
{
	if (identifiantPremierSommet < this->nombreSommets() && (identifiantPremierSommet + nombreSommets - 1 < this->nombreSommets() || nombreSommets == -1))
	{
		std::string identifiants[8] = { "0", "1", "2", "3", "4", "5", "6", "7" };
		float texturesExistantes0123 = (m_textures[0].taille() != glm::vec2(0, 0))
			+ (m_textures[1].taille() != glm::vec2(0, 0)) * 10
			+ (m_textures[2].taille() != glm::vec2(0, 0)) * 100
			+ (m_textures[3].taille() != glm::vec2(0, 0)) * 1000;
		float texturesExistantes4567 = (m_textures[4].taille() != glm::vec2(0, 0))
			+ (m_textures[5].taille() != glm::vec2(0, 0)) * 10
			+ (m_textures[6].taille() != glm::vec2(0, 0)) * 100
			+ (m_textures[7].taille() != glm::vec2(0, 0)) * 1000;

		glEnable(GL_DEPTH_TEST);
		glUseProgram(m_shader.identifiant());

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, &m_informationsSommets[0]);
		glEnableVertexAttribArray(0);

		for (int i = 0; i < 8; ++i)
		{
			if (m_textures[i].taille() != glm::vec2(0, 0))
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textures[i].identifiant());

				glUniform1i(glGetUniformLocation(m_shader.identifiant(), ("texture" + identifiants[i]).c_str()), i);
			}
		}

		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "texturesExistantes0123"), texturesExistantes0123);
		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "texturesExistantes4567"), texturesExistantes4567);
		glUniformMatrix4fv(glGetUniformLocation(m_shader.identifiant(), "matriceAffichage"), 1, GL_FALSE, glm::value_ptr(m_matriceProjection * m_matriceVue));
		glUniform4fv(glGetUniformLocation(m_shader.identifiant(), "coordonneesSommetsModele"), m_coordonneesSommets.size() / 4, &m_coordonneesSommets[0]);
		glUniform3fv(glGetUniformLocation(m_shader.identifiant(), "coordonneesTextureModele"), m_coordonneesTexture.size() / 3, &m_coordonneesTexture[0]);

		
		glDrawArrays(GL_TRIANGLES, identifiantPremierSommet, (nombreSommets < 0 ? this->nombreSommets() - identifiantPremierSommet : nombreSommets));

		for (int i = 0; i < 8; ++i)
		{
			if (m_textures[i].taille() != glm::vec2(0, 0))
			{
				glDisable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		glDisableVertexAttribArray(0);

		glUseProgram(0);
		glDisable(GL_DEPTH_TEST);
	}
}
