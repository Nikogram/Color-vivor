#ifndef _FRAMEBUFFER
#define _FRAMEBUFFER

#include "Texture.hpp"

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ng
{
	class FrameBuffer
	{
		public:
			FrameBuffer(glm::vec2 tailleTexture);
			~FrameBuffer();
			bool charger();
			GLuint identifiant() const;
			const glm::vec2& taille() const;
			GLuint identifiantTexture() const;
			GLuint identifiantDepthBuffer() const;

		protected:
			GLuint m_identifiant;
			GLuint m_identifiantTexture;
			glm::vec2 m_taille;
			GLuint m_identifiantTamponProfondeur;
	};
}

#endif