#pragma once

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <functional>
#include <string_view>

namespace jps::Logging
{
/// Log level
enum class Level : int32_t { Debug = 0, Info = 1, Warning = 2, Error = 3 };
/// Type for log callbacks
using LogCallback = std::function<void(std::string_view)>;

/// This function is not supposed to be called directly from library code, use LOG_DEBUG(...)
/// instead.
void Debug(std::string_view msg);
/// This function is not supposed to be called directly from library code, use LOG_INFO(...)
/// instead.
void Info(std::string_view msg);
/// This function is not supposed to be called directly from library code, use LOG_WARNING(...)
/// instead.
void Warning(std::string_view msg);
/// This function is not supposed to be called directly from library code, use LOG_ERROR(...)
/// instead.
void Error(std::string_view msg);
/// Inject callbacks to receive log messages for the respective log level.
/// If not explicitly set all logging calls are effectively no-ops.
/// Note: To unset the log callback call this function with an empty LogCallback
///       e.g. SetCallback(Logging::Level::Debug, Logging::LogCallback{});
/// @param log_level to receive messages for
/// @param callback function to call with log message
void SetCallback(Level log_level, LogCallback callback);

} // namespace jps::Logging

// Convenience macros to add log messages with compile time check to validate
// used format string.I have not been able to get the FMT_STRING macro to work
// in a variadic template so I used variadic macros which now requires to
// silence a modernization warning. Further the macro relies on the clang / gcc
// no standard extension to use ##__VA_ARGS to solve the issue of trailing ','
// if the var args are empty. MSVC eliminates the trailing ',' silently but
// errors out on the clang / gcc variant.

#ifdef _MSC_VER
// NOLINTNEXTLINE
#define __LOG(Level, FormatString, ...)                                                            \
    Logging::Level(fmt::format(FMT_STRING(FormatString), __VA_ARGS__))
// NOLINTNEXTLINE
#define LOG_DEBUG(FormatString, ...) __LOG(Debug, FormatString, __VA_ARGS__)
// NOLINTNEXTLINE
#define LOG_INFO(FormatString, ...) __LOG(Info, FormatString, __VA_ARGS__)
// NOLINTNEXTLINE
#define LOG_WARNING(FormatString, ...) __LOG(Warning, FormatString, __VA_ARGS__)
// NOLINTNEXTLINE
#define LOG_ERROR(FormatString, ...) __LOG(Error, FormatString, __VA_ARGS__)
#else
// NOLINTNEXTLINE
#define __LOG(Level, FormatString, ...)                                                            \
    Logging::Level(fmt::format(FMT_STRING(FormatString), ##__VA_ARGS__))
// NOLINTNEXTLINE
#define LOG_DEBUG(FormatString, ...) __LOG(Debug, FormatString, ##__VA_ARGS__)
// NOLINTNEXTLINE
#define LOG_INFO(FormatString, ...) __LOG(Info, FormatString, ##__VA_ARGS__)
// NOLINTNEXTLINE
#define LOG_WARNING(FormatString, ...) __LOG(Warning, FormatString, ##__VA_ARGS__)
// NOLINTNEXTLINE
#define LOG_ERROR(FormatString, ...) __LOG(Error, FormatString, ##__VA_ARGS__)
#endif
