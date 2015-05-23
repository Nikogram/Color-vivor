#ifndef _JOUEUR
#define _JOUEUR

#include "../Nikograph/Nikograph.hpp"

class Joueur
{
	public :
		Joueur(ng::Fenetre& fenetre, const glm::vec2& position, const std::string& pseudo, bool estEnnemi);
		~Joueur();
		Joueur operator=(Joueur& joueur);
		const std::string& pseudo() const;
		const glm::vec2& position() const;
		float angle() const;
		float vie() const;
		int identifiantArmeSelectionne() const;
		const glm::vec2& coordonneesViseur() const;
		bool tire() const;
		bool estEnnemi() const;
		void modifierPseudo(const std::string& pseudo);
		void modifierCoordonneesViseur(const glm::vec2& coordonneesViseur);
		void translater(const glm::vec2& distance);
		void ajouterAAffichage(ng::Affichage2D& affichage);
		void ajouterAAffichageSuperieur(ng::Affichage2D& affichage);
		void tirer();
		void mettreAJourAffichage(float tempsFrame, bool prendreEnCompteControles);
		void mettreAJour(const std::string& pseudo, const glm::vec2& position, float angle, float vie, int identifiantArmeSelectionne, const glm::vec2& coordonneesViseur);

	protected :
		ng::Fenetre& m_fenetre;
		ng::Texte2D m_etiquettePseudo;
		ng::Rectangle2D m_avatar;
		ng::Rectangle2D m_arme;
		ng::Rectangle2D m_etincellesArme;
		std::vector<ng::Rectangle2D*> m_balles;
		std::string m_pseudo;
		float m_vie;
		int m_identifiantArmeSelectionne;
		glm::vec2 m_coordonneesViseur;
		float m_tempsAffichageEtincelles;
		float m_tempsAvantProchainTir;
		bool m_estEnnemi;
};

#endif
