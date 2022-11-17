# 使用nan包实现
## 安装
```bash   
npm i --save nan # 地址 https://github.com/nodejs/nan
npm i --save bindings # 用于加载c++模块
```

## 配置gyp文件
```json
// nan的头文件的搜索路径
"include_dirs": [
    "<!(node -e \"require('nan')\")"
]
```
## 引入头文件
`#include <nan.h>`

## 编译
`node-gyp rebuild`

## 测试
`node test.js`

