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
    std::array<Logging::LogCallback, 4> callbacks{};

public:
    static Log & instance()
    {
        static Log log{};
        return log;
    }

    void set_callback(Logging::Level level, Logging::LogCallback callback)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        callbacks[to_underlying(level)] = std::move(callback);
    }

    void msg(Logging::Level level, std::string_view msg)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        if(auto & cb = callbacks[to_underlying(level)]; cb) {
            cb(msg);
        }
    }
};

namespace Logging
{
void Debug(std::string_view msg)
{
    Log::instance().msg(Level::Debug, msg);
}

void Info(std::string_view msg)
{
    Log::instance().msg(Level::Info, msg);
}

void Warning(std::string_view msg)
{
    Log::instance().msg(Level::Warning, msg);
}

void Error(std::string_view msg)
{
    Log::instance().msg(Level::Error, msg);
}

void SetCallback(Level level, LogCallback callback)
{
    Log::instance().set_callback(level, std::move(callback));
}
} // namespace Logging
} // namespace jps
