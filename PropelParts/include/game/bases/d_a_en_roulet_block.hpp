#pragma once

#include <game/bases/d_a_en_blockmain.hpp>
#include <game/bases/d_heap_allocator.hpp>
#include <game/mLib/m_3d.hpp>

/// @unofficial
class daEnRouletBlock_c : public daEnBlockMain_c {
public:
    dHeapAllocator_c mAllocator;
    nw4r::g3d::ResFile mResFile;
    m3d::mdl_c mModel;
    m3d::mdl_c mEmptyMdl;
    nw4r::g3d::ResAnmTexPat mResAnmTexPat;
    m3d::anmTexPat_c mAnmTexPat;
    m3d::anmTexSrt_c mAnmTexSrt;
    sBgSetInfo mBgSetInfo;
    mVec3_c mBgCrtScale;
    mVec3_c mInitialPos;
    int mItemType; // Nybble 12
    int mRollDelay;
    u8 mCurrItem;
    bool mIsHit;

    static const int sc_itemTypes[];
    static const float sc_rollFrames[][4];
};
