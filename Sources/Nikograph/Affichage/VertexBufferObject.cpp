#include "VertexBufferObject.hpp"

ng::VertexBufferObject::VertexBufferObject(int taille) :
	m_identifiant(0),
	m_taille(taille)
{
	if (glIsBuffer(m_identifiant) == GL_TRUE)
		glDeleteBuffers(1, &m_identifiant);

	glGenBuffers(1, &m_identifiant);
	glBindBuffer(GL_ARRAY_BUFFER, m_identifiant);
	glBufferData(GL_ARRAY_BUFFER, taille * sizeof(float), 0, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ng::VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &m_identifiant);
}

GLuint ng::VertexBufferObject::identifiant() const
{
	return m_identifiant;
}

int ng::VertexBufferObject::taille() const
{
	return m_taille;
}

void ng::VertexBufferObject::ajouterDonnees(int position, int taille, const float* donnees)
{
	if (glIsBuffer(m_identifiant) == GL_TRUE && position + taille <= m_taille)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_identifiant);
		glBufferSubData(GL_ARRAY_BUFFER, position * sizeof(float), taille * sizeof(float), donnees);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}