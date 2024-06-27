#ifdef _WIN32

#include <Windows.h>
#include "OS/events.h"

Events::Events()
{
for (int i = 0; i < EVENT_KEY_COUNT; i++)
    {
        m_Keys[i] = EVENT_NONE;
    }
}

Events::~Events()
{

}

void Events::Update()
{
    // Update key states
    for (int i = 0; i < EVENT_KEY_COUNT; i++)
    {
        SHORT keyState = GetAsyncKeyState(i);

        if (keyState & 0x8000)
        {
            // Key is down
            if (m_Keys[i] == EVENT_NONE)
            {
                m_Keys[i] = EVENT_PRESSED;
            }
            else
            {
                m_Keys[i] = EVENT_ACTIVE;
            }
        }
        else
        {
            // Key is up
            if (m_Keys[i] == EVENT_ACTIVE || m_Keys[i] == EVENT_PRESSED)
            {
                m_Keys[i] = EVENT_RELEASED;
            }
            else
            {
                m_Keys[i] = EVENT_NONE;
            }
        }
    }
}

bool Events::Pressed(event::Type type) const
{
	return m_Keys[type] == EVENT_PRESSED;
}

bool Events::Active(event::Type type) const
{
	return m_Keys[type] == EVENT_ACTIVE;
}

bool Events::Released(event::Type type) const
{
	return m_Keys[type] == EVENT_RELEASED;
}

#endif // _WIN32
