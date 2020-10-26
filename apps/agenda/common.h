#ifndef AGENDA_APP_COMMON_H
#define AGENDA_APP_COMMON_H

#include <math.h>
#include "agenda_types.h"

namespace Agenda {

char* strcat(char *dest, const char *src);
char* itoa(int num, char* buffer, int base);
void timeToString(char* str, const AgendaTime& t);
void gapToString(char* str, const Gap& g);

bool operator==(const Gap& g1, const Gap &g2);
bool operator>(const AgendaTime& t1, const AgendaTime &t2);
bool operator==(const AgendaTime& t1, const AgendaTime &t2);
bool operator<=(const AgendaTime& t1, const AgendaTime &t2);

} // Agenda

bool operator<(const CommonGap& g1, const CommonGap &g2);
bool operator<(const AgendaTime& t1, const AgendaTime &t2);

#endif //AGENDA_APP_COMMON_H
