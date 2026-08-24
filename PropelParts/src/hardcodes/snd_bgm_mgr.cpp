#include <kamek.h>
#include <propelparts/constants/sound_list.h>
#include <game/snd/snd_scene_manager.hpp>

/*
==============| ADDING NEW MUSIC SLOTS |==============
1. Add the normal & fast brstms to the brsar (with pysar)
2. Add the normal & fast bah sequence brseqs to the brsar (optional)
3. Add entries for them in the NEW_SOUND_e enum using their sound IDs
4. Add their enum entries in each table, indexed by the music ID in the level file
    scNewGameBgmTable is for the normal brstm
    scNewGameFastBgmTable is for the fast brstm
    scNewGameControlBgmTable is for the normal bah brseq
    scNewGameControlBgmTable is for the fast bah brseq
    Music slots without bah brseqs should use SE_DEMO_OP_DUMMY_U instead
5. Recompile your source code. If everything was done right, your music will play in any level set to use it.
*/


u32 scNewGameBgmTable[] = {
    SE_DEMO_OP_DUMMY_U,             // None
    STRM_BGM_CHIJOU,                // Overworld
    STRM_BGM_CHIKA,                 // Underground
    STRM_BGM_WATER,                 // Underwater
    STRM_BGM_ATHLETIC,              // Athletic
    STRM_BGM_OBAKE,                 // Ghost House
    STRM_BGM_SABAKU,                // Pyramids
    STRM_BGM_YUKI,                  // Snow
    STRM_BGM_KAZAN,                 // Lava
    STRM_BGM_TORIDE,                // Tower
    STRM_BGM_SHIRO,                 // Castle
    STRM_BGM_HIKOUSEN,              // Airship
    STRM_BGM_BONUS,                 // Bonus Area
    STRM_BGM_ROAD_TO_LAST,          // Drum Rolls
    STRM_BGM_TORIDE_BOSS,           // Tower Boss
    STRM_BGM_SHIRO_BOSS,            // Castle Boss
    STRM_BGM_MINIGAME,              // Toad House
    STRM_BGM_HIKOUSEN_BOSS,         // Airship Boss
    STRM_BGM_MORI,                  // Forest
    STRM_BGM_MG_BTL,                // Enemy Ambush
    STRM_BGM_SANBASHI,              // Beach
    STRM_BGM_KAZAN_TIKA,            // Lava Cave
    STRM_BGM_PEACH_CASTLE,          // Peach's Castle
    STRM_BGM_STAFF_CREDIT,          // Credits Jazz
    STRM_BGM_HIKOUSEN_ROUKA,        // Airship Drums
    STRM_BGM_LAST_BOSS,             // Bowser
    STRM_BGM_LAST_BOSS2,            // Mega Bowser
    STRM_BGM_LAST_BOSS2_HARP,       // Epilogue
    // Start of custom entries
};

u32 scNewGameFastBgmTable[] = {
    SE_DEMO_OP_DUMMY_U,             // None
    STRM_BGM_CHIJOU_FAST,           // Overworld
    STRM_BGM_CHIKA_FAST,            // Underground
    STRM_BGM_WATER_FAST,            // Underwater
    STRM_BGM_ATHLETIC_FAST,         // Athletic
    STRM_BGM_OBAKE_FAST,            // Ghost House
    STRM_BGM_SABAKU_FAST,           // Pyramids
    STRM_BGM_YUKI_FAST,             // Snow
    STRM_BGM_KAZAN_FAST,            // Lava
    STRM_BGM_TORIDE_FAST,           // Tower
    STRM_BGM_SHIRO_FAST,            // Castle
    STRM_BGM_HIKOUSEN_FAST,         // Airship
    STRM_BGM_BONUS_FAST,            // Bonus Area
    STRM_BGM_ROAD_TO_LAST_FAST,     // Drum Rolls
    STRM_BGM_TORIDE_BOSS_FAST,      // Tower Boss
    STRM_BGM_SHIRO_BOSS_FAST,       // Castle Boss
    STRM_BGM_MINIGAME,              // Toad House
    STRM_BGM_HIKOUSEN_BOSS_FAST,    // Airship Boss
    STRM_BGM_MORI_FAST,             // Forest
    STRM_BGM_MG_BTL,                // Enemy Ambush
    STRM_BGM_SANBASHI_FAST,         // Beach
    STRM_BGM_KAZAN_TIKA_FAST,       // Lava Cave
    STRM_BGM_PEACH_CASTLE,          // Peach's Castle
    STRM_BGM_STAFF_CREDIT,          // Credits Jazz
    STRM_BGM_HIKOUSEN_ROUKA_FAST,   // Airship Drums
    STRM_BGM_LAST_BOSS_FAST,        // Bowser
    STRM_BGM_LAST_BOSS2_FAST,       // Mega Bowser
    STRM_BGM_LAST_BOSS2_HARP,       // Epilogue
    // Start of custom entries
};

