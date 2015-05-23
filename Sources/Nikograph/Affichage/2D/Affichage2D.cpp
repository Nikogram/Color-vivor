#include "Affichage2D.hpp"

ng::Affichage2D::Affichage2D(const glm::vec2* taillePixelsFenetre, ng::GrandeurMetrique grandeurMetrique, int nombreSommetsMaximumVBO) :
	m_taillePixelsFenetre(taillePixelsFenetre),
	m_grandeurMetrique(grandeurMetrique),
	m_shader("Shaders/Affichage2D.vert", "Shaders/Affichage2D.frag"),
	m_VBO(nombreSommetsMaximumVBO * 9)
{
	/*
	 * textures : 8 maximum (identifiants de 0 à 7
	 * m_coordonneesTexture : coordonnée z pour l'identifiant de la texture (-1 pour aucune texture)
	*/


	// Initialisation des 8 textures
	for (int i = 0; i < 8; ++i)
		m_textures.push_back(Texture());
}

int ng::Affichage2D::nombreSommetsMaximumVBO() const
{
	return m_VBO.taille() / 9;
}

int ng::Affichage2D::nombreSommets() const
{
	return int(m_coordonneesSommets.size() / 2);
}

glm::vec2 ng::Affichage2D::tailleTexture(int identifiantTexture) const
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		return m_textures[identifiantTexture].taille();
	return glm::vec2(0, 0);
}

glm::vec2 ng::Affichage2D::coordonneesSommet(int identifiantSommet) const
{
	if (identifiantSommet >= 0 && identifiantSommet < nombreSommets())
		return glm::vec2(m_coordonneesSommets[2 * identifiantSommet], m_coordonneesSommets[2 * identifiantSommet + 1]);
	return glm::vec2(0, 0);
}

glm::vec4 ng::Affichage2D::couleur(int identifiantSommet) const
{
	if (identifiantSommet >= 0 && identifiantSommet < nombreSommets())
		return glm::vec4(m_couleurs[4 * identifiantSommet], m_couleurs[4 * identifiantSommet + 1], m_couleurs[4 * identifiantSommet + 2], m_couleurs[4 * identifiantSommet + 3]);
	return glm::vec4(0, 0, 0, 0);
}

glm::vec3 ng::Affichage2D::coordonneesTexture(int identifiantSommet) const
{
	if (identifiantSommet >= 0 && identifiantSommet < nombreSommets())
		return glm::vec3(m_coordonneesTexture[3 * identifiantSommet], m_coordonneesTexture[3 * identifiantSommet + 1], m_coordonneesTexture[3 * identifiantSommet + 2]);
	return glm::vec3(0, 0, 0);
}

glm::vec2 ng::Affichage2D::ratioAffichage() const
{
	return glm::vec2((m_grandeurMetrique == RelatifRedimensionneX ? m_taillePixelsFenetre->y / m_taillePixelsFenetre->x : 1),
		(m_grandeurMetrique == RelatifRedimensionneY ? m_taillePixelsFenetre->x / m_taillePixelsFenetre->y : 1));
}

void ng::Affichage2D::modifierGrandeurMetrique(ng::GrandeurMetrique grandeurMetrique)
{
	m_grandeurMetrique = grandeurMetrique;
}

void ng::Affichage2D::ajouterSommets(const std::vector<float>& coordonneesSommets, const std::vector<float>& couleurs, const std::vector<float>& coordonneesTexture)
{
	float nombreSommetsAvantAjout = nombreSommets();


	// Ajout des sommets dans le tableau des coordonnées
	for (int i = 0; i < coordonneesSommets.size() / 2; ++i)
	{
		if (m_grandeurMetrique == Pixels)
		{
			m_coordonneesSommets.push_back(2 * coordonneesSommets[2 * i] / m_taillePixelsFenetre->x - 1);
			m_coordonneesSommets.push_back(1 - 2 * coordonneesSommets[2 * i + 1] / m_taillePixelsFenetre->y);
		}
		else
		{
			m_coordonneesSommets.push_back(coordonneesSommets[2 * i] * 2 - 1);
			m_coordonneesSommets.push_back(1 - coordonneesSommets[2 * i + 1] * 2);
		}

		m_couleurs.push_back(couleurs[4 * i]);
		m_couleurs.push_back(couleurs[4 * i + 1]);
		m_couleurs.push_back(couleurs[4 * i + 2]);
		m_couleurs.push_back(couleurs[4 * i + 3]);

		if (coordonneesTexture[3 * i + 2] >= 0 && coordonneesTexture[3 * i + 2] < 8 && m_textures[coordonneesTexture[3 * i + 2]].taille().x != 0 && m_textures[coordonneesTexture[3 * i + 2]].taille().y != 0)
		{
			m_coordonneesTexture.push_back(coordonneesTexture[3 * i] / m_textures[coordonneesTexture[3 * i + 2]].taille().x);
			m_coordonneesTexture.push_back(coordonneesTexture[3 * i + 1] / m_textures[coordonneesTexture[3 * i + 2]].taille().y);
		}
		else
		{
			m_coordonneesTexture.push_back(0);
			m_coordonneesTexture.push_back(0);
		}
		m_coordonneesTexture.push_back(coordonneesTexture[3 * i + 2]);
	}


	// Ajout des nouveaux sommets dans le VBO
	m_VBO.ajouterDonnees(nombreSommetsAvantAjout * 2, coordonneesSommets.size(), &m_coordonneesSommets[nombreSommetsAvantAjout * 2]);
	m_VBO.ajouterDonnees(nombreSommetsMaximumVBO() * 2 + nombreSommetsAvantAjout * 4, couleurs.size(), &m_couleurs[nombreSommetsAvantAjout * 4]);
	m_VBO.ajouterDonnees(nombreSommetsMaximumVBO() * 6 + nombreSommetsAvantAjout * 3, coordonneesTexture.size(), &m_coordonneesTexture[nombreSommetsAvantAjout * 3]);
}

