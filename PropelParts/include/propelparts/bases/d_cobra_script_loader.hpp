#pragma once

#include <game/bases/d_base.hpp>
#include <game/bases/d_heap_allocator.hpp>
#include <game/bases/d_dvd.hpp>
#include <propelparts/cobra.h>

// Cobra .wmsc script file loader

class dCobraScriptLoader_c : public dBase_c {
public:
    virtual int create();
    virtual int doDelete();

    void loadScriptFile(void *scriptBuffer);
    bool isCustomScript(u32 scriptID) const;
    s32 findScriptIndex(u32 scriptID) const;

    dHeapAllocator_c mAllocator;
    WMSCFile mScriptFile;
    dDvd::loader_c mScriptLoader;

    static dCobraScriptLoader_c *m_instance;
};