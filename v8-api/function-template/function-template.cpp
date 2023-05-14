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

    // 也可以使用 NODE_SET_METHOD 宏
    void init(Local<Object> exports) {
       Isolate* isolate = Isolate::GetCurrent();
       HandleScope scope(isolate);

       Local<Context> context = isolate->GetCurrentContext();

       // 实例化函数模板
       Local<FunctionTemplate> ft = FunctionTemplate::New(isolate, Method); // 将Method这个函数包裹，生成一个函数模板
       Local<Function> fn = ft->GetFunction(context).ToLocalChecked(); // 得到一个js中能用的函数实例Function
       
       // 设置函数名为testCreateByTemplate
       Local<String> fnName = String::NewFromUtf8(isolate, "testCreateByTemplate").ToLocalChecked();
       fn->SetName(fnName);
       
       // 挂载testCreateByTemplate函数到exports对象
       exports->Set(context, fnName, fn);
    }

    NODE_MODULE(addon, init)
}