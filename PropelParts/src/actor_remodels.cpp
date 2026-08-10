#include <kamek.h>
#include <game/bases/d_cd.hpp>
#include <game/bases/d_s_crsin.hpp>
#include <game/bases/d_s_stage.hpp>
#include <propelparts/bases/d_custom_profile.hpp>
#include <game/bases/d_res_mng.hpp>
#include <game/bases/d_actor.hpp>

extern const char** l_actor_file_tbl[COURSE_ACTOR_COUNT];
extern const char** l_custom_actor_file_tbl[CourseActor::TOTAL_COURSE_ACTOR_COUNT - COURSE_ACTOR_COUNT];

// Recreation of "SpriteTex" from NewerSMBW that uses separate archives for memory efficiency

bool checkObjectArcList(const char *name) {
    for (int i = 0; i < dScStage_c::m_object_res_num; i++) {
        if (!strcmp(name, dScStage_c::m_object_res_list[i])) {
            return true;
        }
    }

    return false;
}

void setSpriteTexArcList(dCdFile_c *course, u16 mapActorID) {
    for (int i = 0; i < course->mMapActorCount; i++) {
        if (course->mpMapActors[i].mMapActorID != mapActorID) {
            continue;
        }

        u32 param = course->mpMapActors[i].mParam;
        bool setResName = false;
        char nameBuf[32];
        int resNo;

        // Get SpriteTex filename
        switch (mapActorID) {
            case CourseActor::EN_KURIBO:
                resNo = (param >> 24) & 0xF; // Nybble 6
                sprintf(nameBuf, "kuribo_t%02d", resNo);
                setResName = true;
                break;
            case CourseActor::AC_BIGSHELL:
                resNo = (param >> 24) & 0xF;
                sprintf(nameBuf, "big_shell_t%02d", resNo);
                setResName = true;
                break;
        }

        // Add file to list if its not already there, and its not a t00 archive
        if (!checkObjectArcList(nameBuf) && setResName && (resNo > 0)) {
            OSReport("adding %s!\n", nameBuf);
            dScStage_c::addObjectArcList(nameBuf);
        }
    }
}

// Get SpriteTex archive name and put it into r4


// dScCrsin_c::executeState_initStageProc2()
kmBranchDefCpp(0x8091FBD0, NULL, void, dScCrsin_c *this_) {
    for (int cIdx = 0; cIdx < COURSE_FILE_COUNT; cIdx++) {
        dCdFile_c *course = dCd_c::m_instance->getFileP(cIdx);
        if (course == nullptr) {
            continue;
        }

        // Add tilesets to our arc lists
        char tsName[32];
        sTilesetData *pTilesets = course->mpTilesetNames;
        if (pTilesets->mTileset0[0] != '\0') {
            strncpy(tsName, pTilesets->mTileset0, 32);
            dScStage_c::addUnitTexArcList(tsName);
        }
        if (pTilesets->mTileset1[0] != '\0') {
            strncpy(tsName, pTilesets->mTileset1, 32);
            dScStage_c::addUnitTexArcList(tsName);
        }
        if (pTilesets->mTileset2[0] != '\0') {
            strncpy(tsName, pTilesets->mTileset2, 32);
            dScStage_c::addUnitTexArcList(tsName);
        }
        if (pTilesets->mTileset3[0] != '\0') {
            strncpy(tsName, pTilesets->mTileset3, 32);
            dScStage_c::addUnitTexArcList(tsName);
        }

        // Add rails, if applicable
        if (!strcmp(pTilesets->mTileset3, "Pa3_rail") ||
            !strcmp(pTilesets->mTileset3, "Pa3_rail_white") ||
            !strcmp(pTilesets->mTileset3, "Pa3_daishizen") ||
            !strcmp(pTilesets->mTileset3, "Pa3_MG_house_ami_rail")) {
            dScStage_c::addObjectArcList("rail");
        }

        // Now add all of the course actor files
        int loadNum = course->mBlock8ElementCount;
        if (loadNum != 0) {
            for (int i = 0; i < loadNum; i++) {
                u16 actorID = course->mBlock8[i].mMapActorID;

                // Get the file list
                const char **fileList = nullptr;
                if (actorID < COURSE_ACTOR_COUNT) {
                    fileList = l_actor_file_tbl[actorID];
                } else {
                    fileList = l_custom_actor_file_tbl[actorID - COURSE_ACTOR_COUNT];
                }

                if (fileList != nullptr) {
                    for (; *fileList != nullptr; fileList++) {
                        // Prevent duplicate archives from being added to the list
                        // (why does the retail game not do this???)
                        if (!checkObjectArcList(*fileList)) {
                            dScStage_c::addObjectArcList(*fileList);
                        }
                    }
                }

                // Check for SpriteTex archives
                setSpriteTexArcList(course, actorID);
            }
        }
    }

    // Time to load everything
    dResMng_c::m_instance->setRes("Stage/Texture", dScStage_c::m_unit_res_list, dScStage_c::m_unit_res_num, nullptr);
    dResMng_c::m_instance->setRes("Object", dScStage_c::m_object_res_list, dScStage_c::m_object_res_num, nullptr);
    this_->mStateMgr.changeState(dScCrsin_c::StateID_resWaitProc2);
}