void ng::Affichage2D::ajouterSommets(const Rectangle2D& rectangle)
{
	std::vector<float> coordonneesSommets = rectangle.coordonneesSommets();
	for (int i = 0; i < coordonneesSommets.size() / 2; ++i)
	{
		coordonneesSommets[2 * i] = (coordonneesSommets[2 * i] - rectangle.position().x) * ratioAffichage().x + rectangle.position().x;
		coordonneesSommets[2 * i + 1] = (coordonneesSommets[2 * i + 1] - rectangle.position().y) * ratioAffichage().y + rectangle.position().y;
	}

	std::vector<float> couleurs;
	for (int i = 0; i < 6; ++i)
	{
		couleurs.push_back(rectangle.couleur().x);
		couleurs.push_back(rectangle.couleur().y);
		couleurs.push_back(rectangle.couleur().z);
		couleurs.push_back(rectangle.couleur().w);
	}

	ajouterSommets(coordonneesSommets, couleurs, rectangle.coordonneesTexture());
}

void ng::Affichage2D::ajouterSommets(const Texte2D& texte)
{
	std::vector<float> coordonneesSommets = texte.coordonneesSommets();
	for (int i = 0; i < coordonneesSommets.size() / 2; ++i)
	{
		coordonneesSommets[2 * i] = (coordonneesSommets[2 * i] - texte.position().x) * ratioAffichage().x + texte.position().x;
		coordonneesSommets[2 * i + 1] = (coordonneesSommets[2 * i + 1] - texte.position().y) * ratioAffichage().y + texte.position().y;
	}

	std::vector<float> couleurs;
	for (int i = 0; i < 6 * texte.chaine().length(); ++i)
	{
		couleurs.push_back(texte.couleur().x);
		couleurs.push_back(texte.couleur().y);
		couleurs.push_back(texte.couleur().z);
		couleurs.push_back(texte.couleur().w);
	}

	ajouterSommets(coordonneesSommets, couleurs, texte.coordonneesTexture());
}

void ng::Affichage2D::ajouterSommets(const Bouton2D& bouton)
{
	ajouterSommets(bouton.fond());
	ajouterSommets(bouton.texte());
}

