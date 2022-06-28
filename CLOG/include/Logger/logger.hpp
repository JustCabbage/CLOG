// Copyright(c) 2022 Cabbage
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once
#include <iostream>
#include <string>
#include <syncstream>

namespace CLOG
{
	namespace Colors
	{
		struct Color
		{
			const Color() : R(255), G(255), B(255) {}
			const Color(int r, int g, int b) : R(r), G(g), B(b) {}
			int R, G, B = 0;
		};
	}

	namespace Settings
	{
		typedef int LoggerOptions;
		enum LoggerOptions_
		{
			LoggerOptions_Default = 0,
			LoggerOptions_NoTimestamps = (1 << 0),
			LoggerOptions_NoColor = (1 << 1),
			LoggerOptions_NoDate = (1 << 2),
		};

		struct CurrentOptions
		{
			Colors::Color PrimaryColor;
			Colors::Color WarnColor = Colors::Color(231, 231, 31);
			Colors::Color ErrorColor = Colors::Color(231, 31, 31);
			bool Timestamps = true;
			bool UseDate = true;
			bool DrawColor = true;
			bool Initialized = false;
		}Options;
	}

	class ColorUtils
	{
	public:
		static inline std::string ColorToString(const CLOG::Colors::Color& Input)
		{
			return ColorToString(Input.R, Input.G, Input.B);
		}

		static inline std::string ColorToString(unsigned int R, unsigned int G, unsigned int B)
		{
			return std::format("\033[38;2;{};{};{}m", R, G, B);
		}

		static inline std::string Reset()
		{
			return "\033[0;00m";
		}

		static inline std::string ColoredString(const std::string& Input, const CLOG::Colors::Color& OutputColor)
		{
			if (Settings::Options.DrawColor)
			{
				std::string Output = ColorToString(OutputColor) + Input + Reset();
				return Output;
			}
			return Input;
		}
	};

	namespace Logger
	{
		enum LogType_ : int
		{
			LogType_INFO = 0,
			LogType_WARN,
			LogType_ERROR
		};
	}

	namespace Logger
	{
		inline std::string GetTimeStamp(const Colors::Color& TimeColor)
		{
			if (Settings::Options.Timestamps)
			{
				std::string Timestamp;
				time_t Time = time(0);
				struct tm LocalTime;
				localtime_s(&LocalTime, &Time);
				if (Settings::Options.UseDate)
				{
					Timestamp = std::format("{:02}-{:02}-{:02} {:02}:{:02}:{:02}", LocalTime.tm_mon + 1, LocalTime.tm_mday, LocalTime.tm_year % 100, LocalTime.tm_hour, LocalTime.tm_min, LocalTime.tm_sec);
				}
				else
				{
					Timestamp = std::format("{:02}:{:02}:{:02}", LocalTime.tm_hour, LocalTime.tm_min, LocalTime.tm_sec);
				}
				return ColorUtils::ColoredString(std::format("[{}] ", Timestamp), TimeColor);
			}
			return "";
		}

		inline void UpdateColor(LogType_ Type, const Colors::Color& Color)
		{
			switch (Type)
			{
			case LogType_INFO:
				Settings::Options.PrimaryColor = Color;
				break;
			case LogType_WARN:
				Settings::Options.WarnColor = Color;
				break;
			case LogType_ERROR:
				Settings::Options.ErrorColor = Color;
				break;
			}
		}

		inline void Initialize(const Colors::Color& LogColor, Settings::LoggerOptions Options = Settings::LoggerOptions_Default)
		{
			if (!Settings::Options.Initialized) {
				Settings::Options.PrimaryColor = LogColor;
#ifdef _WIN32
				system("cls"); // WINDOWS CMD HAS TO CLEAR CONSOLE FOR ANSI
#endif
				Settings::Options.Timestamps = !(Options & Settings::LoggerOptions_NoTimestamps);
				Settings::Options.DrawColor = !(Options & Settings::LoggerOptions_NoColor);
				Settings::Options.UseDate = !(Options & Settings::LoggerOptions_NoDate);
				Settings::Options.Initialized = true;
			}
		}

		inline void Log(LogType_ Type, const std::string& Message)
		{
			if (Settings::Options.Initialized)
			{
				std::osyncstream safecout(std::cout);
				switch (Type)
				{
				case LogType_INFO:

					safecout << GetTimeStamp(Settings::Options.PrimaryColor) << ColorUtils::ColoredString("[INFO] ", Settings::Options.PrimaryColor) << ColorUtils::ColoredString(Message, Settings::Options.PrimaryColor) << "\n";
					break;
				case LogType_WARN:
					safecout << GetTimeStamp(Settings::Options.WarnColor) << ColorUtils::ColoredString("[WARN] ", Settings::Options.WarnColor) << ColorUtils::ColoredString(Message, Settings::Options.WarnColor) << "\n";
					break;
				case LogType_ERROR:
					safecout << GetTimeStamp(Settings::Options.ErrorColor) << ColorUtils::ColoredString("[ERROR] ", Settings::Options.ErrorColor) << ColorUtils::ColoredString(Message, Settings::Options.ErrorColor) << "\n";
					break;
				}
			}
		}

		inline void Info(const std::string& Message)
		{
			return Log(LogType_INFO, Message);
		}

		inline void Warn(const std::string& Message)
		{
			return Log(LogType_WARN, Message);
		}

		inline void Error(const std::string& Message)
		{
			return Log(LogType_ERROR, Message);
		}
	}
}