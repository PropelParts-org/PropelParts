#include <kamek.h>
#include <game/bases/d_a_mini_game_wire_mesh.hpp>
#include <game/mLib/m_effect.hpp>

// daMiniGameWireMesh_c::EffectItemGet()
kmBranchDefCpp(0x80869530, NULL, void, daMiniGameWireMesh_c *this_) {
    const char *name = ""; // Retail game does nullptr here, which crashes custom items...
    mVec3_c efPos(this_->mPos.x, this_->mPos.y, 5500.0f);
    int type = this_->getItemType();

    const char *sc_effNames[] = {
        "Wm_mg_itemget_kn",
        "Wm_mg_itemget_mm",
        "Wm_mg_itemget_fl",
        "Wm_mg_itemget_if",
        "Wm_mg_itemget_pn",
        "Wm_mg_itemget_pr",
        "Wm_mg_itemget_st",
        "Wm_mg_panelmiss",
        "Wm_mg_panelmiss02",
        "Wm_mg_itemget_hm", // New
    };

    if (type < ARRAY_SIZE(sc_effNames)) {
        name = sc_effNames[type];
    }

    mEf::createEffect(name, 0, &efPos, nullptr, nullptr);
}

// Okay these next two functions are a bit weird unless you understand why Nintendo did it this way
// So, the panel icons and the backing color are both part of the same animation. The first function
// sets the frame ID to one with the icon and a yellow backing. The second function sets it to one
// with the same icon, but the backing texture has been changed to red (paired).

// Yellow frames
kmBranchDefCpp(0x80869340, NULL, void, daMiniGameWireMesh_c *this_) {
    int frame = 22;
    int type = this_->getItemType();

    const int frameIDs[] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 20
    };

    if (type < ARRAY_SIZE(frameIDs)) {
        frame = frameIDs[type];
    }

    this_->mAnmTexPat.setFrame(frame, 0);
    this_->mAnmTexPat.setRate(0.0f, 0);
}

// Set the red (paired) frames
kmBranchDefCpp(0x80869440, NULL, void, daMiniGameWireMesh_c *this_) {
    int frame = 22;
    int type = this_->getItemType();

    const int frameIDs[] = {
        10, 11, 12, 13,
        14, 15, 16, 17,
        18, 19
    };

    if (type < ARRAY_SIZE(frameIDs)) {
        frame = frameIDs[type];
    }

    this_->mAnmTexPat.setFrame(frame, 0);
    this_->mAnmTexPat.setRate(0.0f, 0);
    this_->EffectItemGet();
}

// Play Hammer Panel effect when the minigame ends
kmWrite16(0x8086BBFE, 0xFFF6);
