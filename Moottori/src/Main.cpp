#include <SDL_main.h>
#include "Engine.h"

#include <exception>
#include <fstream>
int main(int argc, char *argv[])
{
	try {
		Engine e;
		e.Run();
	}
	catch (const std::exception &e)
	{
		std::ofstream err("error.log");
		err << "Error: " << e.what();
	}
	return 0;
}