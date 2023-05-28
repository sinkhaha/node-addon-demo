#include <node.h>
#include "my-object.h"

namespace demo {

using v8::Local;
using v8::Object;

void Init(Local<Object> exports, Local<Object> module) {
  MyObject::Init(exports);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

} 