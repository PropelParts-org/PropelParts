#include <propelparts/bases/d_mario_model_custom.hpp>
#include <game/bases/d_a_player_manager.hpp>
#include <game/bases/d_3d.hpp>

const dPlayerMdlCustom_c::ModelInfo_s scArcDt[2] = {
    {
        "Mario", "L_rcha",
        "MB_model", "SMB_model", "PLMB_model", "PMB_model", "HMB_model",
        "MH_model", "SMH_model", "PLMH_model", "PMH_model", "HMH_model",
        13.0f, 10.0f, 13.0f, 13.0f, 13.0f
    },
    {
        "Luigi", "L_rcha",
        "LB_model", "SLB_model", "PLLB_model", "PLB_model", "HLB_model",
        "LH_model", "SLH_model", "PLLH_model", "PLH_model", "HLH_model",
        14.0f, 11.0f, 14.0f, 14.0f, 14.0f
    }
};

const char * const scArcCapDt[2][2] = {
    {"MC_model", "SMC_model"},
    {"LC_model", "SLC_model"}
};

dMarioMdlCustom_c::dMarioMdlCustom_c(u8 modelType) : dPlayerMdlCustom_c(modelType),
    m_824(0), m_870(0), m_86c(0)
{
    mpArcNames = &scArcDt[m_151];
    m_77c = 0x10;
}

dMarioMdlCustom_c::~dMarioMdlCustom_c() {}

void dMarioMdlCustom_c::initialize() {
    dPlayerMdlCustom_c::initialize();
    fn_800cab00(0);
}

void dMarioMdlCustom_c::createPlayerModel() {
    dPlayerMdlCustom_c::createPlayerModel();

    nw4r::g3d::ResAnmTexPat wait_tex_pat = m_20c.GetResAnmTexPat("PH_wait");
    nw4r::g3d::ResMdl res_mdl_head = m_20c.GetResMdl(mpArcNames->mModelNameHead[MODEL_NAME_NORMAL]);
    mTexAnm2.create(res_mdl_head, wait_tex_pat, &mAllocator, nullptr, 2);

    nw4r::g3d::ResMdl res_mdl_peng = m_20c.GetResMdl(mpArcNames->mModelNameHead[MODEL_NAME_PENGUIN]);
    mTexAnmPenguin.create(res_mdl_peng, wait_tex_pat, &mAllocator, nullptr, 2);

    nw4r::g3d::ResMdl res_mdl_prop = m_20c.GetResMdl(mpArcNames->mModelNameHead[MODEL_NAME_PROPELLER]);
    mTexAnmPropeller.create(res_mdl_prop, wait_tex_pat, &mAllocator, nullptr, 2);

    nw4r::g3d::ResMdl res_mdl_ham = m_20c.GetResMdl(mpArcNames->mModelNameHead[MODEL_NAME_HAMMER]);
    mTexAnmHammer.create(res_mdl_ham, wait_tex_pat, &mAllocator, nullptr, 2);

    nw4r::g3d::ResMdl res_mdl_body = m_20c.GetResMdl(mpArcNames->mModelNameBody[MODEL_NAME_NORMAL]);
    nw4r::g3d::ResAnmTexPat switch_tex_pat = m_20c.GetResAnmTexPat("PB_switch");
    mTexAnm1.create(res_mdl_body, switch_tex_pat, &mAllocator);

    for (int i = 0; i < (int) ARRAY_SIZE(mCapModels); i++) {
        nw4r::g3d::ResMdl res_cap_mdl = m_20c.GetResMdl(scArcCapDt[m_151][i]);
        mCapModels[i].create(res_cap_mdl, &mAllocator, 0x863);
        setSoftLight(mCapModels[i]);
    }

    int idx = 0;
    if (mPyPlayerMode == 1) {
        idx = 1;
    }

    nw4r::g3d::ResMdl res_cap_mdl_2 = m_20c.GetResMdl(scArcCapDt[m_151][idx]);
    nw4r::g3d::ResAnmTexPat cap_switch_tex_pat = m_20c.GetResAnmTexPat("PC_switch");
    mCapPatAnm.create(res_cap_mdl_2, cap_switch_tex_pat, &mAllocator);
}

