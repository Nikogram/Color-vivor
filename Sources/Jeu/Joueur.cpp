#include "Joueur.hpp"

Joueur::Joueur(ng::Fenetre& fenetre, const glm::vec2& position, const std::string& pseudo, bool estEnnemi) :
	m_fenetre(fenetre),
	m_etiquettePseudo(0, pseudo, position + glm::vec2(0, -60), 20),
	m_avatar(position, glm::vec2(50, 50)),
	m_arme(position, glm::vec2(50, 100)),
	m_etincellesArme(position, glm::vec2(50, 100)),
	m_pseudo(pseudo),
	m_vie(100),
	m_identifiantArmeSelectionne(0),
	m_coordonneesViseur(0, 0),
	m_tempsAffichageEtincelles(0),
	m_tempsAvantProchainTir(0),
	m_estEnnemi(estEnnemi)
{
	m_avatar.modifierTexture(1, glm::vec2(25, 25), glm::vec2(50, 50));

	if (!m_estEnnemi)
		m_avatar.modifierCouleur(glm::vec4(0.2, 0.6, 1, 1));
	else
		m_avatar.modifierCouleur(glm::vec4(1, 0, 0, 1));
	m_arme.modifierTexture(2, glm::vec2(25, 50), glm::vec2(50, 100));
	m_etincellesArme.modifierTexture(3, glm::vec2(25, 50), glm::vec2(50, 100));
}

Joueur::~Joueur()
{
	for (int i = 0; i < m_balles.size(); ++i)
		delete m_balles[i];
}

Joueur Joueur::operator=(Joueur& joueur)
{
	Joueur nouveauJoueur(joueur.m_fenetre, joueur.m_avatar.position(), joueur.m_pseudo, m_estEnnemi);
	nouveauJoueur.mettreAJour(joueur.m_pseudo, joueur.m_avatar.position(), joueur.angle(), joueur.vie(), joueur.identifiantArmeSelectionne(), joueur.m_coordonneesViseur);

	return nouveauJoueur;
}

const std::string& Joueur::pseudo() const
{
	return m_pseudo;
}

const glm::vec2& Joueur::position() const
{
	return m_avatar.position();
}

float Joueur::angle() const
{
	return m_avatar.angle();
}

float Joueur::vie() const
{
	return m_vie;
}

int Joueur::identifiantArmeSelectionne() const
{
	return m_identifiantArmeSelectionne;
}

const glm::vec2& Joueur::coordonneesViseur() const
{
	return m_coordonneesViseur;
}

bool Joueur::tire() const
{
	return m_tempsAvantProchainTir != 0;
}

bool Joueur::estEnnemi() const
{
	return m_estEnnemi;
}

void Joueur::modifierPseudo(const std::string& pseudo)
{
	m_pseudo = pseudo;
	m_etiquettePseudo.modifierChaine(pseudo);
}

void Joueur::modifierCoordonneesViseur(const glm::vec2& coordonneesViseur)
{
	m_coordonneesViseur = coordonneesViseur;
}

void Joueur::translater(const glm::vec2& distance)
{
	m_avatar.translater(distance);
}

void Joueur::ajouterAAffichage(ng::Affichage2D& affichage)
{
	for (int i = 0; i < m_balles.size(); ++i)
		affichage.ajouterSommets(*m_balles[i]);

	affichage.ajouterSommets(m_avatar);
	affichage.ajouterSommets(m_arme);

	if (m_tempsAffichageEtincelles != 0)
		affichage.ajouterSommets(m_etincellesArme);
}

void Joueur::ajouterAAffichageSuperieur(ng::Affichage2D& affichage)
{
	if (!m_estEnnemi)
		affichage.ajouterSommets(m_etiquettePseudo);
}

void Joueur::tirer()
{
	if (m_tempsAvantProchainTir == 0)
	{
		m_tempsAvantProchainTir = 0.5;
		m_tempsAffichageEtincelles = 0.1;
		m_balles.push_back(new ng::Rectangle2D(m_avatar.position(), glm::vec2(50, 50), m_avatar.angle()));
		m_balles[m_balles.size() - 1]->modifierTexture(4, glm::vec2(25, 25), glm::vec2(50, 50));
		m_balles[m_balles.size() - 1]->translater(glm::vec2(10, -25));
		m_balles[m_balles.size() - 1]->modifierVitesse(glm::vec2(0, -1000));
	}
}

