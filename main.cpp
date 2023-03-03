#include <iostream>
#include <cstring>

using std::cerr;
using std::endl;
using std::stoi;

#define INVALID_USAGE_CODE 64

typedef enum { write_through, write_back} Memory_Access;
typedef enum { lru, fifo} Eviction;

bool is_power_of_two(unsigned int value) {
  if (value == 1) {
    return true;
  } else if (value % 2 != 0 || value == 0) {
    return false;
  }
  return is_power_of_two(value / 2);
}

bool read_args(char* argv[], int &sets, int &blocks, int &bytes_per_block, bool &write_allocate,
               Memory_Access &memory_access, Eviction &eviction) {
  bool valid = true;

  try {
    sets = stoi(argv[1]);
  }
  catch (...) {
    cerr << "Invalid parameter: can't parse number of sets: " << argv[1] << "." << endl;
    valid = false;
  }

  try {
    blocks = stoi(argv[2]);
  }
  catch (...) {
    cerr << "Invalid parameter: can't parse number of blocks: " << argv[2] << "." << endl;
    valid = false;
  }

  try {
    bytes_per_block = stoi(argv[3]);
  }
  catch (...) {
    cerr << "Invalid parameter: can't parse number of bytes per block: " << argv[3]  << "." << endl;
    valid = false;
  }

  if((strcmp(argv[4], "write-allocate") == 0)) {
    write_allocate = true;
  } else {
    if(strcmp(argv[4],"no-write-allocate") == 0) {
      write_allocate = false;
    } else {
      cerr << "Invalid parameter: option for write allocation " <<
           argv[4] << " does not exist. Must use write-allocate or no-write-allocate." << endl;
      valid = false;
    }
  }

  if(strcmp(argv[5], "write-through") == 0) {
    memory_access = write_through;
  } else {
    if(strcmp(argv[5],"write-back") == 0) {
    memory_access = write_back;
    } else {
      cerr << "Invalid parameter: option for memory access " <<
           argv[5] << " does not exist. Must use write-through or write-back." << endl;
      valid = false;
   }
  }

  if(strcmp(argv[6], "lru") == 0) {
    eviction = lru;
  } else {
    if(strcmp(argv[6],"fifo") == 0) {
      eviction = fifo;
    } else {
      cerr << "Invalid parameter: option for eviction " <<
           argv[6] << " does not exist. Must use lru or fifo." << endl;
      valid = false;
    }
  }

  return valid;
}

bool validate_args(int sets, int blocks, int bytes_per_block, bool write_allocate,
                   Memory_Access memory_access) {
  bool valid = true;
  if (!is_power_of_two(sets)) {
    cerr << "Invalid parameter: number of sets: " << sets << " must be a positive power of 2." << endl;
    valid = false;
  }
  if (!is_power_of_two(blocks)) {
    cerr << "Invalid parameter: number of blocks: " << bytes_per_block << " must be a positive power of 2." << endl;
    valid = false;
  }
  if (bytes_per_block < 4 || !is_power_of_two(bytes_per_block)) {
    cerr << "Invalid parameter: number of sets: " << bytes_per_block << " must be a positive power of 2 at least 4." << endl;
    valid = false;
  }
  if (!write_allocate && memory_access == write_back) {
    cerr << "Invalid parameter: no-write-allocate cannot be combined with write-back" << endl;
    valid = false;
  }
  return valid;
}

int main(int argc, char* argv[]) {
  if(argc != 7) {
    cerr << "Invalid usage: must be invoked with 6 arguments. e.g." << endl;
    cerr << "./csim 256 4 16 write-allocate write-back lru < sometracefile" << endl;
    return INVALID_USAGE_CODE;
  }
  int sets, blocks, bytes_per_block;
  bool write_allocate;
  Memory_Access memory_access;
  Eviction eviction;
  if(!read_args(argv, sets, blocks, bytes_per_block, write_allocate, memory_access, eviction)) {
    return INVALID_USAGE_CODE;
  }
  if(!validate_args(sets, blocks, bytes_per_block, write_allocate, memory_access)) {
    return INVALID_USAGE_CODE; // invalid usage
  }
  return 0;
}
