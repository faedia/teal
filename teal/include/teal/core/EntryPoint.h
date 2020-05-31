#pragma once

#include "teal/Core.h"

extern Teal::Application* Teal::CreateApplication();

int main(int argc, char** argv)
{
	Teal::Logger::Init();

	TL_CORE_TRACE("The engine has started!");

	auto app = Teal::CreateApplication();
	app->Run();
	delete app;

	return 0;
}