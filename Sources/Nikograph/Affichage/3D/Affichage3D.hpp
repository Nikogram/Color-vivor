#ifndef _AFFICHAGE3D
#define _AFFICHAGE3D

#include "Elements/Cube3D.hpp"
#include "../Shader.hpp"
#include "../Texture.hpp"
#include "../VertexBufferObject.hpp"
#include "../../BibliothequesExternes.hpp"

namespace ng
{
	class Affichage3D
	{
		public :
			Affichage3D(const glm::mat4& matriceProjection = glm::mat4(1), const glm::mat4& matriceVue = glm::mat4(1), int nombreSommetsMaximumVBO = 0);
			int nombreSommetsMaximumVBO() const;
			int nombreSommets() const;
			int nombreSourcesLumineuses() const;
			glm::vec2 tailleTexture(int identifiantTexture) const;
			glm::vec3 coordonneesSommet(int identifiantSommet) const;
			glm::vec4 couleur(int identifiantSommet) const;
			glm::vec3 coordonneesTexture(int identifiantSommet) const;
			const glm::mat4& matriceProjection() const;
			const glm::mat4& matriceVue() const;
			void modifierMatriceProjection(const glm::mat4& matrice);
			void modifierMatriceVue(const glm::mat4& matrice);
			void modifierDirectionRayonsLumineux(const glm::vec3& direction);
			void modifierIntensiteLumiereMinimale(float intensite);
			void modifierIntensiteLumiereMaximale(float intensite);
			void modifierFacesSombresEclairees(bool facesSombresEclairees);
			void ajouterSommets(const std::vector<float>& coordonneesSommets, const std::vector<float>& couleurs, const std::vector<float>& coordonneesTexture, const std::vector<float>& normales);
			void ajouterSommets(const Cube3D& cube, const std::vector<bool>& facesAffichees = std::vector<bool>({ true, true, true, true, true, true }));
			void ajouterSourceLumineuse(const glm::vec3& coordonnees, float intensite);
			void ajouterTexture(int identifiantTexture, std::string cheminTexture, bool textureAdoucie = false);
			void supprimerTexture(int identifiantTexture);
			void reinitialiser();
			void afficher(int identifiantPremierSommet = 0, int nombreSommets = -1);

		protected :
			Shader m_shader;
			std::vector<Texture> m_textures;
			std::vector<float> m_coordonneesSommets;
			std::vector<float> m_couleurs;
			std::vector<float> m_coordonneesTexture;
			std::vector<float> m_normales;
			VertexBufferObject m_VBO;
			glm::mat4 m_matriceProjection;
			glm::mat4 m_matriceVue;
			glm::vec3 m_directionRayonsLumineux;
			float m_intensiteLumiereMinimale;
			float m_intensiteLumiereMaximale;
			bool m_facesSombresEclairees;
			std::vector<float> sourcesLumineuses;
	};
}

#endif