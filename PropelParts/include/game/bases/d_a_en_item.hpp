#pragma once
#include <game/bases/d_enemy.hpp>

/// @unofficial
class daEnItem_c : public dEn_c {
public:
    enum INTERNAL_TYPE_e {
        TYPE_MUSHROOM = 0,
        TYPE_FIRE_FLOWER,
        TYPE_STAR,
        TYPE_COIN,
        TYPE_ICE_FLOWER,
        TYPE_1UP = 6,
        TYPE_PROPELLER = 11,
        TYPE_MINI_MUSHROOM = 13,
        TYPE_PENGUIN,
        TYPE_MEGA_MUSHROOM,
        TYPE_ALT_COIN,

        // NEW
        TYPE_HAMMER_SUIT = 5,
    };

    int chkItemValid();
    void setInternalTypeSpecific(int isDropMove);

    u8 mPad[0x844];
    int mIsDropMove;
    u8 mPad2[0x20];
    int mItemType; ///< Raw type from mParam
    u8 mPad3[0x3A];
    short mInternalType;
};
