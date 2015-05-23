#include "Texte2D.hpp"

ng::Texte2D::Texte2D(int identifiantTexturePolice, const std::string& chaine, const glm::vec2& position, float taillePolice, bool petiteTexture) :
	m_taillePolice(taillePolice),
	m_chaine(chaine),
	m_position(position),
	m_couleur(1, 1, 1, 1),
	m_angle(0),
	m_identifiantTexturePolice(identifiantTexturePolice),
	m_petiteTexture(petiteTexture)
{
}

float ng::Texte2D::taillePolice() const
{
	return m_taillePolice;
}

std::string ng::Texte2D::chaine() const
{
	return m_chaine;
}

const glm::vec2& ng::Texte2D::position() const
{
	return m_position;
}

const glm::vec4& ng::Texte2D::couleur() const
{
	return m_couleur;
}

float ng::Texte2D::angle() const
{
	return m_angle;
}

int ng::Texte2D::identifiantTexturePolice() const
{
	return m_identifiantTexturePolice;
}

glm::vec2 ng::Texte2D::taille() const
{
	return glm::vec2((nombreColonnes() + 1 - 1) * m_taillePolice / 1.8, nombreLignes() * m_taillePolice);
}

std::vector<float> ng::Texte2D::coordonneesSommets() const
{
	std::vector<float> coordonneesSommets;

	for (int i = 0; i < m_rectanglesAffichage.size(); ++i)
	{
		std::vector<float> coordonneesSommetsRectangle = m_rectanglesAffichage[i].coordonneesSommets();
		for (int j = 0; j < coordonneesSommetsRectangle.size(); ++j)
			coordonneesSommets.push_back(coordonneesSommetsRectangle[j]);
	}

	return coordonneesSommets;
}

std::vector<float> ng::Texte2D::coordonneesTexture() const
{
	std::vector<ng::Rectangle2D> rectanglesAffichage = this->rectanglesAffichage();
	std::vector<float> coordonneesTexture;

	for (int i = 0; i < rectanglesAffichage.size(); ++i)
	{
		std::vector<float> coordonneesSommetsRectangle = rectanglesAffichage[i].coordonneesTexture();
		for (int j = 0; j < coordonneesSommetsRectangle.size(); ++j)
			coordonneesTexture.push_back(coordonneesSommetsRectangle[j]);
	}

	return coordonneesTexture;
}

int ng::Texte2D::nombreLignes() const
{
	int nombreLignes = 1;

	for (int i = 0; i < m_chaine.length(); ++i)
	{
		if (m_chaine.substr(i, 1) == "\n" || m_chaine.substr(i, 1) == "\r")
			++nombreLignes;
	}

	return nombreLignes;
}

int ng::Texte2D::nombreColonnes() const
{
	int nombreColonnesMax = 0;
	int nombreColonnesLigneActuelle = 1;
	
	for (int i = 0; i < m_chaine.length(); ++i)
	{
		++nombreColonnesLigneActuelle;

		if (m_chaine.substr(i, 1) == "\n" || m_chaine.substr(i, 1) == "\r" || i == m_chaine.length() - 1)
		{
			if (nombreColonnesLigneActuelle > nombreColonnesMax)
				nombreColonnesMax = nombreColonnesLigneActuelle - 1;
			nombreColonnesLigneActuelle = 1;
		}
			
	}

	return nombreColonnesMax;
}

int ng::Texte2D::nombreColonnes(int numeroLigne) const
{
	if (numeroLigne < nombreLignes())
	{
		int numeroLigneActuelle = 0;
		int nombreColonnesLigneActuelle = 1;

		for (int i = 0; i < m_chaine.length(); ++i)
		{
			++nombreColonnesLigneActuelle;

			if (m_chaine.substr(i, 1) == "\n" || m_chaine.substr(i, 1) == "\r" || i == m_chaine.length() - 1)
			{
				if (numeroLigne == numeroLigneActuelle)
					return nombreColonnesLigneActuelle - 1;
				else
				{
					++numeroLigneActuelle;
					nombreColonnesLigneActuelle = 1;
				}
			}
		}
	}

	return 0;
}

void ng::Texte2D::modifierTaillePolice(float taille)
{
	m_taillePolice = taille;
}

void ng::Texte2D::modifierChaine(const std::string& chaine)
{
	m_chaine = chaine;
}

void ng::Texte2D::modifierPosition(const glm::vec2& position)
{
	m_position = position;
}

void ng::Texte2D::modifierCouleur(const glm::vec4& couleur)
{
	m_couleur = couleur;
}

void ng::Texte2D::modifierAngle(float angle)
{
	m_angle = angle;
}

