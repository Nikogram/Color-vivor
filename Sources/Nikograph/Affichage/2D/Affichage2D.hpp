#ifndef _AFFICHAGE2D
#define _AFFICHAGE2D

#include "../Shader.hpp"
#include "../Texture.hpp"
#include "../VertexBufferObject.hpp"
#include "Rectangle2D.hpp"
#include "Texte2D.hpp"
#include "Elements/Bouton2D.hpp"
#include "Elements/ZoneTexte2D.hpp"
#include "../../Enumerations.hpp"

namespace ng
{
	class Affichage2D
	{
		public :
			Affichage2D(const glm::vec2* taillePixelsFenetre, ng::GrandeurMetrique grandeurMetrique = Pixels, int nombreSommetsMaximumVBO = 0);
			int nombreSommetsMaximumVBO() const;
			int nombreSommets() const;
			glm::vec2 tailleTexture(int identifiantTexture) const;
			glm::vec2 coordonneesSommet(int identifiantSommet) const;
			glm::vec4 couleur(int identifiantSommet) const;
			glm::vec3 coordonneesTexture(int identifiantSommet) const;
			glm::vec2 ratioAffichage() const;
			void modifierGrandeurMetrique(ng::GrandeurMetrique grandeurMetrique);
			void ajouterSommets(const std::vector<float>& coordonneesSommets, const std::vector<float>& couleurs, const std::vector<float>& coordonneesTexture);
			void ajouterSommets(const Rectangle2D& rectangle);
			void ajouterSommets(const Texte2D& texte);
			void ajouterSommets(const Bouton2D& bouton);
			void ajouterSommets(const ZoneTexte2D& zoneTexte);
			void modifierSommet(int identifiantSommet, const glm::vec2& coordonneesSommet, const glm::vec4& couleur, const glm::vec3& coordonneesTexture);
			void modifierSommets(int identifiantPremierSommet, const std::vector<float>& coordonneesSommets, const std::vector<float>& couleurs, const std::vector<float>& coordonneesTexture);
			void ajouterTexture(int identifiantTexture, std::string cheminTexture, bool textureAdoucie = false);
			void supprimerTexture(int identifiantTexture);
			void ajouterTexturePolice(int identifiantTexture, std::string nomPolice, bool gras = false, bool italique = false, bool textureAdoucie = false);
			void reinitialiser();
			void afficher(int identifiantPremierSommet = 0, int nombreSommets = -1);

		protected :
			const glm::vec2* m_taillePixelsFenetre;
			ng::GrandeurMetrique m_grandeurMetrique;
			Shader m_shader;
			std::vector<Texture> m_textures;
			std::vector<float> m_coordonneesSommets;
			std::vector<float> m_couleurs;
			std::vector<float> m_coordonneesTexture;
			ng::VertexBufferObject m_VBO;
	};
}

#endif
