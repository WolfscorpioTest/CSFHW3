Mac Millan nmacmil1
Alexander Shen ashen12

Part b: Best Cache Experiment
The experiment should be run on a large trace file 
We decided to choose gcc.trace 
the size for all caches will be 256 and number of bytes per block is 16
Each type of cache will need to be tested for combinations of 
write-allocate write-through
write-allocate write-back
no-write-allocate write-through

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
LRU:
1. write-allocate write-through: 256 4 16
Total loads: 318197
Total stores: 197486
Load hits: 314798
Load misses: 3399
Store hits: 188250
Store misses: 9236
Total cycles: 25318283

2. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 314798
Load misses: 3399
Store hits: 188250
Store misses 9236
Total cycles: 9344483

3. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 311613
Load misses: 6584
Store hits: 164819
Store misses: 32667
Total cycles: 22865216

FIFO:
4. write-allocate write-through: 256 4 16
Total loads: 318197
Total stores: 197486
Load hits: 314171
Load misses: 4026
Store hits: 188047
Store misses: 9439
Total cycles: 25650283

5. write-allocate write-back
Total loads: 318197
Total stores: 197486
Load hits: 314171
Load misses: 4026
Store hits: 188047
Store misses: 9439
Total cycles: 9845283

6. no-write-allocate write-through
Total loads: 318197
Total stores: 197486
Load hits: 311017
Load misses: 7180
Store hits: 163705
Store misses: 33781
Total cycles: 23102502

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

The most load hits are from

The most store hits are from

The Least Amount of cycles

Hardware perspective: 

Contributions:
Mac: argument parsing and validation, Directly Associative, Set Associative, Fully Associative
Alexander: reading traces, Best Cache Experiment, Set Associative, Fully Associative