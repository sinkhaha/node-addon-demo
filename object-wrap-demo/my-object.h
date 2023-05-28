#ifndef MY_OBJECT_H
#define MY_OBJECT_H

#include <node.h>
#include <node_object_wrap.h>

namespace demo {

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

// 自定义类，继承 Node.js 的ObjectWrap 类
class MyObject : public node::ObjectWrap {
 public:
  static void Init(Local<Object> exports);
  static void New(const FunctionCallbackInfo<Value>& args);
  static void SetRef(const FunctionCallbackInfo<Value>& args);
 private:
  explicit MyObject();
  ~MyObject();
};

}

#endif
