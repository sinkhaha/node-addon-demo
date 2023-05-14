#include <node.h>
// 等价于function-template-inherit.js的js代码
namespace __inherit__ {

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

Persistent<Function> cons;

void SetName(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    Local<Object> self = args.Holder();

    // 等价于 this.name = 传进来的第一个参数
    self->Set(context, String::NewFromUtf8(isolate, "name").ToLocalChecked(), args[0]);
}

void Summary(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    Local<Object> self = args.Holder();
    char temp[512];

    String::Utf8Value type(isolate, self->Get(context, String::NewFromUtf8(isolate, "type").ToLocalChecked()).ToLocalChecked()->ToString(context).ToLocalChecked());
    String::Utf8Value name(isolate, self->Get(context, String::NewFromUtf8(isolate, "name").ToLocalChecked()).ToLocalChecked()->ToString(context).ToLocalChecked());

    // 把值赋给temp 等价于js的`${this.name} is a/an ${this.type}`
    snprintf(temp, 511, "%s is a/an %s.", *name, *type);

    // 返回temp
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, temp).ToLocalChecked());
}

void Pet(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    Local<Object> self = args.Holder();

    // 等价于
    // this.name = 'Unknown';
    // this.type = 'animal';
    self->Set(context, String::NewFromUtf8(isolate, "name").ToLocalChecked(), String::NewFromUtf8(isolate, "Unknown").ToLocalChecked());
    self->Set(context, String::NewFromUtf8(isolate, "type").ToLocalChecked(), String::NewFromUtf8(isolate, "animal").ToLocalChecked());

    // 返回this
    args.GetReturnValue().Set(self);
}

void Dog(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    Local<Object> self = args.Holder(); // 获取this对象
    Local<Function> super = cons.Get(isolate); // 获取super，即Pet

    // 即等价于js代码的 Pet.call(this)
    super->Call(context, self, 0, NULL);
    // => this.type = 'dog'
    self->Set(context, String::NewFromUtf8(isolate, "type").ToLocalChecked(), String::NewFromUtf8(isolate, "dog").ToLocalChecked());

    // 返回自身
    args.GetReturnValue().Set(self);
}

void Init(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = Isolate::GetCurrent();
    Local<Context> context = isolate->GetCurrentContext();
    HandleScope scope(isolate);

    // 函数模板Pet
    Local<FunctionTemplate> pet = FunctionTemplate::New(isolate, Pet);
    // PrototypeTemplate返回了这个函数模板的原型链上的原型对象模板prototype
    // 在Pet的原型对象上设置setName函数和summary函数
    pet->PrototypeTemplate()->Set(
            String::NewFromUtf8(isolate, "setName").ToLocalChecked(),
            FunctionTemplate::New(isolate, SetName));
    pet->PrototypeTemplate()->Set(
            String::NewFromUtf8(isolate, "summary").ToLocalChecked(),
            FunctionTemplate::New(isolate, Summary));

    Local<Function> pet_cons = pet->GetFunction(context).ToLocalChecked();

    cons.Reset(isolate, pet_cons);

    Local<FunctionTemplate> dog = FunctionTemplate::New(isolate, Dog);
    dog->Inherit(pet); // Dog继承Pet

    Local<Function> dog_cons = dog->GetFunction(context).ToLocalChecked();
    
    // 暴露Pet和Dog函数
    exports->Set(context, String::NewFromUtf8(isolate, "Pet").ToLocalChecked(), pet_cons);
    exports->Set(context, String::NewFromUtf8(isolate, "Dog").ToLocalChecked(), dog_cons);
}

NODE_MODULE(_template, Init)

}
