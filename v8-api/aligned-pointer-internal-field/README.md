# 前提条件

此例子基于 `node v18.15.0`  版本

> 这是一个 `node addon` 的例子，里面直接使用了 `V8` 的 `API`， 注意不同 `Node.js` 版本 `V8` 的 `API` 有差异，运行时要根据具体的 `Node.js` 版本调整 `V8` 的 `API`，不同的 `Node.js` 版本使用的 `V8 API` 可见[此文档](https://v8docs.nodesource.com/)



# 构建

1. 安装对应 node 版本的开发环境

```bash
node-gyp install
```

2. 构建

```bash
node-gyp configure # 在构建前先生成项目Makefile文件和一些配置文件
node-gyp build # 构建，在build/Release下生成二进制文件，名字由binding.gyp的target_name配置
```

3. 其他命令

```bash
node-gyp clean # 清掉build构建目录和out目录

# 也可以直接使用rebuid命令，此命令依次执行clean/configure/build命令
node-gyp rebuild 
```



# 测试

```bash
node test.js # 测试
```

