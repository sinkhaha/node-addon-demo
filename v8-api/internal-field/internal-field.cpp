#include <node.h>

namespace __internal_field_right__ {

using v8::FunctionCallbackInfo;
using v8::HandleScope;
using v8::ObjectTemplate;
using v8::FunctionTemplate;
using v8::Function;
using v8::Isolate;
using v8::Local;
using v8::Persistent;
using v8::External;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Array;
using v8::MaybeLocal;
using v8::Context;

// 自定义数据结构
struct PersistentWrapper {
    Persistent<Object> persistent; // 持久句柄
    int value;
};

void WeakCallback(const v8::WeakCallbackInfo<PersistentWrapper>& data)
{
    PersistentWrapper* wrapper = data.GetParameter(); // 获取到SetWeak方法传的第一个参数，此时是wrapper参数

    printf("deleting 0x%.8X: %d...", wrapper, wrapper->value); // NOLINT

    wrapper->persistent.Reset(); // 重置这个持久句柄
    delete wrapper; // 删除堆内存分配的指针

    printf("ok\n");
}

// 当obj对象被垃圾回收时，会触发一个WeakCallback回调，这个回调里主要是删除new出来的PersistentWrapper对象
void CreateObject(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    // 新建对象模板
    Local<ObjectTemplate> templ = ObjectTemplate::New(isolate);
    templ->SetInternalFieldCount(1);

    // 新建对象以及设置内置字段
    PersistentWrapper* wrapper = new PersistentWrapper();
    // 方法传入的第一个参数赋值给valu
    wrapper->value = args[0]->ToNumber(context).ToLocalChecked()->Int32Value(context).FromJust();
    
    // obj模板对象设置内置字段
    Local<Object> obj = templ->NewInstance(context).ToLocalChecked();
    obj->SetInternalField(0, External::New(isolate, wrapper));

    // 基于 obj 新建持久句柄
    wrapper->persistent.Reset(isolate, obj); // 重置这个持久句柄

    // 将持久句柄设置为弱持久句柄。wrapper参数可以在WeakCallback方法中获取到
    wrapper->persistent.SetWeak(wrapper, WeakCallback, v8::WeakCallbackType::kInternalFields);
    // wrapper->persistent.MarkIndependent(); // TODO 标记独立句柄 此版本没有此函数

    args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = Isolate::GetCurrent();
    Local<Context> context = isolate->GetCurrentContext();
    HandleScope scope(isolate);

    // 暴露create函数，其函数体为CreateObject
    exports->Set(context, String::NewFromUtf8(isolate, "create").ToLocalChecked(), FunctionTemplate::New(isolate, CreateObject)->GetFunction(context).ToLocalChecked());
}

NODE_MODULE(_template, Init)

}
