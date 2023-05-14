# 构建
```bash
# 基于node v18.15.0版本

node-gyp install # 安装对应node版本的开发环境

node-gyp configure # 在构建前先生成项目Makefile文件和一些配置文件
node-gyp build # 构建，在build下生成Release/function-template.node

node-gyp clean # 清掉build构建目录和out目录

node-gyp rebuild # 即依次执行clean/configure/build命令
```
# 测试
```bash
node test.js # 测试
```