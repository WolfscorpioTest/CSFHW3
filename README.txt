Mac Millan nmacmil1
Alexander Shen ashen12

Part b: Best Cache Experiment
The experiment should be run on a large trace file 
We decided to choose gcc.trace 
the size for all caches will be 524288 bytes or 524 kb
Each type of cache will need to be tested for combinations of 
write-allocate write-through
write-allocate write-back
no-write-allocate write-through

Set associative caches will have to be tested for large and small block sizes
We will use 8 bytes and 64 bytes for small and large block sizes


associative caches will need to be tested with lru or fifo for all combinations
Directly mapped small: 65536 1 8
Directly mapped large: 8192 1 64
Set Associative small: 512 128 8
Set Associative large: 512 16 64
Fully associative small: 1 65536 8
Fully associative large: 1 8192 64

Directly Mapped Cache Small:
1. write-allocate write-through: 65536 1 8
Total loads: 318197
Total stores: 197486
Load hits: 314534
Load misses: 3663
Store hits: 180088
Store misses: 17398
Total cycles: 24476483

2. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 314534
Load misses: 3663
Store hits: 180088
Store misses: 17398
Total cycles: 4796483

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 309667
Load misses: 8530
Store hits: 161278
Store misses: 36208
Total cycles: 21934075

Directly Mapped Cache Large:
1. write-allocate write-through: 8192 1 64
Total loads: 318197
Total stores: 197486
Load hits: 317153
Load misses: 1044
Store hits: 195087
Store misses: 2399
Total cycles: 25773083

2. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 317153
Load misses: 1044
Store hits: 195087
Store misses: 2399
Total cycles: 6370083

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 315866
Load misses: 2331
Store hits: 173664
Store misses: 23822
Total cycles: 23970061

Set Associative small: 512 128 8
LRU:
1. write-allocate write-through: 512 128 8
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180111
Store misses: 17375
Total cycles: 24464483

2. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180111
Store misses: 17375
Total cycles: 4715883

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 309698
Load misses: 8499
Store hits: 161302
Store misses: 36184
Total cycles: 21927899

FIFO:
4. write-allocate write-through: 
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180111
Store misses: 17375
Total cycles: 24464483

5. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180111
Store misses: 17375
Total cycles: 4715883

6. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 309698
Load misses: 8499
Store hits: 161302
Store misses: 36184
Total cycles: 21927899

Set Associative large: 512 16 64

LRU: 
1. write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 317201
Load misses: 996
Store hits: 195111
Store misses: 2375
Total cycles: 25657883

2. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 317201
Load misses: 996
Store hits: 195111
Store misses: 2375
Total cycles: 5947683

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 315895
Load misses: 2302
Store hits: 173709
Store misses: 23777
Total cycles: 23923706

FIFO:
4. write-allocate write-through: 
Total loads: 318197
Total stores: 197486
Load hits: 317200
Load misses: 997
Store hits: 195110
Store misses: 2376
Total cycles: 25661083

5. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 317200
Load misses: 997
Store hits: 195110
Store misses: 2376
Total cycles: 5954083

6. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 315895
Load misses: 2302
Store hits: 173709
Store misses: 23777
Total cycles: 23923706


Fully associative small: 1 65536 8

LRU:
1. write-allocate write-through 
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180111
Store misses: 17375
Total cycles: 24464483

2. write-allocate write-back 
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180111
Store misses: 17375
Total cycles: 4715883

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 309698
Load misses: 8499
Store hits: 161302
Store misses: 36184
Total cycles: 21927899

FIFO:
4. write-allocate write-through 
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180111
Store misses: 17375
Total cycles: 24464483

5. write-allocate write-back 
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180111
Store misses: 17375
Total cycles: 4715883

6. no-write-allocate write-through 
Total loads: 318197
Total stores: 197486
Load hits: 309698
Load misses: 8499
Store hits: 161302
Store misses: 36184
Total cycles: 21927899

Fully associative large: 1 8192 64
LRU:
1. write-allocate write-through 
Total loads: 318197
Total stores: 197486
Load hits: 317204
Load misses: 993
Store hits: 195112
Store misses: 2374
Total cycles: 25651483

2. write-allocate write-back 
Total loads: 318197
Total stores: 197486
Load hits: 317204
Load misses: 993
Store hits: 195112
Store misses: 2374
Total cycles: 5902883

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 315897
Load misses: 2300
Store hits: 173709
Store misses: 23777
Total cycles: 23920506

FIFO:
4. write-allocate write-through 
Total loads: 318197
Total stores: 197486
Load hits: 317204
Load misses: 993
Store hits: 195112
Store misses: 2374
Total cycles: 25651483

5. write-allocate write-back 
Total loads: 318197
Total stores: 197486
Load hits: 317204
Load misses: 993
Store hits: 195112
Store misses: 2374
Total cycles: 5902883

6. no-write-allocate write-through 
Total loads: 318197
Total stores: 197486
Load hits: 315897
Load misses: 2300
Store hits: 173709
Store misses: 23777
Total cycles: 23920506

The most load hits are from the Fully Associative Cache followed by Set associative and ending with Directly Mapped with the least amount of hits
When the block size is larger, there are usually more hits, and when using write allocate write back

Store hits are pretty consistent between the different caches for their most amount of hits depending on which combinations of settings they are using with fully
associative caches having a slight edge 

The Directly Mapped and Set associative Caches have the least amount of cycles overall 

Hardware perspective: 
Different types of caches have different needs for power, speed, and area
Traditionally, directly mapped have the fastest speed and lowest power in contrast to fully associative and have set associative as middle ground between the two
This is somewhat consistent with our experimental results 

Looking at these results, the set associative cache is the best cache. It is pretty consistent with the fully associative cache for number of load hits and store
hits while also having the least amount of cycles. This means it is both efficient in accessing data as well as saving time (electricity/power, etc)

For gcc.trace, having larger block sizes gave less misses in general

Contributions:
Mac: argument parsing and validation, Directly Associative, Set Associative, Fully Associative
Alexander: reading traces, Best Cache Experiment, Set Associative, Fully Associative