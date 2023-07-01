#include "uv-coro/utils/sync_wait_task.h"

#include "uv-coro/utils/fire_once_event.h"

namespace uv_coro::utils {

void SyncWaitTaskPromise::Awaiter::await_suspend(
    std::coroutine_handle<SyncWaitTaskPromise> coro) noexcept {
  FireOnceEvent* const event = coro.promise().event_;
  if (event != nullptr) {
    event->Set();
  }
}

bool SyncWaitTaskPromise::Awaiter::await_ready() noexcept { return false; }
void SyncWaitTaskPromise::Awaiter::await_resume() noexcept {}

std::suspend_always SyncWaitTaskPromise::initial_suspend() noexcept {
  return {};
}

SyncWaitTaskPromise::Awaiter SyncWaitTaskPromise::final_suspend() noexcept {
  return {};
}

SyncWaitTask SyncWaitTaskPromise::get_return_object() noexcept {
  return SyncWaitTask{
      std::coroutine_handle<SyncWaitTaskPromise>::from_promise(*this)};
}

void SyncWaitTaskPromise::unhandled_exception() noexcept {
  std::exit(EXIT_FAILURE);
}

SyncWaitTask::SyncWaitTask(std::coroutine_handle<SyncWaitTaskPromise> coro)
    : handle_(coro) {}

SyncWaitTask::~SyncWaitTask() {
  if (handle_) {
    handle_.destroy();
  }
}

void SyncWaitTask::Run(FireOnceEvent& event) {
  handle_.promise().event_ = &event;
  handle_.resume();
}

}  // namespace uv_coro::utils