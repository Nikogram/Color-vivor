#include "Shader.hpp"

ng::Shader::Shader(const std::string& fichierVertexShader, const std::string& fichierFragmentShader, const std::string& fichierGeometryShader)
{
	// Compilation des shaders
	compilerShader(m_identifiantVertexShader, GL_VERTEX_SHADER, fichierVertexShader);
	compilerShader(m_identifiantFragmentShader, GL_FRAGMENT_SHADER, fichierFragmentShader);
	if (fichierGeometryShader != "")
		compilerShader(m_identifiantGeometryShader, GL_GEOMETRY_SHADER, fichierGeometryShader);

	// Création du programme
	m_identifiant = glCreateProgram();


	// Association des shaders
	glAttachShader(m_identifiant, m_identifiantVertexShader);
	glAttachShader(m_identifiant, m_identifiantFragmentShader);
	if (fichierGeometryShader != "")
		glAttachShader(m_identifiant, m_identifiantGeometryShader);


	// Verrouillage des entrées shader
	glBindAttribLocation(m_identifiant, 0, "in_coordonneesSommet");
	glBindAttribLocation(m_identifiant, 1, "in_couleur");
	glBindAttribLocation(m_identifiant, 2, "in_coordonneesTexture");
	glBindAttribLocation(m_identifiant, 3, "in_normale");

	// Linkage du programme
	glLinkProgram(m_identifiant);


	// Vérification du linkage
	GLint erreurLink(0);
	glGetProgramiv(m_identifiant, GL_LINK_STATUS, &erreurLink);

	if (erreurLink != GL_TRUE)
	{
		GLint tailleErreur(0);
		glGetProgramiv(m_identifiant, GL_INFO_LOG_LENGTH, &tailleErreur);

		char *erreur = new char[tailleErreur + 1];

		glGetShaderInfoLog(m_identifiant, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';
		std::cout << erreur << std::endl;

		delete[] erreur;
		glDeleteProgram(m_identifiant);
	}
}

ng::Shader::~Shader()
{
	glDeleteShader(m_identifiantVertexShader);
	glDeleteShader(m_identifiantFragmentShader);
	if (m_identifiantGeometryShader != 0)
		glDeleteShader(m_identifiantGeometryShader);
	glDeleteProgram(m_identifiant);
}

GLuint ng::Shader::identifiant() const
{
	return m_identifiant;
}

bool ng::Shader::compilerShader(GLuint &identifiantShader, GLenum type, std::string const &fichierShader)
{
	// Création du shader
	identifiantShader = glCreateShader(type);
	if (identifiantShader == 0)
	{
		std::cout << "[ERREUR] Shader " << type << " non existant" << std::endl;
		return false;
	}


	// Lecture du fichier
	std::string codeSource;

	std::ifstream fichier(fichierShader.c_str());
	std::string ligneFichier;

	if (!fichier)
	{
		std::cout << "[ERREUR] " << fichierShader << " introuvable" << std::endl;
		glDeleteShader(identifiantShader);
		return false;
	}

	while (getline(fichier, ligneFichier))
		codeSource += ligneFichier + '\n';

	fichier.close();


	// Compilation du shader
	const GLchar* chaineCodeSource = codeSource.c_str();
	glShaderSource(identifiantShader, 1, &chaineCodeSource, 0);
	glCompileShader(identifiantShader);


	// Vérification de la compilation
	GLint erreurCompilation(0);
	glGetShaderiv(identifiantShader, GL_COMPILE_STATUS, &erreurCompilation);

	if (erreurCompilation != GL_TRUE)
	{
		GLint tailleErreur(0);
		glGetShaderiv(identifiantShader, GL_INFO_LOG_LENGTH, &tailleErreur);

		char *erreur = new char[tailleErreur + 1];
		glGetShaderInfoLog(identifiantShader, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';
		std::cout << erreur << std::endl;

		delete[] erreur;
		glDeleteShader(identifiantShader);
		return false;
	}
	else
		return true;
}
