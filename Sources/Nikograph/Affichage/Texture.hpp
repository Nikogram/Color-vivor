#ifndef _TEXTURE
#define _TEXTURE

#include "../BibliothequesExternes.hpp"

namespace ng
{
	class Texture
	{
		public:
			Texture();
			~Texture();
			GLuint identifiant() const;
			const glm::vec2& taille() const;
			bool charger(const std::string& fichier, bool genererMipMap = false, GLuint qualiteProche = GL_NEAREST, GLuint qualiteLoin = GL_NEAREST);

		private :
			GLuint m_identifiant;
			glm::vec2 m_taille;
	};
}

#endif
