#include <kamek.h>
#include <propelparts/game_config.h>

// Hide star coin outline if the coin is visible
kmBranchDefAsm(0x80010E9C, 0x80010EA0) {
    stb r0, 0xBB(r3) // Overwritten insn

    lwz r3, 0x3E0(r29) // Get star coin outline
    li  r0, 0 // New alpha value
    stb r0, 0xB8(r3) // Put alpha into outline pane
    blr
}

#ifdef NEWER_MAP_HUD

// TODO: Make HUD tell KP HUD to load level data instead

// Skip drawing the original HUD
kmWriteNop(0x80010B2C);

// Show KP HUD
kmBranchDefCpp(0x80931050, NULL, void) {
    OSReport("disp kp\n");
    
}

// Hide KP HUD
/*kmBranchDefCpp(0x808FB74C, 0x808FB754, void) {
    OSReport("hiding kp\n");
    
}*/

// Show header + lives
kmBranchDefCpp(0x80931090, NULL, void) {
    dKPHud_c::m_instance->playShowAnim(dKPHud_c::ANIM_SHOW_HEADER);
    dKPHud_c::m_instance->playShowAnim(dKPHud_c::ANIM_SHOW_LIVES);
}

// Hide header + lives
kmBranchDefCpp(0x809310F0, NULL, void) {
    dKPHud_c::m_instance->playHideAnim(dKPHud_c::ANIM_SHOW_HEADER);
    //dKPHud_c::m_instance->playHideAnim(dKPHud_c::ANIM_SHOW_LIVES);
}

// Show footer
kmBranchDefCpp(0x80931110, NULL, void) {
    dKPHud_c::m_instance->playShowAnim(dKPHud_c::ANIM_SHOW_FOOTER);
}

// Hide footer
kmBranchDefCpp(0x80931170, NULL, void) {
    dKPHud_c::m_instance->playHideAnim(dKPHud_c::ANIM_SHOW_FOOTER);
}

#endif