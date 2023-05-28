#include "my-object.h"

namespace demo {

MyObject::MyObject(): node::ObjectWrap() {
}

MyObject::~MyObject() {
  printf("~MyObject\n");
}

void MyObject::New(const FunctionCallbackInfo<Value>& args) {
  MyObject* obj = new MyObject();
  obj->Wrap(args.This()); // 调用ObjectWrap 的 Wrap函数，里面会设置弱引用回调
  args.GetReturnValue().Set(args.This());
}

// 主动调用 Ref()；ObjectWrap 默认设置了弱引用，如果管理的JS对象没有被其他变量引用则会被GC，这里主动调Ref()后不会被GC
void MyObject::SetRef(const FunctionCallbackInfo<Value>& args) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
  obj->Ref();
}

void MyObject::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<String> name = String::NewFromUtf8(isolate, "MyObject").ToLocalChecked();
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, MyObject::New);
  tpl->SetClassName(name);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(tpl, "ref", MyObject::SetRef);

  exports->Set(context, name, tpl->GetFunction(context).ToLocalChecked()).Check();
}


}
