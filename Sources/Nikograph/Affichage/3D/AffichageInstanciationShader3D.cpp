#include "AffichageInstanciationShader3D.hpp"

#define RESOLUTION_OMBRES 4096
#define DISTANCE_AFFICHAGE_OMBRE 200

ng::AffichageInstanciationShader3D::AffichageInstanciationShader3D(const glm::mat4& matriceProjection, const glm::mat4& matriceVue) :
	m_shader("Shaders/AffichageInstanciationShader3D.vert", "Shaders/AffichageInstanciationShader3D.frag", "Shaders/AffichageInstanciationShader3D.geom"),
	m_shaderOmbres("Shaders/AffichageInstanciationShader3D.vert", "Shaders/AffichageInstanciationShader3D - Ombres.frag", "Shaders/AffichageInstanciationShader3D - Ombres.geom"),
	m_matriceProjection(matriceProjection),
	m_matriceVue(matriceVue),
	m_frameBuffer(glm::vec2(RESOLUTION_OMBRES, RESOLUTION_OMBRES))
{
	// Initialisation des 8 textures
	for (int i = 0; i < 8; ++i)
		m_textures.push_back(Texture());

	m_frameBuffer.charger();
}

int ng::AffichageInstanciationShader3D::nombreSommets() const
{
	return int(m_informationsSommets.size() / 4);
}

glm::vec2 ng::AffichageInstanciationShader3D::tailleTexture(int identifiantTexture) const
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		return m_textures[identifiantTexture].taille();
	return glm::vec2(0, 0);
}

const glm::mat4& ng::AffichageInstanciationShader3D::matriceProjection() const
{
	return m_matriceProjection;
}

const glm::mat4& ng::AffichageInstanciationShader3D::matriceVue() const
{
	return m_matriceVue;
}

void ng::AffichageInstanciationShader3D::modifierMatriceProjection(const glm::mat4& matrice)
{
	m_matriceProjection = matrice;
}

void ng::AffichageInstanciationShader3D::modifierMatriceVue(const glm::mat4& matrice)
{
	m_matriceVue = matrice;
}

void ng::AffichageInstanciationShader3D::ajouterSommets(const glm::vec3& position, const glm::vec3& taille, int identifiantBloc, float facesAffichees)
{
	m_informationsSommets.push_back((int)identifiantBloc * 100000.0 + (int)taille.x * 1000.0 + int(position.x * 10) / 10.);
	m_informationsSommets.push_back((int)taille.y * 1000.0 + int(position.y * 10) / 10.);
	m_informationsSommets.push_back((int)taille.z * 1000.0 + int(position.z * 10) / 10.);
	m_informationsSommets.push_back(facesAffichees);
	m_positionElements.push_back(position);
}

void ng::AffichageInstanciationShader3D::ajouterSommets(const std::vector<float>& positions, const std::vector<float>& tailleFaces, const std::vector<float>& identifiantsBlocs, const std::vector<float>& facesAffichees)
{
	for (int i = 0; i < positions.size() / 3; ++i)
		ajouterSommets(glm::vec3(positions[3 * i], positions[3 * i + 1], positions[3 * i + 2]), glm::vec3(tailleFaces[3 * i], tailleFaces[3 * i + 1], tailleFaces[3 * i + 2]), identifiantsBlocs[i], facesAffichees[i]);
}

void ng::AffichageInstanciationShader3D::ajouterTexture(int identifiantTexture, std::string cheminTexture, bool textureAdoucie)
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		m_textures[identifiantTexture].charger(cheminTexture, textureAdoucie, GL_LINEAR, (textureAdoucie ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST));
}

void ng::AffichageInstanciationShader3D::supprimerSommets(int identifiantElement)
{
	m_informationsSommets.erase(m_informationsSommets.begin() + identifiantElement * 4, m_informationsSommets.begin() + (identifiantElement + 1) * 4);
	m_positionElements.erase(m_positionElements.begin() + identifiantElement);
}

bool ng::AffichageInstanciationShader3D::supprimerSommetsCube(const glm::vec3& positionCube)
{
	for (int i = 0; i < m_informationsSommets.size() / 4; ++i)
	{
		if (m_positionElements[i].x == positionCube.x && m_positionElements[i].y == positionCube.y && m_positionElements[i].z == positionCube.z)
		{
			supprimerSommets(i);
			return true;
		}
	}

	return false;	
}

