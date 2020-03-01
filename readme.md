# Simple File Storage

## Background

序列化 (Serialization)是将对象的状态信息转换为可以存储或传输的形式的过程。在序列化期间，对象将其当前状态写入到临时或持久性存储区。以后，可以通过从存储区中读取或反序列化对象的状态，重新创建该对象。

本次任务就要求你完成一个简单的C语言序列化库，用以将包含定长和变长字段的struct数组存入文件中。

## Details

本次任务的接口和文档已经给出 具体请查看相应的文件

+ sfs.h 
  + 头文件 sfs库接口
+ sfs_file_structure.md 
  + sfs存储文件的文件格式。
  + 函数sfsDatabaseSave和sfsDatabaseCreateLoad存储和读取的文件都应是该格式
+ sfs_doc.md 
  + sfs库的文档
  + （很不完善 
+ sfs_test.c
  + 测试代码，会不定期更新
  + 使用greatest测试框架 更多用法参阅其文档
  + 鼓励选手补充自己的测试用例

## Attention

+ 有任何问题 请联系出题人 提issue就可

+ 这是一道提高大家代码能力和实际工程经验的题目 基本不涉及大家没学过的知识 因此**完成这道题获得的评价会比其他题目稍低**。

+ 题目的相关文档和测试用例等会不定期在github上更新 请用好git

## Hint

* 你可能注意到了 table要随着数据增加动态改变申请的空间 这里你可以参考C++ STL vector的实现
* 尽管已经给出了外部接口的函数定义 在你自己的程序中进行合理抽象 定义函数来降低单个函数的复杂度 是十分有必要的
* 代码风格和git commit习惯等 挺重要的

## Advanced(Optional)

* 这是一道代码题 因此有时间建议花在其他题目上

## References

+ [Configuring a remote for a fork](https://link.zhihu.com/?target=https%3A//help.github.com/articles/configuring-a-remote-for-a-fork/)
+ [Syncing a fork](https://link.zhihu.com/?target=https%3A//help.github.com/articles/syncing-a-fork/)

