#pragma once
#include <game/bases/d_a_en_blockmain.hpp>
#include <game/bases/d_PanelObjList.hpp>

class daEnObjCoinBlock_c : public daEnBlockMain_c {
public:
    /// @unofficial
    enum MovementType_e {
        TYPE_RAIL = 0, ///< Only if mMovementID is not 0
        TYPE_TWO_WAY_LINE,
        TYPE_UNK_FLOAT_UP,
        TYPE_WATER_MOVE,
        TYPE_DANCE,
        TYPE_SPIN_LIFT,
        TYPE_SPIN_LIFT_CHILD,
        TYPE_DANCE_REVERSE,
        TYPE_CROWD_CLAP_COIN,
    };

    virtual ~daEnObjCoinBlock_c(); 

    virtual void initialize_upmove();
    virtual void initialize_downmove();

    virtual void block_upmove();
    virtual void block_upmove_diff();
    virtual void block_downmove();
    virtual void block_downmove_end();
    virtual void block_downmove_diff();
    virtual void block_downmove_diffend();

    void nice_search();
    void getInfoSave();

    bool coin_collisionCheck();
    void block_collisionCheck();
    void coin_objbg_set(ulong chainlinkMode, u8 layer);
    void block_objbg_set(ulong chainlinkMode, u8 layer);
    void switch_on_check();

    bool rail_serchID();
    bool objpol_serchID();
    bool watermove_serchID();
    bool spinlift_serchID();
    bool spinlift_child_serchID();

    STATE_FUNC_DECLARE(daEnObjCoinBlock_c, SerchRailID);
    STATE_FUNC_DECLARE(daEnObjCoinBlock_c, SerchObjPolID);
    STATE_FUNC_DECLARE(daEnObjCoinBlock_c, SerchWaterMoveID);
    STATE_FUNC_DECLARE(daEnObjCoinBlock_c, SerchSpinLiftID);
    STATE_FUNC_DECLARE(daEnObjCoinBlock_c, SerchSpinLiftChildID);
    STATE_FUNC_DECLARE(daEnObjCoinBlock_c, CoinWait);
    STATE_FUNC_DECLARE(daEnObjCoinBlock_c, BlockWait);

    dPanelObjList_c mPanelObjList;
    int mControllerID; ///< UniqueID of the paired controller actor
    sBgSetInfo mBgSetInfo;
    mVec3_c mBgCtrScale;
    mVec3_c mTilePos;
    mVec3_c mPosCopy; ///< Y is updated to position of dancing block, unsure if this serves other purposes
    mVec3_c mCtrlDeltaPos;
    float mTwoWayLinePos;
    int mIsBlock; ///< Otherwise, its a coin
    int mIsTypeSwap; ///< Specifies if a P-Switch has flipped the block to a coin (or vice-versa)
    int mMovementType; ///< Type of movement the coin/block uses. See MovementType_e
    int mMovementID; ///< Movement controller ID to try to pair with
    int mTwoWayLineIsVertical;
    int mCrowdClapID; ///< Crowd Clap controller ID to try to pair with
};

extern const sBgSetInfo l_coin_bgc_info;
extern const sBgSetInfo l_block_bgc_info;