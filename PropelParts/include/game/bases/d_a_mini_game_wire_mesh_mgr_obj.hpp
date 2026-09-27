#pragma once
#include <game/bases/d_base.hpp>
#include <constants/game_constants.h>

/// @unofficial
class daMiniGameWireMeshMgrObj_c : public dBase_c {
public:
    daMiniGameWireMeshMgrObj_c();

    u8 mPad[0x178];
    int mWinItemCount;
    u8 mPad2[0x51C];

    // New
    int mNewWinItems[NEW_ITEM_COUNT];
};
