#ifndef CSFHW3_CACHE_H
#define CSFHW3_CACHE_H

#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <queue>
#include <algorithm>

using std::vector;
using std::map;
using std::cout;
using std::cerr;
using std::pair;

#define CACHE_ACCESS_TIME 1
#define MEMORY_ACCESS_TIME 100

typedef unsigned int Address;

typedef enum {
    load, store
} Operation;


//Memory Access struct for every operation and its address
struct Memory_Access {
  Operation op;
  Address address;
};

//types of write and eviction policies
typedef enum { write_through, write_back} Write_Policy;
typedef enum { lru, fifo} Eviction_Policy; // Only matters when not direct mapped

//returning log
static Address ilog2(Address value) {
  //floor rounds down
  return floor(log2(value));
}

//Block struct with address, age of access, valid, dirty bit
struct Block {
    Address tag;
    bool valid;
    bool dirty;
    int age;
};

//comparing age of two blocks
static bool compare(const pair<Address, Block> &a, const pair<Address, Block> &b) {
  return a.second.age < b.second.age;
}

//Set struct containing addresses, number of accesses
struct Set {
  map<Address, Block> blocks;
  int accesses=0;
};

//Cache class 
class Cache {
private:
    //basic parameters
    int block_size, blocks_per_set, no_sets;

    //set up
    vector<Set> sets;
    Write_Policy writePolicy;
    bool writeAllocate;
    Eviction_Policy evictionPolicy;

    //getting the offset of the address 
    Address get_offset(Address address) const {
      return address & (block_size-1);
    }

    //getting the index of the address in the entire set
    Address get_index(Address address) const {
      return (address >>  ilog2(block_size)) & (no_sets - 1);
    }

    //getting the tag of the address vs every address
    Address get_tag(Address address) const {
      return (address >>  ilog2(block_size * no_sets));
    }

    //address exists
    bool has_entry(Address address) {
      Set & set = sets[get_index(address)];
      if(!set.blocks.empty()) {
        auto block = set.blocks.find(get_tag(address));
        return  block != set.blocks.end() && block->second.valid;
      }
      return false;
    }

    //creates a memory access that also updates the cycle
    void create_entry(Address address, int & total_cycles) {
      Set & set = sets[get_index(address)];
      map<Address, Block> & blocks = set.blocks;

      //checks if we need to evict anything
      evict_if_necessary(set, total_cycles);
      // the first block will also happen to have the first block.size()
      blocks[get_tag(address)] = Block {get_tag(address), true, false, set.accesses};
      set.accesses++;
      total_cycles += MEMORY_ACCESS_TIME/4 * block_size;
    }

    //marking the block at the addres as dirty
    void mark_dirty(Address address) {
      Set & set = sets[get_index(address)];
      set.blocks.find(get_tag(address))->second.dirty = true;
    }

    //changing the age of an access
    void renew(Address address) {
      Set & set = sets[get_index(address)];
      // the lower the number the older the age
      set.blocks.find(get_tag(address))->second.age = set.accesses; // why does this help
      set.accesses++;
    }

    //checking to see if we need to evict a block, then evicting it
    void evict_if_necessary(Set & set, int & total_cycles) const {
      map<Address, Block> & blocks = set.blocks;
      int blocks_in_set = (int) blocks.size();
      // we don't normally have to evict if we have a direct mapped set but due to the way map works this is necessary
      if(blocks_in_set == 0) {
        // no need to evict
      } else if (blocks_in_set == blocks_per_set) { // we have to evict in this case
        // find oldest block/furthest accesed
        if (blocks_in_set == 1) {
          auto it = blocks.begin(); //  evict the only element we have
          if (it->second.dirty) {
            total_cycles += MEMORY_ACCESS_TIME/4 * block_size;
          }
          blocks.clear();
        } else {
          if (blocks_in_set == 2) {
            // do special handling so std::min is happy
            Address block = blocks[0].age < blocks[1].age ?
                     blocks[0].tag : blocks[1].tag;
            if (blocks[block].dirty) {
              total_cycles += MEMORY_ACCESS_TIME/4 * block_size;
            }
            blocks.erase(block);
          } else {
            // map<Address, Block> size is not 0, 1, 2
            auto it = *std::min_element(blocks.begin(),blocks.end(), compare);
            //cout << "evicting at " << set.accesses << std::endl;
            if (it.second.dirty) {
              total_cycles += MEMORY_ACCESS_TIME/4 * block_size;
            }
            blocks.erase(it.first);
          }
        }
      }
    }
public:

