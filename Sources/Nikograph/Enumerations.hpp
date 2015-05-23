#ifndef _ENUMERATION
#define _ENUMERATION

namespace ng
{
	enum GrandeurMetrique { Relatif, RelatifRedimensionneX, RelatifRedimensionneY, Pixels };
	/*
	* Relatif : entre 0 et 1
	* RelatifRedimensionne* : entre 0 et 1, avec même echelle sur chaque axe (taille modifiee suivant l'axe *)
	* Pixels : en pixels
	*/
}

#endif