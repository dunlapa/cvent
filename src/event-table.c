#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "event-table.h"

static EventSubscribers* EventTable[SIZE];
static unsigned int TableLoad = 0;

unsigned int fast_mod(unsigned int num)
{
	return num >= SIZE ? num >> DIVISION_SHIFT : num;
}

unsigned int hash_key(KeyString keystring)
{
	unsigned int hash = 7;
	for(unsigned int i = 0; i < strlen(keystring); i++)
	{
		hash = hash * 3 + (char)keystring[i];
	}
	return fast_mod(hash);
};

void add_event(KeyString eventstring, void* subscribers)
{
	EventSubscribers* es;
	EventSubscribers* tmp_es;
	unsigned int index  = hash_key(eventstring);
	unsigned int probe = 0;

	// Search for existing entry or empty spot
	// while robin hooding smaller probes
	for(;;)
	{
		// Error State: table is full
		if (SIZE == TableLoad)
		{
			return;
		}
		// Empty spot 
		if (NULL == EventTable[index])
		{
			es = malloc(sizeof(EventSubscribers));
			strcpy(es->Key, eventstring);
			es->Probe = probe;
			es->Subscribers = subscribers;
			EventTable[index] = es;
			TableLoad++;
			return;
		}
		// Existing entry with same key, so update
		else if (!strcmp(eventstring, EventTable[index]->Key))
		{
			EventTable[index]->Subscribers = subscribers;
			return;
		}
		// New entry is large than current so swap
		else if (probe > EventTable[index]->Probe)
		{
			es = EventTable[index];
			EventTable[index] = malloc(sizeof(EventSubscribers));
			strcpy(EventTable[index]->Key, eventstring);
			EventTable[index]->Probe = probe;
			EventTable[index]->Subscribers = subscribers;
			TableLoad++;
		}
		probe++;
		index = fast_mod(index + 1);
	}
}

void* get_subscribers(KeyString eventstring)
{
	//unsigned int index = rhh_probe(hash_key(eventstring));
	unsigned int index = 0;
	if (0 == index)
	{
		return NULL;
	}
	return EventTable[index]->Subscribers;
}
