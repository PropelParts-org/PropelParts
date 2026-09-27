#include <kamek.h>
#include <game/bases/d_mj2d_data.hpp>
#include <game/bases/d_a_mini_game_wire_mesh_mgr_obj.hpp>

// daMiniGameWireMeshMgrObj_c_classInit()
kmBranchDefCpp(0x8086A070, NULL, daMiniGameWireMeshMgrObj_c *) {
    return new daMiniGameWireMeshMgrObj_c;
}

// Set panel dummy item ID to 10
kmWrite16(0x8086A2BA, 10);

// Set item counts to 0
kmBranchDefAsm(0x8086A544, 0x8086A560) {
    stw r5, 0x708(r29)
    stw r5, 0x70C(r29)
    stw r5, 0x710(r29)
    stw r5, 0x714(r29)
    stw r5, 0x718(r29)
    stw r5, 0x71C(r29)
    stw r5, 0x720(r29)
    stw r5, 0x724(r29)
}

// Fix item count offsets
kmWrite16(0x8086BF66, offsetof(daMiniGameWireMeshMgrObj_c, mNewWinItems[0]));
kmWrite16(0x8086B296, offsetof(daMiniGameWireMeshMgrObj_c, mNewWinItems[0]));

// Item count fix
kmWrite16(0x8086B2AA, NEW_ITEM_COUNT);

// Fix savefile StockItem offset
kmWrite16(0x8086B27A, 0x969);

// daMiniGameWireMeshMgrObj_c::setItem()
kmBranchDefCpp(0x8086A990, NULL, void, daMiniGameWireMeshMgrObj_c *this_, int itemType) {
    this_->mWinItemCount += 1;

    // Basically we're converting the Flip Panel item IDs to StockItem IDs
    switch (itemType) {
        case 0:
            this_->mNewWinItems[ITEM_MUSHROOM] += 1;
            break;
        case 1:
            this_->mNewWinItems[ITEM_MINI_MUSHROOM] += 1;
            break;
        case 2:
            this_->mNewWinItems[ITEM_FIRE_FLOWER] += 1;
            break;
        case 3:
            this_->mNewWinItems[ITEM_ICE_FLOWER] += 1;
            break;
        case 4:
            this_->mNewWinItems[ITEM_PENGUIN_SUIT] += 1;
            break;
        case 5:
            this_->mNewWinItems[ITEM_PROPELLER_SHROOM] += 1;
            break;
        case 6:
            this_->mNewWinItems[ITEM_STAR_POWER] += 1;
            break;
        case 9: // NEW
            this_->mNewWinItems[ITEM_HAMMER_SUIT] += 1;
            break;
    }
}

// TODO
// 0x8086b230 sets stockItem, class itself needs expansion to have room for 8th item to keep track of (plus some layout edits)
