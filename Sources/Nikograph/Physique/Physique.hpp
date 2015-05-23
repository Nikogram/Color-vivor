#ifndef _PHYSIQUE
#define _PHYSIQUE

#include "../BibliothequesExternes.hpp"

namespace ng
{
	float vitessePoussePourSaut(float hauteurMaximale, float gravite);
	bool rayonTriangle3DEnCollision(const glm::vec3& origineRayon, const glm::vec3& directionRayon, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3);
	bool triangles2DEnCollision(const std::vector<glm::vec2>& coordonneesPointsTriangle1, const std::vector<glm::vec2>& coordonneesPointsTriangle2);
	bool triangles3DEnCollision(const std::vector<glm::vec3>& coordonneesPointsTriangle1, const std::vector<glm::vec3>& coordonneesPointsTriangle2);
	bool modeles2DEnCollision(const std::vector<float>& coordonneesPointsModele1, const std::vector<float>& coordonneesPointsModele2);
	bool rayonModele3DEnCollision(const glm::vec3& origineRayon, const glm::vec3& directionRayon, const std::vector<float>& coordonneesPointsModele);
	bool modeles3DEnCollision(const std::vector<float>& coordonneesPointsModele1, const std::vector<float>& coordonneesPointsModele2);
}

#endif