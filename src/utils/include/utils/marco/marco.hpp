#pragma once

#define CALIB_MARCO_MAKE_SINGLETON(className)                                                                          \
  public:                                                                                                              \
    className(className const &) = delete;                                                                             \
    className &operator=(className const &) = delete;                                                                  \
    static className &instance()                                                                                       \
    {                                                                                                                  \
        static className instance;                                                                                     \
        return instance;                                                                                               \
    }                                                                                                                  \
                                                                                                                       \
  private:                                                                                                             \
    className() = default;                                                                                             \
    ~className() = default;

#include <memory>
#define CALIB_MARCO_MAKE_SMART_PTR(className)                                                                          \
  public:                                                                                                              \
    using Ptr = std::shared_ptr<className>;                                                                            \
    using UPtr = std::unique_ptr<className>;

// Make exception class marco
//
#include <exception>
#define CALIB_MARCO_MAKE_EXCEPTION(excepName)                                                                          \
    struct DetectorException : public std::exception                                                                   \
    {                                                                                                                  \
        const char *what() const noexcept                                                                              \
        {                                                                                                              \
            return #excepName;                                                                                         \
        }                                                                                                              \
    };

