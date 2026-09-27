#pragma once
#include <game/bases/d_enemy.hpp>

/// @unofficial
class daMiniGameWireMesh_c : public dEn_c {
public:
    int getItemType();
    void EffectItemGet();

    u8 mPad[0x3AC];
    m3d::anmTexPat_c mAnmTexPat;
};
