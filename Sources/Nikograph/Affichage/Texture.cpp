#include "Texture.hpp"

ng::Texture::Texture() :
m_identifiant(0),
m_taille(0, 0)
{
}

ng::Texture::~Texture()
{
	glDeleteTextures(1, &m_identifiant);
}

GLuint ng::Texture::identifiant() const
{
	return m_identifiant;
}

const glm::vec2& ng::Texture::taille() const
{
	return m_taille;
}

bool ng::Texture::charger(const std::string& fichier, bool genererMipMap, GLuint qualiteProche, GLuint qualiteLoin)
{
	sf::Image texture;
	texture.loadFromFile(fichier);

	m_taille = glm::vec2(texture.getSize().x, texture.getSize().y);

	if (glIsTexture(m_identifiant) == GL_TRUE)
		glDeleteTextures(1, &m_identifiant);
	glGenTextures(1, &m_identifiant);

	glBindTexture(GL_TEXTURE_2D, m_identifiant);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_taille.x, m_taille.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, qualiteLoin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, qualiteProche);

	if (genererMipMap)
		glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}
