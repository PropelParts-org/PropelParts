#include <kamek.h>
#include <propelparts/bases/d_a_en_nokogiri.hpp>
#include <propelparts/bases/d_custom_profile.hpp>
#include <game/bases/d_a_player.hpp>
#include <propelparts/constants/sound_list.h>

bool daEnNokogiri_c::sSoundPlaying = false;

CUSTOM_ACTOR_PROFILE(EN_NOKOGIRI, daEnNokogiri_c, fProfile::EN_STAR_COIN_LINE, fProfile::DRAW_ORDER::EN_STAR_COIN_LINE, 0x2);

const char* l_NOKOGIRI_res[] = {"nokogiri", NULL};
const dActorData_c c_NOKOGIRI_actor_data = {fProfile::EN_NOKOGIRI, 8, -8, 0, 8, 8, 8, 28, 0, 0, 0, ACTOR_CREATE_GROUPABLE};
dCustomProfile_c l_NOKOGIRI_profile(&g_profile_EN_NOKOGIRI, "EN_NOKOGIRI", CourseActor::EN_NOKOGIRI, &c_NOKOGIRI_actor_data, l_NOKOGIRI_res);

void daEnNokogiri_c::callBackF(dActor_c *self, dActor_c *other) {
    if (other->mKind == STAGE_ACTOR_PLAYER) {
        daPlBase_c *player = (daPlBase_c *)other;
        player->setExtraPushForce(self->mPosDelta.x);
        if (self->mPosDelta.y <= 0.0f) {
            player->setBgPressReq(self, daPlBase_c::BG_PRESS_FOOT);
        } else {
            player->setBgPressReq(self, (daPlBase_c::BgPress_e)1);
        }
    }
}

void daEnNokogiri_c::callBackH(dActor_c *self, dActor_c *other) {
    if (other->mKind == STAGE_ACTOR_PLAYER) {
        daPlBase_c *player = (daPlBase_c *)other;
        if (self->mPosDelta.y < 0.0f) {
            player->setBgPressReq(self, (daPlBase_c::BgPress_e)2);
        } else {
            player->setBgPressReq(self, daPlBase_c::BG_PRESS_HEAD);
        }
    }
}

void daEnNokogiri_c::callBackW(dActor_c *self, dActor_c *other, u8 direction) {
    if (other->mKind == STAGE_ACTOR_PLAYER) {
        daPlBase_c *player = (daPlBase_c *)other;
        if (direction == 1) {
            if (self->mPosDelta.x > 0.f) {
                player->setBgPressReq(self, (daPlBase_c::BgPress_e)6);
            } else {
                player->setBgPressReq(self, daPlBase_c::BG_PRESS_L);
            }
        } else {
            if (self->mPosDelta.x < 0.0f) {
                player->setBgPressReq(self, (daPlBase_c::BgPress_e)5);
            } else {
                player->setBgPressReq(self, daPlBase_c::BG_PRESS_R);
            }
        }
    }
}

bool daEnNokogiri_c::checkRevFoot(dActor_c *self, dActor_c *other) {
    return self->mPosDelta.y > 0.0f;
}

bool daEnNokogiri_c::checkRevHead(dActor_c *self, dActor_c *other) {
    return self->mPosDelta.y < 0.0f;
}

bool daEnNokogiri_c::checkRevWall(dActor_c *self, dActor_c *other, u8 direction) {
    if (direction == 0) {
        return self->mPosDelta.x < 0.0f;
    } else {
        return self->mPosDelta.x > 0.0f;
    }
}

float l_nokogiri_line_speeds[] = {
    1.0f, 1.5f, 2.0f, 3.2f,
    0.25f, 0.5f, 0.75f, 2.5f
};

sBgSetInfo l_nokogiri_bgc_info = {
    mVec2_c(-8, 7),
    mVec2_c(8, -7),
    &daEnNokogiri_c::callBackF,
    &daEnNokogiri_c::callBackH,
    &daEnNokogiri_c::callBackW
};

