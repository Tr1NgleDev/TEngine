#pragma once

#include <string>
#include <sstream> 

namespace TEngine
{
	enum CColor
	{
		BLACK = 30,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE
	};
	enum CVariant
	{
		NORMAL = 0,
		BRIGHT,
		DIM,
		ITALIC,
		UNDERLINE,
		BLINKING,
		INVERSE = 7,
		HIDDEN,
		STRIKETHROUGH
	};
	struct CMode
	{
		CColor color;
		CVariant variant;

		CMode(CColor color = WHITE, CVariant variant = NORMAL) : color(color), variant(variant) {}
	};
}

// some std extensions
namespace std
{
	inline string to_string(const TEngine::CMode& mode) noexcept
	{
		stringstream ss;
		ss << "\x1B[";
		ss << mode.variant << ';' << mode.color << 'm';
		return ss.str();
	}
	inline ostream& operator<<(ostream& os, const TEngine::CMode& mode)
	{
		os << to_string(mode);
		return os;
	}
} 

namespace TEngine
{
	class Console
	{
	private:
		static bool _open;
		static bool _initialized;
	public:
		// Initializes and opens a console (WINDOWS ONLY)
		static void init();
		// Closes console (WINDOWS ONLY)
		static void close();
		// Opens console (WINDOWS ONLY)
		static void open();
		template <typename... Args>
		inline static void print(Args const&... args)
		{
			std::stringstream s;
			s << CMode();
			(s << ... << args);
			s << CMode();
			printf(s.str().c_str());
		}
		template <typename... Args>
		inline static void printLine(Args const&... args)
		{
			std::stringstream s;
			s << CMode();
			(s << ... << args);
			s << '\n';
			s << CMode();
			printf(s.str().c_str());
		}
		// Clears console output (not really. but. it works. ig)
		static void clear();

		static bool isOpen();
		static bool isInitialized();
	};
}
