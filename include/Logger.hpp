#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <chrono>
#include <iostream>
#include <string>
#include <sstream> 
#include <iomanip>

std::string GetDateAndTime();

#define LOG(...) Logger::Log(__VA_ARGS__)
#define LOG_(...) Logger::Log_(__VA_ARGS__)
#define ERR(...) Logger::Err(__VA_ARGS__)


class Logger
{
private:

public:
	template <typename T, typename... Args>
	static void Log(const T& msg, const Args&... args)
	{
 		std::string timestamp = GetDateAndTime();
		std::cout << "LOG::" << timestamp << ": " << msg;
		((std::cout << " " << args), ...);
		std::cout << std::endl;
	}

	template <typename T, typename... Args>
	static void Log_(const T& msg, const Args&... args) // log without timestamp
	{
		std::cout << "LOG:: "  << msg;
		((std::cout << " " << args), ...);
		std::cout << std::endl;
	}


	static void Err(const std::string& err)
    {
	    std::cerr << "ERROR:: " << err << std::endl;
    }   
	static void Err(const std::string& err, const char* errMsg)
    {
	    std::cerr << "ERROR:: " << err << " " << errMsg << std::endl;
    }
	static void Err(const std::string& err, const std::string errMsg)
    {
	    std::cerr << "ERROR:: " << err << " " << errMsg << std::endl;
    }

};





#endif // end logger