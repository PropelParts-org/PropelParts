#include <kamek.h>
#include <propelparts/bases/d_cobra_script_loader.hpp>

// Add new "manager" actors to the worldmap creation function

extern "C" bool SetupWorldmapActors(dBase_c *);

bool SetupWorldmapActors_Ext(dBase_c *this_) {
    // Create original managers
    SetupWorldmapActors(this_);

    // New managers
    // Cobra Script loader
    dCobraScriptLoader_c::m_instance = (dCobraScriptLoader_c *)fBase_c::createChild(fProfile::COBRA_SCRIPT_LOADER, this_, 0, 0);
    return true;
}

kmWritePointer(0x8098e140, &SetupWorldmapActors_Ext);