#pragma once

#include <propelparts/bases/d_player_model_custom.hpp>

class dKinopioMdlCustom_c : public dPlayerMdlCustom_c {
public:
    dKinopioMdlCustom_c(u8 modelType);
    ~dKinopioMdlCustom_c() override;

    void initialize() override;
    void play() override;
    void _calc() override;
    void draw() override;
    void setColorType(u8 type) override;
    bool setPersonalAnm(int anmID, nw4r::g3d::ResAnmChr *outAnmChr, int) override;
    bool setPersonalRideAnm(int anmID, nw4r::g3d::ResAnmChr *outAnmChr) override;
    void setTexAnmType(TexAnmType_e type) override;
    void callbackTimingA(nw4r::g3d::ChrAnmResult *anmRes, nw4r::g3d::ResNode resNode) override;
    float getAimMotionShareScale() override;
    void createPlayerModel() override;

    m3d::anmTexPat_c &getBodyTexAnm();

    m3d::anmTexPat_c mAnimPropeller;
    m3d::anmTexPat_c mAnimPenguin;
    m3d::anmTexPat_c mAnimHammer;
};
