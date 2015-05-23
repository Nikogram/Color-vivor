#include "Physique.hpp"

float ng::vitessePoussePourSaut(float hauteurMaximale, float gravite)
{
	return glm::sqrt(2 * hauteurMaximale * glm::abs(gravite));
}

bool ng::rayonTriangle3DEnCollision(const glm::vec3& origineRayon, const glm::vec3& directionRayon, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3)
{
	glm::vec3 e1 = point2 - point1;
	glm::vec3 e2 = point3 - point1;

	// Calcul du déterminant
	glm::vec3 P = glm::cross(directionRayon, e2);
	float det = glm::dot(e1, P);

	if (glm::abs(det) < FLT_EPSILON)
		return false;

	// Calcul de la distance entre le point 1 du triangle et l'origine du rayon
	glm::vec3 T = origineRayon - point1;

	// Calcul de u
	float u = glm::dot(T, P) / det;

	if (u < 0 || u > 1)
		return false;

	// Préparation du calcul de v
	glm::vec3 Q = glm::cross(T, e1);

	// Calcul de v
	float v = glm::dot(directionRayon, Q) / det;

	if (v < 0 || u + v > 1)
		return false;


	float t = glm::dot(e2, Q) / det;

	if (t > FLT_EPSILON)
		return true;
	return false;
}

bool ng::triangles2DEnCollision(const std::vector<glm::vec2>& coordonneesPointsTriangle1, const std::vector<glm::vec2>& coordonneesPointsTriangle2)
{
	if (coordonneesPointsTriangle1.size() == 3 && coordonneesPointsTriangle2.size() == 3)
	{
		glm::vec3 coordonneesIntersection;

		for (int i = 0; i < 3; ++i)
		{
			bool collisionRayon = ng::rayonTriangle3DEnCollision(glm::vec3(coordonneesPointsTriangle1[i], 1), glm::vec3(0, 0, -1), glm::vec3(coordonneesPointsTriangle2[0], 0), glm::vec3(coordonneesPointsTriangle2[1], 0), glm::vec3(coordonneesPointsTriangle2[2], 0));
			
			if (collisionRayon)
				return true;
		}
	}

	return false;
}

bool ng::triangles3DEnCollision(const std::vector<glm::vec3>& coordonneesPointsTriangle1, const std::vector<glm::vec3>& coordonneesPointsTriangle2)
{
	if (coordonneesPointsTriangle1.size() == 3 && coordonneesPointsTriangle2.size() == 3)
	{
		glm::vec3 coordonneesIntersection;

		for (int i = 0; i < 3; ++i)
		{
			int identifiantPoint1 = i;
			int identifiantPoint2 = (i == 2 ? 0 : i + 1);

			bool collisionRayon1 = ng::rayonTriangle3DEnCollision(coordonneesPointsTriangle1[identifiantPoint1], coordonneesPointsTriangle1[identifiantPoint2] - coordonneesPointsTriangle1[identifiantPoint1], coordonneesPointsTriangle2[0], coordonneesPointsTriangle2[1], coordonneesPointsTriangle2[2]);
			bool collisionRayon2 = ng::rayonTriangle3DEnCollision(coordonneesPointsTriangle1[identifiantPoint2], coordonneesPointsTriangle1[identifiantPoint1] - coordonneesPointsTriangle1[identifiantPoint2], coordonneesPointsTriangle2[0], coordonneesPointsTriangle2[1], coordonneesPointsTriangle2[2]);

			if (collisionRayon1 && collisionRayon2)
				return true;
		}
	}

	return false;
}

