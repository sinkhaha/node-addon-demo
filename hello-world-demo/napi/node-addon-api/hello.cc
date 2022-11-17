#include <napi.h>

namespace __node_addon_api_hello__ {

// Hello方法的实现，该方法返回hello-world
Napi::String Hello(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::String::New(env, "hello-world"); // 返回hello-world
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {

  // 在exports对象挂上hello属性，其值为Hello函数，也可以用以下的Nan::Export宏实现
  exports.Set(Napi::String::New(env, "hello"),
              Napi::Function::New(env, Hello));

  return exports;
}

NODE_API_MODULE(addon, Init)

}