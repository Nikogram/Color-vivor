#include "Application.hpp"

#include <stdlib.h>

int main(int argc, char **argv)
{
	Application application;
	if (application.initialiser())
		application.lancer();
	
	//exit(EXIT_SUCCESS);
	return 0;
}