void Joueur::mettreAJourAffichage(float tempsFrame, bool prendreEnCompteControles)
{
	if (m_fenetre.active() && prendreEnCompteControles)
	{
		float angleDeplacement = 0;
		m_coordonneesViseur = m_fenetre.controles().positionSouris() * m_fenetre.taillePixels();

		// Translation du personnage
		if (m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::Z) && m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::Q))
			angleDeplacement = 45;
		else if (m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::S) && m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::Q))
			angleDeplacement = 90 + 45;
		else if (m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::S) && m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::D))
			angleDeplacement = 180 + 45;
		else if (m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::Z) && m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::D))
			angleDeplacement = 270 + 45;
		else if (m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::Z))
			angleDeplacement = 0;
		else if (m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::Q))
			angleDeplacement = 90;
		else if (m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::S))
			angleDeplacement = 180;
		else if (m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::D))
			angleDeplacement = 270;

		if (m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::Z) || m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::S) ||
			m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::Q) || m_fenetre.controles().toucheClavierAppuyee(sf::Keyboard::D))
		{
			m_avatar.modifierAngle(angleDeplacement);
			m_avatar.translater(glm::vec2(0, -100) * tempsFrame);
			m_arme.modifierAngle(angleDeplacement);
			m_arme.translater(glm::vec2(0, -100) * tempsFrame);
			m_etincellesArme.modifierAngle(angleDeplacement);
			m_etincellesArme.translater(glm::vec2(0, -100) * tempsFrame);
		}
	}

	// Rotation du personnage vers l'endroit visé
	glm::vec2 directionVisee = m_avatar.position() - m_coordonneesViseur;
	float angleVisee = glm::atan(directionVisee.x, directionVisee.y);
	m_avatar.modifierAngle(glm::degrees(angleVisee));

	if (m_estEnnemi)
		std::cout << glm::degrees(angleVisee) << std::endl;

	if (m_fenetre.active() && prendreEnCompteControles && m_fenetre.controles().boutonSourisGaucheAppuye())
		tirer();


	// Mise à jour de la position de l'affichage du personnage
	m_avatar.mettreAJourPosition(tempsFrame, true);
	m_arme.modifierAngle(m_avatar.angle());
	m_arme.modifierPosition(m_avatar.position());
	m_etincellesArme.modifierAngle(m_avatar.angle());
	m_etincellesArme.modifierPosition(m_avatar.position());


	// Mise à jour de l'étiquette pour le pseudo
	m_etiquettePseudo.modifierPosition(m_avatar.position() + glm::vec2(0, -60));
	m_etiquettePseudo.mettreAJourAffichage();


	// Mise à jour des balles
	for (int i = 0; i < m_balles.size(); ++i)
	{
		m_balles[i]->mettreAJourPosition(tempsFrame, true);

		if (m_balles[i]->position().x < -50 || m_balles[i]->position().y < -50 || m_balles[i]->position().x > m_fenetre.taillePixels().x + 50 || m_balles[i]->position().y > m_fenetre.taillePixels().y + 50)
		{
			delete m_balles[i];
			m_balles.erase(m_balles.begin() + i);
		}
	}

	if (m_tempsAffichageEtincelles > 0)
		m_tempsAffichageEtincelles -= tempsFrame;
	if (m_tempsAffichageEtincelles < 0)
		m_tempsAffichageEtincelles = 0;
	if (m_tempsAvantProchainTir > 0)
		m_tempsAvantProchainTir -= tempsFrame;
	if (m_tempsAvantProchainTir < 0)
		m_tempsAvantProchainTir = 0;
}

void Joueur::mettreAJour(const std::string& pseudo, const glm::vec2& position, float angle, float vie, int identifiantArmeSelectionne, const glm::vec2& coordonneesViseur)
{
	m_pseudo = pseudo;
	m_avatar.modifierPosition(position);
	m_avatar.modifierAngle(angle);
	m_arme.modifierPosition(position);
	m_arme.modifierAngle(angle);
	m_etincellesArme.modifierPosition(position);
	m_etincellesArme.modifierAngle(angle);
	m_vie = vie;
	m_identifiantArmeSelectionne = identifiantArmeSelectionne;
	m_coordonneesViseur = coordonneesViseur;

	m_etiquettePseudo.modifierChaine(pseudo);
}