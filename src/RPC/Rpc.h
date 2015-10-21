#ifndef RPC_BASE
#define RPC_BASE

#include <mutex>
#include <condition_variable>

#include "Proto/Message.h"
#include "Utility/CallBack.h"
#include "RpcSession_pb.h"

namespace RPC {

class Rpc {
 public:
  enum ClientStatus {
    INIT = 0,
    SUCCESS = 1,
    INTERNAL_CHANNEL_ERROR = 2,
    CHECK_NUM_ERROR = 3,
    RESPONSE_HEADER_SIZE_ERROR = 4,
    RESPONSE_SIZE_ERROR = 5,
    BAD_RESPONSE_HEADER = 6,
  };

  Rpc();
  virtual ~Rpc();

  const proto::Message* internal_request() const { return request_; }
  void set_internal_request(const proto::Message* req) { request_ = req; }

  proto::Message* internal_response() const { return response_; }
  void set_internal_response(proto::Message* res) { response_ = res; }

  proto::Message* internal_stream() const { return stream_; }
  void set_internal_stream(proto::Message* stream) { stream_ = stream; }

  Base::Closure* cb_final() const { return cb_final_; }
  void set_cb_final(Base::Closure* cb_final) { cb_final_ = cb_final; }

  ClientStatus client_status() const { return client_status_; }
  void set_client_status(ClientStatus status) { client_status_ = status; }

  int check_num() const { return check_num_; }
  void set_check_num(int num) { check_num_ = num; }

  void SetRpcFinished();

  void Wait();

 private:
  const proto::Message* request_;
  proto::Message* response_;
  proto::Message* stream_;
  Base::Closure* cb_final_;

  int check_num_;
  ClientStatus client_status_ = INIT;

  bool rpc_finished_ = false;
  std::mutex rpc_wait_mutex_;
  std::condition_variable rpc_wait_cond_;
};

}  // namespace RPC

// force initialization of RpcSession_pb protos
static int InitRpcSessionProto() {
  RPC::RpcResponseHeader _default_response_header__;
  RPC::RpcRequestHeader _default_request_header__;
  (void)_default_request_header__;
  (void)_default_response_header__;
  return 1;
}

static int init_rpc_session_pb = InitRpcSessionProto();

#endif  /* RPC_BASE */
