#include "Affichage3D.hpp"

ng::Affichage3D::Affichage3D(const glm::mat4& matriceProjection, const glm::mat4& matriceVue, int nombreSommetsMaximumVBO) :
	m_shader("Shaders/Affichage3D.vert", "Shaders/Affichage3D.frag"),
	m_matriceProjection(matriceProjection),
	m_matriceVue(matriceVue),
	m_VBO(nombreSommetsMaximumVBO * 13),
	m_directionRayonsLumineux(0, 0, 0),
	m_intensiteLumiereMinimale(0),
	m_intensiteLumiereMaximale(1),
	m_facesSombresEclairees(false)
{
	/*
	 * textures : 8 maximum (identifiants de 0 à 7
	 * m_coordonneesTexture : coordonnée z pour l'identifiant de la texture (-1 pour aucune texture)
	*/


	// Initialisation des 8 textures
	for (int i = 0; i < 8; ++i)
		m_textures.push_back(Texture());
}

int ng::Affichage3D::nombreSommetsMaximumVBO() const
{
	return m_VBO.taille() / 13;
}

int ng::Affichage3D::nombreSommets() const
{
	return int(m_coordonneesSommets.size() / 3);
}

int ng::Affichage3D::nombreSourcesLumineuses() const
{
	return int(sourcesLumineuses.size() / 4);
}

glm::vec2 ng::Affichage3D::tailleTexture(int identifiantTexture) const
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		return m_textures[identifiantTexture].taille();
	return glm::vec2(0, 0);
}

glm::vec3 ng::Affichage3D::coordonneesSommet(int identifiantSommet) const
{
	if (identifiantSommet >= 0 && identifiantSommet < nombreSommets())
		return glm::vec3(m_coordonneesSommets[3 * identifiantSommet], m_coordonneesSommets[3 * identifiantSommet + 1], m_coordonneesSommets[3 * identifiantSommet + 2]);
	return glm::vec3(0, 0, 0);
}

glm::vec4 ng::Affichage3D::couleur(int identifiantSommet) const
{
	if (identifiantSommet >= 0 && identifiantSommet < nombreSommets())
		return glm::vec4(m_couleurs[4 * identifiantSommet], m_couleurs[4 * identifiantSommet + 1], m_couleurs[4 * identifiantSommet + 2], m_couleurs[4 * identifiantSommet + 3]);
	return glm::vec4(0, 0, 0, 0);
}

glm::vec3 ng::Affichage3D::coordonneesTexture(int identifiantSommet) const
{
	if (identifiantSommet >= 0 && identifiantSommet < nombreSommets())
		return glm::vec3(m_coordonneesTexture[3 * identifiantSommet], m_coordonneesTexture[3 * identifiantSommet + 1], m_coordonneesTexture[3 * identifiantSommet + 2]);
	return glm::vec3(0, 0, 0);
}

const glm::mat4& ng::Affichage3D::matriceProjection() const
{
	return m_matriceProjection;
}

const glm::mat4& ng::Affichage3D::matriceVue() const
{
	return m_matriceVue;
}

void ng::Affichage3D::modifierMatriceProjection(const glm::mat4& matrice)
{
	m_matriceProjection = matrice;
}

void ng::Affichage3D::modifierMatriceVue(const glm::mat4& matrice)
{
	m_matriceVue = matrice;
}

void ng::Affichage3D::modifierDirectionRayonsLumineux(const glm::vec3& direction)
{
	m_directionRayonsLumineux = direction;
}

void ng::Affichage3D::modifierIntensiteLumiereMinimale(float intensite)
{
	m_intensiteLumiereMinimale = intensite;
}

void ng::Affichage3D::modifierIntensiteLumiereMaximale(float intensite)
{
	m_intensiteLumiereMaximale = intensite;
}

void ng::Affichage3D::modifierFacesSombresEclairees(bool facesSombresEclairees)
{
	m_facesSombresEclairees = facesSombresEclairees;
}

void ng::Affichage3D::ajouterSommets(const std::vector<float>& coordonneesSommets, const std::vector<float>& couleurs, const std::vector<float>& coordonneesTexture, const std::vector<float>& normales)
{
	float nombreSommetsAvantAjout = nombreSommets();

	// Ajout des sommets dans le tableau des coordonnées
	for (int i = 0; i < coordonneesSommets.size() / 3; ++i)
	{
		m_coordonneesSommets.push_back(coordonneesSommets[3 * i]);
		m_coordonneesSommets.push_back(coordonneesSommets[3 * i + 1]);
		m_coordonneesSommets.push_back(coordonneesSommets[3 * i + 2]);

		m_couleurs.push_back(couleurs[4 * i]);
		m_couleurs.push_back(couleurs[4 * i + 1]);
		m_couleurs.push_back(couleurs[4 * i + 2]);
		m_couleurs.push_back(couleurs[4 * i + 3]);

		m_coordonneesTexture.push_back(coordonneesTexture[3 * i]);
		m_coordonneesTexture.push_back(coordonneesTexture[3 * i + 1]);
		m_coordonneesTexture.push_back(coordonneesTexture[3 * i + 2]);

		m_normales.push_back(normales[3 * i]);
		m_normales.push_back(normales[3 * i + 1]);
		m_normales.push_back(normales[3 * i + 2]);
	}


	// Ajout des nouveaux sommets dans le VBO
	m_VBO.ajouterDonnees(nombreSommetsAvantAjout * 3, coordonneesSommets.size(), &coordonneesSommets[0]);
	m_VBO.ajouterDonnees(nombreSommetsMaximumVBO() * 3 + nombreSommetsAvantAjout * 4, couleurs.size(), &couleurs[0]);
	m_VBO.ajouterDonnees(nombreSommetsMaximumVBO() * 7 + nombreSommetsAvantAjout * 3, coordonneesTexture.size(), &coordonneesTexture[0]);
	m_VBO.ajouterDonnees(nombreSommetsMaximumVBO() * 10 + nombreSommetsAvantAjout * 3, normales.size(), &normales[0]);
}

