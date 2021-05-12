#include "log.hpp"

#include "enum.hpp"

#include <array>

namespace jps
{
/// Internal class to manage log callbacks.
/// Only a single callback per level can be registered.
/// Any use of this class should be facilitated trough
/// Logging::(Debug,Info,Warning,Error,SetCallback) calls
class Log
{
private:
    std::array<Logging::LogCallback, 4> m_callbacks{};

public:
    static auto instance() -> Log &
    {
        static Log log{};
        return log;
    }

    void setCallback(Logging::Level p_level, Logging::LogCallback p_callback)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        m_callbacks[static_cast<size_t>(toUnderlying(p_level))] = std::move(p_callback);
    }

    void msg(Logging::Level p_level, std::string_view p_msg)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        if(auto & cb = m_callbacks[static_cast<size_t>(toUnderlying(p_level))]; cb) {
            cb(p_msg);
        }
    }
};

namespace Logging
{
void debug(std::string_view p_msg)
{
    Log::instance().msg(Level::Debug, p_msg);
}

void info(std::string_view p_msg)
{
    Log::instance().msg(Level::Info, p_msg);
}

void warning(std::string_view p_msg)
{
    Log::instance().msg(Level::Warning, p_msg);
}

void error(std::string_view p_msg)
{
    Log::instance().msg(Level::Error, p_msg);
}

void setCallback(Level p_level, LogCallback p_callback)
{
    Log::instance().setCallback(p_level, std::move(p_callback));
}
} // namespace Logging
} // namespace jps
