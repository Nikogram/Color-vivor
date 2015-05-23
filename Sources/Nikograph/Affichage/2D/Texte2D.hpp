#ifndef _TEXTE2D
#define _TEXTE2D

#include "../../BibliothequesExternes.hpp"
#include "Rectangle2D.hpp"

namespace ng
{
	class Texte2D
	{
		public :
			Texte2D(int identifiantTexturePolice = 0, const std::string& chaine = "", const glm::vec2& position = glm::vec2(0, 0), float taillePolice = 0, bool petiteTexture = false);
			float taillePolice() const;
			std::string chaine() const;
			const glm::vec2& position() const;
			const glm::vec4& couleur() const;
			float angle() const;
			int identifiantTexturePolice() const;
			glm::vec2 taille() const;
			std::vector<float> coordonneesSommets() const;
			std::vector<float> coordonneesTexture() const;
			int nombreLignes() const;
			int nombreColonnes() const;
			int nombreColonnes(int numeroLigne) const;
			void modifierTaillePolice(float taille);
			void modifierChaine(const std::string& chaine);
			void modifierPosition(const glm::vec2& position);
			void modifierCouleur(const glm::vec4& couleur);
			void modifierAngle(float angle);
			void modifierIdentifiantTexturePolice(int identifiantTexturePolice);
			void translater(const glm::vec2& deplacement);
			void modifierEchelle(float echelle);
			void tourner(float angle);
			void mettreAJourAffichage();

		protected :
			std::vector<Rectangle2D> rectanglesAffichage() const;

			float m_taillePolice;
			std::string m_chaine;
			glm::vec2 m_position;
			glm::vec4 m_couleur;
			float m_angle;
			int m_identifiantTexturePolice;
			std::vector<Rectangle2D> m_rectanglesAffichage;
			bool m_petiteTexture;
	};
}

#endif
