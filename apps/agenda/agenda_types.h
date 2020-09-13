#ifndef AGENDA_TYPES_H
#define AGENDA_TYPES_H

#define AGENDA_MAX_GAPS 5

#include <string.h>

struct AgendaTime {
	int hours;
	int minutes;
};

struct Gap {
	AgendaTime start;
	AgendaTime end;
};

struct CommonGap {
	const char* name;
	AgendaTime start;
	AgendaTime end;
};

struct Day {
	AgendaTime	startTime;
	size_t gapsCount;
	Gap		gaps[AGENDA_MAX_GAPS];
	AgendaTime	endTime;
};

struct AgendaDef {
	const char* name;
	Day days[12];
};

#endif //AGENDA_TYPES_H
