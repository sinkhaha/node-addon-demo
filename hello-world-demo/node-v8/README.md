# 构建
```bash
# 基于node v16.18.0版本

node-gyp install # 安装对应node版本的开发环境，此步骤只需要第一次安装node-gyp后执行

node-gyp rebuild # 即依次执行clean/configure/build命令
```
# 测试
```bash
node test.js # 测试
```