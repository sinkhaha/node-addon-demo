const objectTpl = require('./build/Release/object-template');

/** ========= 测试1 ==========*/
console.log(objectTpl.TestClass); // [Function: TestClass]

const a = new objectTpl.TestClass();
console.log(a); // TestClass { value: 233 }

let value = a.get();
console.log(value); // 233

/** ========= 测试2 ==========*/
const array = objectTpl.array;
console.log(array);
// 输出
// [
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 }
//   ]

array[0].num = 666;
console.log(array);
// 输出
// [
//     TestClass2 { num: 666 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 },
//     TestClass2 { num: 233 }
//   ]

/** ========= 测试3 ==========*/
const func = objectTpl.func;
console.log(func); // { cat: '南瓜饼', dog: '蛋花汤' }

const funcRst = func();
console.log(funcRst); // 2333
