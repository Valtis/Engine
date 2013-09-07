#include "Graphics/Renderer/Renderer.h"

#include <iostream>
int main(int argc, char *argv[])
{
	Renderer::Instance().CreateWindow("Foo", 640, 480);

	return 0;
}