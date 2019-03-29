#pragma once

#define SIZE 97

typedef char* KeyString;

typedef struct
{
	int Key;
	void* Subscribers;
} EventSubscribers;

unsigned int hash_key( KeyString );
void add_event(KeyString keystring, void* subscribers);
void* get_subscribers(KeyString eventstring);