void ng::Affichage3D::ajouterSommets(const Cube3D& cube, const std::vector<bool>& facesAffichees)
{
	int nombreSommetsCube = 0;
	for (int i = 0; i < 6; ++i)
		nombreSommetsCube += (facesAffichees[i] ? 6 : 0);

	ajouterSommets(cube.coordonneesSommets(facesAffichees), cube.couleurs(facesAffichees), cube.coordonneesTexture(facesAffichees), cube.normales(facesAffichees));
}

void ng::Affichage3D::ajouterSourceLumineuse(const glm::vec3& coordonnees, float intensite)
{
	if (nombreSourcesLumineuses() < 50)
	{
		sourcesLumineuses.push_back(coordonnees.x);
		sourcesLumineuses.push_back(coordonnees.y);
		sourcesLumineuses.push_back(coordonnees.z);
		sourcesLumineuses.push_back(intensite);
	}
}

void ng::Affichage3D::ajouterTexture(int identifiantTexture, std::string cheminTexture, bool textureAdoucie)
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		m_textures[identifiantTexture].charger(cheminTexture, textureAdoucie, GL_LINEAR, (textureAdoucie ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST));
}

void ng::Affichage3D::supprimerTexture(int identifiantTexture)
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		m_textures[identifiantTexture] = Texture();
}

void ng::Affichage3D::reinitialiser()
{
	m_coordonneesSommets.clear();
	m_couleurs.clear();
	m_coordonneesTexture.clear();
	m_normales.clear();
}

void ng::Affichage3D::afficher(int identifiantPremierSommet, int nombreSommets)
{
	if (identifiantPremierSommet < this->nombreSommets() && (identifiantPremierSommet + nombreSommets - 1 < this->nombreSommets() || nombreSommets == -1))
	{
		std::string identifiants[8] = {"0", "1", "2", "3", "4", "5", "6", "7"};
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

		if (m_VBO.taille() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO.identifiant());

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(nombreSommetsMaximumVBO() * 3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(nombreSommetsMaximumVBO() * 7 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)(nombreSommetsMaximumVBO() * 10 * sizeof(float)));
			glEnableVertexAttribArray(3);
		}
		else
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &m_coordonneesSommets[0]);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, &m_couleurs[0]);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, &m_coordonneesTexture[0]);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, &m_normales[0]);
			glEnableVertexAttribArray(3);
		}

		for (int i = 0; i < 8; ++i)
		{
			if (m_textures[i].taille() != glm::vec2(0, 0))
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textures[i].identifiant());

				glUniform1i(glGetUniformLocation(m_shader.identifiant(), ("texture" + identifiants[i]).c_str()), i);
			}
		}

		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "intensiteLumiereMinimale"), m_intensiteLumiereMinimale);
		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "intensiteLumiereMaximale"), m_intensiteLumiereMaximale);
		glUniform3fv(glGetUniformLocation(m_shader.identifiant(), "directionRayonsLumineux"), 1, glm::value_ptr(m_directionRayonsLumineux));
		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "facesSombresEclairees"), m_facesSombresEclairees);
		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "nombreSourcesLumineuses"), nombreSourcesLumineuses());
		glUniform4fv(glGetUniformLocation(m_shader.identifiant(), "sourcesLumineuses"), nombreSourcesLumineuses(), &sourcesLumineuses[0]);
		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "texturesExistantes0123"), texturesExistantes0123);
		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "texturesExistantes4567"), texturesExistantes4567);
		glUniformMatrix4fv(glGetUniformLocation(m_shader.identifiant(), "matriceAffichage"), 1, GL_FALSE, glm::value_ptr(m_matriceProjection * m_matriceVue));

		glDrawArrays(GL_TRIANGLES, identifiantPremierSommet, (nombreSommets < 0 ? this->nombreSommets() - identifiantPremierSommet : nombreSommets));

		for (int i = 0; i < 8; ++i)
		{
			if (m_textures[i].taille() != glm::vec2(0, 0))
			{
				glDisable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
		glDisable(GL_DEPTH_TEST);
	}
}
