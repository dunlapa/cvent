#pragma once

#define SIZE 3 

typedef void (*Callback)();

typedef enum
{
	EventA,
	EventB,
	EventC
} Event;

typedef struct
{
	Callback* subscribers;
	unsigned int size;
} EventSubscribers;

void init();
void sub( Event, Callback );
void pub( Event );

