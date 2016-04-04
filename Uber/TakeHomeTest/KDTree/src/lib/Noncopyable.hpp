#ifndef _UBER_LIB_NONCOPYABLE_H_
#define _UBER_LIB_NONCOPYABLE_H_
namespace uber {
struct Noncopyable {
  Noncopyable &operator=(const Noncopyable &) = delete;
  Noncopyable(const Noncopyable &) = delete;
  Noncopyable() = default;
};
}
#endif //_UBER_LIB_NONCOPYABLE_H_
