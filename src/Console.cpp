#include "../include/tengine/Console.h"

#ifdef _WIN32
#include <windows.h>
#endif

bool TEngine::Console::_open = false;
bool TEngine::Console::_initialized = false;

void TEngine::Console::init()
{
#ifdef _WIN32
	AllocConsole();
	_open = true;

	if (_initialized) return;

	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);

	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT);

	_initialized = true;
#endif
}

void TEngine::Console::close()
{
#ifdef _WIN32
	if (!_open) return;

	FreeConsole();
	_open = false;
#endif
}

void TEngine::Console::open()
{
#ifdef _WIN32
	if (_open) return;

	AllocConsole();
	_open = true;
#endif
}

void TEngine::Console::clear()
{
	printf("\x1B[2J\x1B[H");
}

bool TEngine::Console::isOpen()
{
	return _open;
}

bool TEngine::Console::isInitialized()
{
	return _initialized;
}
