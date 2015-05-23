#ifndef _SHADER
#define _SHADER

#include "../BibliothequesExternes.hpp"

namespace ng
{
	class Shader
	{
		public :
			Shader(const std::string& fichierVertexShader, const std::string& fichierFragmentShader, const std::string& fichierGeometryShader = "");
			~Shader();
			GLuint identifiant() const;
			bool compilerShader(GLuint &identifiantShader, GLenum type, const std::string &fichierShader);

		private :
			GLuint m_identifiantVertexShader;
			GLuint m_identifiantFragmentShader;
			GLuint m_identifiantGeometryShader;
			GLuint m_identifiant;
	};
}

#endif
