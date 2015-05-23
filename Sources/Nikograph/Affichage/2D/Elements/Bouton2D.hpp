#ifndef _BOUTON2D
#define _BOUTON2D

#include "../Rectangle2D.hpp"
#include "../Texte2D.hpp"
#include "../../../Entrees/Controles.hpp"

namespace ng
{
	class Bouton2D
	{
		public :
			Bouton2D(const ng::Controles* controles, const std::string& texte, float tailleTexte, int identifiantTexturePolice = 0, const glm::vec2& position = glm::vec2(0, 0), bool petiteTexture = false);
			const glm::vec4& couleurNormal() const;
			const glm::vec4& couleurPointe() const;
			const glm::vec4& couleurClique() const;
			const Texte2D& texte() const;
			const Rectangle2D& fond() const;
			bool estPointe() const;
			bool estClique() const;
			bool estRelache() const;
			void modifierTexte(std::string texte);
			void modifierTaillePoliceTexte(float taille);
			void modifierPosition(const glm::vec2& position);
			void modifierTaille(const glm::vec2& taille);
			void modifierAngle(float angle);
			void modifierCouleurTexte(const glm::vec4& couleur);
			void modifierCouleurNormal(const glm::vec4& couleur);
			void modifierCouleurPointe(const glm::vec4& couleur);
			void modifierCouleurClique(const glm::vec4& couleur);
			void modifierIdentifiantTexturePolice(int identifiant);
			void modifierTextureFond(int identifiantTexture, const glm::vec2& positionTexture, const glm::vec2& tailleTexture);
			void retirerTextureFond();
			void translater(const glm::vec2& deplacement);
			void modifierEchelle(const glm::vec2& echelle);
			void tourner(float angle);
			void mettreAJourAffichage();


		protected :
			const ng::Controles* m_controles;
			glm::vec4 m_couleurNormal;
			glm::vec4 m_couleurPointe;
			glm::vec4 m_couleurClique;
			Texte2D m_texte;
			Rectangle2D m_fond;
			bool m_forcerMiseAJourChaine;
	};
}

#endif
