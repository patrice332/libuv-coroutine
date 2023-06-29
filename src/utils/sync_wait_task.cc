#include "src/utils/sync_wait_task.h"

namespace lib_uv_coro::utils {

void sync_wait_task_promise::awaiter::await_suspend(
    std::coroutine_handle<sync_wait_task_promise> coro) noexcept {
  fire_once_event* const event = coro.promise().m_event;
  if (event != nullptr) {
    event->set();
  }
}

bool sync_wait_task_promise::awaiter::await_ready() noexcept { return false; }
void sync_wait_task_promise::awaiter::await_resume() noexcept {}

std::suspend_always sync_wait_task_promise::initial_suspend() noexcept {
  return {};
}

sync_wait_task_promise::awaiter
sync_wait_task_promise::final_suspend() noexcept {
  return {};
}

sync_wait_task sync_wait_task_promise::get_return_object() noexcept {
  return sync_wait_task{
      std::coroutine_handle<sync_wait_task_promise>::from_promise(*this)};
}

void sync_wait_task_promise::unhandled_exception() noexcept {
  std::exit(EXIT_FAILURE);
}

sync_wait_task::sync_wait_task(
    std::coroutine_handle<sync_wait_task_promise> coro)
    : m_handle(coro) {}

sync_wait_task::~sync_wait_task() {
  if (m_handle) {
    m_handle.destroy();
  }
}

void sync_wait_task::run(fire_once_event& event) {
  m_handle.promise().m_event = &event;
  m_handle.resume();
}

}  // namespace lib_uv_coro::utils