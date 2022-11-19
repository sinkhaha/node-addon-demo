{
  "targets": [
    {
      "target_name": "hello",
      "sources": [ "hello.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")" # 头文件的搜索路径，这样就能直接在项目中通过 #include <nan.h>来引入NAN
      ]
    }
  ]
}