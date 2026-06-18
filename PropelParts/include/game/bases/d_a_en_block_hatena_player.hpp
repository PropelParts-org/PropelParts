#pragma once
#include <game/bases/d_a_en_blockmain.hpp>
#include <game/bases/d_bg.hpp>

/// @unofficial
class daEnBlockHatenaPlayer_c : public daEnBlockMain_c {
public:
    enum KinopioType_e {
        TYPE_NONE = 0,
        TYPE_BIG,
        TYPE_SMALL
    };

    enum BlockType_e {
        TYPE_HATENA_BLOCK = 0,
        TYPE_RENGA_BLOCK = 2,
        TYPE_USED_BLOCK
    };

    virtual ~daEnBlockHatenaPlayer_c();

    virtual int create();
    virtual int doDelete();
    virtual int execute();
    virtual int draw();

    virtual void block_upmove_diff();
    virtual void block_downmove_diff();

    short getAtanDeltaPos(mVec2_c *deltaPos);
    float checkPlyInDistance(float dist, mVec2_c *deltaPos, short atanVal);
    void playKinopioCry();

    void brickBreak();
    void procBlockHit();
    void block_move_diff();

    static bool isItemKinopioExist();

    STATE_FUNC_DECLARE(daEnBlockHatenaPlayer_c, Wait);
    STATE_FUNC_DECLARE(daEnBlockHatenaPlayer_c, HitWait);

    dPanelObjList_c mPanelObjList;
    dBg_c *mpBg;
    u32 m_6C0; ///< Unused
    sBgSetInfo mBgSetInfo;
    mVec3_c mBgCtrScale;
    mVec3_c mPosCopy;
    int mKinopioType; ///< The type of Toad in this block. See KinopioType_e
    int mBlockType; ///< The type of this block. See BlockType_e
    int mInitialBlockType; ///< Copied from above field, never updated

    static bool sc_forceKinopio; ///< Forces the block to always contain a Toad.
    static int sc_kinopioTypes[2];
    static short sc_tileIDs[4];
};
