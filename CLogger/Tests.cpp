#include "Logger/logger.hpp"


int main()
{
	CLOG::Logger::Initialize(CLOG::Colors::Color(231, 31, 231));


	CLOG::Logger::Log(CLOG::Logger::LogType_INFO, "Wassup");

}




