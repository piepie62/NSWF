#pragma once

namespace NSWF
{
    struct CLIPEVENTFLAGS
    {
        bool clipEventKeyUp : 1;
        bool clipEventKeyDown : 1;
        bool clipEventMouseUp : 1;
        bool clipEventMouseDown : 1;
        bool clipEventMouseMove : 1;
        bool clipEventUnload : 1;
        bool clipEventEnterFrame : 1;
        bool clipEventLoad : 1;
        bool clipEventDragOver : 1;
        bool clipEventRollOut : 1;
        bool clipEventRollOver : 1;
        bool clipEventReleaseOutside : 1;
        bool clipEventRelease : 1;
        bool clipEventPress : 1;
        bool clipEventInitialize : 1;
        bool clipEventData : 1;
        bool clipEventConstruct : 1;
        bool clipEventKeyPress : 1;
        bool clipEventDragOut : 1;
    };
}
