#pragma once

#include <propelparts/bases/d_player_model_custom.hpp>

class dMarioMdlCustom_c : public dPlayerMdlCustom_c {
public:
    dMarioMdlCustom_c(u8 modelType);
    ~dMarioMdlCustom_c() override;

    void initialize() override;
    void play() override;
    void _calc() override;
    void draw() override;
    void setColorType(u8 type) override;
    bool setPersonalAnm(int anmID, nw4r::g3d::ResAnmChr *outAnmChr, int) override;
    void setTexAnmType(TexAnmType_e type) override; // useless override
    void updateBonusCap() override;
    void FUN_800d4750(int mode) override;
    float getAimMotionShareScale() override;
    void createPlayerModel() override;

    void fn_800cab00(int); ///< @unofficial

    u32 m_824;
    m3d::smdl_c mCapModels[2];
    m3d::anmTexPat_c mCapPatAnm;
    u32 m_86c;
    u32 m_870;
};
