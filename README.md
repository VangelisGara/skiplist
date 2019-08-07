## Skiplists
Implementing a data structure that will help us insert, access and edit records for universities, with insert cost *O(n)* , n the number of records, and access *O(1)* or *O(k)* , k the number of records that relate to the query.

The data structure is implemented with a **skip list** for fast access  *O(n)* to the records and **chained hashing** for *O(k)* range queries.

To detailed schema of the implementation is the following:
![enter image description here](https://github.com/VangelisGara/skiplist/blob/master/about%20skiplists/HashTable.png)
## To compile and execute

    make clean & make
    ./stucs < ./inputs/test1.txt
There is a prompt menu that will guide you to use the program.
