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

    STATE_FUNC_DECLARE(dLineMng_c, StateID_Idle__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_FallDown__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Left45__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Right45__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Side__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Height__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_CornerHeightLine__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_CornerSideLine__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Left30Left__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Left30Right__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Right30Left__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Right30Right__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Left60Up__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Left60Down__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Right60Down__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Right60Up__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle2x2Leftup__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle2x2Rightup__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle2x2LeftDown__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle2x2RightDown__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle4x4Rightup__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle4x4LeftUp__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle4x4LeftDown__10dLineMng_c);
    STATE_FUNC_DECLARE(dLineMng_c, StateID_Circle4x4RightDown__10dLineMng_c);
    
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
