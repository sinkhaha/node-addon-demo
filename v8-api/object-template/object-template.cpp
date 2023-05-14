#include <node.h>

// 对象模板
namespace __objectTemplate__ {

using v8::FunctionCallbackInfo;
using v8::Value;
using v8::String;
using v8::Isolate;
using v8::HandleScope;
using v8::Context;
using v8::FunctionTemplate;
using v8::ObjectTemplate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Array;
 
/**
 * 
 */
void Constructor(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    // 设置this对象的value值为233
    args.This()->Set(context, String::NewFromUtf8(isolate, "value").ToLocalChecked(), Number::New(isolate, 233)).Check();

    // args.This() 为this对象，此时返回this对象
    return args.GetReturnValue().Set(args.This());
}


/**
 * get方法
 */
void ClassGet(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    // 返回this的value值
    return args.GetReturnValue().Set(args.This()->Get(context, String::NewFromUtf8(isolate, "value").ToLocalChecked()).ToLocalChecked());
}

void Func(const FunctionCallbackInfo<Value>& args) {
    args.GetReturnValue().Set(2333);
}

void Init(Local<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<Context> context = isolate->GetCurrentContext();

    // 用法1: 函数模板有一个与之关联的对象模板(此时是原型链对象模板)

    // 新建一个函数模板，并设置类名为TestClass，其函数体为Constructor函数
    Local<FunctionTemplate> ft = FunctionTemplate::New(isolate, Constructor); 
    Local<String> className = String::NewFromUtf8(isolate, "TestClass").ToLocalChecked();
    ft->SetClassName(className);

    // 获取函数模板的原型对象，并设置为get函数，其函数体为ClassGet函数
    Local<ObjectTemplate> proto = ft->PrototypeTemplate();
    proto->Set(String::NewFromUtf8(isolate, "get").ToLocalChecked(), FunctionTemplate::New(isolate, ClassGet));

    // 暴露TestClass对象，其值为TestClass函数
    exports->Set(context, className, ft->GetFunction(context).ToLocalChecked()).Check();;

    /** ================================================================== */

    // 用法2：对象模板脱离函数模板使用，作为对象模板创建对象

    //新建一个函数模板，并设置类名为TestClass2
    Local<FunctionTemplate> fun = FunctionTemplate::New(isolate);
    fun->SetClassName(String::NewFromUtf8(isolate, "TestClass2").ToLocalChecked());

    // 新建一个对象模板
    Local<ObjectTemplate> obj_tpl = ObjectTemplate::New(isolate, fun);
    // 对象模板设置一个num属性，值为233
    obj_tpl->Set(String::NewFromUtf8(isolate, "num").ToLocalChecked(), Number::New(isolate, 233)); 
    
    // 实例一个3个长度的数组，往里面存入对象
    Local<Array> array = Array::New(isolate, 3);
    for(int i = 0; i < 3; i++) {
        array->Set(context, Number::New(isolate, i), obj_tpl->NewInstance(context).ToLocalChecked()).Check(); // NewInstance()每个实体不同
    }

    // 把整个数组挂到exports的array属性
    exports->Set(context, String::NewFromUtf8(isolate, "array").ToLocalChecked(), array).Check();;

    /** ================================================================== */

    // 用法3:设置函数体
    // 实例化函数模板
    Local<ObjectTemplate> obj_with_func_tpl = ObjectTemplate::New(isolate);

    // 对象设置cat属性，值为小猫
    obj_with_func_tpl->Set(String::NewFromUtf8(isolate, "cat").ToLocalChecked(), String::NewFromUtf8(isolate, "小猫").ToLocalChecked());
    // 对象设置dog属性，值为小狗
    obj_with_func_tpl->Set(String::NewFromUtf8(isolate, "dog").ToLocalChecked(), String::NewFromUtf8(isolate, "小狗").ToLocalChecked());
   
    // 设置函数体为Func方法
    obj_with_func_tpl->SetCallAsFunctionHandler(Func);

    Local<Object> newInstance = obj_with_func_tpl->NewInstance(context).ToLocalChecked();
    
    // 暴露func方法
    exports->Set(context, String::NewFromUtf8(isolate, "func").ToLocalChecked(), newInstance).Check();;
}

NODE_MODULE(addon, Init)

}
