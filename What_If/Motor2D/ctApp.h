#ifndef __ctAPP_H__
#define __ctAPP_H__

#include <list>
#include <string>
#include "ctModule.h"
#include "ctPerfTimer.h"
#include "ctTimer.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class ctWindow;
class ctInput;
class ctRender;
class ctTextures;
class ctAudio;
class ctEntities;
class ctGui;
class ctFonts;

class SceneCity;

class ctFadeToBlack;
class j1Printer;
class j1Collision;

class ctApp
{
public:

	// Constructor
	ctApp(int argc, char* args[]);

	// Destructor
	virtual ~ctApp();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(ctModule* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Load entities file
	pugi::xml_node LoadEntities(pugi::xml_document&) const;

	// Load data file
	pugi::xml_node LoadData(pugi::xml_document&) const;

	// Load languages file
	pugi::xml_node LoadLanguages(pugi::xml_document&) const;

	//Load items
	pugi::xml_node LoadItems(pugi::xml_document&) const;

	// Load abilities file
	pugi::xml_node LoadAbilities(pugi::xml_document&) const;

	pugi::xml_node LoadEmitters(pugi::xml_document& psystem_file) const;

private:

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

public:

	// Modules
	ctWindow*			win = nullptr;
	ctInput*			input = nullptr;
	ctRender*			render = nullptr;
	ctTextures*			tex = nullptr;
	ctAudio*			audio = nullptr;
	ctEntities*			entities = nullptr;

	SceneCity*			city = nullptr;

	ctGui*				gui = nullptr;
	ctFonts*			fonts = nullptr;
	ctFadeToBlack*		fadeToBlack = nullptr;
	j1Printer*			printer = nullptr;
	j1Collision*		collision = nullptr;

	bool				cap_state = false;

private:

	std::list<ctModule*>	modules;
	int					argc = 0;
	char**				args = nullptr;

	std::string			game_title;
	std::string				organization;
	std::string				vsync_to_show;
	std::string				cap_to_show;

	ctPerfTimer			perf_timer;
	ctTimer				simple_timer;

	ctPerfTimer			ptimer;
	uint64				frame_count = 0;
	uint				cap = 0u;
	ctTimer				startup_time;
	float				dt = 0.0f;
	int					capped_ms = -1;
	bool				all_modules_loaded = false;

};

extern ctApp* App;

#endif