# 使用node-addon-api包实现（外挂式）
## 安装
```bash   
npm i --save node-addon-api # 地址 https://github.com/nodejs/node-addon-api
npm i --save bindings # 用于加载c++模块
```

## 配置gyp文件
```json
// 表示从外挂式头文件的头文件搜索路径：
 `"include_dirs": [ "<!@(node -p \"require('node-addon-api').include\")" ]`
```
## 引入头文件
`#include <napi.h>`

## 编译
`node-gyp rebuild`

## 测试
`node test.js`

