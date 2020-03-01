## structuer of sfs file

file header  
table1  
table2  
table3  
...

### sfs file header

All values used little-endian
The "offset" is measured from the start of the file in bytes

start|size| description
------|----|----
00| 4B| Magic number(0x534653aa, "SFS.")
04| 4B| CRC-32
08| 4B| Version number
0c| 4B| FIle size
10| 1B| The number of tables
11| 3B| Pad bytes
14|64B| tables offset(uint32[16])

### Table 

table header  
record1  
record2  
...  
free space  
...  
Varchar2  
Varchar1  
record metadata

Note that the free space in the table is located between the last record and varchar, and that varchars are in reverse order. This way, new record and varchar can simply be added without having torearrange existing items. New record go after the last record, and new varchar before the first(physical) varchar. 
### Table header

All values used little-endian
The "offset" is measured from the start of the table in bytes

start|size| description
------|----|----|
00| 4B| total size of the Table( include the table header)
04| 4B| Free space left in the table
08| 4B| Space usd to store data in the table(except header and recordMeta)
0c| 4B| Number of Varchars in the table
10| 4B| Number of Records in the table
14| 4B| size of a record
18| 4B| offset to the Record metadata in the table
1c| 4B| offset to the last Varchar in the table()
20| 4B| The database's offset(a unsigned integer)

### Varchar
start|size| description
------|----|----
00| 4B | the length of the varchar content
04| 1B*length | varchar content 

### Record metadata
record metadata is a special varchar

start|size| description
------|----|----
00| 4B | the number of fields
04| 1B*fieldsNum | the length/type of fields 

the length of fields is a unsigned char means the size of the fields in bytes   
if it is 0, the fields is a offset of a varchar, which is measured from the start of the table

