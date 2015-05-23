#ifndef _FENETRE
#define _FENETRE

#include "../BibliothequesExternes.hpp"
#include "../Entrees/Controles.hpp"

namespace ng
{
	class Fenetre
	{
		public:
			Fenetre(ng::GrandeurMetrique grandeurMetriqueControles);
			~Fenetre();
			const glm::vec2& taillePixels() const;
			float ratio(bool inverse = false) const;
			float tempsDerniereFrame() const;
			const ng::Controles& controles();
			bool fermer() const;
			bool active() const;
			bool initialiserAffichage(const glm::vec2& taillePixelsFenetre, const std::string& titreFenetre = "");
			void recupererEvenements();
			void demarrerAffichage();
			void terminerAffichage();

		private :
			sf::Window *m_fenetre;
			sf::ContextSettings m_parametresContexte;
			glm::vec2 m_taillePixels;
			float m_tempsDerniereFrame;
			Controles m_controles;
			bool m_fermer;
			bool m_active;
			sf::Clock m_horloge;
	};
}

#endif
