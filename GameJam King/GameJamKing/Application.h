#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Module.h"
#include "Globals.h"
#include <list>
#include <string>
#include "PugiXml/src/pugixml.hpp"
#include "Timer.h"


class Window;
class Input;
class Render;
class Scene;
class Fonts;
class MapGenerator;
class ModulePrinter;
class ModuleProjectiles;

class Application
{
public:

	Application(int argc, char* args[]);
	virtual ~Application();

	bool Awake();
	bool Start();
	bool Update();
	bool CleanUp();

	void AddModule(Module* module);

	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

private:

	bool PrepareUpdate();
	bool FinishUpdate();
	bool PreUpdate();
	bool DoUpdate();
	bool PostUpdate();

public:

	Window*					window = nullptr;
	Input*					input = nullptr;
	Render*					render = nullptr;
	Scene*					scene = nullptr;
	MapGenerator*			map = nullptr;
	ModulePrinter*			printer = nullptr;
	ModuleProjectiles*		projectiles = nullptr;

private:

	std::list<Module*>	modules;
	int					argc;
	char**				args;

	std::string			title;
	std::string			organization;

	float dt = 0.0f;

	mutable bool savegame = false;
	bool loadgame = false;
};

extern Application* App;

#endif