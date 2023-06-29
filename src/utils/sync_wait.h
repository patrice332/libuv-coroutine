#pragma once

#include "src/utils/sync_wait_task.h"

namespace lib_uv_coro::utils {

template <typename Task>
void sync_wait(Task&& task) {
  fire_once_event event;
  auto wait_task = make_sync_wait_task(task);
  wait_task.run(event);
  event.wait();
}

}  // namespace lib_uv_coro::utils