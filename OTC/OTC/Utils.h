#pragma once

#include "pch.h"

//A simple solution for not use exceptions.
struct ExecutionStatus {
    //Return value from function. (If exception value always NULL)
    DWORD value;
    //Return result. (If exception return exception reason)
    const char* msg;
    //If exception result true.
    bool isCause;
};

class Utils {

public:

    /**
     * Get module base address from internal process.
     *
     * @param module - Module name.
     **/

    static HMODULE GetModule (const char* module);

    /**
     * Get module info from internal process.
     * 
     * @param module - Module name.
     **/

    static MODULEINFO GetModuleInfo (const char* module);

    /**
     * Get function address from module.
     *
     * @param module - Module name.
     * @param function - Function name.
     **/

    static DWORD GetFunction (const char* module, const char* function);

};