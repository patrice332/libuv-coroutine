#include "src/utils/fire_once_event.h"

namespace lib_uv_coro::utils {

void fire_once_event::set() {
  m_flag.test_and_set();
  m_flag.notify_all();
}

void fire_once_event::wait() { m_flag.wait(false); }

}  // namespace lib_uv_coro::utils