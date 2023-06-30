#pragma once

#include <atomic>
#include <coroutine>
#include <cstdlib>

#include "src/utils/fire_once_event.h"

namespace lib_uv_coro::utils {

struct SyncWaitTaskPromise;

// sync_wait_task is a utility struct to allow you to wait on an async task in a
// sync context. You should not be using it directly. Use sync_wait(task t);
struct [[nodiscard]] SyncWaitTask {
 public:
  using promise_type = SyncWaitTaskPromise;

  explicit SyncWaitTask(std::coroutine_handle<SyncWaitTaskPromise> coro);
  SyncWaitTask(const SyncWaitTask& o) = delete;
  SyncWaitTask& operator=(const SyncWaitTask& o) = delete;
  SyncWaitTask(SyncWaitTask&& o) = delete;
  SyncWaitTask& operator=(SyncWaitTask&& o) = delete;
  ~SyncWaitTask();

  void Run(FireOnceEvent& event);

 private:
  std::coroutine_handle<SyncWaitTaskPromise> handle_;
};

// Promise of the wait task
struct SyncWaitTaskPromise {
 public:
  [[nodiscard]] static std::suspend_always initial_suspend() noexcept;

  struct Awaiter {
    static bool await_ready() noexcept;

    static void await_suspend(
        std::coroutine_handle<SyncWaitTaskPromise> coro) noexcept;

    void await_resume() noexcept;
  };

  [[nodiscard]] static Awaiter final_suspend() noexcept;

  SyncWaitTask get_return_object() noexcept;

  static void unhandled_exception() noexcept;

 private:
  friend struct SyncWaitTask;
  FireOnceEvent* event_ = nullptr;
};

// Create a sync_wait_task out of an awaitable object
template <typename Task>
SyncWaitTask MakeSyncWaitTask(Task&& task) {
  co_await task;
}

}  // namespace lib_uv_coro::utils