#include <stdlib.h>
#include <stdio.h>
#include "cvent.h"

static EventSubscribers* EventTable[SIZE];
static EventSubscribers EventASubscribers;
static EventSubscribers EventBSubscribers;
static EventSubscribers EventCSubscribers;

void init()
{
	EventTable[EventA] = &EventASubscribers;
	EventTable[EventB] = &EventBSubscribers;
	EventTable[EventC] = &EventCSubscribers;
	for (unsigned int i = 0; i < SIZE; i++)
	{
		EventTable[i]->size = 0;
	}
}

void sub( Event event, Callback func)
{
	// Add callback to event
	EventSubscribers* es = EventTable[event];
	es->size += 1;
	es->subscribers = realloc(es->subscribers, es->size * sizeof(Callback));
	es->subscribers[es->size - 1] = func;
}

void pub( Event event )
{
	// Invoke callbacks for event
	EventSubscribers* es = EventTable[event];
	for (unsigned int i = 0; i < es->size; i++)
	{
		es->subscribers[i]();
	}
}

