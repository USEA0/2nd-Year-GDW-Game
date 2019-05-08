#pragma once
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")

#include "FMOD/inc/fmod.hpp"
#include "FMOD//inc/fmod_errors.h"
#include <Windows.h>
#include <iostream>

void FmodErrorCheck(FMOD_RESULT result);

struct Listener
{
	FMOD_VECTOR pos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR	vel = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR	forward = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR	up = { 0.0f, 1.0f, 0.0f };
};

class SoundEngine
{
public:
	bool init();
	void update(FMOD_VECTOR cameraPos);
	~SoundEngine();

	Listener listener;
	FMOD::System *system;

private:
	unsigned int version;
	void *extradriverdata = 0;
	bool isSoundEngineInit = false;
	FMOD_RESULT result;
};

class Sound
{
public:
	bool Load(const char* fileName);
	FMOD::Channel* Play(bool loop);
	static void SetRollOff(FMOD::Channel* thisChannel, int rolloff); // change the rolloff mode 0 for linear, 1 for inverserolloff
	static void SetPosition(FMOD::Channel* thisChannel, FMOD_VECTOR newPos, FMOD_VECTOR newVel = { 0.0f, 0.0f, 0.0f });
	static void SetVolume(FMOD::Channel* thisChannel, float v);
	static void PlayState(FMOD::Channel* thisChannel, bool play);
	static void Stop(FMOD::Channel* thisChannel);
	~Sound();

	FMOD::Sound *sound;
	FMOD_VECTOR pos = { -10.0f, 0.0f, 0.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	static SoundEngine engine;

private:
	FMOD::Channel *channel = 0;
	static FMOD_RESULT result;
	bool isSoundInit = false;
};