load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "srcs",
    srcs = glob(["**"]),
)

cmake(
    name = "libuv",
    generate_args = ["-GNinja"],
    lib_source = ":srcs",
    visibility = ["//visibility:public"],
)
