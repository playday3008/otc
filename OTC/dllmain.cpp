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
 * | Segment | =======+                              -======> | Reconstruct hotpoints with new base addr. | ======> | OWN FUNCTIONS | ====> | Call Original Entry Point |
 * |---------|        |      |---------------|       |        |-------------------------------------------|         |---------------|       |---------------------------|
 *                    +++++> |    Imports    | ======+
 *                           |---------------|
 *
 *
 *                                  +--------------------------------------------------------------+
 *                                 + ############################################################## +
 *                                + ################################################################ +
 *                               + [+----------------------------------------------------------------+] +
 *                            + # ]|[ #                      Dev - 0x000cb                         # ]|[ # +
 *                            + # ]|[ #       Telegram - t.me/array0 | Discord - 0xb00b1e5#0089    # ]|[ # +
 *                            + # ]|[ #   ------------------------------------------------------   # ]|[ # +
 *                            + # ]|[ #                   Legacy help - HoShiMin                   # ]|[ # +
 *                            + # ]|[ #                  Telegram - t.me/HoShiMin                  # ]|[ # +
 *                               + [+----------------------------------------------------------------+] +
 *                                 + ################################################################ +
 *                                  + ############################################################## +
 *                                   +--------------------------------------------------------------+
 *
 */

//Scary but necessary.
DWORD Segment::UnsafeAllocatedPointer = 0x0;
DWORD Segment::UnsafeLibraryPointer = 0x0;
SegmentFramework::VirtualFunctionCaller SegmentFramework::OriginalVirtualFunctionCaller = 0x0;

BOOL APIENTRY DllMain(HMODULE module, DWORD callReason, LPVOID lpReserved) {

    //ALL DOCS INSIDE FUNCTIONS, AND HEADERS.

    if (callReason == DLL_PROCESS_ATTACH) {

        Segment segment;
        Logger logger (Logger::LoggerType::CONSOLE);
        RuntimeHandler runtime (segment);

        PanicUtils::SetImportant (&Segment::UnsafeLibraryPointer, reinterpret_cast<DWORD> (module));

        //Logo.
        logger.Info ("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
        logger.Info ("MMMMMMMMMMMMMMMWNXKKKKXNWMMMMMMMMMMMMMMM");
        logger.Info ("MMMMMNKNMMMWKOxdollllllodxOKWMMMMMMMMMMM");
        logger.Info ("MMMMNOdONNOdlcclllloooooollloONMMMMMMMMM");
        logger.Info ("MMMMMNXN0occcllooooooooooooolco0WMMMMMMM");
        logger.Info ("MMMMMMWOccclooooooooooooollooolcOWMMMMMM");
        logger.Info ("MMMMMM0lccloooooooooooolokxoloocl0MMMMMM");
        logger.Info ("MMMMMWdcccooooloooooooolokkolooocdNMMMMM"); 
        logger.Info ("MMMMMXocllooolldolooooooollooooocoNMMMMM");
        logger.Info ("MMMMMNdcoooooooloooolllllooooooocdNMMMMM");
        logger.Info ("MMMMMM0clooooooooooollllloooooolc0MMMMMM");
        logger.Info ("MMMMMMWkcloooooooooooooooooooolckNWMMMMM");
        logger.Info ("MMMMMMMWOlcllllllllllllllllllclOX0kKWMMM");
        logger.Info ("MMMMMMMMMKl:llllllllllllllll:lKWNOkKWMMM");
        logger.Info ("MMMMMMMNOdlldddddddddddxxxxxoldONMWMMMMM");
        logger.Info ("MMMMMMXd:clllllllllllllooodoolc:dXMMMMMM");
        logger.Info ("MMMMMNd;ccccccccccccccccccllcccc;dNMMMMM");
        logger.Info ("MMMMMWOxxxxxxxxxxxxxxxxxxxxxxxxxxOWMMMMM");
        logger.Info ("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
        logger.Info ("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
        
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

        //TODO: Waiting you beatiful name.
        segment.GetFramework().UpdateWatermark ("Powered by OTC", getenv ("USERNAME"));
        segment.GetFramework().UpdateMenuWatermark ("Nightly IO ");

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
        logger.Info ("| Github repo - www.github.com/0x000cb/otc   |");
        logger.Info ("| Configs - www.yadi.sk/d/KZNcRdMSheLTfw     |");
        logger.Info ("|--------------------------------------------|");
        logger.Info ("| Donate (BTC):                              |");
        logger.Info ("| bc1qjsjmddxegh2a0nys7czn2qztuzq8g6nwk743vg |");
        logger.Info ("+--------------------------------------------+");

        logger.Space (2);

    }

    return TRUE;
}