void dMarioMdlCustom_c::_calc() {
    dPlayerMdlCustom_c::_calc();

    // This feels very fake, but I couldn't get it to match another way...
    if (!((mPyPlayerMode != PLAYER_MODE_NORMAL) && (mPyPlayerMode != PLAYER_MODE_RIDE))) {
        if (m_86c == 0) {
            d3d::setMatCullMode(&mInfo[mPyPlayerMode].mMdl2, 2, GX_CULL_ALL);
            d3d::setMatCullMode(&mInfo[mPyPlayerMode].mMdl2, 3, GX_CULL_BACK);
        } else {
            d3d::setMatCullMode(&mInfo[mPyPlayerMode].mMdl2, 2, GX_CULL_BACK);
            d3d::setMatCullMode(&mInfo[mPyPlayerMode].mMdl2, 3, GX_CULL_ALL);
        }
    }

    mMtx_c mtx;
    getJointMtx(&mtx, 15);
    mCapModels[m_870].setLocalMtx(&mtx);
    mCapModels[m_870].calc(false);
}

void dMarioMdlCustom_c::play() {
    dPlayerMdlCustom_c::play();
    mCapModels[m_870].play();
}

void dMarioMdlCustom_c::draw() {
    dPlayerMdlCustom_c::draw();

    if (m_17c & 1) {
        mCapModels[m_870].entry();
        setSoftLight(mCapModels[m_870]);
    }
}

void dMarioMdlCustom_c::setColorType(u8 type) {
    if (mPowerupTex == type) return;

    if (((mPyPlayerMode != PLAYER_MODE_NORMAL) && (mPyPlayerMode != PLAYER_MODE_RIDE)))
        return;

    mPowerupTex = type;

    float f1 = 0.0f;
    if (type == POWERUP_MUSHROOM) {
        f1 = 1.0f;
    } else if (type == POWERUP_FIRE_FLOWER) {
        f1 = 2.0f;
    }

    nw4r::g3d::ResAnmTexPat ph_switch_anm = m_20c.GetResAnmTexPat("PH_switch");
    mTexAnm2.setAnm(mInfo[0].mMdl2, ph_switch_anm, 0, m3d::PLAYMODE_INHERIT);
    mTexAnm2.setRate(0.0f, 0);
    mTexAnm2.setFrame(f1, 0);
    mInfo[0].mMdl2.setAnm(mTexAnm2);

    nw4r::g3d::ResAnmTexPat pb_switch_anm = m_20c.GetResAnmTexPat("PB_switch");
    mTexAnm1.setAnm(*getBodyMdl(), pb_switch_anm, 0, m3d::PLAYMODE_INHERIT);
    mTexAnm1.setRate(0.0f, 0);
    mTexAnm1.setFrame(f1, 0);
    getBodyMdl()->setAnm(mTexAnm1);

    nw4r::g3d::ResAnmTexPat pc_switch_anm = m_20c.GetResAnmTexPat("PC_switch");
    mCapPatAnm.setAnm(mCapModels[0], pc_switch_anm, 0, m3d::PLAYMODE_INHERIT);
    mCapPatAnm.setRate(0.0f, 0);
    mCapPatAnm.setFrame(f1, 0);
    mCapModels[0].setAnm(mCapPatAnm);
}


void dMarioMdlCustom_c::setTexAnmType(dPyMdlBase_c::TexAnmType_e type) {
    dPlayerMdlCustom_c::setTexAnmType(type);
}

