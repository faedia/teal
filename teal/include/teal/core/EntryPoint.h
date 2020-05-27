#pragma once

#include "Common.h"

extern Teal::Application* Teal::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Teal::CreateApplication();
	app->Run();
	delete app;

	return 0;
}