# Notes

## Need for Memory Management
* Allocate, Deallcoate memory for processes
* Expand the memory(virtual memory, swapping)
* Handle non contiguous memory
* Independent address space for each process

# Memory Mapping
* Absolute vs Relative addressing (base + offset)
* Do any software piece runs with absolute addresses?
* Logical vs Physical memory
* Logical address vs Physical address
* Page vs Frame
* Who does the mapping in modern architectures?

# Page Tables, Page Table Entries 
* Pages as the basic unit of memory management
* Page Size - cons and pros
* Offset within logical page, physical frame
* Page Table Entry(PTE)
* Page no.s are sequential but not mapped frame numbers
* Contiguous Virtual Memory -> Non Contiguous Physical memory
* Complexity of finding PTE in Page table?
* Per process addressable memory

# Page Faults
* Page out, Page in
* Valid bit in PTE
* Loading a page when page fault occurs (Page fault excpetion handler)
* Page Fault Ratio
* Locality of reference principle - Temporal, Spatial locality

# Caching PTEs
* TLB Cache
* Cache hit vs Cache miss
* Locality of reference principle

# Other concepts
* Demand paging / Lazy Allocation

* Major vs Minor page faults
* Page Replacement Algorithms

* Dirty bit
* Copy on write
* Thrashing
* Page locking techniques
* Pagin Daemom

# Analysis
* cat /proc/<pid>/maps
* pmap





