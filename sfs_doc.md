# simple file storage

## quick start

```C++
typedef struct A{
    int8_t x0_1;
    SFSVarchar *x2_v;
    char x3_10[10];
}A;
char AMeta_c[] = {3, 0, 0, 0, 1, 0, 10};
SFSVarchar *AMeta = (SFSVarchar *)AMeta_c;
/*  .len = 5,
    .buf = {1,4,0,10,0} */
const uint32_t ArecordSize = sizeof(A);
int main(){
	SFSDatabase *db = sfsDatabaseCreate();
	SFSTable *table = sfsTableCreate(5 * ArecordSize, AMeta, db);
    A* record = sfsTableAddRecord(&table);
    A.x0_1 = 2;
    A.x2_v = sfsTableAddVarchar(&table, 4, "test");
    sfsDatabaseSave("file.sfs", db);
    return 0;
}

```

## functions

这里应该是函数列表 但出题人是只鸽子

xxxCreate()是指申请内存并创建一个对象，根据参数构造对象，返回他的指针

xxxCons()是指在已经申请的内存空间，根据参数构造对象，返回他的指针。调用者要保证指向的内存空间足够大

xxxRelease()是指讲对象销毁 把内存free掉

传入指针是二重指针时 表示该函数由于table所需的内存大小可能变化 所以分配内存的位置可能变化 

sfsTableReserve()的意思是 你调用函数之后 保证table->storSize大于传入的storSize

