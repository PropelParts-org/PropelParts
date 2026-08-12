#include <kamek.h>
#include <game/mLib/m_vec.hpp>

extern "C" mVec3_c s_wmplayer_shadow_scales[];

kmBranchDefAsm(0x808eb658, 0x808eb668) {
    lis  r5, s_wmplayer_shadow_scales@ha
    addi r5, r5, s_wmplayer_shadow_scales@l
    add  r4, r5, r0
    lfs  f2, 0x0(r4)
    lfs  f3, 0x4(r4)
    lfs  f4, 0x8(r4)
    blr
}