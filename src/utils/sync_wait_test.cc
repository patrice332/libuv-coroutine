#include "src/utils/sync_wait.h"

#include <__coroutine/trivial_awaitables.h>

#include "gtest/gtest.h"

namespace lib_uv_coro::utils {

namespace {

TEST(SyncWait, sanity) {
  bool ran = false;
  auto coro = [&ran]() -> std::suspend_never {
    ran = true;
    return {};
  };
  sync_wait(coro());
  EXPECT_TRUE(ran);
}

}  // namespace

}  // namespace lib_uv_coro::utils