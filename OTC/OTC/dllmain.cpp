#include "pch.h"
#include "PatchManager.h"
#include "GameUtils.h"
#include "SegmentUtils.h"

/**
 *
 *   ---------------- o
 * | How it's works ? |
 * o ----------------
 *
 *                           |---------------|
 *                    +++++> |  Relocations  | ======+
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 * | Segment | =======+                              -======> | Reconstruct hotpoints with new base addr. | ======> | OWN FUNCTIONS | ====> | Call Original Entry Point |
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 *                    +++++> |    Imports    | ======+
 *                           |---------------|
 *
 *
 *                                                  +--------------------------------------------------------------+
 *                                                 + ############################################################## +
 *                                                + ################################################################ +
 *                                              + [+----------------------------------------------------------------+] +
 *                                           + # ]|[ #                       Dev - 0x000cb                        # ]|[ # +
 *                                           + # ]|[ #       Telegram - t.me/array0 | Discord - 0xb00b1e5#0089    # ]|[ # +
 *                                           + # ]|[ #   ------------------------------------------------------   # ]|[ # +
 *                                           + # ]|[ #                  Legacy help - HoShiMin                    # ]|[ # +
 *                                           + # ]|[ #                 Telegram - t.me/HoShiMin                   # ]|[ # +
 *                                              + [+----------------------------------------------------------------+] +
 *                                                + ################################################################ +
 *                                                 + ############################################################## +
 *                                                   +--------------------------------------------------------------+
 *
 */

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lpReserved) {

    if (callReason == DLL_PROCESS_ATTACH) {

        PatchManager patchManager;
        SegmentUtils segmentUtils;
        GameUtils gameUtils;

        gameUtils.ExecuteAtConsole ("log_color General 00FFFFFF");
        gameUtils.ExecuteAtConsole ("developer 1");
        gameUtils.ExecuteAtConsole ("clear");

        ExecutionStatus allocationResult = patchManager.ExtractToMemory ();

        gameUtils.PrintToConsole (allocationResult.msg);
        if (allocationResult.isCause) return TRUE;

        ExecutionStatus reconstructResult = patchManager.ReconstructHotPoints (allocationResult.value);

        gameUtils.PrintToConsole (reconstructResult.msg);
        if (reconstructResult.isCause) return TRUE;

        gameUtils.PrintToConsole ("Performing routine work with the segment...");
        segmentUtils.CreateInfoTable (allocationResult.value, "yougame.biz | infocheats.net"); //Maximum nickname length: 32 characters.
        segmentUtils.UpdateNetVars (allocationResult.value);
        segmentUtils.CreateHook (allocationResult.value);
        gameUtils.PrintToConsole ("Complete.");

        ExecutionStatus invokeResult = patchManager.InvokeOEP (allocationResult.value);
        
        gameUtils.PrintToConsole (invokeResult.msg);
        if (invokeResult.isCause) return TRUE;

        gameUtils.PrintToConsole ("All complete. GL&HF.");

    }

    return TRUE;
}