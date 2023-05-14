const functionTemplate = require('./build/Release/function-template');

const result = functionTemplate.testCreateByTemplate();
console.log(result); // this is function

// 用 new 实例化
const rst = new functionTemplate.MyFunctionTemplate();
console.log(rst); // MyFunctionTemplate {}
