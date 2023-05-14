const internalField = require('./build/Release/internal-field');

// 创建10个对象，这些对象都与各自的WeakCallback关联起来
for (let i = 0; i < 10; i++) {
    const rst = internalField.create(i);
    console.log(rst); 
}
