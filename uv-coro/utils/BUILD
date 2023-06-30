load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "fire_once_event",
    srcs = [
        "fire_once_event.cc",
    ],
    hdrs = [
        "fire_once_event.h",
    ],
)

cc_library(
    name = "sync_wait_task",
    srcs = [
        "sync_wait_task.cc",
    ],
    hdrs = [
        "sync_wait_task.h",
    ],
    deps = [
        ":fire_once_event",
    ],
)

cc_library(
    name = "sync_wait",
    srcs = [
        "sync_wait.cc",
    ],
    hdrs = [
        "sync_wait.h",
    ],
    deps = [
        ":sync_wait_task",
    ],
)

cc_test(
    name = "sync_wait_test",
    srcs = [
        "sync_wait_test.cc",
    ],
    deps = [
        ":sync_wait",
        "@com_google_googletest//:gtest_main",
    ],
)
