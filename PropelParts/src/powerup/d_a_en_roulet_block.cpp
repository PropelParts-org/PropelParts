#include <kamek.h>
#include <game/bases/d_a_en_roulet_block.hpp>

const float daEnRouletBlock_c::sc_rollFrames[][4] = {
    {0.0f, 3.0f, 1.0f, 2.0f}, // Fire Flower
    {0.0f, 4.0f, 1.0f, 2.0f}, // Propeller
    {0.0f, 5.0f, 1.0f, 2.0f}, // Ice Flower
    {0.0f, 6.0f, 1.0f, 2.0f}, // Penguin
    {0.0f, 7.0f, 1.0f, 2.0f}  // Hammer Suit
};

extern "C" void sc_rollFrames__17daEnRouletBlock_c(void);

// Allow for Hammer Suit as possible mParam value
// This makes it read mParam & 7, which I think is kinda weird
// but I don't know of a better way to allow for a value of 4
kmWrite32(0x80A9A5CC, 0x5400077E);

// Read new TexPAT frame table
kmCallDefAsm(0x80A9AE34) {
    lis r5, sc_rollFrames__17daEnRouletBlock_c@h
    ori r5, r5, sc_rollFrames__17daEnRouletBlock_c@l
    blr
}

// Add Hammer Suit to item type table
kmWrite32(0x80AD41C4, 17);
