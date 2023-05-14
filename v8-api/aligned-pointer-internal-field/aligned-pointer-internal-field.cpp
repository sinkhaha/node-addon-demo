#include <node.h>

namespace __aligned_pointer_internal_field__ {

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

// 自定义数据结构，内部加了一个persistent持久句柄，作用是用于回收自定义字段
struct PersistentWrapper {
    Persistent<Object> persistent; // 持久句柄
    int value;
};

/**
 * 弱持久句柄的回调函数
 * 当对象被回收时，此回调会被触发
 */
void WeakCallback(const v8::WeakCallbackInfo<PersistentWrapper>& data)
{
    PersistentWrapper* wrapper = data.GetParameter(); // 获取到SetWeak方法传的第一个参数，此时是wrapper参数

    printf("deleting 0x%.8X: %d...", wrapper, wrapper->value);

    wrapper->persistent.Reset(); // 重置(释放)这个持久句柄

    delete wrapper; // 删除wrapper对象，即删除堆内存分配的指针

    printf("ok\n");
}

/**
 * 当obj对象被垃圾回收时，会触发WeakCallback回调，这个回调里主要是删除new出来的PersistentWrapper对象
 */
void CreateObject(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    Local<ObjectTemplate> templ = ObjectTemplate::New(isolate);
    // 设置对象模板的内置字段数为1
    templ->SetInternalFieldCount(1);

    // 实例子化PersistentWrapper
    PersistentWrapper* wrapper = new PersistentWrapper();
    // 方法传入的第一个参数赋值给value
    wrapper->value = args[0]->ToNumber(context).ToLocalChecked()->Int32Value(context).FromJust();
    
    // obj模板对象设置内置字段，值为wrapper对象
    Local<Object> obj = templ->NewInstance(context).ToLocalChecked();


    obj->SetAlignedPointerInInternalField(0, wrapper); // 时内置字段是一个 External 永生句柄类型

    // 重置(释放)wrapper的持久句柄
    wrapper->persistent.Reset(isolate, obj);
    // 将持久句柄设置为弱持久句柄，回调函数为WeakCallback（当被回收时被调用）。wrapper参数可以在WeakCallback方法中获取到
    wrapper->persistent.SetWeak(wrapper, WeakCallback, v8::WeakCallbackType::kInternalFields);

    args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = Isolate::GetCurrent();
    Local<Context> context = isolate->GetCurrentContext();
    HandleScope scope(isolate);

    // 暴露create函数，其函数体为CreateObject
    exports->Set(context, String::NewFromUtf8(isolate, "create").ToLocalChecked(), FunctionTemplate::New(isolate, CreateObject)->GetFunction(context).ToLocalChecked()).Check();
}

NODE_MODULE(_template, Init)

}
