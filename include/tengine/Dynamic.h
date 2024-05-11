#pragma once

namespace TEngine
{
	enum DynamicType
	{
		C,
		I,
		L,
		B,
		F,
		D,
		S
	};
	struct Dynamic
	{
		union
		{
			int i;
			long long ll;
			bool b;
			float f;
			double d;
			char c;
			std::string str;
		};
		DynamicType type;

		Dynamic(const Dynamic& other)
		{
			type = other.type;

			switch (type)
			{
			case DynamicType::C:
				c = other.c;
				break;
			case DynamicType::I:
				i = other.i;
				break;
			case DynamicType::L:
				ll = other.ll;
				break;
			case DynamicType::B:
				b = other.b;
				break;
			case DynamicType::F:
				f = other.f;
				break;
			case DynamicType::D:
				d = other.d;
				break;
			case DynamicType::S:
				str = other.str;
				break;
			}
		}

		Dynamic(Dynamic&& other) noexcept
		{
			type = other.type;

			switch (type)
			{
			case DynamicType::C:
				c = std::move(other.c);
				break;
			case DynamicType::I:
				i = std::move(other.i);
				break;
			case DynamicType::L:
				ll = std::move(other.ll);
				break;
			case DynamicType::B:
				b = std::move(other.b);
				break;
			case DynamicType::F:
				f = std::move(other.f);
				break;
			case DynamicType::D:
				d = std::move(other.d);
				break;
			case DynamicType::S:
				str = std::move(other.str);
				break;
			}

			other.type = DynamicType::C;
		}

		~Dynamic()
		{
			switch (type)
			{
			case DynamicType::C:
			case DynamicType::I:
			case DynamicType::L:
			case DynamicType::B:
			case DynamicType::F:
			case DynamicType::D:
				break;
			case DynamicType::S:
				str.~basic_string();
				break;
			}
		}
		Dynamic(char v) : c{ v } { type = C; }
		Dynamic(int v) : i{ v } { type = I; }
		Dynamic(long long v) : ll{  v } { type = L; }
		Dynamic(bool v) : b{ v } { type = B; }
		Dynamic(float v) : f{ v } { type = F; }
		Dynamic(double v) : d{ v } { type = D; }
		Dynamic(const std::string& v) : str{ v } { type = S; }

		explicit operator char() const
		{
			return c;
		}
		explicit operator int() const
		{
			return i;
		}
		explicit operator long long() const
		{
			return ll;
		}
		explicit operator bool() const
		{
			return b;
		}
		explicit operator float() const
		{
			return f;
		}
		explicit operator double() const
		{
			return d;
		}
		explicit operator std::string() const
		{
			return str;
		}

		char typeChar() const
		{
			switch (type) {
			case C:
				return 'c';
			case I:
				return 'i';
			case L:
				return 'l';
			case B:
				return 'b';
			case F:
				return 'f';
			case D:
				return 'd';
			case S:
				return 's';
			default: return 'b';
			}
		}
		static Dynamic fromString(const std::string& str)
		{
			std::string a = str.substr(1);
			char c = str[0];

			if (c == 'b') return a == "True";
			if (c == 'i') return std::stoi(a);
			if (c == 'f') return std::stof(a);
			if (c == 'd') return std::stod(a);
			if (c == 'c') return a[0];
			if (c == 's') return a;
			if (c == 'l') return std::stoll(a);
			return 0;
		}
		static std::string toString(const Dynamic& obj)
		{
			char typeChar = obj.typeChar();

			switch(obj.type)
			{
			case C:
				return std::format("{}{}", typeChar, obj.c);
			case I:
				return std::format("{}{}", typeChar, std::to_string(obj.i));
			case L:
				return std::format("{}{}", typeChar, std::to_string(obj.ll));
			case B:
				return std::format("{}{}", typeChar, obj.b ? "True" : "False");
			case F:
				return std::format("{}{}", typeChar, std::to_string(obj.f));
			case D:
				return std::format("{}{}", typeChar, std::to_string(obj.d));
			case S:
				return std::format("{}{}", typeChar, obj.str);
			default: return std::format("{}{}", typeChar, obj.b ? "True" : "False");
			}
		}
		Dynamic& operator=(const Dynamic& other)
		{
			if (this == &other)
			{
				return *this;
			}

			type = other.type;

			switch (type)
			{
			case DynamicType::C:
				c = other.c;
				break;
			case DynamicType::I:
				i = other.i;
				break;
			case DynamicType::L:
				ll = other.ll;
				break;
			case DynamicType::B:
				b = other.b;
				break;
			case DynamicType::F:
				f = other.f;
				break;
			case DynamicType::D:
				d = other.d;
				break;
			case DynamicType::S:
				str = other.str;
				break;
			}

			return *this;
		}

		Dynamic& operator=(Dynamic&& other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}

			type = other.type;

			switch (type)
			{
			case DynamicType::C:
				c = std::move(other.c);
				break;
			case DynamicType::I:
				i = std::move(other.i);
				break;
			case DynamicType::L:
				ll = std::move(other.ll);
				break;
			case DynamicType::B:
				b = std::move(other.b);
				break;
			case DynamicType::F:
				f = std::move(other.f);
				break;
			case DynamicType::D:
				d = std::move(other.d);
				break;
			case DynamicType::S:
				str = std::move(other.str);
				break;
			}

			other.type = DynamicType::B;

			return *this;
		}

	};

}
