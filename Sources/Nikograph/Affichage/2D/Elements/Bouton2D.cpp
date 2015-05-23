#include "Bouton2D.hpp"

ng::Bouton2D::Bouton2D(const ng::Controles* controles, const std::string& texte, float tailleTexte, int identifiantTexturePolice, const glm::vec2& position, bool petiteTexture) :
	m_controles(controles),
	m_couleurNormal(glm::vec4(1, 1, 1, 1)),
	m_couleurPointe(glm::vec4(1, 1, 1, 1)),
	m_couleurClique(glm::vec4(1, 1, 1, 1)),
	m_texte(identifiantTexturePolice, " ", position, tailleTexte, petiteTexture),
	m_fond(position, m_texte.taille()),
	m_forcerMiseAJourChaine(true)
{
	m_fond.modifierTaille(glm::vec2(m_texte.taille().x * (texte.length() + 1), m_fond.taille().y * 2));
	m_fond.modifierCouleur(m_couleurNormal);
	m_texte.modifierChaine(texte);
	m_texte.modifierCouleur(glm::vec4(0, 0, 0, 1));
}

const glm::vec4& ng::Bouton2D::couleurNormal() const
{
	return m_couleurNormal;
}

const glm::vec4& ng::Bouton2D::couleurPointe() const
{
	return m_couleurPointe;
}

const glm::vec4& ng::Bouton2D::couleurClique() const
{
	return m_couleurClique;
}

const ng::Texte2D& ng::Bouton2D::texte() const
{
	return m_texte;
}

const ng::Rectangle2D& ng::Bouton2D::fond() const
{
	return m_fond;
}

bool ng::Bouton2D::estPointe() const
{
	if (m_controles->identifiantDoigtDansRectangle(m_fond) >= 0 || m_controles->sourisDansRectangle(m_fond))
		return true;
	return false;
}

bool ng::Bouton2D::estClique() const
{
	if (m_controles->identifiantDoigtDansRectangle(m_fond) >= 0 || (m_controles->sourisDansRectangle(m_fond) && m_controles->boutonSourisGaucheAppuye()))
		return true;
	return false;
}

bool ng::Bouton2D::estRelache() const
{
	if (m_controles->doigtRetire(m_controles->identifiantDoigtDansRectangle(m_fond)) || (m_controles->sourisDansRectangle(m_fond) && m_controles->boutonSourisGaucheRelache()))
		return true;
	return false;
}

void ng::Bouton2D::modifierTexte(std::string texte)
{
	m_texte.modifierChaine(texte);
	m_forcerMiseAJourChaine = true;
}

void ng::Bouton2D::modifierTaillePoliceTexte(float taille)
{
	m_texte.modifierTaillePolice(taille);
	m_forcerMiseAJourChaine = true;
}

void ng::Bouton2D::modifierPosition(const glm::vec2& position)
{
	m_texte.modifierPosition(position);
	m_fond.modifierPosition(position);
	m_forcerMiseAJourChaine = true;
}

void ng::Bouton2D::modifierTaille(const glm::vec2& taille)
{
	m_fond.modifierTaille(taille);
}

void ng::Bouton2D::modifierAngle(float angle)
{
	m_texte.modifierAngle(angle);
	m_fond.modifierAngle(angle);
	m_forcerMiseAJourChaine = true;
}

void ng::Bouton2D::modifierCouleurTexte(const glm::vec4& couleur)
{
	m_texte.modifierCouleur(couleur);
	m_forcerMiseAJourChaine = true;
}

void ng::Bouton2D::modifierCouleurNormal(const glm::vec4& couleur)
{
	m_couleurNormal = couleur;
}

void ng::Bouton2D::modifierCouleurPointe(const glm::vec4& couleur)
{
	m_couleurPointe = couleur;
}

void ng::Bouton2D::modifierCouleurClique(const glm::vec4& couleur)
{
	m_couleurClique = couleur;
}

void ng::Bouton2D::modifierIdentifiantTexturePolice(int identifiant)
{
	m_texte.modifierIdentifiantTexturePolice(identifiant);
}

void ng::Bouton2D::modifierTextureFond(int identifiantTexture, const glm::vec2& positionTexture, const glm::vec2& tailleTexture)
{
	m_fond.modifierTexture(identifiantTexture, positionTexture, tailleTexture);
}

void ng::Bouton2D::retirerTextureFond()
{
	m_fond.retirerTexture();
}

void ng::Bouton2D::translater(const glm::vec2& deplacement)
{
	m_texte.translater(deplacement);
	m_fond.translater(deplacement);
	m_forcerMiseAJourChaine = true;
}

void ng::Bouton2D::modifierEchelle(const glm::vec2& echelle)
{
	m_fond.modifierEchelle(echelle);
	m_forcerMiseAJourChaine = true;
}

void ng::Bouton2D::tourner(float angle)
{
	m_texte.tourner(angle);
	m_fond.tourner(angle);
	m_forcerMiseAJourChaine = true;
}

void ng::Bouton2D::mettreAJourAffichage()
{
	if (estClique())
		m_fond.modifierCouleur(m_couleurClique);
	else if (estPointe())
		m_fond.modifierCouleur(m_couleurPointe);
	else
		m_fond.modifierCouleur(m_couleurNormal);

	m_texte.mettreAJourAffichage();
	m_forcerMiseAJourChaine = false;
}
