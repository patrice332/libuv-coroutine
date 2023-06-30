#pragma once

#include "uv-coro/utils/fire_once_event.h"
#include "uv-coro/utils/sync_wait_task.h"

namespace lib_uv_coro::utils {

template <typename Task>
void SyncWait(Task&& task) {
  FireOnceEvent event;
  auto wait_task = MakeSyncWaitTask(task);
  wait_task.Run(event);
  event.Wait();
}

}  // namespace lib_uv_coro::utils