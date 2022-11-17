#define NAPI_VERSION 8
#include <assert.h>
#include <node_api.h>

// Hello方法的实现，该方法返回hello
static napi_value Hello(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value world;

  status = napi_create_string_utf8(env, "hello-world", 12, &world);

  assert(status == napi_ok);

  return world;
}


#define DECLARE_NAPI_METHOD(name, func) \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

static napi_value Init(napi_env env, napi_value exports) {
  napi_status status;

  napi_property_descriptor desc = DECLARE_NAPI_METHOD("hello", Hello); // 设置exports对象的描述结构体

  status = napi_define_properties(env, exports, 1, &desc); // env表示底层上下文的参数

  assert(status == napi_ok);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init) // 注册模块
