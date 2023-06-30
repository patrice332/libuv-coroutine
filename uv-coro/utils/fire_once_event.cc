#include "uv-coro/utils/fire_once_event.h"

namespace lib_uv_coro::utils {

void FireOnceEvent::Set() {
  flag_.test_and_set();
  flag_.notify_all();
}

void FireOnceEvent::Wait() { flag_.wait(false); }

}  // namespace lib_uv_coro::utils