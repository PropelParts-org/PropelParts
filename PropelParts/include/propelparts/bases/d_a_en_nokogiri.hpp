#pragma once

#include <game/bases/d_enemy.hpp>
#include <game/bases/d_heap_allocator.hpp>
#include <game/bases/d_res_mng.hpp>
#include <game/bases/d_line_mng.hpp>
#include <game/bases/d_bg_ctr.hpp>

class daEnNokogiri_c : public dEn_c {
public:
    virtual int create();
    virtual int doDelete();
    virtual int execute();
    virtual int draw();

    virtual void Normal_VsPlHitCheck(dCc_c *self, dCc_c *other);
    virtual void Normal_VsYoshiHitCheck(dCc_c *self, dCc_c *other);

    virtual bool hitCallback_Star(dCc_c *self, dCc_c *other);

    virtual void FumiJumpSet(dActor_c *actor);
    virtual void FumiScoreSet(dActor_c *actor);
    virtual void MameFumiJumpSet(dActor_c *actor);

    virtual void YoshiFumiScoreSet(dActor_c *actor);

    virtual void fumiSE(dActor_c *actor);
    virtual void fumiEffect(dActor_c *actor);
    virtual void spinfumiSE(dActor_c *actor);
    virtual void spinfumiEffect(dActor_c *actor);
    virtual void mamefumiSE(dActor_c *actor);
    virtual void mamefumiEffect(dActor_c *actor);

    static void callBackF(dActor_c *self, dActor_c *other);
    static void callBackH(dActor_c *self, dActor_c *other);
    static void callBackW(dActor_c *self, dActor_c *other, u8 direction);

    static bool checkRevFoot(dActor_c *self, dActor_c *other);
    static bool checkRevHead(dActor_c *self, dActor_c *other);
    static bool checkRevWall(dActor_c *self, dActor_c *other, u8 direction);

    dHeapAllocator_c mAllocator;
    nw4r::g3d::ResFile mRes;
    m3d::mdl_c mModel;
    m3d::anmChr_c mAnmChr;

    dLineMng_c mLineMng;
    float mLineSpeed;
    dBg_ctr_c mBg;
    bool mIsSpinJumped;
    bool mIsMasterSaw;

    static bool sSoundPlaying;
};
