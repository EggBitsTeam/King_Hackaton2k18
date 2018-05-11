#include <iostream>
#include <fstream>
#include <sstream>

#include "p2Defs.h"
#include "Log.h"
#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "Scene.h"
#include "ModulePrinter.h"
#include "ModuleProjectiles.h"

#include "Brofiler\Brofiler.h"

Application::Application(int argc, char* args[]) : argc(argc), args(args)
{
	window = new Window();
	render = new Render();
	input = new Input();
	scene = new Scene();
	printer = new ModulePrinter();
	projectiles = new ModuleProjectiles();
	// Ordered for awake / Start / Update
	// Reverse order of CleanUp

	AddModule(window);
	AddModule(input);
	AddModule(projectiles);
	AddModule(printer);
	AddModule(scene);
	AddModule(render);

	organization = "EggTeam";
	title = "GameJam King";
}

Application::~Application()
{
	std::list<Module*>::reverse_iterator it;
	for (it = modules.rbegin(); it != modules.rend(); ++it)
	{
		delete (*it);
	}

	modules.clear();
}

void Application::AddModule(Module* module)
{
	module->Init();
	modules.push_back(module);
}

bool Application::Awake()
{
	bool ret = true;

	std::list<Module*>::const_iterator item;

	for (item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		pugi::xml_node node;
		ret = (*item)->Awake(node);
	}

	return ret;
}

bool Application::Start()
{
	bool ret = true;
	std::list<Module*>::const_iterator item;

	for (item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		if ((*item)->isActive())
			ret = (*item)->Start();
	}

	return ret;
}

bool Application::Update()
{
	bool ret = true;

	if (input->GetWindowEvent(WE_QUIT))
		ret = false;

	if (ret == true)
		ret = PrepareUpdate();

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	if (ret == true)
		ret = FinishUpdate();

	return ret;
}

bool Application::PrepareUpdate()
{
	return true;
}

bool Application::FinishUpdate()
{
	bool ret = true;

	return ret;
}

bool Application::PreUpdate()
{
	bool ret = true;

	std::list<Module*>::const_iterator item;
	Module* pModule = nullptr;

	for (item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		pModule = (*item);

		if (pModule->isActive() == false)
		{
			continue;
		}

		ret = (*item)->PreUpdate();
	}

	return ret;
}

bool Application::DoUpdate()
{
	bool ret = true;

	std::list<Module*>::const_iterator item;
	Module* pModule = nullptr;

	BROFILER_CATEGORY("AppUpdate", Profiler::Color::Chocolate);
	for (item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		pModule = (*item);

		if (pModule->isActive() == false)
		{
			continue;
		}

		ret = (*item)->Update(dt);
	}

	return ret;
}

bool Application::PostUpdate()
{
	bool ret = true;

	std::list<Module*>::const_iterator item;
	Module* pModule = nullptr;

	BROFILER_CATEGORY("AppPostUpdate", Profiler::Color::Chocolate);
	for (item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		pModule = (*item);

		if (pModule->isActive() == false)
		{
			continue;
		}

		ret = (*item)->PostUpdate();
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	std::list<Module*>::reverse_iterator it;

	for (it = modules.rbegin(); it != modules.rend(); ++it)
	{
		ret = (*it)->CleanUp();
	}

	return ret;
}

int Application::GetArgc() const
{
	return argc;
}

const char* Application::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

const char* Application::GetTitle() const
{
	return title.data();
}

const char* Application::GetOrganization() const
{
	return organization.data();
}