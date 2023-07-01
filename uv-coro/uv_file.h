#pragma once

#include <cstddef>
#include <span>
#include <string_view>

#include "uv-coro/uv_awaitable.h"

struct uv_loop_s;

namespace uv_coro {

using FileHandle = int;

struct Buffer {
  char* Data;
  size_t Size;
};

struct ConstBuffer {
  const char* Data;
  size_t Size;
};

// Open the file at |path| with |flags| and |mode|.
Awaitable<FileHandle> Open(uv_loop_s* loop, const char* path, int flags,
                           int mode);

// Close the file handle.
Awaitable<void> Close(uv_loop_s* loop, FileHandle handle);

// Read from set of buffers and return number of bytes read
Awaitable<ssize_t> Read(uv_loop_s* loop, FileHandle handle,
                        std::span<Buffer> buffers, std::int64_t offset = -1);

// Write from the set of buffers and returns the number of bytes written
Awaitable<ssize_t> Write(uv_loop_s* loop, FileHandle handle,
                         std::span<ConstBuffer> buffers,
                         std::int64_t offset = -1);

}  // namespace uv_coro