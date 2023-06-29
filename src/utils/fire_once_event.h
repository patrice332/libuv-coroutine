#pragma once

#include <atomic>

namespace lib_uv_coro::utils {

// Wrapper around atomic flags
struct fire_once_event {
 public:
  void set();
  void wait();

 private:
  std::atomic_flag m_flag;
};

}  // namespace lib_uv_coro::utils