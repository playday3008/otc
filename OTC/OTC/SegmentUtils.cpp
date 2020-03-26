#include "pch.h"
#include "SegmentUtils.h"

void SegmentUtils::CreateInfoTable (DWORD pointer, const char* nick) {

    //We use this as a temporary storage. (The compiler will replace the vector with an array)

    std::vector<DWORD> info;

    //Some value in steam client. idk.

    info.emplace_back(reinterpret_cast<DWORD> (Utils::GetModule ("steamclient.dll") + SEGMENT_LIBRARY_RVA));

    //Base addresses of game modules for stable operation of the onetap.

    for (const auto& library : m_libraries) info.emplace_back (reinterpret_cast<DWORD> (Utils::GetModule(library)));

    //Offsets are needed so that OneTap internal functions can find functions from outside. (For example, the render of the menu depends on the same offset)
    //p.s Index 1 - client_panorama base address.

    for (const auto& offset : m_offsets) info.emplace_back (info.at(1) + offset);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // And so, consider everything in order. Here we move the finished table to the allocated segment memory.
    // Onetap has a function that automatically takes information from the allocated memory because it knows what will be there : "Nickname, libraries, Offsets.".
    // Since the original loader loads there as we do.
    //
    // What is the number 0x20 and why is it here ? The function starts reading data (base addresses, offsets) starting from :Base address + offset by 0x20 bytes.
    // And since we only have data that the function reads in the table, we can safely move the data directly to the place where the function reads.
    //
    // What is 0x18C? Original table size. (Taken from the original crack)

       std::memmove (reinterpret_cast<DWORD*> (pointer + 0x20), reinterpret_cast<PVOID> (info.data()), 0x18C);
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // We move the nickname to the start of the segment since the function reads the nickname first, then the library, then the offsets.
    //
    // What is the offset 0x1 ? If the internal OneTap function reads the first byte and it turns out to be non - zero - crash.
    //
    // What is the value 0x20 ? This is the maximum nickname length. 0x20 translated from hex to dec - This is 32 characters.
    //
       std::memmove (reinterpret_cast<DWORD*> (pointer + 0x1), nick, strlen(nick) > 0x20 ? 0x20 : strlen(nick));
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
}

void SegmentUtils::UpdateNetVars (DWORD pointer) {
    //Netvars are offsets to parent variables in valve sdk. (In this example, we only fix m_isScope)
    for (const auto& netvar : m_netvars) {
        *reinterpret_cast<DWORD*> (pointer + netvar.rva) = netvar.new_value;
    }
}

void SegmentUtils::CreateHook (DWORD pointer) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // We create a hook to prevent a crash due to incorrect indexes, but first, let's look at everything in order. 
    //
    // How does a hook work at all? The function is called -> The call is redirected to our function -> Next, we can do whatever we want. 
    //
    // Why do we need a hook here? OneTap uses virtual functions for internal purposes (find out what kind of weapon the player currently has, find out which object holds the weapon). 
    //
    // Virtual functions are called using an index table. 
    //
    // Since the game is constantly being updated, the indexes are shifted, and therefore, every time we call a function on the wrong index, a crash occurs.
    // In order not to patch a binary file every time, creating a hook is the simplest solution. 
    // (And it gets even easier with HookLib. More details: https://www.github.com/HoShiMin/HookLib)
    //
       SetHook (reinterpret_cast<PVOID> (pointer + SEGMENT_FUNCTION_HOOK_RVA), &CustomFunctionHook, reinterpret_cast<PVOID*> (&g_OriginalFunctionHookCaller));
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}