void ng::Texte2D::modifierIdentifiantTexturePolice(int identifiantTexturePolice)
{
	m_identifiantTexturePolice = identifiantTexturePolice;
}

void ng::Texte2D::translater(const glm::vec2& deplacement)
{
	m_position += deplacement;
}

void ng::Texte2D::modifierEchelle(float echelle)
{
	m_taillePolice *= echelle;
}

void ng::Texte2D::tourner(float angle)
{
	m_angle += angle;
}

std::vector<ng::Rectangle2D> ng::Texte2D::rectanglesAffichage() const
{
	float numeroCaractereLigne = 0;
	int numeroLigne = 1;

	char caracteresAccents[15] = {'à', 'â', 'ä', 'é', 'è', 'ê', 'ë', 'î', 'ï', 'ô', 'ö', 'ù', 'û', 'ü', 'ç'};
	char caracteresAutresFins[16] = {'.', ',', ';', '\'', '(', ')', '[', ']', '{', '}', '/', '\\', '*', '°', ':', '!'};
	char caracteresAutres[16] = {'"', '#', '&', '_', '@', '€', '$', '£', 'µ', '^', '?', '=', '+', '-', '<', '>'};

	Rectangle2D rectangleTailleCaractere(glm::vec2(0, 0), glm::vec2(m_taillePolice / 1.8, m_taillePolice), 0);
	std::vector<Rectangle2D> rectanglesAffichage;

	for (int i = 0; i < m_chaine.length(); ++i)
	{
		char caractere = m_chaine.c_str()[i];
		glm::ivec2 positionCaractereTexture = glm::ivec2(0, 13);

		// Récupération de la position du caractère dans la texture de police
		if (caractere >= 'a' && caractere <= 'm')
			positionCaractereTexture = glm::ivec2(0, caractere - 'a');
		else if (caractere >= 'n' && caractere <= 'z')
			positionCaractereTexture = glm::ivec2(1, caractere - 'n');
		else if (caractere >= 'A' && caractere <= 'M')
			positionCaractereTexture = glm::ivec2(2, caractere - 'A');
		else if (caractere >= 'N' && caractere <= 'Z')
			positionCaractereTexture = glm::ivec2(3, caractere - 'N');
		else if (caractere >= '0' && caractere <= '9')
			positionCaractereTexture = glm::ivec2(4, caractere - '0');
		else
		{
			for (int j = 0; j < 15; ++j)
			{
				if (caractere == caracteresAccents[j])
					positionCaractereTexture = glm::ivec2(5, j);
			}

			for (int j = 0; j < 16; ++j)
			{
				if (caractere == caracteresAutresFins[j])
					positionCaractereTexture = glm::ivec2(6, j);
			}

			for (int j = 0; j < 16; ++j)
			{
				if (caractere == caracteresAutres[j])
					positionCaractereTexture = glm::ivec2(7, j);
			}
		}


		// Ajout du caractère dans la liste à afficher
		if (caractere != '\n' && caractere != '\r')
		{
			Rectangle2D rectangleCaractere(glm::vec2(numeroCaractereLigne * rectangleTailleCaractere.taille().x, numeroLigne * rectangleTailleCaractere.taille().y), glm::vec2(m_taillePolice / 1.8, m_taillePolice));
			rectangleCaractere.modifierTexture(m_identifiantTexturePolice, glm::vec2(positionCaractereTexture.x * 120 + 60, positionCaractereTexture.y * 120 + 60) / (m_petiteTexture ? 4.0f : 1.0f), glm::vec2(120 / 1.8, 120) / (m_petiteTexture ? 4.0f : 1.0f));
			++numeroCaractereLigne;
			rectanglesAffichage.push_back(rectangleCaractere);
		}
		else
		{
			++numeroLigne;
			numeroCaractereLigne = 0;
		}
	}


	// Rotation de chaque caractère en fonction de l'angle
	for (int i = 0; i < rectanglesAffichage.size(); ++i)
	{
		rectanglesAffichage[i].translater(glm::vec2(m_position.x - (nombreColonnes() - 1) * rectangleTailleCaractere.taille().x / 2, m_position.y - (nombreLignes() + 1) * rectangleTailleCaractere.taille().y / 2));
		rectanglesAffichage[i].modifierCouleur(m_couleur);
		rectanglesAffichage[i].modifierAngle(m_angle);

		Rectangle2D rectangle(m_position, (m_position - rectanglesAffichage[i].position()) * 2.0f, m_angle);

		rectanglesAffichage[i].modifierPosition(rectangle.coordonneesSommet(0));
	}


	return rectanglesAffichage;
}

void ng::Texte2D::mettreAJourAffichage()
{
	m_rectanglesAffichage = rectanglesAffichage();
}