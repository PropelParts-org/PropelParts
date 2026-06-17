#pragma once
#include <game/bases/d_a_en_obj_coin_block.hpp>
#include <game/bases/d_line_mng.hpp>
#include <game/bases/d_bg.hpp>

/// @unofficial
class daEnObjBlock_c : public daEnObjCoinBlock_c {
public:
    enum BlockType_e {
        TYPE_HATENA_BLOCK = 0,
        TYPE_HATENAB_BLOCK, ///< TODO: Is there any difference?
        TYPE_RENGA_BLOCK,
        TYPE_USED_BLOCK,
        TYPE_CLEAR_BLOCK
    };

    virtual ~daEnObjBlock_c();

    virtual int create();
    virtual int doDelete();
    virtual int execute();

    virtual bool isQuakeDamage();
    virtual void block_upmove_diff();
    virtual void block_downmove_diff();
    virtual void block_downmove_diffend();

    void initLineMng();
    void calcLineMng();

    void procObjBlock();
    void procClearBlock();

    bool tencoin_check();
    void continue_star_check();

    void itemCreate();
    void blockWasHit();

    void searchRail();
    void searchObjPol();

    STATE_FUNC_DECLARE(daEnObjBlock_c, SerchRailID);
    STATE_FUNC_DECLARE(daEnObjBlock_c, SerchObjPolID);
    STATE_FUNC_DECLARE(daEnObjBlock_c, Wait);
    STATE_FUNC_DECLARE(daEnObjBlock_c, HitWait);

    dLineMng_c mLineMng;
    dBg_c *mpBg;
    u32 m_818;
    mVec3_c mPosCopy;
    mVec3_c mRailCtrlPos;
    float mPosZ;
    u32 m_838;
    float mRailCtrlY;
    float mMoveSpeed;
    int m_844; ///< Nybble 9 of spritedata
    int mDoUseLineMng;
    int mBlockType; ///< The type of this block. See BlockType_e
    int mInitialBlockType; ///< Copied from above field, never updated
    int mItemType;
    int mIsDanceType;
    float mDancePosX; ///< Added to mPos.x if mIsDanceType != 0

    static sCcDatNewF sc_CcDat;
    static float sc_moveSpeeds[8];
    static short sc_tileIDs[4];
};