const sCcDatNewF l_nokogiri_cc = {
    0.0f, 23.0f,
    6.0f, 14.0f,
    CC_KIND_ENEMY,
    CC_ATTACK_NONE,
    BIT_FLAG(CC_KIND_PLAYER) | BIT_FLAG(CC_KIND_PLAYER_ATTACK) | BIT_FLAG(CC_KIND_YOSHI) | BIT_FLAG(CC_KIND_TAMA),
    0,
    CC_STATUS_NONE,
    &dEn_c::normal_collcheck,
};

int daEnNokogiri_c::create() {
    // Load the model
    mAllocator.createFrmHeap(-1, mHeap::g_gameHeaps[mHeap::GAME_HEAP_DEFAULT], nullptr, 0x20);

    mRes = dResMng_c::m_instance->getRes("nokogiri", "g3d/nokogiri.brres");
    nw4r::g3d::ResMdl mdl = mRes.GetResMdl("nokogiri");
    mModel.create(mdl, &mAllocator, 0x20, 1, nullptr);
    setSoftLight_Enemy(mModel);

    nw4r::g3d::ResAnmChr resAnmChr = mRes.GetResAnmChr("run");
    mAnmChr.create(mdl, resAnmChr, &mAllocator, 0);
    mAnmChr.setAnm(mModel, resAnmChr, m3d::FORWARD_LOOP);
    mModel.setAnm(mAnmChr, 0.0f);
    mAnmChr.setRate(0.9f);

    mAllocator.adjustFrmHeap();

    mVisibleAreaSize.set(16.0f, 44.0f);
    mVisibleAreaOffset.set(0.0f, 14.0f);

    // Set line speed
    float chosenSpeed = l_nokogiri_line_speeds[mParam >> 4 & 7];
    mLineSpeed = chosenSpeed;
    if (mParam & 1) {
        mLineSpeed = -chosenSpeed;
    }

    // "Place Behind Other Sprites" behavior
    if (mParam >> 12 & 1) {
        mPos.z = -3000.0f;
        mCc.mAmiLine = l_Ami_Line[1];
    }

    // Set collider
    mBg.set(this, &l_nokogiri_bgc_info, 3, mLayer, nullptr);

    mBg.mBelowCheckFunc = &daEnNokogiri_c::checkRevFoot;
    mBg.mAboveCheckFunc = &daEnNokogiri_c::checkRevHead;
    mBg.mAdjCheckFunc = &daEnNokogiri_c::checkRevWall;

    mBg.mBelowCallback = &daEnNokogiri_c::callBackF;
    mBg.mAboveCallback = &daEnNokogiri_c::callBackH;
    mBg.mAdjCallback = &daEnNokogiri_c::callBackW;

    mBg.entry();

    // Set hitbox
    mCc.set(this, (sCcDatNewF *)&l_nokogiri_cc);
    mCc.entry();

    // Setup line movement
    mVec2_c initPos(mPos.x, mPos.y);
    mLineMng.init(initPos, mLineSpeed, 0, 0);
    mLineMng.start_line_move();

    return SUCCEEDED;
};

int daEnNokogiri_c::doDelete() {
    mBg.release();

    if (mIsMasterSaw) {
        sSoundPlaying = false;
    }
    return SUCCEEDED;
}

