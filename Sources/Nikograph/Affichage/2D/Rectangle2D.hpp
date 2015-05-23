#ifndef _RECTANGLE2D
#define _RECTANGLE2D

#include "../../BibliothequesExternes.hpp"
#include "../../Enumerations.hpp"

namespace ng
{
	class Rectangle2D
	{
		public :
			Rectangle2D(glm::vec2 position, glm::vec2 taille, float angle = 0);
			glm::vec2 position() const;
			glm::vec2 vitesse() const;
			glm::vec2 acceleration() const;
			glm::vec2 taille() const;
			float angle() const;
			glm::vec4 couleur() const;
			int identifiantTexture() const;
			glm::vec2 positionTexture() const;
			glm::vec2 tailleTexture() const;
			glm::vec2 coordonneesSommet(int identifiant) const;
			std::vector<float> coordonneesSommets() const;
			std::vector<float> coordonneesTexture() const;
			void modifierPosition(const glm::vec2& position);
			void modifierVitesse(const glm::vec2& vitesse);
			void modifierAcceleration(const glm::vec2& acceleration);
			void modifierTaille(const glm::vec2& taille);
			void modifierAngle(float angle);
			void modifierCouleur(const glm::vec4& couleur);
			void modifierTexture(int identifiantTexture, const glm::vec2& positionTexture, const glm::vec2& tailleTexture);
			void retirerTexture();
			void translater(const glm::vec2& deplacement);
			void modifierEchelle(const glm::vec2& echelle);
			void tourner(float angle);
			void mettreAJourPosition(float tempsFrame, bool anglePrisEnCompte = true);

		protected :
			glm::vec2 m_position;
			glm::vec2 m_vitesse;
			glm::vec2 m_acceleration;
			glm::vec2 m_taille;
			float m_angle;
			glm::vec4 m_couleur;
			int m_identifiantTexture;
			glm::vec2 m_positionTexture;
			glm::vec2 m_tailleTexture;
	};
}

#endif
