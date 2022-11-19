#include <node.h>

namespace __v8_hello__{
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

// Hello方法的实现，该方法返回hello-world
void Hello(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    // Set方法用于设置返回值
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hello-world").ToLocalChecked());
}

void init(Local<Object> exports) {
    // 在exports对象挂上hello属性，其值为Hello函数
    // NODE_SET_METHOD是一个宏，用于设置方法模板，它是node.h提供
    NODE_SET_METHOD(exports, "hello", Hello);
}

NODE_MODULE(addon, init)
}