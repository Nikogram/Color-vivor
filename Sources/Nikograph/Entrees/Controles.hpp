#ifndef _CONTROLES
#define _CONTROLES

#include "../Affichage/2D/Rectangle2D.hpp"
#include "../Physique/Physique.hpp"
#include "../BibliothequesExternes.hpp"

namespace ng
{
	struct Doigt
	{
		int identifiant;
		bool ecranTouche;
		bool pose;
		bool retire;
		glm::vec2 position;
		glm::vec2 deplacement;
	};

	struct Souris
	{
		bool boutonGaucheAppuye;
		bool boutonDroiteAppuye;
		bool boutonMilieuAppuye;
		bool boutonGaucheRelache;
		bool boutonDroiteRelache;
		bool boutonMilieuRelache;
		glm::vec2 position;
		glm::vec2 deplacement;
	};

	class Controles
	{
		public :
			Controles(const sf::Window* fenetre, glm::vec2& taillePixelsFenetre, ng::GrandeurMetrique grandeurMetrique = Pixels, int nombreDoigts = 1);
			int identifiantDoigtDansRectangle(const Rectangle2D& rectangle) const;
			bool doigtPose(int identifiantDoigt) const;
			bool doigtRetire(int identifiantDoigt) const;
			bool doigtBouge(int identifiantDoigt) const;
			bool ecranToucheParDoigt(int identifiantDoigt) const;
			glm::vec2 positionDoigt(int identifiantDoigt) const;
			glm::vec2 deplacementDoigt(int identifiantDoigt) const;
			bool sourisDansRectangle(const Rectangle2D& rectangle) const;
			const glm::vec2& positionSouris() const;
			const glm::vec2& deplacementSouris() const;
			bool boutonSourisGaucheAppuye() const;
			bool boutonSourisDroiteAppuye() const;
			bool boutonSourisMilieuAppuye() const;
			bool boutonSourisGaucheRelache() const;
			bool boutonSourisDroiteRelache() const;
			bool boutonSourisMilieuRelache() const;
			bool toucheClavierAppuyee(sf::Keyboard::Key touche) const;
			char caractereEntre() const;
			bool tactileActive() const;
			void modifierFenetre(const sf::Window* fenetre);
			void modifierTactileActive(bool tactileActive);
			void recupererEntrees();
			void recupererCaractereEntre(const sf::Event& evenements);
			void reinitialiser();

		protected :
			glm::vec2 coordonneesSommetRectangleAvecRatio(const glm::vec2& coordonnees, const glm::vec2& coordonneesCentreRectangle) const;

			const sf::Window* m_fenetre;
			glm::vec2& m_taillePixelsFenetre;
			ng::GrandeurMetrique m_grandeurMetrique;
			std::vector<Doigt> m_doigts;
			Souris m_souris;
			char m_caractereEntre;
			bool m_tactileActive;
	};
}

#endif
