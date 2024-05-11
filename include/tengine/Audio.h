#pragma once

#include "../bass/bass.h"
#include "../bass/bass_fx.h"

#include "BasicIncludes.h"

namespace TEngine
{
	class Sound;
	class Audio
	{
	public:
		inline static float globalVolume = 1.f;
		inline static float globalPan = 0.f;

		inline static std::vector<Sound*> sounds;
		inline static std::unordered_map<std::string, HSAMPLE> samples;

		static void init();
		static void update();
		static void destroy();
	};
	class Sound
	{
	private:
		HCHANNEL _id = 0;
		HSAMPLE _sampleId = 0;
		double _length = 0.0;

		static void CALLBACK endCallback(HSYNC handle, DWORD channel, DWORD data, void* user);

		friend class Audio;
	public:
		float volume = 1.f;
		float pan = 0.f;
		bool loop = false;
		bool destroyAtEnd = true;

		int id() const;
		double length() const;
		double getPos() const;
		void setPos(double pos) const;
		bool isStopped() const;
		bool isPlaying() const;
		bool isStalled() const;
		bool isPaused() const;

		Sound(const std::string& path, float volume = 1.f, float pan = 0.f);
		void update();
		void destroy(bool removeFromList = true);
		void play(bool destroyAtEnd = true, bool loop = false);
		void pause() const;
		void resume() const;
	};
}
