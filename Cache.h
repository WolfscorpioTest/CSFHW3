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

static unsigned int get_offset(unsigned int address, unsigned int block_size) {
  return address & block_size;
}

static unsigned int get_index(unsigned int address, unsigned int block_size, unsigned int blocks) {
  return (address >>  ilog2(block_size)) & blocks;
}



#endif //CSFHW3_CACHE_H
