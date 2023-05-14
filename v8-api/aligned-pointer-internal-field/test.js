const { FuncWithCallback } = require('./build/Release/aligned-pointer-internal-field.node');

const instance = new FuncWithCallback();
console.log(instance.method());
