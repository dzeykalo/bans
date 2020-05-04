
#include "lib.h"

int main(int argc, char* argv[]) 
{
  uint64_t limit = 30000000;

  if (argc == 2) // file generation data.bin data_sort.bin data_sort.txt
  { 
    limit = std::stoul(argv[1],nullptr,0);
    generation(limit);
  }
  else if (argc > 2) // sorting in to out
  {
    if (argc > 3)
      limit = std::stoul(argv[3],nullptr,0);
    
    std::ifstream file;
    file.open(argv[1], std::ios::binary);
    if(!file)
      { std::cerr << "Open file error " << argv[1] << "\n"; exit(-1); }
    uint64_t f_out = read(file, limit);
    file.close();

    for(uint64_t f_in = 0; f_in < f_out; f_in+=2)
    {
      ++f_out;
      std::string out_name  = std::to_string(f_out);
      sorting_in_file(f_in, f_in+1, f_out);
    }
    write_to_file(argv[2], f_out);
  } 
  else
    { std::cerr << "no input and output file\n"; exit(-1); }
  
  return 0;
}

