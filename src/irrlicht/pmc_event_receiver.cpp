#include "pmc_event_receiver.h"

bool PMCEventReceiver::OnEvent(const irr::SEvent& event)
{
    if(event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown; //Store if the key is down or not

    else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        MouseIsDown[0] = event.MouseInput.isLeftPressed();
        MouseIsDown[1] = event.MouseInput.isRightPressed();
        MouseIsDown[2] = event.MouseInput.isMiddlePressed();
    }
    return false; //I don't know why this is here???
}

bool PMCEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const //Check if key is pressed
{
    return KeyIsDown[keyCode];
}

bool PMCEventReceiver::IsMouseDown(int i) const
{
    return MouseIsDown[i];
}

PMCEventReceiver::PMCEventReceiver()
{
    for(irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; i++)
        KeyIsDown[i] = false;
}
