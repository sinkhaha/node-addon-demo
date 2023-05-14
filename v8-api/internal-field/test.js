const internalField = require('./build/Release/internal-field');

function test() {
    const result = {};
    // 创建3个对象，这些对象都与各自的WeakCallback关联起来
    for (let i = 0; i < 3; i++) {
        result[i] = internalField.create(i);
    }
    return result;
}

const result = test();

console.log(result); // { '0': {}, '1': {}, '2': {} }

// 删除每个对象，运气好的话，V8的垃圾回收机制会触发
delete result[0];
delete result[1];
delete result[2];

console.log(result); // {}

