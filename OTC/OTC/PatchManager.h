#pragma once

#include "pch.h"
#include "Segment.h"

class PatchManager {

public:

    //Extract segment to memory.
    ExecutionStatus ExtractToMemory ();

    //Patch relocations and imports.
    ExecutionStatus ReconstructHotPoints (DWORD pointer);

    //Just invoke segment.
    ExecutionStatus InvokeOEP (DWORD pointer);

private:

    //Pseudoheader for allocation and reconstruct.
    SegmentHeader m_SegmentHeader;

};