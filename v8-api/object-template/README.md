# 构建
```bash
# 基于node v18.15.0版本

node-gyp install # 安装对应node版本的开发环境

node-gyp configure # 在构建前先生成项目Makefile文件和一些配置文件
node-gyp build # 构建，在build下生成Release/object-template.node，名字由binding.gyp的target_name配置

node-gyp clean # 清掉build构建目录和out目录

# 也可以直接使用rebuid命令，此命令依次执行clean/configure/build命令
node-gyp rebuild 
```

# 测试
```bash
node test.js # 测试
```