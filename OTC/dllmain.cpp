#include "framework.h"
#include "headers/runtime/RuntimeHandler.h"

/**
 *
 *   ---------------- o
 * | How it's works ? |
 * o ----------------
 *
 *                           |---------------|
 *                    +++++> |  Relocations  | ======+
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 * | Segment | =======+                              -======> | Reconstruct hotpoints with new base addr  | ======> | OWN FUNCTIONS | ====> | Call Original entry point |
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 *                    +++++> |    Imports    | ======+
 *                           |---------------|
 *
 */

//Scary but necessary.
DWORD Segment::UnsafeAllocatedPointer = 0x0;
DWORD Segment::UnsafeLibraryPointer = 0x0;
SegmentFramework::oVirtualFunctionCaller SegmentFramework::OriginalVirtualCaller = 0x0;

BOOL APIENTRY DllMain (HMODULE module, DWORD callReason, LPVOID lpReserved) {

    //ALL DOCS INSIDE FUNCTIONS, AND HEADERS.

    if (callReason == DLL_PROCESS_ATTACH) {

        Segment segment;
        Logger logger (Logger::LoggerType::CONSOLE);
        RuntimeHandler runtime (segment);

        PanicUtils::SetImportant (&Segment::UnsafeLibraryPointer, reinterpret_cast<DWORD> (module));

        //Logo. 
        logger.Info ("MMMMMMMMMMWKkdoooooooooooodkKWMMMMMMMMMM");
        logger.Info ("MMMMMMMMW0oldkKXNNNXXNNNXKkdloONMMMMMMMM");
        logger.Info ("MMMMMMWKolxKNNNWNkooookNWNNNKxlo0WMMMMMM");
        logger.Info ("MMMMMWOcoKNNOooooldkkdlooooONNKockWMMMMM");
        logger.Info ("MMMMM0coXWM0::xdoooooooodx::0MWXdcOWMMMM");
        logger.Info ("MMMMNocKWWNx : oxcloolloolcxd:xNWWKcoXMM");
        logger.Info ("MMMM0cdNMKl : dkclxccodclxlckd:lKMNdc0MM");
        logger.Info ("MMMM0cdNM0c : xkcoxclddlcxockx:c0MNdc0MM");
        logger.Info ("MMMMXllXMN0o : dxcloolloolcxd:o0NMXllXMM");
        logger.Info ("MMMMWkcxWMWO : ckxolooooooxkc:OWMWx:kWMM");
        logger.Info ("MMMMMXxcxNMXdclllldOOdllllldXMNxcdXMMMMM");
        logger.Info ("MMMMMWNkco0NNKKK0ocllco0KKKNN0olkXWMMMMM");
        logger.Info ("MMMMMMWNKxlokKNWWNK00KNWWNKkolxKNWMMMMMM");
        logger.Info ("MMMMMMMMWNKkdlo0XXXXXXXXOoldkKNWMMMMMMMM");
        logger.Info ("MMMMMMMMMMWWN0l; lddddddl; l0NWWMMMMMMMM");
        logger.Info ("MMMMMMMMMMMMMNx; cooooooc; xWMMMMMMMMMMM");
        logger.Info ("MMMMMMMMMMMMMWx, :llllll:, xWMMMMMMMMMMM");
        logger.Info ("MMMMMMMMMMMMMWk; , looool;; kWMMMMMMMMMM");
        logger.Info ("MMMMMMMMMMMMMMNxc : cllc:cxXMMMMMMMMMMMM");
        logger.Info ("MMMMMMMMMMMMMMMW0o : cc:o0NWMMMMMMMMMMMM");
        logger.Info ("MMMMMMMMMMMMMMMMWNK00KNWMMMMMMMMMMMMMMMM");
        logger.Info ("MMMMMMMMMMMMMMMMMMWWWWMMMMMMMMMMMMMMMMMM");

        logger.Space ();

        logger.Info ("Welcome to OTC Loader.");

        logger.Space (2);

        logger.Info ("| [~] Extracting segment to memory....");

        runtime.ExtractSegment();
        
        logger.Info ("| [~] Reconstructing hot-points...");

        runtime.ReconstructHotPoints();
        
        logger.Info ("| [+] Wait until the framework complete routine work...");
        logger.Info ("| [~] Filling the dependency table... (~7-15 sec)");

        segment.GetFramework().CreateDependencyTable ();

        logger.Info ("| [~] Updating netvars...");

        segment.GetFramework().UpdateNetVars();

        logger.Info ("| [~] Creating hook for internal function...");

        segment.GetFramework().CreateHook();

        logger.Info ("| [~] Updating watermark...");

        //TODO: Waiting your beatiful name.
        //README: !!getenv it's a function!!. Please read docs before edit and ask questions.
        segment.GetFramework().UpdateWatermark (getenv ("USERNAME"), "github.com/0x000cb/otc");
        segment.GetFramework().UpdateMenuWatermark ("Assembled ");

        logger.Info ("| [~] Invoking OEP...");
       
        //Make segment alive.
        runtime.InvokeOEP();

        //Hide menu for better log look.
        segment.GetFramework().SetMenuStatus (false);

        logger.Info ("| [+] OTC initialized.");

        logger.Space ();
       
        logger.Info ("+--------+-----------------------------------+");
        logger.Info ("| Loader |                                   |");
        logger.Info ("|--------+                                   |");
        logger.Info ("|                                            |");
        logger.Info ("| 0x000cb - Project creator & reverse staff. |");
        logger.Info ("| HoShiMin - Legacy & Native help.           |");
        logger.Info ("| playday3008 - Help with github stuff.      |");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("|                                            |");
        logger.Info ("|-------+------------------------------------|");
        logger.Info ("| Crack |                                    |");
        logger.Info ("|-------+                                    |");
        logger.Info ("|                                            |");
        logger.Info ("| toast - module dumper.                     |");
        logger.Info ("| wzn   - module reconstruction.             |");
        logger.Info ("| d3x   - disassembly & advice.              |");
        logger.Info ("| 0x000cb - Current reverse & patch staff.   |");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("|                                            |");
        logger.Info ("|---------+----------------------------------|");
        logger.Info ("|  About  |                                  |");
        logger.Info ("|---------+                                  |");
        logger.Info ("|                                            |");
        logger.Info ("| Source code - www.github.com/0x000cb/otc   |");
        logger.Info ("| DS server - https://discord.gg/JeMKbzW     |");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("| Donate (BTC):                              |");
        logger.Info ("| bc1qjsjmddxegh2a0nys7czn2qztuzq8g6nwk743vg |");
        logger.Info ("+--------------------------------------------+");

        logger.Space (2);

    }

    return TRUE;
}