    //different consturctors for Cache set ups
    Cache(int block_size, int blocks_per_set, int sets) : block_size(block_size),
                                                          blocks_per_set(blocks_per_set),
                                                          no_sets(sets), writePolicy(write_through), writeAllocate(false),
                                                          evictionPolicy(lru)
                                                          {}

    Cache(int block_size, int blocks_per_set, int sets, Write_Policy writePolicy) : block_size(block_size),
                                                          blocks_per_set(blocks_per_set),
                                                          no_sets(sets), writePolicy(writePolicy), writeAllocate(false),
                                                          evictionPolicy(lru) {}
    Cache(int block_size, int blocks_per_set, int sets,
          Write_Policy writePolicy, bool writeAllocate, Eviction_Policy evictionPolicy) : block_size(block_size),
                                                          blocks_per_set(blocks_per_set), no_sets(sets),
                                                          writePolicy(writePolicy), writeAllocate(writeAllocate),
                                                          evictionPolicy(evictionPolicy) {
      // Empty map
      map<Address, Block> empty;
      this->sets = vector<Set>(sets, empty.get_allocator());
    }

    //method to load
    void do_load(Memory_Access access, int & total_cycles, int & total_loads, int & load_hits, int & load_misses) {
      total_loads++;

      //check if has to evict or not
      //check if load is a hit or miss
      if (has_entry(access.address)) {
        if (evictionPolicy == lru) {
          renew(access.address);
        }
        load_hits++;
      } else {
        create_entry(access.address, total_cycles);
        load_misses++;
      }
      total_cycles += CACHE_ACCESS_TIME;
    }

    //check if has to evict or not
    //chec kif store is a hit or miss
    void do_store(Memory_Access access, int & total_cycles, int & total_stores, int & store_hits, int & store_misses) {
      total_stores++;
      if (writeAllocate) {
        if (has_entry(access.address)) {
          if (evictionPolicy == lru) {
            renew(access.address);
          }
          store_hits++;
        } else {
          store_misses++;
          create_entry(access.address, total_cycles);
        }
        total_cycles += CACHE_ACCESS_TIME;
        if (writePolicy == write_through) {
          total_cycles += MEMORY_ACCESS_TIME;
        } else if (writePolicy == write_back){
          mark_dirty(access.address); // this must be written when it gets evicted later
        }
      } else { // no write allocate
        // we write straight to memory whatever happens
        if (has_entry(access.address)) {
          if (evictionPolicy == lru) {
            renew(access.address);
          }
          total_cycles += CACHE_ACCESS_TIME;
          store_hits++;
        } else {
          store_misses ++; // does not modify cache
        }
        total_cycles += MEMORY_ACCESS_TIME;
      }
    }


    //runs trace simulater with vector of Memory_Access structs
    void simulate_traces(vector<Memory_Access> & accesses) {
      int total_loads = 0, total_stores = 0, load_hits = 0,
          load_misses = 0, store_hits = 0, store_misses = 0, total_cycles = 0;

      for (Memory_Access access : accesses) {
        if (access.op == load) {
          do_load(access, total_cycles, total_loads, load_hits, load_misses);
        } else if (access.op == store) {
          do_store(access, total_cycles, total_stores, store_hits, store_misses);
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
    void display_address(Address address) const {
      printf("address %08x\n", address);
      printf("  offset %02x\n", get_offset(address));
      printf("  index %04x\n", get_index(address));
      printf("  tag %03x\n", get_tag(address));
    }
};


#endif //CSFHW3_CACHE_H