// Archive name hooks
//static char l_arc_name_buf[32];
static const char *l_arc_name_format = "kuribo_t%02d";

void getArchiveName(dActor_c *, char *baseName, const char *brresName, int nybbleValue) {
    char l_arc_name_buf[32];
    OSReport("r4: %s\n", baseName);
    OSReport("r6: %d\n", nybbleValue);

    sprintf(l_arc_name_buf, "big_shell_t%02d", nybbleValue);
    OSReport("%s\n", l_arc_name_buf);
    strcpy(baseName, l_arc_name_buf);
}

extern "C" void getArchiveName__FP8dActor_cPcPCci(void);
extern "C" void getSpriteTexName(void);

static const char *kuribo_name = "kuribo";

// big shell
kmCallDefAsm(0x807be52c) {
    addi r3, r3, 0x4

    lwz r6, 0x4(r30)
    srwi r6, r6, 24
    andi. r6, r6, 0xF

    cmpwi r6, 0
    //ble _done

    stwu sp, -0x20(sp)
    mflr r0
    stw r0, 0x24(sp)
    stw r3, 0x1C(sp)
    stw r5, 0x18(sp)
    //stw r6, 0x14(sp)
    stw r7, 0x10(sp)
    stw r8, 0xC(sp)
    stw r9, 0x8(sp)

    b getArchiveName

    lwz r0, 0x24(sp)
    lwz r3, 0x1C(sp)
    lwz r5, 0x18(sp)
    //lwz r6, 0x14(sp)
    lwz r7, 0x10(sp)
    lwz r8, 0xC(sp)
    lwz r9, 0x8(sp)
    mtlr r0
    addi sp, sp, 0x20

    // TODO: This should be moved to its own function eventually~
    /*stwu sp, -0x20(sp)
    mflr r0
    stw r0, 0x24(sp)
    stw r3, 0x1C(sp)
    stw r4, 0x18(sp)
    stw r6, 0x14(sp)
    stw r7, 0x10(sp)
    stw r8, 0xC(sp)
    stw r9, 0x8(sp)

    lis r3, l_arc_name_buf@h
    ori r3, r3, l_arc_name_buf@l

    lis r4, l_arc_name_format@h
    ori r4, r4, l_arc_name_format@l

    // Put nybble value into r5
    or r5, r6, r6

    crclr 4*cr1+eq
    bl sprintf

    lis r5, l_arc_name_buf@h
    ori r5, r5, l_arc_name_buf@l

    lwz r0, 0x24(sp)
    lwz r3, 0x1C(sp)
    lwz r4, 0x18(sp)
    lwz r6, 0x14(sp)
    lwz r7, 0x10(sp)
    lwz r8, 0xC(sp)
    lwz r9, 0x8(sp)
    mtlr r0
    addi sp, sp, 0x20*/

_done:
    blr
}

// kmCallDefAsm(0x80031384) {
//     lwz r6, 0x4(r3)
//     srwi r6, r6, 24
//     andi. r6, r6, 0xF

//     cmpwi r6, 0
//     ble _done

//     b getSpriteTexName

// _done:
//     blr
// }