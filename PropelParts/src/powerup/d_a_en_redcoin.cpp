#include <kamek.h>
#include <game/bases/d_a_en_redcoin.hpp>

// Red ring respects custom powerups
kmWrite32(0x80A942EC, 0x28000005);

// Read 7 bits for item type
kmWrite32(0x80A94038, 0x5400E77E);

const int daEnRedcoin_c::sc_itemTypes[] = {
    0x9,  // Fire Flower
    0x15, // Propeller
    0x11, // Penguin
    0xE,  // Ice Flower
    0x6,  // Hammer Suit
    0, 0, 0
};

extern "C" void sc_itemTypes__13daEnRedcoin_c(void);

// Read new item table
kmCallDefAsm(0x80A94278) {
    lis r28, sc_itemTypes__13daEnRedcoin_c@h
    ori r28, r28, sc_itemTypes__13daEnRedcoin_c@l
    blr
}
