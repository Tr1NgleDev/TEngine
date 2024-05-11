#include "../include/tengine/Audio.h"

#include "../include/tengine/MainGame.h"

void TEngine::Audio::init()
{
	BASS_Init(-1, 44100, 0, MainGame::getInstance()->getHWND(), nullptr);
	BASS_SetConfig(BASS_CONFIG_FLOATDSP, TRUE);
}

void TEngine::Audio::update()
{
	for (auto& sound : sounds)
		sound->update();
}

void TEngine::Audio::destroy()
{
	for(auto& sound : sounds)
	{
		sound->destroy(false);

		delete sound;
	}
	sounds.clear();
	for(auto& sample : samples)
	{
		BASS_SampleFree(sample.second);
	}
	samples.clear();

	BASS_Free();
}

TEngine::Sound::Sound(const std::string& path, float volume, float pan)
{
	this->volume = volume;
	this->pan = pan;

	if (!Audio::samples.contains(path))
		Audio::samples[path] = BASS_SampleLoad(false, path.c_str(), 0, 0, 65535, 0);

	_sampleId = Audio::samples[path];

	if(_sampleId == 0)
	{
		Console::print(std::format("TEngine::Audio::Sound::Sound(): _sampleId == 0. BASS Error Code:{}\n", BASS_ErrorGetCode()));
		return;
	}
	_id = BASS_SampleGetChannel(_sampleId, 1);

	if (_id == 0)
	{
		Console::print(std::format("TEngine::Audio::Sound::Sound(): _id == 0. BASS Error Code:{}\n", BASS_ErrorGetCode()));
		return;
	}

	BASS_ChannelSetSync(_id, BASS_SYNC_END, 0, endCallback, this);

	update();
}

int TEngine::Sound::id() const
{
	return _id;
}

double TEngine::Sound::getPos() const
{
	if (_id != 0)
		return BASS_ChannelBytes2Seconds(_id, BASS_ChannelGetPosition(_id, BASS_POS_BYTE));
	return 0;
}

void TEngine::Sound::setPos(double pos) const
{
	if (_id != 0)
		BASS_ChannelSetPosition(_id, BASS_ChannelSeconds2Bytes(_id, pos), BASS_POS_BYTE);
}

double TEngine::Sound::length() const
{
	if (_id != 1)
		BASS_ChannelBytes2Seconds(_id, BASS_ChannelGetLength(_id, BASS_POS_BYTE));
	return 0;
}

void TEngine::Sound::play(bool destroyAtEnd, bool loop)
{
	Audio::sounds.push_back(this);
	this->loop = loop;
	this->destroyAtEnd = destroyAtEnd;

	bool status = BASS_ChannelPlay(_id, true);
	if (!status)
		Console::print(std::format("TEngine::Audio::Sound::play(): BASS Error Code:{}\n", BASS_ErrorGetCode()));
}

void TEngine::Sound::pause() const
{
	BASS_ChannelPause(_id);
}

void TEngine::Sound::resume() const
{
	BASS_ChannelPlay(_id, false);
}

void TEngine::Sound::update()
{
	if (_id == 0) return;

	BASS_ChannelSetAttribute(_id, BASS_ATTRIB_VOL, volume * Audio::globalVolume);
	BASS_ChannelSetAttribute(_id, BASS_ATTRIB_PAN, pan + Audio::globalPan);
}

void TEngine::Sound::endCallback(HSYNC handle, DWORD channel, DWORD data, void* user)
{
	if (user == nullptr) return;

	Sound* self = (Sound*)user;

	if (self->_id == 0) return;
	if (!self->loop && self->destroyAtEnd)
		self->destroy();
	else if (self->loop)
		self->play(self->destroyAtEnd, self->loop);
}

void TEngine::Sound::destroy(bool removeFromList)
{
	BASS_ChannelPause(_id);
	_id = 0;
	if (removeFromList)
		VECTOR_REMOVE(Audio::sounds, this);
}

bool TEngine::Sound::isStopped() const
{
	return BASS_ChannelIsActive(_id) == 0;
}

bool TEngine::Sound::isPlaying() const
{
	return BASS_ChannelIsActive(_id) == 1;
}

bool TEngine::Sound::isStalled() const
{
	return BASS_ChannelIsActive(_id) == 2;
}

bool TEngine::Sound::isPaused() const
{
	return BASS_ChannelIsActive(_id) == 3;
}
