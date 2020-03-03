# FAQ

### 这个库是做什么的？

简单来说 是用来存储多个C语言结构体到文件中的。比如说你有一个结构体数组。

```c++
typedef struct A{
    char x1_1;
    char *s2_v;
    char x3_10[10];
}A[100];
```

要把他的内容存到文件里 直接把A[100]的内容fwrite到文件里是不行的 因为你有一个char*字符串 是引用外部的字符数组。

所以使用了这个库 你就可以这么搞 重要过程写在注释里了

```cpp
typedef struct A{
    char x1_1;
    SFSVarchar *x2_v;
    char x3_10[10];
}A;
char AMeta_c[] = {3, 0, 0, 0, 1, 0, 10};
SFSVarchar *AMeta = (SFSVarchar *)AMeta_c;
/*  AMeta->len = 3,
    AMeta->buf = {1,0,10} */
const uint32_t ArecordSize = sizeof(A);
int main(){
	SFSDatabase *db = sfsDatabaseCreate();
	SFSTable *table = sfsTableCreate(5 * ArecordSize, AMeta, db);
    A* record = sfsTableAddRecord(&table);// 在table中留出了一个record的位置 并返回它的指针 给你填空
    A.x1_1 = 2; 
    A.x2_v = sfsTableAddVarchar(&table, 4, "test"); // 在talbe里面 插入一个变长字符串 长度为4 内容为“test” 返回他的指针 把指针填到刚才A指向的结构里
    sfsDatabaseSave("file.sfs", db);
    return 0;
}
```

### 为什么文件结构和sfs.h中结构有一些差别？

在C程序中有指针 文件中显然没有指针 所以在文件中 我们用offset(偏移量)来表示，即存储一个目标地址和当前地址的位移差值。这个库的作用，或者说你要做的事情其中之一就是要把比如SFSTable *、SFSVarchar * 之类的指针 和 文件中的 offset做一个转换

