#pragma once

#define SIZE 10

typedef void (*Callback)();

typedef enum
{
	Test
} Event;

typedef struct
{
	Callback* subscribers;
	int size;
} EventSubscribers;

void init();
void sub( Event, Callback );
void pub( Event );

