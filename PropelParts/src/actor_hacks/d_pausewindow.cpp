#include <kamek.h>
#include <propelparts/game_config.h>

#ifdef NEWER_PAUSE_MENU
#include <game/bases/d_info.hpp>
#include <game/bases/d_pausewindow.hpp>
#include <propelparts/constants/message_list.h>

extern ulong pregameGetLevelNumberID(u8 world, u8 level);

const char *newerPauseMenuName = "pauseMenu_newer/pauseMenu.arc";
kmBranchDefAsm(0x8015A790, 0x8015A794) {
    lis r4, newerPauseMenuName@h
    ori r4, r4, newerPauseMenuName@l
    lwz r4, 0(r4)
    blr
}

kmBranchDefCpp(0x8015AC60, NULL, void, Pausewindow_c *this_) {
    LytBase_c *layout = this_->GetLayout();
    LytTextBox_c
        *LevelNumShadow, *LevelNum,
        *LevelNameShadow, *LevelName;

    LevelNumShadow = (LytTextBox_c *)layout->findTextBoxByName("LevelNumShadow");
    LevelNum = (LytTextBox_c *)layout->findTextBoxByName("LevelNum");
    LevelNameShadow = (LytTextBox_c *)layout->findTextBoxByName("LevelNameShadow");
    LevelName = (LytTextBox_c *)layout->findTextBoxByName("LevelName");

    MsgRes_c *msgRes = dMessage_c::getPropelMsgRes();

    // Grab names based on world + level number
    ulong category = BMG_CATEGORY_LEVEL_NAMES + dInfo_c::m_startGameInfo.mWorld1+1;
    ulong id = dInfo_c::m_startGameInfo.mLevel1+1;
    
    if (msgRes->getMsgEntry(category, id)) {
        LevelNameShadow->setMessage(msgRes, category, id, 0);
        LevelName->setMessage(msgRes, category, id, 0);
    } else {
        LevelNameShadow->SetString(L"NO LEVEL NAME", 0);
        LevelName->SetString(L"NO LEVEL NAME", 0);
    }

    ulong number = pregameGetLevelNumberID(dInfo_c::m_startGameInfo.mWorld1, dInfo_c::m_startGameInfo.mLevel1);

    if (msgRes->getMsgEntry(BMG_CATEGORY_LEVEL_NAMES, number)) {
        LevelNumShadow->setMessage(msgRes, BMG_CATEGORY_LEVEL_NAMES, number, 0);
        LevelNum->setMessage(msgRes, BMG_CATEGORY_LEVEL_NAMES, number, 0);
    } else {
        char worldNumString[13];
        sprintf(worldNumString, "World %d-%d\n", dInfo_c::m_instance->mDisplayCourseWorld, dInfo_c::m_instance->mDisplayCourseNum);
        size_t newsize = strlen(worldNumString) + 1;
        wchar_t *wcWorldNumString = new wchar_t[newsize];
        mbstowcs(wcWorldNumString, worldNumString, newsize);
        LevelNumShadow->SetString(wcWorldNumString, 0);
        LevelNum->SetString(wcWorldNumString, 0);
    }
}
#endif
