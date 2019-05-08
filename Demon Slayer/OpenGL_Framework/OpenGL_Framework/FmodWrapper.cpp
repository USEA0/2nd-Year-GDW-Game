#include "FmodWrapper.h"

void FmodErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << FMOD_ErrorString(result) << std::endl;
		system("pause");
	}
}

bool SoundEngine::init()
{
	if (!isSoundEngineInit)
	{
		// Create a System object and initialize
		result = FMOD::System_Create(&system);
		FmodErrorCheck(result);

		// check for any Fmod errors
		if (result != FMOD_OK)
			return false;

		result = system->getVersion(&version);
		FmodErrorCheck(result);

		result = system->init(100, FMOD_INIT_NORMAL, extradriverdata);
		FmodErrorCheck(result);

		result = system->set3DSettings(1.0, 1.0, 1.0f);
		FmodErrorCheck(result);

		// Fmod initialize working
		isSoundEngineInit = true;
	}

	return true;
}

void SoundEngine::update(FMOD_VECTOR cameraPos)
{
	// update the listener
	result = system->set3DListenerAttributes(0, &cameraPos, &listener.vel, &listener.forward, &listener.up);
	FmodErrorCheck(result);

	result = system->update();
	FmodErrorCheck(result);
}

SoundEngine::~SoundEngine()
{
	if (isSoundEngineInit)
	{
		result = system->close();
		FmodErrorCheck(result);
		result = system->release();
		FmodErrorCheck(result);
		isSoundEngineInit = false;
	}
}

FMOD_RESULT Sound::result;
SoundEngine Sound::engine;

bool Sound::Load(const char * fileName)
{
	if (!isSoundInit)
	{
		engine.init();

		result = engine.system->createSound(fileName, FMOD_3D, 0, &sound);
		FmodErrorCheck(result);
		

		if (result != FMOD_OK)
			return false;

		result = sound->set3DMinMaxDistance(1.0f, 100.0f);
		FmodErrorCheck(result);

		isSoundInit = true;
	}
	return true;
}

FMOD::Channel* Sound::Play(bool loop)
{
	if (isSoundInit)
	{
		result = engine.system->playSound(sound, 0, true, &channel);
		FmodErrorCheck(result);
		result = channel->set3DAttributes(&pos, &vel);
		FmodErrorCheck(result);

		if (loop)
		{
			channel->setMode(FMOD_LOOP_NORMAL);
		}
		else
		{
			channel->setMode(FMOD_LOOP_OFF);
		}

		// set 2D/3D sounds

		result = channel->setPaused(false);
		FmodErrorCheck(result);
	}

	return channel;
}

void Sound::SetRollOff(FMOD::Channel * thisChannel, int rolloff) // change the rolloff mode 0 for linear, 1 for inverserolloff
{
	if (rolloff == 0)
	{
		thisChannel->setMode(FMOD_3D_LINEARROLLOFF); // set mode to linear
	}
	else if (rolloff == 1)
	{
		thisChannel->setMode(FMOD_3D_INVERSEROLLOFF); // set mode to inverserolloff
	}
}

void Sound::SetPosition(FMOD::Channel * thisChannel, FMOD_VECTOR newPos, FMOD_VECTOR newVel)
{
	result = thisChannel->set3DAttributes(&newPos, &newVel);
	FmodErrorCheck(result);
}

void Sound::SetVolume(FMOD::Channel * thisChannel, float v) //set volume of channel
{
	result = thisChannel->setVolume(v);
	FmodErrorCheck(result);
}

void Sound::PlayState(FMOD::Channel * thisChannel, bool play) //play or pause channel
{
	result = thisChannel->setPaused(play);
	FmodErrorCheck(result);
}

void Sound::Stop(FMOD::Channel * thisChannel) //stop channel from playing sound
{
	result = thisChannel->stop();
	FmodErrorCheck(result);
}

Sound::~Sound()
{
	if (isSoundInit)
	{
		result = sound->release();
		FmodErrorCheck(result);
	}
}
