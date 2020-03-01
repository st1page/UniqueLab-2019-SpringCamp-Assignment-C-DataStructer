#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "./sfs.h"
#include "./greatest/greatest.h"

GREATEST_MAIN_DEFS();

#pragma pack(1)
typedef struct A{
    int8_t x0_1;
    uint32_t x1_4;
    union{
        SFSVarchar *ptr;
        uint32_t offset;
    }x2_v;
    char x3_10[10];
    union{
        SFSVarchar *ptr;
        uint32_t offset;
    }x4_v;
}A;
char AMeta_c[] = {5, 0, 0, 0, 1, 4, 0, 10, 0};
SFSVarchar *AMeta = (SFSVarchar *)AMeta_c;
/*    .len = 5,
    .buf = {1,4,0,10,0} */
const uint32_t ArecordSize = sizeof(A);
SFSDatabase *db = NULL;
SFSTable *table = NULL;
uint32_t initStorSize = 0;

static enum greatest_test_res talbeAinit(){
    table = sfsTableCreate(initStorSize, AMeta, db);
    if(table==NULL) FAILm(sfsErrMsg());
    PASS();
}

static enum greatest_test_res tableDestory(){
    if(!sfsTableRelease(table)) FAILm(sfsErrMsg());
    table = NULL;
    PASS();
}

uint32_t ptrOffset(void *x, void *y){
    return (char*)y > (char*)x ?
            (char*)y - (char*)x:
            (char*)x - (char*)y;
}

TEST tableInitTest(uint32_t StorSize) {
    initStorSize = StorSize;
    CHECK_CALL(talbeAinit()); 
    ASSERT_EQ_FMT(ArecordSize, table->recordSize, "%d");
    ASSERT_EQ_FMT(initStorSize, table->freeSpace, "%d");
    ASSERT_EQ_FMT(0, table->recordNum, "%d");
    ASSERT_EQ_FMT(0, table->varcharNum, "%d");
    uint32_t lastVarcharOffset = ptrOffset(table, table->lastVarchar);
    uint32_t recordMetaOffset = ptrOffset(table, table->recordMeta);

    ASSERT_EQ_FMT(lastVarcharOffset, recordMetaOffset, "%d");
    ASSERT_EQ_FMT(sizeof(AMeta_c), table->size - recordMetaOffset, "%d");
    ASSERT_MEM_EQ(AMeta_c, (char*)table + recordMetaOffset , sizeof(AMeta_c));
    CHECK_CALL(tableDestory()); 
    PASS();
}
TEST tableStatic(void) {
    initStorSize = ArecordSize * 5;
    uint32_t storSize = initStorSize;
    CHECK_CALL(talbeAinit()); 

    A* addrs[5];
    for(int i=0;i<5;i++){
        ASSERT_EQ_FMT(storSize, table->freeSpace, "%d");
        addrs[i] = sfsTableAddRecord(&table);
        storSize -= ArecordSize;
        ASSERT_EQ_FMT(i+1, table->recordNum, "%d");
    }
    ASSERT_EQ_FMT(0, table->freeSpace, "%d");
    ASSERT_EQ_FMT(0, (char*)addrs[0] - (char*)table->buf, "%d");
    for(int i=1;i<5;i++){
        ASSERT_EQ_FMT(ArecordSize, ptrOffset(addrs[i], addrs[i-1]), "%d");
    }
    uint32_t lastVarcharOffset = ptrOffset(table, table->lastVarchar);
    ASSERT_EQ_FMT(ArecordSize, ptrOffset(table->lastVarchar, addrs[4]) , "%d");

    CHECK_CALL(tableDestory()); 
    PASS();
}
TEST tableReserve(void) {
    initStorSize = 1;
    CHECK_CALL(talbeAinit()); 
    uint32_t storSize = ArecordSize * 5;;
    sfsTableReserve(&table, storSize);
    ASSERT_EQ_FMT(ArecordSize, table->recordSize, "%d");
    ASSERT_EQ_FMT(storSize, table->freeSpace, "%d");
    ASSERT_EQ_FMT(0, table->recordNum, "%d");
    ASSERT_EQ_FMT(0, table->varcharNum, "%d");
    uint32_t lastVarcharOffset = ptrOffset(table, table->lastVarchar);
    uint32_t recordMetaOffset = ptrOffset(table, table->recordMeta);

    ASSERT_EQ_FMT(lastVarcharOffset, recordMetaOffset, "%d");
    ASSERT_EQ_FMT(sizeof(AMeta_c), table->size - recordMetaOffset, "%d");
    ASSERT_MEM_EQ(AMeta_c, (char*)table + recordMetaOffset , sizeof(AMeta_c));
    A* addrs[5];
    for(int i=0;i<5;i++){
        ASSERT_EQ_FMT(storSize, table->freeSpace, "%d");
        addrs[i] = sfsTableAddRecord(&table);
        storSize -= ArecordSize;
        ASSERT_EQ_FMT(i+1, table->recordNum, "%d");
    }
    ASSERT_EQ_FMT(0, table->freeSpace, "%d");
    ASSERT_EQ_FMT(0, (char*)addrs[0] - (char*)table->buf, "%d");
    for(int i=1;i<5;i++){
        ASSERT_EQ_FMT(ArecordSize, (char*)addrs[i] - (char*)addrs[i-1], "%d");
    }
    ASSERT_EQ_FMT(ArecordSize, ptrOffset(table->lastVarchar, addrs[4]) , "%d");

    CHECK_CALL(tableDestory()); 
    PASS();
}

SUITE(table_suite) {
    RUN_TEST1 (tableInitTest, ArecordSize*1);
    RUN_TEST1 (tableInitTest, ArecordSize*5);
    RUN_TEST1 (tableInitTest, 1);

    RUN_TEST (tableStatic);
    RUN_TEST (tableReserve);
}
int main(int argc, char **argv){
    //    for(int i=0;i<A_meta->len;i++) printf("%d\n", A_meta->buf[i]); 
    GREATEST_MAIN_BEGIN();     /* command-line arguments, initialization. */

    RUN_SUITE(table_suite);
//    RUN_SUITE(file_suite);
    
    GREATEST_MAIN_END();
    return 0;
}