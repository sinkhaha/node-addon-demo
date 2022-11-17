let addon = require('./build/Release/hello'); // 直接导入，也可以用bindings包导入

// let addon = require('bindings')('hello');

console.log(addon.hello()); // 输出 hello-world
