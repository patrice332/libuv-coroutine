#include "uv-coro/uv_file.h"

#include <__coroutine/trivial_awaitables.h>
#include <fcntl.h>

#include "gtest/gtest.h"
#include "uv-coro/uv_awaitable.h"
#include "uv.h"

namespace uv_coro {

namespace {

struct Task {
  // trunk-ignore(clang-tidy/readability-identifier-naming)
  struct promise_type {
    // trunk-ignore(clang-tidy/readability-identifier-naming)
    static constexpr Task get_return_object() { return {}; }

    // trunk-ignore(clang-tidy/readability-identifier-naming)
    static constexpr std::suspend_never initial_suspend() { return {}; }

    // trunk-ignore(clang-tidy/readability-identifier-naming)
    static constexpr std::suspend_never final_suspend() noexcept { return {}; }

    // trunk-ignore(clang-tidy/readability-identifier-naming)
    void return_void() {}

    // trunk-ignore(clang-tidy/readability-identifier-naming)
    void unhandled_exception() {}
  };
};

TEST(File, Sanity) {
  auto* loop = uv_default_loop();
  bool done = false;
  auto test = [loop, &done]() -> Task {
    auto file =
        co_await Open(loop, "test.txt", O_RDWR | O_CLOEXEC | O_CREAT, 00600);
    constexpr std::span<char const> kMessage{"Hello, World!"};
    ConstBuffer buf{kMessage.data(), kMessage.size()};
    EXPECT_EQ(co_await Write(loop, file, {&buf, 1}, 0), kMessage.size());
    std::array<char, kMessage.size()> read_message{};
    Buffer read_buf{read_message.data(), read_message.size()};
    EXPECT_EQ(co_await Read(loop, file, {&read_buf, 1}, 0), kMessage.size());
    EXPECT_TRUE(
        std::equal(kMessage.begin(), kMessage.end(), read_message.begin()));
    co_await Close(loop, file);
    done = true;
  };
  test();
  uv_run(loop, UV_RUN_DEFAULT);
  EXPECT_TRUE(done);
}

}  // namespace

}  // namespace uv_coro