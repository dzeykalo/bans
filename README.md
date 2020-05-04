# Bans

Merge sort out of file

## Conditions

```
1. 256 MB of RAM
2. byte order little endian
3. File 64 bit unsigned integer number
```

## Example

```c
bans 100 // generating 100 values ​​in binary file data.bin. data_sort - sorted file to check.
bans input_file output_file 100  // input file sorting to output file. 100 - memory limit.  
                                 // Default limit 30.000.000 values ~ 229 Mb memory. limit * sizeof(uint64_t) 
```