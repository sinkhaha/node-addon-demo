let addon = require('bindings')('hello'); // 用bindings包加载c++模块，也可以直接引入 let addon = require('./build/Release/hello');

console.log(addon.hello()); // hello-world
