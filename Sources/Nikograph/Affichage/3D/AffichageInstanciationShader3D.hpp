#ifndef _AFFICHAGEINSTANCIATIONSHADER3D
#define _AFFICHAGEINSTANCIATIONSHADER3D

#include "Elements/Cube3D.hpp"
#include "../Shader.hpp"
#include "../Texture.hpp"
#include "../FrameBuffer.hpp"
#include "../../BibliothequesExternes.hpp"

namespace ng
{
	class AffichageInstanciationShader3D
	{
		public :
			AffichageInstanciationShader3D(const glm::mat4& matriceProjection = glm::mat4(1), const glm::mat4& matriceVue = glm::mat4(1));
			int nombreSommets() const;
			glm::vec2 tailleTexture(int identifiantTexture) const;
			const glm::mat4& matriceProjection() const;
			const glm::mat4& matriceVue() const;
			void modifierMatriceProjection(const glm::mat4& matrice);
			void modifierMatriceVue(const glm::mat4& matrice);
			void ajouterSommets(const glm::vec3& position, const glm::vec3& taille, int identifiantBloc, float facesAffichees);
			void ajouterSommets(const std::vector<float>& positions, const std::vector<float>& tailleFaces, const std::vector<float>& identifiantsBlocs, const std::vector<float>& facesAffichees);
			void ajouterTexture(int identifiantTexture, std::string cheminTexture, bool textureAdoucie = false);
			void supprimerSommets(int identifiantElement);
			bool supprimerSommetsCube(const glm::vec3& positionCube);
			void supprimerSommetsCube(const glm::vec3& positionCubeMini, const glm::vec3& positionCubeMaxi);
			void supprimerTexture(int identifiantTexture);
			void reinitialiser();
			void afficher(const glm::vec3& positionCamera, int identifiantPremierSommet = 0, int nombreSommets = -1);
			void genererOmbre(const glm::vec3& positionCamera, const glm::vec2& tailleFenetre, int identifiantPremierSommet = 0, int nombreSommets = -1);

		protected :
			Shader m_shader;
			std::vector<Texture> m_textures;
			std::vector<float> m_informationsSommets;
			std::vector<glm::vec3> m_positionElements;

			glm::mat4 m_matriceProjection;
			glm::mat4 m_matriceVue;

			GLuint m_identifiantVBO;

			Shader m_shaderOmbres;
			ng::FrameBuffer m_frameBuffer;
	};
}

#endif
