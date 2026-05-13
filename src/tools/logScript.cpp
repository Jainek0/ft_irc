
#include "../header/irc.hpp"

std::string getTime()
{
    std::time_t now = std::time(NULL);
    std::tm* t = std::localtime(&now);

    std::ostringstream oss;
    oss << std::setfill('0')
        << (t->tm_year + 1900) << "-"
        << std::setw(2) << (t->tm_mon + 1) << "-"
        << std::setw(2) << t->tm_mday << " "
        << std::setw(2) << t->tm_hour << ":"
        << std::setw(2) << t->tm_min << ":"
        << std::setw(2) << t->tm_sec;

    return oss.str();
}

void logScript(const std::string& str)
{
    static std::ofstream logFile("irc.log", std::ios::app);

    if (!logFile)
    {
        std::cerr << "LOG ERROR: fallback to stderr\n";
        std::cerr << "[" << getTime() << "] " << str << std::endl;
        return;
    }

    logFile << "[" << getTime() << "] " << str << std::endl;
}