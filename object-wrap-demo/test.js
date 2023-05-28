const { MyObject } = require('./build/Release/addon');

// 测试1：执行gc()后，MyObject会被回收，触发析构函数
new MyObject();

// 测试2：主动调用ref()，避免被gc，执行gc()后，MyObject不会被回收
// global.object = new MyObject();
// new MyObject().ref();

gc();
