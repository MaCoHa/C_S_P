# C_S_P

Run: `g++ -std=c++20 filename -o output.o`

Run with CMake: `cmake CMakeLists.txt` and then `make` (since cmake creates the make and the make creates the binary)

## CPU info
```bash 
group42@dionysos:~$ numactl --hardware
available: 2 nodes (0-1)
node 0 cpus: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
node 0 size: 64132 MB
node 0 free: 58741 MB
node 1 cpus: 1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31
node 1 size: 64454 MB
node 1 free: 61728 MB
node distances:
node   0   1 
  0:  10  21 
  1:  21  10 
```

Get picture of cpu:
Run: `lstopo --output-format png output.png`