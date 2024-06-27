#ifndef OS_EVENTS_H
#define OS_EVENTS_H

#include "OS/event_types.h"

class Events {
public:
	Events();
	~Events();

	void Update();

	bool Pressed(event::Type type) const;
	bool Active(event::Type type) const;
	bool Released(event::Type type) const;

private:
	enum Status
	{
		EVENT_NONE = 0,
		EVENT_PRESSED,
		EVENT_ACTIVE ,
		EVENT_RELEASED
	};

	Status m_Keys[EVENT_KEY_COUNT] = {	EVENT_NONE	};
};

#endif // !OS_EVENTS_H