bool ng::modeles2DEnCollision(const std::vector<float>& coordonneesPointsModele1, const std::vector<float>& coordonneesPointsModele2)
{
	if (coordonneesPointsModele1.size() % 6 == 0 && coordonneesPointsModele2.size() % 6 == 0)
	{
		for (int i = 0; i < coordonneesPointsModele1.size() / 6; ++i)
		{
			std::vector<glm::vec2> coordonneesTriangle1 = { glm::vec2(coordonneesPointsModele1[6 * i + 0], coordonneesPointsModele1[6 * i + 1]), glm::vec2(coordonneesPointsModele1[6 * i + 2], coordonneesPointsModele1[6 * i + 3]), glm::vec2(coordonneesPointsModele1[6 * i + 4], coordonneesPointsModele1[6 * i + 5]) };

			for (int j = 0; j < coordonneesPointsModele2.size() / 6; ++j)
			{
				std::vector<glm::vec2> coordonneesTriangle2 = { glm::vec2(coordonneesPointsModele2[6 * j + 0], coordonneesPointsModele2[6 * j + 1]), glm::vec2(coordonneesPointsModele2[6 * j + 2], coordonneesPointsModele2[6 * j + 3]), glm::vec2(coordonneesPointsModele2[6 * j + 4], coordonneesPointsModele2[6 * j + 5]) };

				if (ng::triangles2DEnCollision(coordonneesTriangle1, coordonneesTriangle2))
					return true;
			}
		}
	}

	return false;
}

bool ng::rayonModele3DEnCollision(const glm::vec3& origineRayon, const glm::vec3& directionRayon, const std::vector<float>& coordonneesPointsModele)
{
	if (coordonneesPointsModele.size() % 9 == 0)
	{
		for (int i = 0; i < coordonneesPointsModele.size() / 9; ++i)
		{
			std::vector<glm::vec3> coordonneesTriangle = { glm::vec3(coordonneesPointsModele[9 * i + 0], coordonneesPointsModele[9 * i + 1], coordonneesPointsModele[9 * i + 2]), glm::vec3(coordonneesPointsModele[9 * i + 3], coordonneesPointsModele[9 * i + 4], coordonneesPointsModele[9 * i + 5]), glm::vec3(coordonneesPointsModele[9 * i + 6], coordonneesPointsModele[9 * i + 7], coordonneesPointsModele[9 * i + 8]) };
		
			if (ng::rayonTriangle3DEnCollision(origineRayon, directionRayon, coordonneesTriangle[0], coordonneesTriangle[1], coordonneesTriangle[2]))
				return true;
		}
	}

	return false;
}

bool ng::modeles3DEnCollision(const std::vector<float>& coordonneesPointsModele1, const std::vector<float>& coordonneesPointsModele2)
{
	if (coordonneesPointsModele1.size() % 9 == 0 && coordonneesPointsModele2.size() % 9 == 0)
	{
		for (int i = 0; i < coordonneesPointsModele1.size() / 9; ++i)
		{
			std::vector<glm::vec3> coordonneesTriangle1 = { glm::vec3(coordonneesPointsModele1[9 * i + 0], coordonneesPointsModele1[9 * i + 1], coordonneesPointsModele1[9 * i + 2]), glm::vec3(coordonneesPointsModele1[9 * i + 3], coordonneesPointsModele1[9 * i + 4], coordonneesPointsModele1[9 * i + 5]), glm::vec3(coordonneesPointsModele1[9 * i + 6], coordonneesPointsModele1[9 * i + 7], coordonneesPointsModele1[9 * i + 8]) };

			for (int j = 0; j < coordonneesPointsModele2.size() / 9; ++j)
			{
				std::vector<glm::vec3> coordonneesTriangle2 = { glm::vec3(coordonneesPointsModele2[9 * j + 0], coordonneesPointsModele2[9 * j + 1], coordonneesPointsModele2[9 * j + 2]), glm::vec3(coordonneesPointsModele2[9.0f * j + 3], coordonneesPointsModele2[9 * j + 4], coordonneesPointsModele2[9 * j + 5]), glm::vec3(coordonneesPointsModele2[9 * j + 6], coordonneesPointsModele2[9 * j + 7], coordonneesPointsModele2[9 * j + 8]) };

				if (ng::triangles3DEnCollision(coordonneesTriangle1, coordonneesTriangle2))
					return true;
			}
		}
	}

	return false;
}