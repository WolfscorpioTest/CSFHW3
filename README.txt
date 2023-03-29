Mac Millan nmacmil1
Alexander Shen ashen12

Part b: Best Cache Experiment
The experiment should be run on a large trace file 
We decided to choose gcc.trace 
the size for all caches will be 4096 kb
Each type of cache will need to be tested for combinations of 
write-allocate write-through
write-allocate write-back
no-write-allocate write-through

Set associative caches will have to be tested for large and small block sizes
We will use 4 bytes and 8 bytes


associative caches will need to be tested with lru or fifo for all combinations

Directly Mapped Cache:
1. write-allocate write-through: 256 1 16
Total loads: 318197
Total stores: 197486
Load hits: 298863
Load misses: 19334
Store hits: 185202
Store misses: 12284
Total cycles: 32911483

2. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 298863
Load misses: 19334
Store hits: 185202
Store misses: 12284
Total cycles: 20312483

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 296251
Load misses: 21946
Store hits: 158894
Store misses: 38592
Total cycles: 29004091

Set Associative Cache: choosing 4 blocks per set
Small Block Size 4 byte per block
LRU:
1. write-allocate write-through: 256 4 4
Total loads: 318197
Total stores: 197486
Load hits: 310247
Load misses: 7950
Store hits: 168688
Store misses: 28798
Total cycles: 23939083

2. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 310247
Load misses: 7950
Store hits: 168688
Store misses: 28798
Total cycles: 7187283

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 306405
Load misses: 11792
Store hits: 158905
Store misses: 38581
Total cycles: 21404902

FIFO:
4. write-allocate write-through: 256 4 4
Total loads: 318197
Total stores: 197486
Load hits: 308203
Load misses: 9994
Store hits: 167708
Store misses: 29778
Total cycles: 24241483

5. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 308203
Load misses: 9994
Store hits: 167708
Store misses: 29778
Total cycles: 7668383

6. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 304826
Load misses: 13371
Store hits: 157404
Store misses: 40082
Total cycles: 21561301

Large block Size
8 bytes per block

LRU: 256 2 8
1. write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180110
Store misses: 17376
Total cycles: 24464683

2. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180110
Store misses: 17376
Total cycles: 4716283

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 309698
Load misses: 8499
Store hits: 161302
Store misses: 36184
Total cycles: 21927899

FIFO:
4. write-allocate write-through: 256 2 8
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180110
Store misses: 17376
Total cycles: 24464683

5. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180110
Store misses: 17376
Total cycles: 4716283

6. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 309698
Load misses: 8499
Store hits: 161302
Store misses: 36184
Total cycles: 21927899

Fully Associative Cache:
LRU:
1. write-allocate write-through 1 256 16
Total loads: 318197
Total stores: 197486
Load hits: 313123
Load misses: 5074
Store hits: 187653
Store misses: 9833
Total cycles: 26227083

2. write-allocate write-back 
Total loads: 318197
Total stores: 197486
Load hits: 313123
Load misses: 5074
Store hits: 187653
Store misses: 9833
Total cycles: 10802483

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 309777
Load misses: 8420
Store hits: 163612
Store misses: 33874
Total cycles: 23598409

FIFO:
4. write-allocate write-through 1 256 16
Total loads: 318197
Total stores: 197486
Load hits: 311025
Load misses: 7172
Store hits: 186977
Store misses: 10509
Total cycles: 27336683

5. write-allocate write-back 
Total loads: 318197
Total stores: 197486
Load hits: 311025
Load misses: 7172
Store hits: 186977
Store misses: 10509
Total cycles: 12461283

6. no-write-allocate write-through 
Total loads: 318197
Total stores: 197486
Load hits: 307970
Load misses: 10227
Store hits: 161070
Store misses: 36416
Total cycles: 24318667

The most load hits are from all combinations of Fully Associative Cache followed by Set associative and ending with Directly Mapped with the least amount of hits

Store hits are pretty consistent between the different caches for their most amount of hits depending on which combinations of settings they are using with fully
associative caches having a slight edge 

The Set associative Caches have the least amount of cycles overall

Hardware perspective: 
Different types of caches have different needs for power, speed, and area
Traditionally, directly mapped have the fastest speed and lowest power in contrast to fully associative and have set associative as middle ground between the two
This is somewhat consistent with our experimental results 

Looking at these results, the set associative cache is the best cache. It is pretty consistent with the fully associative cache for number of load hits and store
hits while also having the least amount of cycles. This means it is both efficient in accessing data as well as saving time (electricity/power, etc)


Contributions:
Mac: argument parsing and validation, Directly Associative, Set Associative, Fully Associative
Alexander: reading traces, Best Cache Experiment, Set Associative, Fully Associative