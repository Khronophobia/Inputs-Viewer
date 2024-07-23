#pragma once

#define GEODE_NS_IV_BEGIN namespace inputs_viewer {
#define GEODE_NS_IV_END }

#if defined(NDEBUG) && !defined(GEODE_ASSERT_FORCE_ENABLE)
    #define GEODE_ASSERT(cond, msg) ((void)0)
    #define GEODE_ASSERT_FMT(cond, fmtstring, ...) ((void)0)
#else
    #define GEODE_ASSERT(cond, msg) \
        do { \
            if (!(cond)) { \
                geode::utils::terminate("Assertion failed at " __FILE__ ", line " GEODE_STR(__LINE__) ": " msg); \
            } \
        } while (0)
    #define GEODE_ASSERT_FMT(cond, fmtstr, ...) \
        do { \
            if (!(cond)) { \
                geode::utils::terminate( \
                    "Assertion failed at " __FILE__ ", line " GEODE_STR(__LINE__) ": " + \
                    []<typename... Args>(Args&&... args) { \
                        return fmt::format(fmtstr, geode::log::impl::wrapCocosObj(std::forward<Args>(args))...); \
                    }(__VA_ARGS__) \
                ); \
            } \
        } while (0)
#endif