#include <CLOG/logger.hpp>

int main()
{
	CLOG::Logger::Initialize(CLOG::Colors::Color(231, 31, 231), CLOG::Settings::LoggerOptions_NoDate);

	CLOG::Logger::Info("This is Information!");
	CLOG::Logger::Warn("This is a Warning!");
	CLOG::Logger::Error("This is an Error!");

	CLOG::Logger::UpdateColor(CLOG::Logger::LogType_WARN, CLOG::Colors::Color(255, 215, 0));

	CLOG::Logger::Warn("This is a Warning!");

	CLOG::Logger::UpdateColor(CLOG::Logger::LogType_INFO, CLOG::Colors::Color(31, 231, 231));

	CLOG::Logger::Info("This is Information!");
}