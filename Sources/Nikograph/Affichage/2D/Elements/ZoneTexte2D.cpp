#include "ZoneTexte2D.hpp"

ng::ZoneTexte2D::ZoneTexte2D(const ng::Controles* controles, float tailleTexte, const glm::vec2& nombreCaracteresMaximum, int identifiantTexturePolice, const glm::vec2& position, bool petiteTexture) :
	m_controles(controles),
	m_texte(identifiantTexturePolice, " ", position, tailleTexte, petiteTexture),
	m_fond(position, m_texte.taille()),
	m_curseur(glm::vec2(0, 0), glm::vec2(m_texte.taille().x / 5, m_texte.taille().y)),
	m_nombreCaracteresMaximum(nombreCaracteresMaximum),
	m_positionCurseur(0, 0),
	m_selectionne(false),
	m_forcerMiseAJourChaine(true)
{
	m_fond.modifierTaille(glm::vec2(m_texte.taille().x * (m_nombreCaracteresMaximum.x + 1), m_fond.taille().y * (m_nombreCaracteresMaximum.y + 1)));
	m_texte.modifierChaine("");
	m_texte.modifierCouleur(glm::vec4(0, 0, 0, 1));
	m_curseur.modifierCouleur(glm::vec4(0, 0, 0, 1));
}

const ng::Texte2D& ng::ZoneTexte2D::texte() const
{
	return m_texte;
}

const ng::Rectangle2D& ng::ZoneTexte2D::fond() const
{
	return m_fond;
}

const ng::Rectangle2D& ng::ZoneTexte2D::curseur() const
{
	return m_curseur;
}

const std::string& ng::ZoneTexte2D::chaine() const
{
	return m_chaine;
}

bool ng::ZoneTexte2D::selectionne() const
{
	return m_selectionne;
}

bool ng::ZoneTexte2D::estClique() const
{
	if (m_controles->identifiantDoigtDansRectangle(m_fond) >= 0 || (m_controles->sourisDansRectangle(m_fond) && m_controles->boutonSourisGaucheAppuye()))
		return true;
	return false;
}

void ng::ZoneTexte2D::modifierTexte(std::string texte)
{
	m_chaine = texte;
	m_forcerMiseAJourChaine = true;
}

void ng::ZoneTexte2D::modifierTaillePoliceTexte(float taille)
{
	m_texte.modifierTaillePolice(taille);
	m_forcerMiseAJourChaine = true;
}

void ng::ZoneTexte2D::modifierPosition(const glm::vec2& position)
{
	m_texte.modifierPosition(position);
	m_fond.modifierPosition(position);
	m_forcerMiseAJourChaine = true;
}

void ng::ZoneTexte2D::modifierCouleurTexte(const glm::vec4& couleur)
{
	m_texte.modifierCouleur(couleur);
	m_forcerMiseAJourChaine = true;
}

void ng::ZoneTexte2D::modifierCouleurFond(const glm::vec4& couleur)
{
	m_fond.modifierCouleur(couleur);
}

void ng::ZoneTexte2D::modifierIdentifiantTexturePolice(int identifiant)
{
	m_texte.modifierIdentifiantTexturePolice(identifiant);
}

void ng::ZoneTexte2D::modifierTextureFond(int identifiantTexture, const glm::vec2& positionTexture, const glm::vec2& tailleTexture)
{
	m_fond.modifierTexture(identifiantTexture, positionTexture, tailleTexture);
}

void ng::ZoneTexte2D::modifierSelectionne(bool selectionne)
{
	m_selectionne = selectionne;
}

void ng::ZoneTexte2D::retirerTextureFond()
{
	m_fond.retirerTexture();
}

void ng::ZoneTexte2D::translater(const glm::vec2& deplacement)
{
	m_texte.translater(deplacement);
	m_fond.translater(deplacement);
	m_forcerMiseAJourChaine = true;
}

void ng::ZoneTexte2D::modifierEchelle(const glm::vec2& echelle)
{
	m_fond.modifierEchelle(echelle);
	m_forcerMiseAJourChaine = true;
}

