load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "srcs",
    srcs = glob([
        "*",
        "include/**/*",
        "src/**/*",
    ]),
)

cmake(
    name = "libuv",
    cache_entries = {
        "LIBUV_BUILD_TESTS": "OFF",
    },
    generate_args = ["-GNinja"],
    includes = ["include"],
    lib_source = ":srcs",
    visibility = ["//visibility:public"],
)
