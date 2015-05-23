#include "FrameBuffer.hpp"

ng::FrameBuffer::FrameBuffer(glm::vec2 tailleTexture) :
m_identifiant(0),
m_identifiantTexture(0),
m_taille(tailleTexture),
m_identifiantTamponProfondeur(0)
{

}

ng::FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_identifiant);
	glDeleteRenderbuffers(1, &m_identifiantTamponProfondeur);
}

bool ng::FrameBuffer::charger()
{
	// Initialisation du framebuffer
	glGenFramebuffers(1, &m_identifiant);
	glBindFramebuffer(GL_FRAMEBUFFER, m_identifiant);


	// Initialisation de la texture
	glGenTextures(1, &m_identifiantTexture);
	glBindTexture(GL_TEXTURE_2D, m_identifiantTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_taille.x, m_taille.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	// Initialisation du tampon de profondeur
	glGenRenderbuffers(1, &m_identifiantTamponProfondeur);
	glBindRenderbuffer(GL_RENDERBUFFER, m_identifiantTamponProfondeur);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_taille.x, m_taille.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_identifiantTamponProfondeur);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);


	// Configuration du tampon d'image
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_identifiantTexture, 0);
	glDrawBuffer(GL_NONE);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		glDeleteFramebuffers(1, &m_identifiant);
		glDeleteRenderbuffers(1, &m_identifiantTamponProfondeur);

		std::cout << "[ERREUR] Initialisation du Frame Buffer" << std::endl;
		return false;
	}
	return true;
}

GLuint ng::FrameBuffer::identifiant() const
{
	return m_identifiant;
}

const glm::vec2& ng::FrameBuffer::taille() const
{
	return m_taille;
}

GLuint ng::FrameBuffer::identifiantTexture() const
{
	return m_identifiantTexture;
}

GLuint ng::FrameBuffer::identifiantDepthBuffer() const
{
	return m_identifiantTamponProfondeur;
}