int daEnNokogiri_c::execute() {
    mModel.play();

    mLineMng.move();
    mVec2_c newPos = mLineMng.GetPos();
    mPos.x = newPos.x;
    mPos.y = newPos.y;

    mBg.calc();

    changePosAngle(&mPos, &mAngle, 1);
    PSMTXTrans(mMatrix, mPos.x, mPos.y, mPos.z);
    mMatrix.YrotM(mAngle.y);
    mMatrix.XrotM(mAngle.x);
    mModel.setLocalMtx(&mMatrix);
    mModel.setScale(mScale);
    mModel.calc(false);

    if (!sSoundPlaying) {
        mIsMasterSaw = true;
        sSoundPlaying = true;
    }

    if (mIsMasterSaw) {
        dAudio::SoundEffectID_t(SE_OBJ_NOKOGIRI).holdMapSound(mUniqueID, mPos, 0);
    }
    
    if (mAnmChr.checkFrame(0.0f)) {
        mVec3_c effPos(mPos.x + 4.0f, mPos.y + 7.5f, 3300.0f);
        mVec3_c effScale(0.35f, 0.35f, 0.35f);
        mEf::createEffect("Wm_en_killershot", 0, &effPos, nullptr, &effScale);
    }

    if (mAnmChr.checkFrame(10.0f)) {
        mVec3_c effPos(mPos.x - 4.0f, mPos.y + 7.5f, 3300.0f);
        mVec3_c effScale(0.35f, 0.35f, 0.35f);
        mEf::createEffect("Wm_en_killershot", 0, &effPos, nullptr, &effScale);
    }

    ActorScrOutCheck(SKIP_NONE);

    return SUCCEEDED;
}

int daEnNokogiri_c::draw() {
    mModel.entry();

    return SUCCEEDED;
}

void daEnNokogiri_c::Normal_VsPlHitCheck(dCc_c *self, dCc_c *other) {
    daPlBase_c *player = (daPlBase_c *)other->mpOwner;
    int fumiCheck = Enfumi_check(self, other, 0);
    if (fumiCheck != 3) {
        // Enfumi_check prioritizes mini mushroom's jump nerf more than spin jumps, so it registers mini spin jumps as normal ones...
        if (!(player->mPowerup == POWERUP_MINI_MUSHROOM && player->isStatus(daPlBase_c::STATUS_SPIN))) {
            dEn_c::Normal_VsPlHitCheck(self, other);
        }
    }
}

void daEnNokogiri_c::Normal_VsYoshiHitCheck(dCc_c *self, dCc_c *other) {
    int fumiCheck = Enfumi_check(self, other, 1);
    if (fumiCheck == 0) {
        dEn_c::Normal_VsYoshiHitCheck(self, other);
    }
}

bool daEnNokogiri_c::hitCallback_Star(dCc_c *self, dCc_c *other) {
    return true;
}

void daEnNokogiri_c::FumiJumpSet(dActor_c *actor) {
    // Both normal jumps and spin jumps call this function to bounce the player...
    daPlBase_c *player = (daPlBase_c *)actor;
    // This is how Enfumi_check checks if the player is spinning
    if (player->isStatus(daPlBase_c::STATUS_SPIN)) {
        dEn_c::FumiJumpSet(actor);
    }
    return;
}

void daEnNokogiri_c::FumiScoreSet(dActor_c *actor) {
    return;
}

void daEnNokogiri_c::MameFumiJumpSet(dActor_c *actor) {
    daPlBase_c *player = (daPlBase_c *)actor;
    // This is how Enfumi_check checks if the player is spinning
    if (player->isStatus(daPlBase_c::STATUS_SPIN)) {
        dEn_c::FumiJumpSet(actor);
    }
    return;
}

void daEnNokogiri_c::YoshiFumiScoreSet(dActor_c *actor) {
    return;
}

void daEnNokogiri_c::fumiSE(dActor_c *actor) {
    return;
}

void daEnNokogiri_c::fumiEffect(dActor_c *actor) {
    return;
}

void daEnNokogiri_c::spinfumiSE(dActor_c *actor) {
    dAudio::SoundEffectID_t(SE_EMY_YOSHI_STEP).playEmySound(getCenterPos(), 0);
}

void daEnNokogiri_c::spinfumiEffect(dActor_c *actor) {
    return;
}

void daEnNokogiri_c::mamefumiSE(dActor_c *actor) {
    daPlBase_c *player = (daPlBase_c *)actor;
    // This is how Enfumi_check checks if the player is spinning
    if (player->isStatus(daPlBase_c::STATUS_SPIN)) {
        dAudio::SoundEffectID_t(SE_EMY_YOSHI_STEP).playEmySound(getCenterPos(), 0);
    }
    return;
}

void daEnNokogiri_c::mamefumiEffect(dActor_c *actor) {
    return;
}
