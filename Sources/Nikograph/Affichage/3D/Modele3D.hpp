#ifndef _MODELE3D
#define _MODELE3D

#include "../../BibliothequesExternes.hpp"

namespace ng
{
	class Modele3D
	{
		public :
			Modele3D(const glm::vec3& position = glm::vec3(0, 0, 0), const glm::vec3& taille = glm::vec3(1, 1, 1));
			const glm::vec3& position() const;
			const glm::vec3& taille() const;
			const glm::vec3& angles() const;
			std::vector<float> coordonneesSommets() const;
			const std::vector<float>& couleurs() const;
			std::vector<float> coordonneesTexture() const;
			std::vector<float> normales() const;
			void modifierIdentifiantTexture(int identifiantTexture);
			void modifierPosition(const glm::vec3& position);
			void modifierTaille(const glm::vec3& taille);
			void modifierAngles(const glm::vec3& angles);
			void translater(const glm::vec3& deplacement);
			void modifierEchelle(const glm::vec3& echelle);
			void tourner(const glm::vec3& angles);
			void chargerCube();
			bool ajouterSommets(std::string nomFichier, const glm::vec2& signeCoordonneesTexture = glm::vec2(1, 1));

		protected :
			void mettreAJourNormales();

			glm::vec3 m_position;
			glm::vec3 m_taille;
			glm::vec3 m_angles;
			std::vector<float> m_coordonneesSommets;
			std::vector<float> m_couleurs;
			std::vector<float> m_coordonneesTexture;
			std::vector<float> m_normales;
			int m_identifiantTexture;
	};
}

#endif