void ng::Affichage2D::ajouterSommets(const ZoneTexte2D& zoneTexte)
{
	ajouterSommets(zoneTexte.fond());

	{
		std::vector<float> coordonneesSommets = zoneTexte.texte().coordonneesSommets();
		for (int i = 0; i < coordonneesSommets.size() / 2; ++i)
		{
			coordonneesSommets[2 * i] = (coordonneesSommets[2 * i] - zoneTexte.fond().position().x) * ratioAffichage().x + zoneTexte.fond().position().x;
			coordonneesSommets[2 * i + 1] = (coordonneesSommets[2 * i + 1] - zoneTexte.fond().position().y) * ratioAffichage().y + zoneTexte.fond().position().y;
		}

		std::vector<float> couleurs;
		for (int i = 0; i < 6 * zoneTexte.texte().chaine().length(); ++i)
		{
			couleurs.push_back(zoneTexte.texte().couleur().x);
			couleurs.push_back(zoneTexte.texte().couleur().y);
			couleurs.push_back(zoneTexte.texte().couleur().z);
			couleurs.push_back(zoneTexte.texte().couleur().w);
		}

		ajouterSommets(coordonneesSommets, couleurs, zoneTexte.texte().coordonneesTexture());
	}

	if (zoneTexte.selectionne())
	{
		std::vector<float> coordonneesSommets = zoneTexte.curseur().coordonneesSommets();
		for (int i = 0; i < coordonneesSommets.size() / 2; ++i)
		{
			coordonneesSommets[2 * i] = (coordonneesSommets[2 * i] - zoneTexte.fond().position().x) * ratioAffichage().x + zoneTexte.fond().position().x;
			coordonneesSommets[2 * i + 1] = (coordonneesSommets[2 * i + 1] - zoneTexte.fond().position().y) * ratioAffichage().y + zoneTexte.fond().position().y;
		}

		std::vector<float> couleurs;
		for (int i = 0; i < 6; ++i)
		{
			couleurs.push_back(zoneTexte.curseur().couleur().x);
			couleurs.push_back(zoneTexte.curseur().couleur().y);
			couleurs.push_back(zoneTexte.curseur().couleur().z);
			couleurs.push_back(zoneTexte.curseur().couleur().w);
		}

		ajouterSommets(coordonneesSommets, couleurs, zoneTexte.curseur().coordonneesTexture());
	}
}

void ng::Affichage2D::modifierSommet(int identifiantSommet, const glm::vec2& coordonneesSommet, const glm::vec4& couleur, const glm::vec3& coordonneesTexture)
{
	// Modification du sommet dans le tableau
	if (m_grandeurMetrique == Pixels)
	{
		m_coordonneesSommets[identifiantSommet * 2] = 2.0 * coordonneesSommet.x / m_taillePixelsFenetre->x - 1.0;
		m_coordonneesSommets[identifiantSommet * 2 + 1] = 1.0 - 2.0 * coordonneesSommet.y / m_taillePixelsFenetre->y;
	}
	else
	{
		m_coordonneesSommets[identifiantSommet * 2] = 2 * coordonneesSommet.x - 1;
		m_coordonneesSommets[identifiantSommet * 2 + 1] = 1 - 2 * coordonneesSommet.y;
	}

	m_couleurs[identifiantSommet * 4] = couleur.x;
	m_couleurs[identifiantSommet * 4 + 1] = couleur.y;
	m_couleurs[identifiantSommet * 4 + 2] = couleur.z;
	m_couleurs[identifiantSommet * 4 + 3] = couleur.w;
	m_coordonneesTexture[identifiantSommet * 3] = coordonneesTexture.x / m_textures[(coordonneesTexture.z >= 0 && coordonneesTexture.z < 8) ? coordonneesTexture.z : 0].taille().x;
	m_coordonneesTexture[identifiantSommet * 3 + 1] = coordonneesTexture.y / m_textures[0].taille().y;
	m_coordonneesTexture[identifiantSommet * 3 + 2] = coordonneesTexture.z;


	// Modification du sommet dans le VBO
	m_VBO.ajouterDonnees(identifiantSommet * 2, 2, &m_coordonneesSommets[identifiantSommet * 2]);
	m_VBO.ajouterDonnees(nombreSommetsMaximumVBO() * 2 + identifiantSommet * 4, 4, &m_couleurs[identifiantSommet * 4]);
	m_VBO.ajouterDonnees(nombreSommetsMaximumVBO() * 6 + identifiantSommet * 3, 3, &m_coordonneesTexture[identifiantSommet * 3]);
}

