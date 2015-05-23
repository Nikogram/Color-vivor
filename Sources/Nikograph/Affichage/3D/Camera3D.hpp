#ifndef _CAMERA
#define _CAMERA

#include "../../BibliothequesExternes.hpp"

namespace ng
{
	class Camera3D
	{
		public :
			Camera3D(const glm::vec3& position = glm::vec3(0, 0, 0));
			const glm::vec3& position() const;
			const glm::vec3& vitesse() const;
			const glm::vec3& acceleration() const;
			const glm::vec3& angles() const;
			glm::vec3 directionVue() const;
			glm::mat4 matriceVue() const;
			void modifierPosition(const glm::vec3& position);
			void modifierVitesse(const glm::vec3& vitesse);
			void modifierAcceleration(const glm::vec3& acceleration);
			void modifierAngles(const glm::vec3& angles);
			void translater(const glm::vec3& deplacement, const glm::bvec3& deplacementAFaire = glm::bvec3(true, true, true), bool prendreEnCompteRotationHauteurCamera = true);
			void tourner(const glm::vec3& angles);
			void mettreAJourPosition(float tempsFrame, bool anglePrisEnCompte = true);
			void annulerMiseAJourPosition(float tempsFrame, bool anglePrisEnCompte = true);
			void fixerPoint(const glm::vec3& positionPoint);
			void arreterFixerPoint();


		private:
			glm::vec3 m_position;
			glm::vec3 m_vitesse;
			glm::vec3 m_acceleration;
			glm::vec3 m_angles;
			glm::vec4 m_pointFixe;
	};
}

#endif