void ng::AffichageInstanciationShader3D::supprimerSommetsCube(const glm::vec3& positionCubeMini, const glm::vec3& positionCubeMaxi)
{
	for (int i = 0; i < m_informationsSommets.size() / 4; ++i)
	{
		if (m_positionElements[i].x >= positionCubeMini.x && m_positionElements[i].y >= positionCubeMini.y && m_positionElements[i].z >= positionCubeMini.z &&
			m_positionElements[i].x <= positionCubeMaxi.x && m_positionElements[i].y <= positionCubeMaxi.y && m_positionElements[i].z <= positionCubeMaxi.z)
		{
			supprimerSommets(i);
			--i;
		}
	}
}

void ng::AffichageInstanciationShader3D::supprimerTexture(int identifiantTexture)
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		m_textures[identifiantTexture] = Texture();
}

void ng::AffichageInstanciationShader3D::reinitialiser()
{
	m_informationsSommets.clear();
}

void ng::AffichageInstanciationShader3D::afficher(const glm::vec3& positionCamera, int identifiantPremierSommet, int nombreSommets)
{
	bool utiliserVBO = false;

	if (m_identifiantVBO == 0 && utiliserVBO)
	{
		glGenBuffers(1, &m_identifiantVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_identifiantVBO);
		glBufferData(GL_ARRAY_BUFFER, m_informationsSommets.size() * sizeof(float), &m_informationsSommets[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if (utiliserVBO)
		glBindBuffer(GL_ARRAY_BUFFER, m_identifiantVBO);

	if (identifiantPremierSommet < this->nombreSommets() && (identifiantPremierSommet + nombreSommets - 1 < this->nombreSommets() || nombreSommets == -1))
	{
		float m_tailleTerrain = DISTANCE_AFFICHAGE_OMBRE / 10.;
		float m_positionOmbres = 1;
		glm::vec3 positionCameraOmbres(m_positionOmbres * m_tailleTerrain * 10, m_positionOmbres * m_tailleTerrain * 10, 0);
		glm::mat4 matriceProjection = glm::ortho<float>(-m_tailleTerrain * 10, m_tailleTerrain * 10, -m_tailleTerrain * 10, m_tailleTerrain * 10, -m_tailleTerrain * 10, m_tailleTerrain * 10);
		glm::mat4 matriceVue = glm::lookAt(glm::vec3(m_tailleTerrain * 5, m_tailleTerrain * 5, m_tailleTerrain * 5), positionCameraOmbres, glm::vec3(0, 0, 1));

		std::string identifiants[8] = { "0", "1", "2", "3", "4", "5", "6", "7" };
		float texturesExistantes0123 = (m_textures[0].taille() != glm::vec2(0, 0))
			+ (m_textures[1].taille() != glm::vec2(0, 0)) * 10
			+ (m_textures[2].taille() != glm::vec2(0, 0)) * 100
			+ (m_textures[3].taille() != glm::vec2(0, 0)) * 1000;
		float texturesExistantes4567 = (m_textures[4].taille() != glm::vec2(0, 0))
			+ (m_textures[5].taille() != glm::vec2(0, 0)) * 10
			+ (m_textures[6].taille() != glm::vec2(0, 0)) * 100
			+ (m_textures[7].taille() != glm::vec2(0, 0)) * 1000;

		std::vector<float> coordonneesSommetsModele = {
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
			-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
		std::vector<float> coordonneesTextureModele = {
			0, 0, 1, 0, 0, 1, 
			1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1 };

		glEnable(GL_DEPTH_TEST);
		glUseProgram(m_shader.identifiant());

		if (!utiliserVBO)
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, &m_informationsSommets[0]);
		else
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
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

		glActiveTexture(GL_TEXTURE0 + 8);
		glBindTexture(GL_TEXTURE_2D, m_frameBuffer.identifiantTexture());
		glUniform1i(glGetUniformLocation(m_shader.identifiant(), "textureOmbres"), 8);

		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "texturesExistantes0123"), texturesExistantes0123);
		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "texturesExistantes4567"), texturesExistantes4567);
		glUniformMatrix4fv(glGetUniformLocation(m_shader.identifiant(), "matriceAffichage"), 1, GL_FALSE, glm::value_ptr(m_matriceProjection * m_matriceVue));
		glUniformMatrix4fv(glGetUniformLocation(m_shader.identifiant(), "matriceOmbres"), 1, GL_FALSE, glm::value_ptr(matriceProjection * matriceVue));
		glUniform3fv(glGetUniformLocation(m_shader.identifiant(), "coordonneesSommetsModele"), coordonneesSommetsModele.size() / 3, &coordonneesSommetsModele[0]);
		glUniform2fv(glGetUniformLocation(m_shader.identifiant(), "coordonneesTextureModele"), coordonneesTextureModele.size() / 2, &coordonneesTextureModele[0]);
		glUniform3f(glGetUniformLocation(m_shader.identifiant(), "coordonneesCamera"), positionCamera.x, positionCamera.y, positionCamera.z);

		
		glDrawArrays(GL_POINTS, identifiantPremierSommet, (nombreSommets < 0 ? this->nombreSommets() - identifiantPremierSommet : nombreSommets));

		for (int i = 0; i < 8; ++i)
		{
			if (m_textures[i].taille() != glm::vec2(0, 0))
			{
				glDisable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisableVertexAttribArray(0);

		glUseProgram(0);
		glDisable(GL_DEPTH_TEST);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ng::AffichageInstanciationShader3D::genererOmbre(const glm::vec3& positionCamera, const glm::vec2& tailleFenetre, int identifiantPremierSommet, int nombreSommets)
{
	if (identifiantPremierSommet < this->nombreSommets() && (identifiantPremierSommet + nombreSommets - 1 < this->nombreSommets() || nombreSommets == -1))
	{
		float m_tailleTerrain = DISTANCE_AFFICHAGE_OMBRE / 10.;
		float m_positionOmbres = 1;

		glm::vec3 positionCameraOmbres(m_positionOmbres * m_tailleTerrain * 10, m_positionOmbres * m_tailleTerrain * 10, 0);

		glm::mat4 matriceProjection = glm::ortho<float>(-m_tailleTerrain * 10, m_tailleTerrain * 10, -m_tailleTerrain * 10, m_tailleTerrain * 10, -m_tailleTerrain * 10, m_tailleTerrain * 10);
		glm::mat4 matriceVue = glm::lookAt(glm::vec3(m_tailleTerrain * 5, m_tailleTerrain * 5, m_tailleTerrain * 5), positionCameraOmbres, glm::vec3(0, 0, 1));

		std::vector<float> coordonneesSommetsModele = {
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
			-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
		std::vector<float> coordonneesTextureModele = {
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 0, 1,
			1, 0, 1, 1, 0, 1 };

		glEnable(GL_DEPTH_TEST);
		glUseProgram(m_shaderOmbres.identifiant());

		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer.identifiant());

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, &m_informationsSommets[0]);
		glEnableVertexAttribArray(0);

		glUniformMatrix4fv(glGetUniformLocation(m_shaderOmbres.identifiant(), "matriceOmbres"), 1, GL_FALSE, glm::value_ptr(matriceProjection * matriceVue));
		glUniform3fv(glGetUniformLocation(m_shaderOmbres.identifiant(), "coordonneesSommetsModele"), coordonneesSommetsModele.size() / 3, &coordonneesSommetsModele[0]);
		glUniform2fv(glGetUniformLocation(m_shaderOmbres.identifiant(), "coordonneesTextureModele"), coordonneesTextureModele.size() / 2, &coordonneesTextureModele[0]);
		glUniform3f(glGetUniformLocation(m_shaderOmbres.identifiant(), "coordonneesCamera"), positionCameraOmbres.x, positionCameraOmbres.y, positionCameraOmbres.z);

		glViewport(0, 0, RESOLUTION_OMBRES, RESOLUTION_OMBRES);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_POINTS, identifiantPremierSommet, (nombreSommets < 0 ? this->nombreSommets() - identifiantPremierSommet : nombreSommets));

		glViewport(0, 0, tailleFenetre.x, tailleFenetre.y);

		glDisableVertexAttribArray(0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glUseProgram(0);
		glDisable(GL_DEPTH_TEST);
	}
}