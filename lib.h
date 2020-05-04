#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>
#include <ctime>
#include "portable_endian.h"

template<typename T>
void sorting(std::vector<T> &v, T f_out)
{
  std::sort(v.begin(), v.end());

  std::string fname = std::to_string(f_out);
  std::ofstream file(fname, std::ios::trunc | std::ios::binary );
  if (file)
  {
    for(auto i: v)
    {
      file << i;
      if (i != v.back())
        file << std::endl;
    }
  }
  file.close();
  v.clear();
}

uint64_t read(std::ifstream &file, uint64_t limit)
{
  std::vector<uint64_t> v;
  uint64_t count = 0;
  uint64_t f_out = 0;
  uint64_t little_endian;
  while(file.read((char*)&little_endian, sizeof(uint64_t)))
  {
     v.push_back(le64toh(little_endian));
     if (count >= limit)
     {
       sorting(v, f_out);
       count = 0;
       ++f_out;
     }
     else
      ++count;
  }
  if (!v.empty())
    sorting(v, f_out);
  else
    --f_out;
  return f_out; 
}

uint64_t get_value(std::ifstream &file)
{
  std::string line;
  std::getline(file, line);
  return std::stoull(line,nullptr,0);
}

void sorting_in_file(uint64_t f_in1, uint64_t f_in2, uint64_t f_out)
{
  std::ifstream file1;
  std::string f_in_name1 = std::to_string(f_in1);
  file1.open(f_in_name1);
  if(!file1)
		{ std::cerr << "Open file error " << f_in1 << "\n"; exit(-1); }

  std::ifstream file2;
  std::string f_in_name2 = std::to_string(f_in2);
  file2.open(f_in_name2);
  if(!file2)
		{ std::cerr << "Open file error " << f_in2 << "\n"; exit(-1); }

  std::string f_out_name = std::to_string(f_out);
  std::ofstream out_file(f_out_name, std::ios::trunc | std::ios::binary );
  if(!out_file)
		{ std::cerr << "Open file error " << f_out << "\n"; exit(-1); }

  uint64_t a = get_value(file1);
  uint64_t b = get_value(file2);
  while(!file1.eof() && !file2.eof())
  {
    if (a < b )
    {
      out_file << a << std::endl;
      a = get_value(file1);
    }
    else
    {
      out_file << b << std::endl;
      b = get_value(file2);
    }
  }

  while (!file1.eof())
  {
    if (a < b)
    {
      out_file << a << std::endl;
      a = get_value(file1);
    }
    else
    {
      out_file << b << std::endl;
      b = get_value(file1);
    }
  }
  while (!file2.eof())
  {
    if (a < b)
    {
      out_file << a << std::endl;
      a = get_value(file2);
    }
    else
    {
      out_file << b << std::endl;
      b = get_value(file2);
    }
  }
  a < b? out_file << a << std::endl << b : out_file << b << std::endl << a;
  
  file1.close();
  file2.close();
  out_file.close();

  remove(f_in_name1.c_str());
  remove(f_in_name2.c_str());
}

void write_to_file(const char* f_out, uint64_t f_in)
{
  std::ifstream file;
  std::string f_in_name = std::to_string(f_in);
  file.open(f_in_name);
  if(!file)
		{ std::cerr << "Open file error " << f_in_name << "\n"; exit(-1); }
  
  std::ofstream out_file(f_out, std::ios::trunc | std::ios::binary );
  if (out_file)
  {
    for (std::string line; std::getline(file, line);)
    {
      uint64_t data = std::stoull(line,nullptr,0);
      data = htole64(data);
      out_file.write((char*)&data, sizeof(uint64_t));
    }
  }
  file.close();
  out_file.close();
  remove(f_in_name.c_str());
}

void generation(const uint64_t limit)
{
  std::mt19937 gen(std::time(nullptr)); 
  std::uniform_int_distribution<> dis(1, 65535);

  std::vector<uint64_t> data;

  for(uint64_t i = 0; i < limit; ++i)
  {
    data.push_back(dis(gen));
  }

  std::ofstream out_file("data.bin", std::ios::trunc | std::ios::binary );
  if (out_file)
  {
    for(auto i:data)
      out_file.write( (char*)&i,sizeof(uint64_t));
  }
  out_file.close();

  std::sort(data.begin(),data.end());

  std::ofstream out_file_sort("data_sort.bin", std::ios::trunc | std::ios::binary );
  if (out_file_sort)
  {
    for(auto i:data)
    {
      out_file_sort.write((char*)&i, sizeof(i));
    }
  }
  out_file_sort.close();
  
  std::ofstream _out_file_sort("data_sort.txt", std::ios::trunc | std::ios::binary );
  if (_out_file_sort)
  {
    for(auto i:data)
    {
      _out_file_sort << i;
      if (i != data.back())
        _out_file_sort << std::endl;
    }
  }
  _out_file_sort.close();
  
}