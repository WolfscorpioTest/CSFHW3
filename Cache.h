#ifndef CSFHW3_CACHE_H
#define CSFHW3_CACHE_H

#include <vector>
#include <cmath>

using std::vector;

typedef enum {
    load, store
} Operation;

struct Memory_Access {
  Operation op;
  unsigned int address;
};

static unsigned int ilog2(unsigned int value) {
  return floor(log2(value));
}


struct Cache_Entry {
    bool valid;
    unsigned int tag; // address of set
    unsigned int address; // address of block
    unsigned int offset; // address within block
};

class Cache {
protected:
    int block_size, blocks_per_set, sets;
    virtual unsigned int get_offset(unsigned int address) = 0;
    virtual unsigned int get_index(unsigned int address) = 0;
    virtual unsigned int get_tag(unsigned int address) = 0;
public:
    Cache(int block_size, int blocks_per_set, int sets) : block_size(block_size),
                                                          blocks_per_set(blocks_per_set),
                                                          sets(sets) {}
    virtual void simulate_traces(vector<Memory_Access> accesses) = 0;
    void display_address(unsigned int address) {
      printf("address %08x\n", address);
      printf("  offset %02x\n", get_offset(address));
      printf("  index %04x\n", get_index(address));
      printf("  tag %03x\n", get_tag(address));
    }
};

class DirectMappedCache : public virtual Cache {
public:
    DirectMappedCache(int block_size, int sets) : Cache(block_size, 1, sets) {}

    void simulate_traces(vector<Memory_Access> accesses) override {

    }

private:
    unsigned int get_offset(unsigned int address) override {
      return address & (block_size-1);
    }

    unsigned int get_index(unsigned int address) override {
      return (address >>  ilog2(block_size)) & (sets - 1);
    }

    unsigned int get_tag(unsigned int address) override {
      return (address >>  ilog2(block_size * sets));
    }

};

#endif //CSFHW3_CACHE_H
