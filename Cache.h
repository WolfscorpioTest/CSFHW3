#ifndef CSFHW3_CACHE_H
#define CSFHW3_CACHE_H

#include <vector>
#include <map>
#include <cmath>
#include <iostream>

using std::vector;
using std::map;
using std::cout;

#define CACHE_ACCESS_TIME 1
#define MEMORY_ACCESS_TIME 100

typedef unsigned int Address;

typedef enum {
    load, store
} Operation;

struct Memory_Access {
  Operation op;
  Address address;
};

typedef enum { write_through, write_back} Write_Policy;
typedef enum { lru, fifo} Eviction_Policy;

static Address ilog2(Address value) {
  return floor(log2(value));
}


struct Cache_Entry {
    Address tag;
    bool valid;
};

class Cache {
private:
    int block_size, blocks_per_set, sets;
    map<Address, Cache_Entry> entries;
    Write_Policy writePolicy;
    bool writeAllocate;

    Address get_offset(Address address) {
      return address & (block_size-1);
    }

    Address get_index(Address address) {
      return (address >>  ilog2(block_size)) & (sets - 1);
    }

    Address get_tag(Address address) {
      return (address >>  ilog2(block_size * sets));
    }

    bool has_entry(Address address) {
      Cache_Entry entry = entries[get_index(address)];
      if (entry.tag == get_tag(address)) {
        return entry.valid;
      }
      return false;
    }
public:
    Cache(int block_size, int blocks_per_set, int sets) : block_size(block_size),
                                                          blocks_per_set(blocks_per_set),
                                                          sets(sets), writePolicy(write_through), writeAllocate(false) {}
    Cache(int block_size, int blocks_per_set, int sets, Write_Policy writePolicy) : block_size(block_size),
                                                          blocks_per_set(blocks_per_set),
                                                          sets(sets), writePolicy(writePolicy), writeAllocate(false) {}
    Cache(int block_size, int blocks_per_set, int sets,
          Write_Policy writePolicy, bool writeAllocate) : block_size(block_size), blocks_per_set(blocks_per_set),
                                                          sets(sets), writePolicy(writePolicy),
                                                          writeAllocate(writeAllocate) {}

    void simulate_traces(vector<Memory_Access> & accesses) {
      int cachetype;
      if (blocks_per_set == 1 && sets > 1) {
        cachetype = 0; //direct map
      } else if (blocks_per_set > 1 && sets > 1) {
        cachetype = 1; //set associative
      } else if (blocks_per_set > 1 && sets == 1) {
        cachetype = 2; //fully associative
      }  else {
        cerr << "This cache is not possible" << endl;
        break;
      }
      int total_loads = 0, total_stores = 0, load_hits = 0,
          load_misses = 0, store_hits = 0, store_misses = 0, total_cycles = 0;

      for (Memory_Access access : accesses) {
        if (access.op == load) {
          total_loads++;
          if (has_entry(access.address)) {
            load_hits++;
            total_cycles += CACHE_ACCESS_TIME;
          } else {
            // no choice for eviction in direct-mapped cache
            if (blocks_per_set == 1) {
              entries[get_index(access.address)] = Cache_Entry {get_tag(access.address), true};
            }
            total_cycles += MEMORY_ACCESS_TIME;
            load_misses++;
          }
        } else if (access.op == store) {
          total_stores++;
          if (has_entry(access.address)) {
            if (writePolicy == write_through) {
              // write directly from cache to memory
              total_cycles += CACHE_ACCESS_TIME;
            } else if (writePolicy == write_back) {
              // defer
            }
            store_hits++;
          } else {
            if (writeAllocate) {
              entries[get_index(access.address)] = Cache_Entry {get_tag(access.address), true};
            } else {
              total_cycles += MEMORY_ACCESS_TIME;
            }
            store_misses++;
          }
        }
      }
        //display_address(access.address);
      std::cout << "Total loads: " << total_loads << std::endl;
      std::cout << "Total stores: " << total_stores << std::endl;
      std::cout << "Load hits: " << load_hits << std::endl;
      std::cout << "Load misses: " << load_misses << std::endl;
      std::cout << "Store hits: " << store_hits << std::endl;
      std::cout << "Store misses: " << store_misses << std::endl;
      std::cout << "Total cycles: " << total_cycles << std::endl;
    }
    void display_address(Address address) {
      printf("address %08x\n", address);
      printf("  offset %02x\n", get_offset(address));
      printf("  index %04x\n", get_index(address));
      printf("  tag %03x\n", get_tag(address));
    }
};


#endif //CSFHW3_CACHE_H
