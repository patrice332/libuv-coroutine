#pragma once

#include <atomic>

namespace lib_uv_coro::utils {

// Wrapper around atomic flags
struct FireOnceEvent {
 public:
  void Set();
  void Wait();

 private:
  std::atomic_flag flag_;
};

}  // namespace lib_uv_coro::utils