#ifndef _VERTEXBUFFEROBJECT
#define _VERTEXBUFFEROBJECT

#include "../BibliothequesExternes.hpp"

namespace ng
{
	class VertexBufferObject
	{
		public:
			VertexBufferObject(int taille);
			~VertexBufferObject();
			GLuint identifiant() const;
			int taille() const;
			void ajouterDonnees(int position, int taille, const float* donnees);

		protected :
			GLuint m_identifiant;
			int m_taille;
	};
}

#endif
