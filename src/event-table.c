#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "event-table.h"

static EventSubscribers* EventTable[SIZE];

unsigned int hash_key(KeyString keystring)
{
	unsigned int hash = 7;
	for(unsigned int i = 0; i < strlen(keystring); i++)
	{
		hash = hash * 3 + (char)keystring[i];
	}
	return hash % SIZE;
};

unsigned int event_index(unsigned int hash)
{
	// TODO: handle collisions
	if (NULL != EventTable[hash])
	{
		return hash;
	}
	return -1;
}

void add_event(KeyString eventstring, void* subscribers)
{
	EventSubscribers* es;
	unsigned int hash = hash_key(eventstring);
	unsigned int index = event_index(hash);

	if (-1 == index)
	{
		es = malloc(sizeof(EventSubscribers));
		es->Key = hash;
		es->Subscribers = subscribers;
		EventTable[index] = es;
	}
	else
	{
		es = EventTable[index];
		es->Subscribers = subscribers;
	}
}

void* get_subscribers(KeyString eventstring)
{
	unsigned int index = event_index(hash_key(eventstring));
	if (-1 == index)
	{
		return NULL;
	}
	return EventTable[index]->Subscribers;
}
