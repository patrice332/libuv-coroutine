#pragma once

#include <coroutine>
#include <functional>
#include <optional>

namespace uv_coro {

template <typename T>
class [[nodiscard]] Awaitable {
 public:
  using CallbackType = std::function<void(std::coroutine_handle<> handle,
                                          std::function<void(T)>)>;

  explicit Awaitable(CallbackType callback) : cb_{std::move(callback)} {}
  Awaitable(const Awaitable& obj) = delete;
  Awaitable& operator=(const Awaitable& obj) = delete;
  Awaitable(Awaitable&& obj) noexcept = default;
  Awaitable& operator=(Awaitable&& obj) noexcept = default;
  ~Awaitable() = default;

  // trunk-ignore(clang-tidy/readability-identifier-naming)
  bool await_ready() { return false; }

  // trunk-ignore(clang-tidy/readability-identifier-naming)
  void await_suspend(std::coroutine_handle<> handle) {
    cb_(handle, [this, handle](T val) {
      rv_.emplace(std::move(val));
      handle();
    });
  }

  // trunk-ignore(clang-tidy/readability-identifier-naming)
  T await_resume() { return std::move(rv_.value()); }

 private:
  CallbackType cb_;
  std::optional<T> rv_;
};

template <>
class [[nodiscard]] Awaitable<void> {
 public:
  using CallbackType =
      std::function<void(std::coroutine_handle<>, std::function<void()>)>;

  explicit Awaitable(CallbackType callback) : cb_{std::move(callback)} {}
  Awaitable(const Awaitable& obj) = delete;
  Awaitable& operator=(const Awaitable& obj) = delete;
  Awaitable(Awaitable&& obj) noexcept = default;
  Awaitable& operator=(Awaitable&& obj) noexcept = default;
  ~Awaitable() = default;

  // trunk-ignore(clang-tidy/readability-identifier-naming)
  static constexpr bool await_ready() { return false; }

  // trunk-ignore(clang-tidy/readability-identifier-naming)
  void await_suspend(std::coroutine_handle<> handle) {
    cb_(handle, [handle]() { handle(); });
  }

  // trunk-ignore(clang-tidy/readability-identifier-naming)
  void await_resume() {}

 private:
  CallbackType cb_;
};

}  // namespace uv_coro