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

/* HOW IT WORKS:
 * Archives are named like "kuribo_tXX.arc"
 * - "tXX" is dynamically generated from a nybble value, like SpriteTex BRRES files
 * setSpriteTexArcList() has a switch case to define which sprites support this
 * - The cases control which nybbles are read, and the original filename
 * - This will load the archive into memory so it is available
 * The "default" style will use the original filename, not a "t00" variant (ex. "kuribo.arc", not "kuribo_t00.arc")
 * The assembly patch to enable functionality on individual sprites is about as simple as with original SpriteTex:
 * - It generally should always patch over the dRes_c::getRes() call
 * - The assembly hack will get the style variant ID from the spritedata and put it into r3
 * - Then call GetDynamicRes() which will handle the rest from there
*/

// Check if this name is already in the arc list
// This is so we don't fill up the list with duplicate entries
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

        // TODO: This should be moved into the padding bytes for universal support,
        // but current tooling doesn't support that...
        u32 param = course->mpMapActors[i].mParam;
        bool setResName = false;
        char nameBuf[32];

        // Most actors use Nybble 6 for styles, so offer that by default
        int resNo = (param >> 24) & 0xF; // Nybble 6

        // Get SpriteTex filename
        switch (mapActorID) {
            case CourseActor::EN_KURIBO:
                sprintf(nameBuf, "kuribo_t%02d", resNo);
                setResName = true;
                break;
            case CourseActor::AC_BIGSHELL:
                sprintf(nameBuf, "big_shell_t%02d", resNo);
                setResName = true;
                break;
        }

        // Add file to list if its not already there, and its not a t00 archive
        if (!checkObjectArcList(nameBuf) && setResName && (resNo > 0)) {
            dScStage_c::addObjectArcList(nameBuf);
        }
    }
}

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
static char l_arc_name_buf[32];

nw4r::g3d::ResFile GetDynamicRes(int resNo, const char *arcName, const char *brresName) {
    if (resNo != 0) {
        sprintf(l_arc_name_buf, "%s_t%02d", arcName, resNo);
    } else {
        strcpy(l_arc_name_buf, arcName);
    }

    return dResMng_c::m_instance->getRes(l_arc_name_buf, brresName);
}

extern "C" void GetDynamicRes__FiPCcPCc(void);

// Big Shell
kmCallDefAsm(0x807BE530) {
    // Nybble 6 & 0xF
    lwz r3, 0x4(r30)
    srwi r3, r3, 24
    andi. r3, r3, 0xF

    b GetDynamicRes__FiPCcPCc
}

// Goomba
kmCallDefAsm(0x8003139C) {
    // Nybble 6 & 0xF
    lwz r3, 0x4(r30)
    srwi r3, r3, 24
    andi. r3, r3, 0xF

    b GetDynamicRes__FiPCcPCc
}
