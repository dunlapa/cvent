#pragma once

#define SIZE 256
#define DIVISION_SHIFT 8

typedef char* KeyString;

typedef struct
{
	KeyString Key;
	unsigned int Probe;
	void* Subscribers;
} EventSubscribers;

unsigned int hash_key(KeyString keystring);
void add_event(KeyString keystring, void* subscribers);
void* get_subscribers(KeyString eventstring);

