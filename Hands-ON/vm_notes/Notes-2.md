# Notes

* Page mapping for kernel space (but no page out)
* Slab Memory
* Buddy Allocator
* kmalloc vs vmalloc

## Kernel Hints
* struct page (for physical pages)
  * page flags (page-flags.h)
  * _count, page_count
  * virtual, NULL for pages not mapped (highmem)
* Zones (struct zone, mmzone.h)
  * ZONE_DMA, ZONE_DMA32
  * ZONE_NORMAL (Low memory, around 896MB, kernel pages)
  * ZONE_HIGHMEM (High memory,not mapped to kernel space)
* Page APIs from gfp.h, gfp_mask  
  * alloc_pages 
  * page_address
  * __get_free_pages (contiguous mem)
  * alloc_page, __get_free_page
  * get_zeroed_page
  * __free_pages
  * free_pages
  * free_page
* kmalloc, kfree
* gfp_mask (gfp:get free pages)
  * Zone modifiers - __GFP_DMA, __GFP_DMA32, __GFP_HIGHMEM
  * Action modifiers
  * Type modifiers
* vmalloc, vfree
* Slab Memory
  * Object cache
  * caches, specific to popular objects
  * kmalloc based on g.p caches
  * Slab states - full, partial, empty
  * kmem_cache - slabs_full, slabs_empty, slabs_partial : kmem_list3
  * struct slab, slab descriptor
  * internally uses __get_free_pages
  * kmem_getpages, kmem_getpage, kmem_cache_alloc, 
  * kmem_cache_free, kmem_cache_destroy
* Permanent Mapping - kmap, kunmap
* struct mm, vm_area_struct
