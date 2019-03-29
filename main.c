#include <stdlib.h>
#include <stdio.h>
#include "main.h"

static EventSubscribers* EventTable[SIZE];
static EventSubscribers TestSubscribers;

void fake() 
{
	printf("CALLBACK!!\n");
}

int main()
{
	init();
	sub(Test, fake);
	printf("%d\n", TestSubscribers.size);
	pub(Test);
	return 0;
}

void init()
{
	TestSubscribers.size = 0;
	EventTable[Test] = &TestSubscribers;
}

void sub( Event event, Callback func)
{
	// Add callback to event
	EventSubscribers* es = EventTable[event];
	es->size = 1;
	es->subscribers = realloc(es->subscribers, es->size * sizeof(Callback));
	es->subscribers[0] = func;
}

void pub( Event event )
{
	// Invoke callbacks for event
	EventSubscribers* es = EventTable[event];
	es->subscribers[0]();
}
