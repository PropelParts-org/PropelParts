#pragma once
#include <game/bases/d_scene.hpp>
#include <game/sLib/s_State.hpp>

class dScCrsin_c : public dScene_c {
public:
    STATE_FUNC_DECLARE(dScCrsin_c, resWaitProc2);

    sFStateMgr_c<dScCrsin_c, sStateMethodUsr_FI_c> mStateMgr;
    static bool m_isDispOff;
};