#pragma once

#include <atomic>
#include <coroutine>
#include <cstdlib>

#include "src/utils/fire_once_event.h"

namespace lib_uv_coro::utils {

struct sync_wait_task_promise;

// sync_wait_task is a utility struct to allow you to wait on an async task in a
// sync context. You should not be using it directly. Use sync_wait(task t);
struct [[nodiscard]] sync_wait_task {
 public:
  using promise_type = sync_wait_task_promise;

  explicit sync_wait_task(std::coroutine_handle<sync_wait_task_promise> coro);
  sync_wait_task(const sync_wait_task& o) = delete;
  sync_wait_task& operator=(const sync_wait_task& o) = delete;
  sync_wait_task(sync_wait_task&& o) = delete;
  sync_wait_task& operator=(sync_wait_task&& o) = delete;
  ~sync_wait_task();

  void run(fire_once_event& event);

 private:
  std::coroutine_handle<sync_wait_task_promise> m_handle;
};

// Promise of the wait task
struct sync_wait_task_promise {
 public:
  [[nodiscard]] static std::suspend_always initial_suspend() noexcept;

  struct awaiter {
    static bool await_ready() noexcept;

    static void await_suspend(
        std::coroutine_handle<sync_wait_task_promise> coro) noexcept;

    void await_resume() noexcept;
  };

  [[nodiscard]] static awaiter final_suspend() noexcept;

  sync_wait_task get_return_object() noexcept;

  static void unhandled_exception() noexcept;

 private:
  friend struct sync_wait_task;
  fire_once_event* m_event = nullptr;
};

// Create a sync_wait_task out of an awaitable object
template <typename Task>
sync_wait_task make_sync_wait_task(Task&& task) {
  co_await task;
}

}  // namespace lib_uv_coro::utils