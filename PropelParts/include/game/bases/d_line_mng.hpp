#pragma once
#include <game/sLib/s_State.hpp>
#include <game/mLib/m_vec.hpp>

class dLineMng_c {
public:
    dLineMng_c();

    void init(const mVec2_c &pos, float baseSpeed, int noReverse, u8);
    void move();

    mVec2_c GetPos() const;
    void SetPos(const mVec2_c &);
    void CalcAdjustPosY(float posX, float baseSpeed);
    void SetBaseSpeed(float);
    short acm_angle() const;
    void setTermCkPos(const mVec2_c &, int index); /// @unofficial

    void init_line_move();
    void change_dir();
    void init_term_ck_pos();
    bool check_term();

    /// @todo The other functions

    STATE_FUNC_DECLARE(dLineMng_c, StateID_Idle);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_FallDown);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Left);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Right);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Side);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Height);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_CornerHeightLine);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_CornerSideLine);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Left30Left);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Left30Right);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Right30Left);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Right30Right);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Left60Up);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Left60Down);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Right60Down);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Right60Up);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle2x2Leftup);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle2x2Rightup);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle2x2LeftDown);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle2x2RightDown);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle4x4Rightup);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle4x4LeftUp);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle4x4LeftDown);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle4x4RightDown);
    
    static void is_unit_circle2x2(ulong);
    static void GetLineUnitNo(float x, float y);

    static bool line_cross_slope_check(const mVec2_c &, const mVec2_c &, float &, float &);
    static bool line_cross_range_check(float, float, float);

    mVec2_c mTermCkPos[7];
    mVec2_c m_38;
    mVec2_c mPos;
    mVec2_c mNewPos;
    mVec2_c m_50;
    mVec2_c m_58;
    float mBaseSpeed;
    short mAngle;
    u8 m_66;
    bool mCannotMove;
    u8 mDirection;
    bool mDoNotReverse;
    bool mIsTerm;
    sFStateStateMgr_c<dLineMng_c,sStateMethodUsr_FI_c,sStateMethodUsr_FI_c> mState;
};
