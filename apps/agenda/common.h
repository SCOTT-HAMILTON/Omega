#ifndef AGENDA_APP_COMMON_H
#define AGENDA_APP_COMMON_H

#include <math.h>
#include "agenda_types.h"

namespace Agenda {

char* strcat(char *dest, const char *src);
char* itoa(int num, char* buffer, int base);
void timeToString(char* str, const AgendaTime& t);
void gapToString(char* str, const Gap& g);

}

#endif //AGENDA_APP_COMMON_H
