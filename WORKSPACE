workspace(name = "com_patrice332_libuv_coroutine")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

BAZEL_TOOLCHAIN_TAG = "0.8.2"

BAZEL_TOOLCHAIN_SHA = "0fc3a2b0c9c929920f4bed8f2b446a8274cad41f5ee823fd3faa0d7641f20db0"

http_archive(
    name = "com_grail_bazel_toolchain",
    canonical_id = BAZEL_TOOLCHAIN_TAG,
    sha256 = BAZEL_TOOLCHAIN_SHA,
    strip_prefix = "bazel-toolchain-{tag}".format(tag = BAZEL_TOOLCHAIN_TAG),
    url = "https://github.com/grailbio/bazel-toolchain/archive/refs/tags/{tag}.tar.gz".format(tag = BAZEL_TOOLCHAIN_TAG),
)

load("@com_grail_bazel_toolchain//toolchain:deps.bzl", "bazel_toolchain_dependencies")

bazel_toolchain_dependencies()

load("@com_grail_bazel_toolchain//toolchain:rules.bzl", "llvm_toolchain")

LLVM_VERSION = "16.0.2"

http_archive(
    name = "org_chromium_sysroot_linux_x64",
    build_file_content = """
filegroup(
  name = "sysroot",
  srcs = glob(["*/**"]),
  visibility = ["//visibility:public"],
)
""",
    sha256 = "",
    urls = ["https://commondatastorage.googleapis.com/chrome-linux-sysroot/toolchain/4c00ba2ad61ca7cc39392f192aa39420e086777c/debian_bullseye_amd64_sysroot.tar.xz"],
)

llvm_toolchain(
    name = "llvm_toolchain",
    cxx_standard = {"": "c++20"},
    llvm_version = LLVM_VERSION,
    sha256 = {"linux-x86_64": "9530eccdffedb9761f23cbd915cf95d861b1d95f340ea36ded68bd6312af912e"},
    strip_prefix = {"linux-x86_64": "clang+llvm-{}-x86_64-linux-gnu-ubuntu-22.04".format(LLVM_VERSION)},
    sysroot = {
        "linux-x86_64": "@org_chromium_sysroot_linux_x64//:sysroot",
    },
    urls = {
        "linux-x86_64": [
            "https://github.com/llvm/llvm-project/releases/download/llvmorg-{}/clang+llvm-{}-x86_64-linux-gnu-ubuntu-22.04.tar.xz".format(LLVM_VERSION, LLVM_VERSION),
        ],
    },
)

load("@llvm_toolchain//:toolchains.bzl", "llvm_register_toolchains")

llvm_register_toolchains()

http_archive(
    name = "com_google_absl",
    sha256 = "5366d7e7fa7ba0d915014d387b66d0d002c03236448e1ba9ef98122c13b35c36",
    strip_prefix = "abseil-cpp-20230125.3",
    urls = ["https://github.com/abseil/abseil-cpp/archive/refs/tags/20230125.3.tar.gz"],
)

http_archive(
    name = "rules_foreign_cc",
    sha256 = "2a4d07cd64b0719b39a7c12218a3e507672b82a97b98c6a89d38565894cf7c51",
    strip_prefix = "rules_foreign_cc-0.9.0",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/refs/tags/0.9.0.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

# This sets up some common toolchains for building targets. For more details, please see
# https://bazelbuild.github.io/rules_foreign_cc/0.9.0/flatten.html#rules_foreign_cc_dependencies
rules_foreign_cc_dependencies()

http_archive(
    name = "com_github_libuv",
    build_file = "//third_party:libuv.BUILD",
    sha256 = "458e34d5ef7f3c0394a2bfd8c39d757cb1553baa5959b9b4b45df63aa027a228",
    strip_prefix = "libuv-1.45.0",
    urls = ["https://github.com/libuv/libuv/archive/refs/tags/v1.45.0.tar.gz"],
)
