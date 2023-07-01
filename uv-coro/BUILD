load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "uv_awaitable",
    srcs = [
        "uv_awaitable.cc",
    ],
    hdrs = [
        "uv_awaitable.h",
    ],
)

cc_library(
    name = "uv_file",
    srcs = [
        "uv_file.cc",
    ],
    hdrs = [
        "uv_file.h",
    ],
    implementation_deps = [
        "@com_github_libuv//:libuv",
    ],
    deps = [
        ":uv_awaitable",
    ],
)

cc_test(
    name = "uv_file_test",
    srcs = [
        "uv_file_test.cc",
    ],
    deps = [
        ":uv_file",
        "@com_github_libuv//:libuv",
        "@com_google_googletest//:gtest_main",
    ],
)
