#include "uv-coro/utils/sync_wait.h"

#include <__coroutine/trivial_awaitables.h>

#include "gtest/gtest.h"

namespace uv_coro::utils {

namespace {

TEST(SyncWait, sanity) {
  bool ran = false;
  auto coro = [&ran]() -> std::suspend_never {
    ran = true;
    return {};
  };
  SyncWait(coro());
  EXPECT_TRUE(ran);
}

}  // namespace

}  // namespace uv_coro::utils