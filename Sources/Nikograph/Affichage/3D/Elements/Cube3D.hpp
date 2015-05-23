#ifndef _CUBE3D
#define _CUBE3D

#include "../../../BibliothequesExternes.hpp"

namespace ng
{
	class Cube3D
	{
		public :
			Cube3D(const glm::vec3& position = glm::vec3(0, 0, 0), const glm::vec3& taille = glm::vec3(1, 1, 1));
			const glm::vec3& position() const;
			const glm::vec3& vitesse() const;
			const glm::vec3& acceleration() const;
			const glm::vec3& taille() const;
			const glm::vec3& angles() const;
			std::vector<float> coordonneesSommets(const std::vector<bool>& facesAffichees = std::vector<bool>({ true, true, true, true, true, true }), bool positionPrisEnCompte = true) const;
			const glm::vec4& couleur() const;
			std::vector<float> couleurs(const std::vector<bool>& facesAffichees = std::vector<bool>({ true, true, true, true, true, true }), bool ajoutLuminosite = false) const;
			std::vector<float> coordonneesTexture(const std::vector<bool>& facesAffichees = std::vector<bool>({ true, true, true, true, true, true })) const;
			std::vector<float> normales(const std::vector<bool>& facesAffichees = std::vector<bool>({ true, true, true, true, true, true })) const;
			void modifierPosition(const glm::vec3& position);
			void modifierVitesse(const glm::vec3& vitesse);
			void modifierAcceleration(const glm::vec3& acceleration);
			void modifierTaille(const glm::vec3& taille);
			void modifierAngles(const glm::vec3& angles);
			void modifierIdentifiantTexturesFaces(const std::vector<float>& identifiants);
			void modifierCouleur(const glm::vec4& couleur);
			void translater(const glm::vec3& deplacement);
			void modifierEchelle(const glm::vec3& echelle);
			void tourner(const glm::vec3& angles);
			void mettreAJourPosition(float tempsFrame, bool anglePrisEnCompte = true);
			void annulerMiseAJourPosition(float tempsFrame, bool anglePrisEnCompte = true);

		private :
			glm::vec3 m_position;
			glm::vec3 m_vitesse;
			glm::vec3 m_acceleration;
			glm::vec3 m_taille;
			glm::vec3 m_angles;
			glm::vec4 m_couleur;
			std::vector<float> m_identifiantTexturesFaces;
	};
}

#endif
