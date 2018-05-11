#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "SDL_mixer\include\SDL_mixer.h"
#include <vector>
#include "ctApp.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class ctAudio : public ctModule
{
public:

	ctAudio();

	// Destructor
	virtual ~ctAudio();

	// Called before render is available
	bool Awake(pugi::xml_node&);


	bool Update(float dt);


	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	//Pause a playing music
	bool PauseMusic(float fade_time = DEFAULT_MUSIC_FADE_TIME);

	//Stop a FX
	bool HaltFX(int id = -1, int fadeseconds = 0);

	//Pause a FX
	bool PauseFX(int id = -1);

	//Resume a previously paused FX
	bool ResumeFX(int id = -1);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	//Return the channel used or -1 if errors happened
	int PlayFx(unsigned int fx, int repeat = 0, int channel = -1);

	//Set Volumes
	void setMusicVolume(uint percent);
	void setFXVolume(uint percent);

	//InitAudio

	void InitAudio();

public:

	//fx sounds
	uint mm_movement_fx = 0u;
	uint mm_select_fx = 0u;

	//music sounds
	std::string MainMenuBSO;
	std::string SettingsBSO;

	//volumes
	uint MusicVolumePercent = 10;
	uint FXVolumePercent = 10;

private:

	_Mix_Music*			music;
	std::vector <Mix_Chunk*> fx;

public:
	bool device_connected = false;

};

#endif // __AUDIO_H__
