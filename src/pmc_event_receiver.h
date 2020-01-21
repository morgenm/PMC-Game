#ifndef PMC_EVENT_RECEIVER_H
#define PMC_EVENT_RECEIVER_H

#include <irrlicht.h>

class PMCEventReceiver : public irr::IEventReceiver //Custom irrlicht event receiver
{
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT]; //Stores the current state (up/down) of each key
    bool MouseIsDown[3];

public:
    virtual bool OnEvent(const irr::SEvent& event);

    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const; //Check if key is pressed

    bool IsMouseDown(int i) const;

    PMCEventReceiver();
};


#endif
