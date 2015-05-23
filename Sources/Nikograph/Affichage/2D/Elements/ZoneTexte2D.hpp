#ifndef _ZONETEXTE2D
#define _ZONETEXTE2D

#include "../Rectangle2D.hpp"
#include "../Texte2D.hpp"
#include "../../../Entrees/Controles.hpp"

namespace ng
{
	class ZoneTexte2D
	{
		public :
			ZoneTexte2D(const ng::Controles* controles, float tailleTexte, const glm::vec2& nombreCaracteresMaximum = glm::vec2(20, 1), int identifiantTexturePolice = 0, const glm::vec2& position = glm::vec2(0, 0), bool petiteTexture = false);
			const Texte2D& texte() const;
			const Rectangle2D& fond() const;
			const Rectangle2D& curseur() const;
			const std::string& chaine() const;
			bool estClique() const;
			bool selectionne() const;
			void modifierTexte(std::string texte);
			void modifierTaillePoliceTexte(float taille);
			void modifierPosition(const glm::vec2& position);
			void modifierCouleurTexte(const glm::vec4& couleur);
			void modifierCouleurFond(const glm::vec4& couleur);
			void modifierIdentifiantTexturePolice(int identifiant);
			void modifierTextureFond(int identifiantTexture, const glm::vec2& positionTexture, const glm::vec2& tailleTexture);
			void modifierSelectionne(bool selectionne);
			void retirerTextureFond();
			void translater(const glm::vec2& deplacement);
			void modifierEchelle(const glm::vec2& echelle);
			void mettreAJourAffichage();


		protected :
			const ng::Controles* m_controles;
			Texte2D m_texte;
			Rectangle2D m_fond;
			Rectangle2D m_curseur;
			glm::vec2 m_nombreCaracteresMaximum;
			glm::vec2 m_positionCurseur;
			std::string m_ancienneChaine;
			std::string m_chaine;
			bool m_selectionne;
			bool m_forcerMiseAJourChaine;
	};
}

#endif