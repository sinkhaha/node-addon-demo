#include <nan.h>

namespace __hello_nan__ {

using v8::String;
using v8::FunctionTemplate;

// Hello方法的实现，该方法返回hello-world
NAN_METHOD(Hello) {
    info.GetReturnValue().Set(Nan::New("hello-world").ToLocalChecked());
}
   
// Init方法的实现
NAN_MODULE_INIT(Init) {
    // target相当于module.exports对象
    // 在module.exports对象挂上hello属性，其值为Hello函数，也可以用以下的Nan::Export宏实现
    Nan::Set(target, Nan::New<String>("hello").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(Hello)).ToLocalChecked());
        
    // 也可以用“模块函数导出宏”
    // Nan::Export(target, "hello", Hello);
}

NODE_MODULE(hello, Init)
}