void ng::Affichage2D::modifierSommets(int identifiantPremierSommet, const std::vector<float>& coordonneesSommets, const std::vector<float>& couleurs, const std::vector<float>& coordonneesTexture)
{
	// Modification du sommet dans le tableau
	for (int i = 0; i < coordonneesSommets.size() / 2; ++i)
	{
		if (m_grandeurMetrique == Pixels)
		{
			m_coordonneesSommets[(identifiantPremierSommet + i) * 2] = 2.0 * coordonneesSommets[2 * i] / m_taillePixelsFenetre->x - 1.0;
			m_coordonneesSommets[(identifiantPremierSommet + i) * 2 + 1] = 1.0 - 2.0 * coordonneesSommets[2 * i + 1] / m_taillePixelsFenetre->y;
		}
		else
		{
			m_coordonneesSommets[(identifiantPremierSommet + i) * 2] = 2 * coordonneesSommets[2 * i] - 1;
			m_coordonneesSommets[(identifiantPremierSommet + i) * 2 + 1] = 1 - 2 * coordonneesSommets[2 * i + 1];
		}

		m_couleurs[(identifiantPremierSommet + i) * 4] = couleurs[4 * i];
		m_couleurs[(identifiantPremierSommet + i) * 4 + 1] = couleurs[4 * i + 1];
		m_couleurs[(identifiantPremierSommet + i) * 4 + 2] = couleurs[4 * i + 2];
		m_couleurs[(identifiantPremierSommet + i) * 4 + 3] = couleurs[4 * i + 3];
		m_coordonneesTexture[(identifiantPremierSommet + i) * 3] = coordonneesTexture[3 * i] / m_textures[(coordonneesTexture[3 * i + 2] >= 0 && coordonneesTexture[3 * i + 2] < 8) ? coordonneesTexture[3 * i + 2] : 0].taille().x;
		m_coordonneesTexture[(identifiantPremierSommet + i) * 3 + 1] = coordonneesTexture[3 * i + 1] / m_textures[(coordonneesTexture[3 * i + 2] >= 0 && coordonneesTexture[3 * i + 2] < 8) ? coordonneesTexture[3 * i + 2] : 0].taille().y;
		m_coordonneesTexture[(identifiantPremierSommet + i) * 3 + 2] = coordonneesTexture[3 * i + 2];
	}

	// Modification du sommet dans le VBO
	m_VBO.ajouterDonnees(identifiantPremierSommet * 2, coordonneesSommets.size(), &m_coordonneesSommets[identifiantPremierSommet * 2]);
	m_VBO.ajouterDonnees(nombreSommetsMaximumVBO() * 2 + identifiantPremierSommet * 4, couleurs.size(), &m_couleurs[identifiantPremierSommet * 4]);
	m_VBO.ajouterDonnees(nombreSommetsMaximumVBO() * 6 + identifiantPremierSommet * 3, coordonneesTexture.size(), &m_coordonneesTexture[identifiantPremierSommet * 3]);
}

void ng::Affichage2D::ajouterTexture(int identifiantTexture, std::string cheminTexture, bool textureAdoucie)
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		m_textures[identifiantTexture].charger(cheminTexture, false, (textureAdoucie ? GL_LINEAR : GL_NEAREST), (textureAdoucie ? GL_LINEAR : GL_NEAREST));
}

void ng::Affichage2D::supprimerTexture(int identifiantTexture)
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
		m_textures[identifiantTexture] = Texture();
}

void ng::Affichage2D::ajouterTexturePolice(int identifiantTexture, std::string nomPolice, bool gras, bool italique, bool textureAdoucie)
{
	if (identifiantTexture >= 0 && identifiantTexture < 8)
	{
		if (gras && italique)
			m_textures[identifiantTexture].charger("Textures/Polices/" + nomPolice + " (gras italique).png", false, GL_NEAREST, (textureAdoucie ? GL_LINEAR : GL_NEAREST));
		else if (gras)
			m_textures[identifiantTexture].charger("Textures/Polices/" + nomPolice + " (gras).png", false, GL_NEAREST, (textureAdoucie ? GL_LINEAR : GL_NEAREST));
		else if (italique)
			m_textures[identifiantTexture].charger("Textures/Polices/" + nomPolice + " (italique).png", false, GL_NEAREST, (textureAdoucie ? GL_LINEAR : GL_NEAREST));
		else
			m_textures[identifiantTexture].charger("Textures/Polices/" + nomPolice + ".png", false, GL_NEAREST, (textureAdoucie ? GL_LINEAR : GL_NEAREST));
	}
}

void ng::Affichage2D::reinitialiser()
{
	m_coordonneesSommets.clear();
	m_couleurs.clear();
	m_coordonneesTexture.clear();
}

void ng::Affichage2D::afficher(int identifiantPremierSommet, int nombreSommets)
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

		glUseProgram(m_shader.identifiant());

		if (m_VBO.taille() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO.identifiant());

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(nombreSommetsMaximumVBO() * 2 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(nombreSommetsMaximumVBO() * 6 * sizeof(float)));
			glEnableVertexAttribArray(2);
		}
		else
		{
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, &m_coordonneesSommets[0]);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, &m_couleurs[0]);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, &m_coordonneesTexture[0]);
			glEnableVertexAttribArray(2);
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

		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "texturesExistantes0123"), texturesExistantes0123);
		glUniform1f(glGetUniformLocation(m_shader.identifiant(), "texturesExistantes4567"), texturesExistantes4567);

		glDrawArrays(GL_TRIANGLES, identifiantPremierSommet, (nombreSommets < 0 ? this->nombreSommets() - identifiantPremierSommet : nombreSommets));

		for (int i = 0; i < 8; ++i)
		{
			if (m_textures[i].taille() != glm::vec2(0, 0))
			{
				glDisable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}
}