#ifndef _AFFICHAGEINSTANCIATION3D
#define _AFFICHAGEINSTANCIATION3D

#include "Elements/Cube3D.hpp"
#include "../Shader.hpp"
#include "../Texture.hpp"
#include "../../BibliothequesExternes.hpp"

namespace ng
{
	class AffichageInstanciation3D
	{
		public :
			AffichageInstanciation3D(const glm::mat4& matriceProjection = glm::mat4(1), const glm::mat4& matriceVue = glm::mat4(1));
			int nombreSommets() const;
			glm::vec2 tailleTexture(int identifiantTexture) const;
			const glm::mat4& matriceProjection() const;
			const glm::mat4& matriceVue() const;
			int identifiantCoordonneesSommetModele(const glm::vec4& coordonnees) const;
			int identifiantCoordonneesTextureModele(const glm::vec3& coordonnees) const;
			void modifierMatriceProjection(const glm::mat4& matrice);
			void modifierMatriceVue(const glm::mat4& matrice);
			void ajouterSommets(const std::vector<float>& coordonneesSommets, const std::vector<float>& coordonneesTexture, const glm::vec3& position, const glm::vec3& taille = glm::vec3(1, 1, 1));
			void ajouterSommets(const std::vector<float>& coordonneesSommets, const std::vector<float>& coordonneesTexture, const std::vector<float>& positions, const std::vector<float>& tailleFaces);
			void ajouterSommetsCube(const Cube3D& cube, const std::vector<bool>& facesAffichees = std::vector<bool>({ true, true, true, true, true, true }));
			void ajouterTexture(int identifiantTexture, std::string cheminTexture, bool textureAdoucie = false);
			void supprimerSommets(int identifiantPremierSommet, int nombreSommets);
			bool supprimerSommetsCube(const glm::vec3& positionCube);
			void supprimerSommetsCube(const glm::vec3& positionCubeMini, const glm::vec3& positionCubeMaxi);
			void supprimerTexture(int identifiantTexture);
			void reinitialiser();
			void afficher(int identifiantPremierSommet = 0, int nombreSommets = -1);

		protected :
			Shader m_shader;
			std::vector<Texture> m_textures;

			std::vector<float> m_coordonneesSommets;
			std::vector<float> m_coordonneesTexture;
			std::vector<float> m_informationsSommets;

			std::vector<glm::vec3> m_positionSommets;
			std::vector<int> m_identifiantPremierSommetPosition;
			std::vector<int> m_nombreSommetsPosition;

			glm::mat4 m_matriceProjection;
			glm::mat4 m_matriceVue;
	};
}

#endif