bool dMarioMdlCustom_c::setPersonalAnm(int anmID, nw4r::g3d::ResAnmChr *outAnmChr, int c) {
    if (dPlayerMdlCustom_c::setPersonalAnm(anmID, outAnmChr, c)) {
        return true;
    }

    char anm_name[32];
    bool ret = false;
    if (m_151 == 1) {
        switch (anmID) {
            case PLAYER_ANIM_WAIT:
                strncpy(anm_name, "LB_wait", ARRAY_SIZE(anm_name));
                ret = true;
                break;
            case PLAYER_ANIM_WALK:
                strncpy(anm_name, "LB_walk", ARRAY_SIZE(anm_name));
                ret = true;
                break;
            case PLAYER_ANIM_RUN:
                strncpy(anm_name, "LB_run", ARRAY_SIZE(anm_name));
                ret = true;
                break;
            case PLAYER_ANIM_WAIT_L:
            case PLAYER_ANIM_WAIT_L_DUPLICATE:
                strncpy(anm_name, "LB_waitL", ARRAY_SIZE(anm_name));
                ret = true;
                break;
            case PLAYER_ANIM_WAIT_R:
            case PLAYER_ANIM_WAIT_R_DUPLICATE:
                strncpy(anm_name, "LB_waitR", ARRAY_SIZE(anm_name));
                ret = true;
                break;
            case PLAYER_ANIM_WAIT_R3:
                strncpy(anm_name, "LB_waitR3", ARRAY_SIZE(anm_name));
                ret = true;
                break;
            case PLAYER_ANIM_WAIT_L3:
                strncpy(anm_name, "LB_waitL3", ARRAY_SIZE(anm_name));
                ret = true;
                break;
            case PLAYER_ANIM_SLOPE_WAIT_L2:
                strncpy(anm_name, "LB_slope_waitL2", ARRAY_SIZE(anm_name));
                ret = true;
                break;
            case PLAYER_ANIM_SLOPE_WAIT_R2:
                strncpy(anm_name, "LB_slope_waitR2", ARRAY_SIZE(anm_name));
                ret = true;
                break;
            case PLAYER_ANIM_ENDING_WAIT:
                strncpy(anm_name, "LB_ending_wait", ARRAY_SIZE(anm_name));
                ret = true;
                break;
        }

        if (ret) {
            *outAnmChr = m_214.GetResAnmChr(anm_name);
            if (c == 0) {
                mFlags |= FLAG_0020_0000;
            }
            m_164 |= FLAG_0020_0000;
            return true;
        }
    }

    return false;
}

void dMarioMdlCustom_c::FUN_800d4750(int mode) {
    dPlayerMdlCustom_c::FUN_800d4750(mode);

    if (mPyPlayerMode == 1) {
        m_870 = 1;
    } else {
        m_870 = 0;
    }
}

void dMarioMdlCustom_c::fn_800cab00(int isHatLess) {
    if (daPyMng_c::mBonusNoCap && !m_151) {
        m_86c = 1;
        m_17c &= ~1;
    } else {
        m_86c = isHatLess;
        if (isHatLess == 1) {
            m_17c |= 1;
        } else {
            m_17c &= ~1;
        }
    }
}

float dMarioMdlCustom_c::getAimMotionShareScale() {
    static const float scMarioHipScale[MODEL_NAME_COUNT] = { 1.0f, 0.546f, 1.0f, 0.72f, 1.0f };
    static const float scMarioHangCliffScale[MODEL_NAME_COUNT] = { 0.0f, 0.0f, 0.0f, 0.55f, 0.0f };
    static const float scLuigiHipScale[MODEL_NAME_COUNT] = { 1.15f, 0.614f, 1.15f, 0.896f, 1.15f };
    static const float scLuigiOrgHipScale[MODEL_NAME_COUNT] = { 1.0f, 0.534f, 1.0f, 0.779f, 1.0f };
    static const float scLuigiHangCliffScale[MODEL_NAME_COUNT] = { -0.25f, -0.05f, -0.25f, 0.4f, -0.25f };

    dPyMdlBase_c::PlayerMode_e mode = mPyPlayerMode;

    if ((mFlags & FLAG_0080_0000) || (mFlags & FLAG_0100_0000)) {
        mode = PLAYER_MODE_NORMAL;
    }

    if (m_151 == 0) {
        float f1 = scMarioHipScale[mode];

        if (!(mFlags & FLAG_0000_0008)) {
            return f1;
        }

        return f1 + scMarioHangCliffScale[mode];
    } else {
        float f1;

        if (mFlags & FLAG_0020_0000) {
            f1 = scLuigiOrgHipScale[mode];
        } else {
            f1 = scLuigiHipScale[mode];
        }

        if (!(mFlags & FLAG_0000_0008)) {
            return f1;
        }

        return f1 + scLuigiHangCliffScale[mode];
    }
}

void dMarioMdlCustom_c::updateBonusCap() {
    fn_800cab00(0);
}