void ng::ZoneTexte2D::mettreAJourAffichage()
{
	std::string ancienneChaine = m_chaine;
	std::string chaine = m_chaine;

	if (estClique())
		m_selectionne = true;
	else if (m_controles->boutonSourisGaucheAppuye())
		m_selectionne = false;

	if (m_selectionne || m_forcerMiseAJourChaine)
	{
		// Récupération du caractère entré
		char caracteresSpeciaux[48] = { 'à', 'â', 'ä', 'é', 'è', 'ê', 'ë', 'î', 'ï', 'ô', 'ö', 'ù', 'û', 'ü', 'ç',
			'.', ',', ';', '\'', '(', ')', '[', ']', '{', '}', '/', '\\', '*', '°', ':', '!',
			'"', '#', '&', '_', '@', '€', '$', '£', 'µ', '^', '?', '=', '+', '-', '<', '>', ' ' };

		bool caractereAccepte = false;
		for (int i = 0; i < 48 && !caractereAccepte; ++i)
		{
			if (i < 27 && m_controles->caractereEntre() == 'a' + i || m_controles->caractereEntre() == 'A' + i)
				caractereAccepte = true;
			if (i  < 10 && m_controles->caractereEntre() == '0' + i)
				caractereAccepte = true;
			if (m_controles->caractereEntre() == caracteresSpeciaux[i])
				caractereAccepte = true;
		}


		// Mise à jour du texte
		if ((m_controles->caractereEntre() == '\r' || m_positionCurseur.x == m_nombreCaracteresMaximum.x) && m_texte.nombreLignes() < m_nombreCaracteresMaximum.y)
			chaine = chaine + '\r';

		if (caractereAccepte && (m_nombreCaracteresMaximum.y == 1 || m_positionCurseur.x < m_nombreCaracteresMaximum.x))
			chaine = chaine + m_controles->caractereEntre();
		else if (m_controles->caractereEntre() == 8 && chaine.length() != 0)
		{
			if (chaine.substr(chaine.length() - 1, 1) == "\r" || chaine.substr(chaine.length() - 1, 1) == "\n")
				chaine = chaine.substr(0, chaine.length() - 2);
			else
				chaine = chaine.substr(0, chaine.length() - 1);
		}

		m_chaine = chaine;
		if (m_nombreCaracteresMaximum.y == 1 && m_chaine.length() > m_nombreCaracteresMaximum.x)
			chaine = chaine.substr(chaine.length() - m_nombreCaracteresMaximum.x, m_nombreCaracteresMaximum.x);
		
		m_texte.modifierChaine(chaine);
	}


	// Mise à jour de l'affichage
	m_positionCurseur.y = m_texte.nombreLignes() - 1;
	m_positionCurseur.x = m_texte.nombreColonnes(m_positionCurseur.y);

	Texte2D texteReference(0, " ", glm::vec2(0, 0), m_texte.taillePolice());
	m_texte.modifierPosition(m_fond.position() + texteReference.taille() / 2.0f - m_fond.taille() / 2.0f + texteReference.taille() * glm::vec2(m_texte.nombreColonnes(), m_texte.nombreLignes()) / 2.0f);
	
	if (m_nombreCaracteresMaximum.y == 1 && m_positionCurseur.x >= m_nombreCaracteresMaximum.x)
		m_curseur.modifierPosition(m_fond.position() + texteReference.taille() * glm::vec2(0.5, 1) - m_fond.taille() / 2.0f + texteReference.taille() * glm::vec2(m_nombreCaracteresMaximum.x, 0));
	else
		m_curseur.modifierPosition(m_fond.position() + texteReference.taille() * glm::vec2(0.5, 1) - m_fond.taille() / 2.0f + texteReference.taille() * m_positionCurseur);

	if (m_chaine != ancienneChaine || m_forcerMiseAJourChaine)
	{
		m_texte.mettreAJourAffichage();
		m_forcerMiseAJourChaine = false;
	}
}