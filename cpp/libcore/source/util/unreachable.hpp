#ifdef __GNUC__
[[noreturn]] inline __attribute__((always_inline)) void unreachable()
{
    __builtin_unreachable();
}
#elif defined(_MSC_VER)
[[noreturn]] __forceinline void unreachable()
{
    __assume(false);
}
#else
#error your compiler is unsupported. Only Clang, GCC and MSVC are supported.
#endif
