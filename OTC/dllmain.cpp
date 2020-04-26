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
        logger.Info ("                  .:rLfth1FUtYJ7ri:.");
        logger.Info ("                 ::iiri77jthXbbDbZDRDR9Fci");
        logger.Info ("                             .:L1f1fhFXPEbDPj:");
        logger.Info ("                     .:LjhhpXXf1ffUfUff1fh1P9Z0t,");
        logger.Info ("                 .71MMRDD99XphXhh2F21f1f1f1212SpZSr");
        logger.Info ("               rPDpXttJjYJYjYjJjjtUft2fF2Ffh2F1hh9E9i");
        logger.Info ("             iEDPfhtJcJJYLY7L777L777L7L7cLJJUJ1fF1P9RP:");
        logger.Info ("           .PQR0FY:.JPUJLLLc7c7c7L7c7L7L7L777L7LLYcU20M2"); 
        logger.Info ("          YQM7:    71cL7L7c7L7cLcLcLYLcLcLcLcLcLL7L7ccjXM:");
        logger.Info ("         :L.     U017L7cLcLcLYLYLc7YLcLYLcLYcjj2th1F2FfFPQF");
        logger.Info ("               iMXJLLLcLcLc7cLcLcLYLcLYcJjh1hjYri::,:,::irbQ.");
        logger.Info ("             1RUcLc7cLc7cLc7cLcLcLJYt2StYi:               JQi");
        logger.Info ("           iD9cLLcLYLYLcLcLcLcLYct11Jr.            . .     rQ7       .:i.");
        logger.Info ("          .SZ2Lc7cLcLcLcLcLcLccjf1c:           .   .   . .   :Qj   :LfjYc9:");
        logger.Info ("        ,fMhJ7LLc7cLcLc7cLL7cJtL:           .             .    ZUrFJr,,..7h");
        logger.Info (" ..::rJ0DXYYLL7cLc7L777L7LLJY7,  .:7Uj:                        cj7:..:,:.:2:");
        logger.Info (" .:LXZRME00ppXPhhfJ777JYJ2XhSYJJc7bEi     .,i7YJ2t1ffJJ7r:.  rUi..,,:,:,,.Yr");
        logger.Info ("     ,.:rricr77hpQpQQ.,:,,. .U:  .icJUYc7r:i:iirir7YjFhXL7,,,:,:,:,:,.rL");
        logger.Info ("                 .fQQQ :Q ..,. :Er:Jhcr::rcYYtSJr   ...   :r:.:,:,:,:,:,:.77");
        logger.Info ("                .hQQQ, 7Q .:,.rQ9t7. :FQQQQQE:.YEQQ7   iEr.,,:,:,:,:.i::,.77");
        logger.Info ("                FQQQQ  QX ,,.rpr.  7QQQQQQQQQQ,   7QQUQQp.,,:,:,:,:,:r,,:.Ui");
        logger.Info ("               cRQQQQQjQ .,:,i.  .QQQQQQQQXQQQQ7    LQh  ....:,:,:,,7:,:.:1.");
        logger.Info ("              .hRQQ0PQQ: ,:,:.. iQQQQQQQf   .QQQ     :Q .:rrr,:,:,,rr.:..LU");
        logger.Info ("              r::QQfhQr .:,:,, :QQQQQQQQ     rQQ,     QQQQQMJ,,:.,77.:,.:F,");
        logger.Info ("             .: rQQQQi .:,:,:. QQQQQQQQ,     :QQ:     Pp    ..,,:7r.,,.,Yt:");
        logger.Info ("         .j2Yf:iQQQQ, .,,:,:, :QQQQQQQQL     XQQ      MQLcr:.,,:7i.,,,.cLF:");
        logger.Info ("         LF:::ii:.  .,:,:,:,: fQQQQQ  QQ.   cQQL      rbQQQ2,,:i:.:,,,c7L2");
        logger.Info ("         cc..,,,...,.:,:,:,:, 2QQQQQ.,QQQ0SQQQZ       .    .,:,,,:,.,Y77F.");
        logger.Info ("         r1.,,:ri,,.:,:,:,:,, :QQQQQQQ0.JEQRQZ       .:,,,,,:,:,:..:cr71:");
        logger.Info ("          fJ...,.,.:r,,:,:,:,, tQQQQRMt  rFPi       .i::,:,:,:,,.,i17L2.  .t");
        logger.Info ("           Y2r:,. ,jt.,,:,:,:,..RQRRQQQM. .        ,i::,:,:,:...i7F9fJ   :PL");
        logger.Info ("            ,77LYjpQj,.:,:,:,:...iL1X9Fj         .:i::,:,:,,.:7UccXEr   7S:.");
        logger.Info ("                QQQQJ,,,:,:,:,:,.              .:::::,:,:,:..FDY7JMi   7h:.,");
        logger.Info ("                LQZQ7,.:,:,:,:,:,:::..    ..,::i::::,:,:,:, 7ZJ7rhF   iS:...");
        logger.Info ("                :QQXr.,,:,:,:,:,:,:,::i:i:i::::,:,:,:,:,:,..pt7r7Pc  .S:.:rr");
        logger.Info ("                ,Qtri.,:,:,:,:,:,:,:::,:,:,:::,:,:,:,:,,. :p27rrcDi  friL7ir");
        logger.Info ("                iQ7L:.:,:,:,:,:,:,:,:,:,:,:,:,:,:,:,,...,Y0j777LhXc:LJcr:...");
        logger.Info ("                tRr:.,,:,:,:,:,:,:,:,:,:,:,:,,,,.....,:UXFL77771fSr7cc:..:,:");
        logger.Info ("              .LXc:...,,:,:,:,:,:,:,:,:,:,:,:,..,,i7t1XtL777772f22irc,.,:,.r");
        logger.Info ("               ,:7JUL7ii::,,.,.,.,.,,:,:,:,:r1pDbbS1YLr77L77LFtfftiY:.,:,.:U");
        logger.Info ("                   .:i7LJYJcc7Lrri:::::,:,:,,.:rJt2JUjULL77Y1UfUFJ7r.,:,,,Jr");
        logger.Info ("                            ...,.rti::,:,:,:,,..   rh1c7rLUhUtjf2Jr,.:,:,c7.");
        logger.Space ();
        logger.Info ("Fluttershy");
        logger.Info ("Friendship is Magic");
        
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
        segment.GetFramework().UpdateWatermark ("PonySense", getenv ("USERNAME"));
        segment.GetFramework().UpdateMenuWatermark ("PonySense ");

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
