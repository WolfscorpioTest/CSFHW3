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
typedef enum { lru, fifo} Eviction_Policy; // Only matters when not direct mapped

static Address ilog2(Address value) {
  return floor(log2(value));
}


struct Block {
    Address tag;
    bool valid;
    bool dirty;
    int age;
};

static bool compare(const map<Address, Block>::iterator &a, const map<Address, Block>::iterator &b) {
  return a->second.age < b->second.age;
}

struct Set {
  map<Address, Block> blocks;
  int count;
};

class Cache {
private:
    int block_size, blocks_per_set, no_sets;
    vector<Set> sets;
    Write_Policy writePolicy;
    bool writeAllocate;
    Eviction_Policy evictionPolicy;

    Address get_offset(Address address) const {
      return address & (block_size-1);
    }

    Address get_index(Address address) const {
      return (address >>  ilog2(block_size)) & (no_sets - 1);
    }

    Address get_tag(Address address) const {
      return (address >>  ilog2(block_size * no_sets));
    }

    bool has_entry(Address address) {
      Set & set = sets[get_index(address)];
      if(!set.blocks.empty()) {
        auto block = set.blocks.find(get_tag(address));
        return  block != set.blocks.end() && block->second.valid;
      }
      return false;
    }

    void create_entry(Address address, int & total_cycles) {
      Set & set = sets[get_index(address)];
      map<Address, Block> & blocks = set.blocks;
      evict_if_necessary(address,set, total_cycles);
      // the first block will also happen to have the first block.size()
      blocks[get_tag(address)] = Block {get_tag(address), true, false, (int) blocks.size()};
      set.count++;
      total_cycles += MEMORY_ACCESS_TIME/4 * block_size;
    }

    void mark_dirty(Address address) {
      Set & set = sets[get_index(address)];
      set.blocks.find(get_tag(address))->second.dirty = true;
    }
    void renew(Address address) {
      Set & set = sets[get_index(address)];
      // the lower the number the older the age
      set.blocks.find(get_tag(address))->second.age = (int) set.blocks.size();
      set.count++;
    }
    void evict_if_necessary(Address address, Set & set, int & total_cycles) const {
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
          auto it = std::min(blocks.begin(),blocks.end(), compare);
          if (blocks_in_set == 2) {
            // do special handling so std::min is happy
            Address block = blocks[0].age < blocks[1].age ?
                     blocks[0].tag : blocks[1].tag;
            if (blocks[block].dirty) {
              total_cycles += MEMORY_ACCESS_TIME/4 * block_size;
            }
            blocks.erase(block);
          } else {
            //cout << "evicting at " << set.count << std::endl;
            if (it->second.dirty) {
              total_cycles += MEMORY_ACCESS_TIME/4 * block_size;
            }
            blocks.erase(it);
          }
        }
      }
    }
public:
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

    void do_load(Memory_Access access, int & total_cycles, int & total_loads, int & load_hits, int & load_misses) {
      total_loads++;
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
      } else {
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

    void simulate_traces(vector<Memory_Access> & accesses) {
      int total_loads = 0, total_stores = 0, load_hits = 0,
          load_misses = 0, store_hits = 0, store_misses = 0, total_cycles = 0;
      
      //queue<Memory_Access> order;

      /*
      if (cachetype == 0) {
       */
      //direct mapped
      for (Memory_Access access : accesses) {
        if (access.op == load) {
          do_load(access, total_cycles, total_loads, load_hits, load_misses);
        } else if (access.op == store) {
          do_store(access, total_cycles, total_stores, store_hits, store_misses);
          /*
          if (has_entry(access.address)) {
            if (writePolicy == write_through) {
              // write immediately from cache to memory
              total_cycles += MEMORY_ACCESS_TIME;
            } else if (writePolicy == write_back) {
              // defer
            }
            //total_cycles += CACHE_ACCESS_TIME;
            store_hits++;
          } else {

            store_misses++;
          }
          */
        }
      }
      /*
      }
      else if (cachetype == 1) { //set associative 

      }
      
      else if (cachetype == 2) { //fully associative
      int blocksfilled = 0;
        if(Eviction_Policy == lru) {
            vector<address> lruorder;
            for(Memory_Access access : accesses) {
              //lru set up
              if (std::find(lruorder.begin(), lruorder.end(), access.address) != v.end()) {
                address temp = access.address;
                lruorder.erase(std::find(lruorder.begin(), lruorder.end(), access.address));
                lruorder.push_back(temp);
              }
              else {
                lruorder.insert(access.address);
              }

              if (access.op == load) {
                
              }
              else if (access.op == store) {
                if(blocksfilled < block_size*sets) {
                  blocksfilled++;
                }
                if (blocksfilled == block_size*sets) {

                }
              }
            }
        } else if (Eviction_Policy == fifo) {
            queue<address> fifoorder
            for(Memory_Access access : accesses) {
              //lru set up
              if (std::find(fifoorder.begin(), fifoorder.end(), access.address) != v.end()) {
               //find element?
              }
              else {
                fifoorder.push(access.address);
              }

              if (access.op == load) {
                
              }
              else if (access.op == store) {
                if(blocksfilled < block_size*sets) {
                  blocksfilled++;
                }
                if (blocksfilled == block_size*sets) {
                  fifoorder.pop();
                  fifoorder.push(access);
                }

              }
            }
        }
      }*/
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
