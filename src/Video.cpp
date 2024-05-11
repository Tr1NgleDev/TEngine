#include <iostream>
#include "../include/tengine/Video.h"
#include "../include/tengine/Shader.h"
#include "../include/tengine/Texture.h"

AVPixelFormat correct_for_deprecated_pixel_format(AVPixelFormat pix_fmt) {
	switch (pix_fmt) {
	case AV_PIX_FMT_YUVJ420P: return AV_PIX_FMT_YUV420P;
	case AV_PIX_FMT_YUVJ422P: return AV_PIX_FMT_YUV422P;
	case AV_PIX_FMT_YUVJ444P: return AV_PIX_FMT_YUV444P;
	case AV_PIX_FMT_YUVJ440P: return AV_PIX_FMT_YUV440P;
	default:                  return pix_fmt;
	}
}

int64_t TEngine::Video::getFrame() const
{
	return (int64_t)max(time * av_q2d(_framerate), 0.0);
}

TEngine::Video::Video(float x, float y, const std::string& videoPath)
{
	if (!IO::File::exists(videoPath))
		return;
	// sprite shit
	setPos(x, y);
	this->color = Color::White();
	shader = Shader::get(Sprite::shaderName);
	tex = new Texture(Color::White());

	// video shit
	av_register_all();
	data._formatCtx = avformat_alloc_context();
	if (avformat_open_input(&data._formatCtx, videoPath.c_str(), nullptr, nullptr) != 0)
	{
		Console::print(CMode(RED, BLINKING), std::format("TEngine::Video: Couldn't open {}!\n", videoPath));
		return;
	}

	if(avformat_find_stream_info(data._formatCtx, nullptr) != 0)
	{
		Console::print(CMode(RED, BLINKING), std::format("TEngine::Video: Couldn't find stream info in {}!\n", videoPath));
		return;
	}

	for(unsigned int i = 0; i < data._formatCtx->nb_streams; i++)
		if(data._formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			data._videoStreamInd = i;
			break;
		}

	if(data._videoStreamInd == -1)
	{
		Console::print(CMode(RED, BLINKING), std::format("TEngine::Video: Couldn't find video stream in {}!\n", videoPath));
		return;
	}

	data._videoStream = data._formatCtx->streams[data._videoStreamInd];

	const AVCodecParameters* codecParameters = data._formatCtx->streams[data._videoStreamInd]->codecpar;
	data._codec = avcodec_find_decoder(codecParameters->codec_id);
	data._codecCtx = avcodec_alloc_context3(data._codec);
	avcodec_parameters_to_context(data._codecCtx, codecParameters);

	if (avcodec_open2(data._codecCtx, data._codec, nullptr) < 0)
	{
		Console::print(CMode(RED, BLINKING), std::format("TEngine::Video: Couldn't open codec for {}!\n", videoPath));
		return;
	}

	_framerate = data._formatCtx->streams[data._videoStreamInd]->r_frame_rate;
	_framesCount = data._formatCtx->streams[data._videoStreamInd]->nb_frames;
	tex->id = 0;
	tex->w = data._codecCtx->width;
	tex->h = data._codecCtx->height;
	tex->channels = 3;

	glGenTextures(1, &tex->id);
	glBindTexture(GL_TEXTURE_2D, tex->id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->w, tex->h, 0, GL_BGR, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	tex->setAntialiasing(false);

	data._convertCtx = sws_getContext(tex->w, tex->h, correct_for_deprecated_pixel_format(data._codecCtx->pix_fmt), tex->w, tex->h, AV_PIX_FMT_BGR24, SWS_BICUBIC, nullptr, nullptr, nullptr);
	data._frame = av_frame_alloc();
	_bitRate = data._codecCtx->bit_rate;

	data._packet = av_packet_alloc();
	av_init_packet(data._packet);
	data._packet->data = nullptr;

	imageData = (uint8_t*)malloc(3 * tex->w * tex->h);
}

void TEngine::Video::render(double deltaTime)
{
	if (playing)
		time += deltaTime * speed;

	const int64_t frame = getFrame();

	if (frame != _prevFrame && frame < _framesCount)
	{
		for (int i = _prevFrame + 1; i <= frame; i++)
			readVideoFrame(i, imageData);

		tex->use();
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, tex->w, tex->h, GL_BGR, GL_UNSIGNED_BYTE, imageData);
		Texture::unbind();
		_prevFrame = frame;
	}

	Sprite::render(deltaTime);
}

