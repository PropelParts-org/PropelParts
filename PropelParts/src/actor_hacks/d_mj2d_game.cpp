#include <kamek.h>
#include <game/bases/d_save_mng.hpp>

// Initialize default Koopatlas world info
kmBranchDefCpp(0x800CE100, NULL, void, dMj2dGame_c *this_) {
    // Set the world name
    memset(this_->mWorldName, 0, 32);
    memcpy(this_->mWorldName, "Yoshi's Island", 32);

    // File Select, HUD text colors
    GXColor fileText[2] = {{0xFF, 0xFF, 0x99, 0xFF}, {0x1F, 0xB4, 0x23, 0xFF}};
    GXColor fileBack[2] = {{0x17, 0x37, 0x14, 0xFF}, {0x3C, 0x91, 0x35, 0xFF}};
    GXColor hudText[2] = {{0xFF, 0xFF, 0x99, 0xFF}, {0x1F, 0xB4, 0x23, 0xFF}};

    for (int i = 0; i < 2; i++) {
        this_->mFileTextColors[i] = fileText[i];
        this_->mFileBgColors[i] = fileBack[i];
        this_->mHudTextColors[i] = hudText[i];
    }

    // HUD + Shop button colors
    this_->mHudHue = 117;
    this_->mHudSat = 46;
    this_->mHudLight = 11;

    this_->mMusicID = 1;
    this_->mLevelInfoID = 1;

    // 01-11.arc
    this_->mTitleWorldNo = 0;
    this_->mTitleLevelNo = 10;
}
