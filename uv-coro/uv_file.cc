#include "uv-coro/uv_file.h"

#include <sys/types.h>

#include <cstdio>

#include "uv.h"

namespace uv_coro {

namespace {
template <typename T>
class FsOp {
 public:
  uv_fs_t FsT{};
  std::function<void(T)> CB{};
};

template <>
class FsOp<void> {
 public:
  uv_fs_t FsT{};
  std::function<void()> CB{};
};

}  // namespace

Awaitable<FileHandle> Open(uv_loop_t* loop, const char* path, int flags,
                           int mode) {
  return Awaitable<FileHandle>(
      [loop, path, flags, mode](std::coroutine_handle<> /* handle */,
                                std::function<void(FileHandle)> callback) {
        using OpenFsOp = FsOp<FileHandle>;
        auto* ptr = new OpenFsOp();
        ptr->CB = std::move(callback);
        ptr->FsT.data = ptr;
        uv_fs_open(loop, &ptr->FsT, path, flags, mode, [](uv_fs_t* req) {
          auto* ptr = reinterpret_cast<OpenFsOp*>(req->data);
          ptr->CB(static_cast<FileHandle>(req->result));
          uv_fs_req_cleanup(req);
          delete (ptr);
        });
      });
}

Awaitable<void> Close(uv_loop_t* loop, FileHandle handle) {
  return Awaitable<void>([loop, handle](std::coroutine_handle<> /*handle*/,
                                        std::function<void()> callback) {
    using CloseFsOp = FsOp<void>;
    auto* ptr = new CloseFsOp();
    ptr->CB = std::move(callback);
    ptr->FsT.data = ptr;

    uv_fs_close(loop, &ptr->FsT, handle, [](uv_fs_t* req) {
      auto* ptr = reinterpret_cast<CloseFsOp*>(req->data);
      ptr->CB();
      uv_fs_req_cleanup(req);
      delete (ptr);
    });
  });
}

Awaitable<ssize_t> Read(uv_loop_t* loop, FileHandle handle,
                        std::span<Buffer> buffers, std::int64_t offset) {
  return Awaitable<ssize_t>(
      [loop, handle, buffers, offset](std::coroutine_handle<> /*handle*/,
                                      std::function<void(ssize_t)> callback) {
        using ReadFsOp = FsOp<ssize_t>;
        auto* ptr = new ReadFsOp();
        ptr->CB = std::move(callback);
        ptr->FsT.data = ptr;
        uv_fs_read(loop, &ptr->FsT, handle,
                   reinterpret_cast<uv_buf_t*>(buffers.data()), buffers.size(),
                   offset, [](uv_fs_t* req) {
                     auto* ptr = reinterpret_cast<ReadFsOp*>(req->data);
                     ptr->CB(req->result);
                     uv_fs_req_cleanup(req);
                     delete (ptr);
                   });
      });
}

Awaitable<ssize_t> Write(uv_loop_t* loop, FileHandle handle,
                         std::span<ConstBuffer> buffers, std::int64_t offset) {
  return Awaitable<ssize_t>(
      [loop, handle, buffers, offset](std::coroutine_handle<> /*handle*/,
                                      std::function<void(ssize_t)> callback) {
        using ReadFsOp = FsOp<ssize_t>;
        auto* ptr = new ReadFsOp();
        ptr->CB = std::move(callback);
        ptr->FsT.data = ptr;
        uv_fs_write(loop, &ptr->FsT, handle,
                    reinterpret_cast<uv_buf_t const*>(buffers.data()),
                    buffers.size(), offset, [](uv_fs_t* req) {
                      auto* ptr = reinterpret_cast<ReadFsOp*>(req->data);
                      ptr->CB(req->result);
                      uv_fs_req_cleanup(req);
                      delete (ptr);
                    });
      });
}

}  // namespace uv_coro