u32 scNewGameControlBgmTable[] = {
    SE_DEMO_OP_DUMMY_U,             // None
    SEQ_BGM_CHIJOU_V,               // Overworld
    SEQ_BGM_CHIKA_V,                // Underground
    SEQ_BGM_WATER_V,                // Underwater
    SEQ_BGM_ATHLETIC_V,             // Athletic
    SE_DEMO_OP_DUMMY_U,             // Ghost House
    SEQ_BGM_SABAKU_V,               // Pyramids
    SEQ_BGM_YUKI_V,                 // Snow
    SEQ_BGM_KAZAN_V,                // Lava
    SEQ_BGM_TORIDE_V,               // Tower
    SEQ_BGM_SHIRO_V,                // Castle
    SE_DEMO_OP_DUMMY_U,             // Airship
    SE_DEMO_OP_DUMMY_U,             // Bonus Area
    SE_DEMO_OP_DUMMY_U,             // Drum Rolls
    SE_DEMO_OP_DUMMY_U,             // Tower Boss
    SE_DEMO_OP_DUMMY_U,             // Castle Boss
    SE_DEMO_OP_DUMMY_U,             // Toad House
    SE_DEMO_OP_DUMMY_U,             // Airship Boss
    SEQ_BGM_MORI_V,                 // Forest
    SE_DEMO_OP_DUMMY_U,             // Enemy Ambush
    SEQ_BGM_SANBASHI_V,             // Beach
    SEQ_BGM_KAZAN_TIKA_V,           // Lava Cave
    SE_DEMO_OP_DUMMY_U,             // Peach's Castle
    SEQ_BGM_STAFFCREDIT_V,          // Credits Jazz
    SE_DEMO_OP_DUMMY_U,             // Airship Drums
    SE_DEMO_OP_DUMMY_U,             // Bowser
    SE_DEMO_OP_DUMMY_U,             // Mega Bowser
    SE_DEMO_OP_DUMMY_U,             // Epilogue
    // Start of custom entries
};

u32 scNewGameControlFastBgmTable[] = {
    SE_DEMO_OP_DUMMY_U,             // None
    SEQ_BGM_CHIJOU_FAST_V,          // Overworld
    SEQ_BGM_CHIKA_FAST_V,           // Underground
    SEQ_BGM_WATER_FAST_V,           // Underwater
    SEQ_BGM_ATHLETIC_FAST_V,        // Athletic
    SE_DEMO_OP_DUMMY_U,             // Ghost House
    SEQ_BGM_SABAKU_FAST_V,          // Pyramids
    SEQ_BGM_YUKI_FAST_V,            // Snow
    SEQ_BGM_KAZAN_FAST_V,           // Lava
    SEQ_BGM_TORIDE_FAST_V,          // Tower
    SEQ_BGM_SHIORO_FAST_V,          // Castle
    SE_DEMO_OP_DUMMY_U,             // Airship
    SE_DEMO_OP_DUMMY_U,             // Bonus Area
    SE_DEMO_OP_DUMMY_U,             // Drum Rolls
    SE_DEMO_OP_DUMMY_U,             // Tower Boss
    SE_DEMO_OP_DUMMY_U,             // Castle Boss
    SE_DEMO_OP_DUMMY_U,             // Toad House
    SE_DEMO_OP_DUMMY_U,             // Airship Boss
    SEQ_BGM_MORI_FAST_V,            // Forest
    SE_DEMO_OP_DUMMY_U,             // Enemy Ambush
    SEQ_BGM_SANBASHI_FAST_V,        // Beach
    SEQ_BGM_KAZAN_TIKA_FAST_V,      // Lava Cave
    SE_DEMO_OP_DUMMY_U,             // Peach's Castle
    SE_DEMO_OP_DUMMY_U,             // Credits Jazz
    SE_DEMO_OP_DUMMY_U,             // Airship Drums
    SE_DEMO_OP_DUMMY_U,             // Bowser
    SE_DEMO_OP_DUMMY_U,             // Mega Bowser
    SE_DEMO_OP_DUMMY_U,             // Epilogue
    // Start of custom entries
};

kmWriteNop(0x8019ba68);
kmWriteNop(0x8019ba6c);
kmWriteNop(0x8019ba70);
kmWriteNop(0x8019ba74);
kmWriteNop(0x8019ba78);
kmWriteNop(0x8019ba7c);

kmBranchDefCpp(0x8019e120, NULL, u32, void *this_, int musicIdx) {
    if (musicIdx > ARRAY_SIZE(scNewGameBgmTable)-1) {
        return SE_DEMO_OP_DUMMY_U;
    }
    if (SndSceneMgr::sInstance->mIsFastMusic) {
        return scNewGameFastBgmTable[musicIdx];
    }
    return scNewGameBgmTable[musicIdx];
}

kmBranchDefCpp(0x8019e170, NULL, u32, void *this_, int musicIdx) {
    if (musicIdx > ARRAY_SIZE(scNewGameControlBgmTable)-1) {
        return SE_DEMO_OP_DUMMY_U;
    }
    if (SndSceneMgr::sInstance->mIsFastMusic) {
        return scNewGameControlFastBgmTable[musicIdx];
    }
    return scNewGameControlBgmTable[musicIdx];
}