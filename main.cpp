#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>

#include "Cache.h"

using std::cerr;
using std::endl;
using std::stoi;

#define INVALID_USAGE_CODE 64

typedef enum { write_through, write_back} Write_Policy;
typedef enum { lru, fifo} Eviction_Policy;

// sizes in cache must be powers of two
bool is_power_of_two(unsigned int value) {
  if (value == 1) {
    return true;
  } else if (value % 2 != 0 || value == 0) {
    return false;
  }
  return is_power_of_two(value / 2);
}

bool read_args(char* argv[], int &sets, int &blocks, int &block_size, bool &write_allocate,
               Write_Policy &write_policy, Eviction_Policy &eviction_policy) {
  bool valid = true;
  // read the three integer arguments
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
    block_size = stoi(argv[3]);
  }
  catch (...) {
    cerr << "Invalid parameter: can't parse number of bytes per block: " << argv[3]  << "." << endl;
    valid = false;
  }

  // read this string argument as boolean
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

  // read the next two string arguments into their enum types
  if(strcmp(argv[5], "write-through") == 0) {
    write_policy = write_through;
  } else {
    if(strcmp(argv[5],"write-back") == 0) {
      write_policy = write_back;
    } else {
      cerr << "Invalid parameter: option for memory access " <<
           argv[5] << " does not exist. Must use write-through or write-back." << endl;
      valid = false;
   }
  }

  if(strcmp(argv[6], "lru") == 0) {
    eviction_policy = lru;
  } else {
    if(strcmp(argv[6],"fifo") == 0) {
      eviction_policy = fifo;
    } else {
      cerr << "Invalid parameter: option for eviction_policy " <<
           argv[6] << " does not exist. Must use lru or fifo." << endl;
      valid = false;
    }
  }

  return valid;
}

bool validate_args(int sets, int blocks, int block_size, bool write_allocate,
                   Write_Policy write_policy) {
  bool valid = true;
  if (!is_power_of_two(sets)) {
    cerr << "Invalid parameter: number of sets: " << sets << " must be a positive power of 2." << endl;
    valid = false;
  }
  if (!is_power_of_two(blocks)) {
    cerr << "Invalid parameter: number of blocks: " << block_size << " must be a positive power of 2." << endl;
    valid = false;
  }
  // each block must be at least 4 bytes to preserve memory alignment
  if (block_size < 4 || !is_power_of_two(block_size)) {
    cerr << "Invalid parameter: number of sets: " << block_size << " must be a positive power of 2 at least 4." << endl;
    valid = false;
  }
  // this combination results in an invalid state
  if (!write_allocate && write_policy == write_back) {
    cerr << "Invalid parameter: no-write-allocate cannot be combined with write-back" << endl;
    valid = false;
  }
  return valid;
}
std::string string[] splitstring(string s){
  std::string parts[3];
  int counter = 0;
  while (ss >> word) { // Extract word from the stream.
        parts[counter] << word << endl;
        counter++;
  }
  return parts;
}

int main(int argc, char* argv[]) {
  // print out usage if wrong number of arguments is given
  if(argc != 7) {
    cerr << "Invalid usage: must be invoked with 6 arguments. e.g." << endl;
    cerr << "./csim 256 4 16 write-allocate write-back lru < sometracefile" << endl;
    return INVALID_USAGE_CODE;
  }
  // cache properties
  int sets, blocks, block_size;
  bool write_allocate;
  Write_Policy write_policy;
  Eviction_Policy eviction_policy;
  // read input arguments: can exit early here if parsing error happens
  if(!read_args(argv, sets, blocks, block_size, write_allocate, write_policy, eviction_policy)) {
    return INVALID_USAGE_CODE;
  }
  // validate input arguments: can exit early if arguments are invalid
  if(!validate_args(sets, blocks, block_size, write_allocate, write_policy)) {
    return INVALID_USAGE_CODE; // invalid usage
  }


  std::string cache [sets*blocks];
  int counter = 0;
  std::ifstream file (argv[6]);
  while (std::getline(file, cache[counter])) { 
    counter++;
  }

  for (int i = 0 ; i < sets*blocks ; i++){
    //method to split up string


  }




  // load from standard input

  // vector of memory accesses
  vector<Memory_Access> accesses;



  return 0;
}
