#include <kamek.h>

// The base player model class only allocates 0xC000 bytes in the allocator, we change that so it allocates dynamically
kmWrite32(0x800d56a0, 0x3880ffff);