#include <kamek.h>
#include <game/bases/d_cs_seq_manager.hpp>
#include <propelparts/bases/d_cobra_script_loader.hpp>

kmBranchDefCpp(0x801016b0, NULL, CutData_s *, dCsSeqMng_c *this_) {
    if (this_->mActiveScriptId > -1) {
        if (dCobraScriptLoader_c::m_instance->isCustomScript(this_->mActiveScriptId)) {
            s32 idx = dCobraScriptLoader_c::m_instance->findScriptIndex(this_->mActiveScriptId);
            if (idx < 0) {
                return nullptr;  // ID not found in this wmsc -- shouldn't happen if isCustomScript is accurate, but safer than an OOB read
            }
            return (CutData_s *)dCobraScriptLoader_c::m_instance->mScriptFile.scriptsTable[idx].start + this_->mScriptIp;
        }
        return dCsSeqMng_c::smc_demo_table[this_->mActiveScriptId] + this_->mScriptIp;
    }
    return nullptr;
}