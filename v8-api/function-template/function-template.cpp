#include <node.h>

// 函数模板
namespace __functionTemplate__ {

using v8::FunctionCallbackInfo;
using v8::Value;
using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::HandleScope;
using v8::FunctionTemplate;
using v8::Function;
using v8::String;
using v8::Context;
    
/**
 * Method方法有单一参数FunctionCallbackInfo<Value>的引用，返回值是void类型
 */
void Method(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // 设置方法返回值为 this is function
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "this is function").ToLocalChecked());
}

void New(const FunctionCallbackInfo<Value>& args)
{
    args.GetReturnValue().Set(args.This()); // 返回this对象
}

void init(Local<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent(); // 获取v8实例
    HandleScope scope(isolate); // 实例化句柄对象

    Local<Context> context = isolate->GetCurrentContext(); // 获取上下文

    // 用法1: 函数模板的用法，设置函数名
    // 实例化函数模板
    Local<FunctionTemplate> ft1 = FunctionTemplate::New(isolate, Method); // 将Method这个函数包裹，生成一个函数模板
    Local<Function> fn1 = ft1->GetFunction(context).ToLocalChecked(); // 得到一个js中能用的函数实例Function
       
    // 设置函数名为testCreateByTemplate
    Local<String> fnName1 = String::NewFromUtf8(isolate, "testCreateByTemplate").ToLocalChecked();
    fn1->SetName(fnName1);
       
    // 挂载testCreateByTemplate函数到exports对象
    exports->Set(context, fnName1, fn1).Check();

    /** ==================================== */

    // 用法2: 设置函数的类名
    // 新建函数模板，对应New函数
    Local<FunctionTemplate> ft2 = FunctionTemplate::New(isolate, New);  // 方法为New
    Local<String> fnName2 = String::NewFromUtf8(isolate, "MyFunctionTemplate").ToLocalChecked();

    // 设置类名 MyFunctionTemplate
    ft2->SetClassName(fnName2);
    Local<Function> fn2 = ft2->GetFunction(context).ToLocalChecked();

    exports->Set(context, fnName2, fn2).Check();

}

NODE_MODULE(addon, init)

}