void TEngine::Video::play()
{
	playing = true;
	time = 0.;
}

void TEngine::Video::pause()
{
	playing = false;
}

void TEngine::Video::resume()
{
	playing = true;
}

void TEngine::Video::destroy()
{
	if (data._frame != nullptr)
		av_free(data._frame);
	if (data._codecCtx != nullptr)
		avcodec_close(data._codecCtx);
	if (data._formatCtx != nullptr)
	{
		avformat_close_input(&data._formatCtx);
	}
	if (data._convertCtx != nullptr)
		sws_freeContext(data._convertCtx);
	if (data._packet->data != nullptr)
	{
		av_packet_unref(data._packet);
		av_free_packet(data._packet);
	}
	data._frame = nullptr;
	data._codecCtx = nullptr;
	data._formatCtx = nullptr;
	data._convertCtx = nullptr;
	data._packet->data = nullptr;
	glDeleteTextures(1, &tex->id);
	free(imageData);
}

int TEngine::Video::stride(int width, int height, int byteDepth)
{
	int stride = 4 * ((width * byteDepth + 3) / 4);
	return stride;
}

uint8_t* TEngine::Video::decodeVideoFrame(uint8_t* data)
{
	if(data == nullptr)
		data = (uint8_t*)malloc(3 * tex->w * tex->h);

	uint8_t* srcData[4] = { data,
		nullptr, nullptr, nullptr };
	int srcLinesize[4] = { stride(tex->w, tex->h, 3), 0, 0, 0};

	sws_scale(this->data._convertCtx, this->data._frame->data, this->data._frame->linesize, 0, tex->h, srcData, srcLinesize);

	return data;
}

int64_t FrameToPTS(AVStream* stream, int frame)
{
	return (int64_t(frame) * stream->r_frame_rate.den * stream->time_base.den)
		/ (int64_t(stream->r_frame_rate.num) * stream->time_base.num);
}

uint8_t* TEngine::Video::readVideoFrame(int frameInd, uint8_t* bitmap)
{
	if (frameInd == -1)
		frameInd = data._nextFrameInd;

	int frameFinished;
	int uint8_tsDecoded;
	bool exit = false;
	bool needsToSeek = false;
	
	if(frameInd != data._nextFrameInd)
	{
		needsToSeek = true;
		avcodec_flush_buffers(data._videoStream->codec);
		int error = av_seek_frame(data._formatCtx, data._videoStreamInd, frameInd, AVSEEK_FLAG_FRAME | AVSEEK_FLAG_BACKWARD);
		if (error < 0)
			return bitmap;
	}

	while(true)
	{
		while(data.uint8_tsRemaining > 0) 
		{
			uint8_tsDecoded = avcodec_decode_video2(data._codecCtx, data._frame, &frameFinished, data._packet);

			if (uint8_tsDecoded < 0)
				return bitmap;

			data.uint8_tsRemaining -= uint8_tsDecoded;

			if(frameFinished)
			{
				if(!needsToSeek || data._frame->pts >= FrameToPTS(data._videoStream, frameInd))
				{
					data._nextFrameInd = frameInd + 1;
					return decodeVideoFrame(bitmap);
				}
			}
		}

		do
		{
			if(data._packet->data != nullptr)
			{
				av_packet_unref(data._packet);
				av_free_packet(data._packet);
				data._packet->data = nullptr;
			}

			if(av_read_frame(data._formatCtx, data._packet) < 0)
			{
				exit = true;
				break;
			}
		} while (data._packet->stream_index != data._videoStreamInd);

		if (exit)
			break;

		data.uint8_tsRemaining = data._packet->size;
	}

	uint8_tsDecoded = avcodec_decode_video2(data._codecCtx, data._frame, &frameFinished, data._packet);
	if (data._packet->data != nullptr)
	{
		av_packet_unref(data._packet);
		av_free_packet(data._packet);
		data._packet->data = nullptr;
	}

	if (frameFinished)
		decodeVideoFrame(bitmap);

	return bitmap;
}
