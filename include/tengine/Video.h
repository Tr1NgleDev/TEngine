#pragma once

#include "Sprite.h"


extern "C" {
#include "../ffmpeg/libavcodec/avcodec.h"
#include "../ffmpeg/libavformat/avformat.h"
#include "../ffmpeg/libavutil/imgutils.h"
#include "../ffmpeg/libavutil/avutil.h"
#include "../ffmpeg/libswscale/swscale.h"
}

namespace TEngine
{
	class Video : public Sprite
	{
	private:
		int64_t _prevFrame = -1;
		AVRational _framerate;
		int64_t _framesCount;
		int64_t _bitRate;
		struct
		{
			AVFormatContext* _formatCtx = nullptr;
			AVCodecContext* _codecCtx = nullptr;
			AVFrame* _frame = nullptr;
			SwsContext* _convertCtx = nullptr;
			AVPacket* _packet;
			const AVCodec* _codec;
			int _videoStreamInd = -1;
			int _nextFrameInd = 0;
			int uint8_tsRemaining = 0;
			AVStream* _videoStream;
		} data;

		uint8_t* imageData;

		uint8_t* decodeVideoFrame(uint8_t* data);
		uint8_t* readVideoFrame(int frameInd = -1, uint8_t* bitmap = nullptr);
		static int stride(int width, int height, int byteDepth);
	public:
		double time = 0.0;
		double speed = 1.0;
		int64_t getFrame() const;
		bool playing = false;

		Video(float x, float y, const std::string& videoPath);
		void play();
		void pause();
		void resume();
		void render(double deltaTime) override;
		void destroy() override;
	};
}
