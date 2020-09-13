#ifndef AGENDA_DATA_H
#define AGENDA_DATA_H

#include "agenda_defs.h"

namespace Agenda {

class AgendaData {
public:
	size_t currentWeek;
	size_t currentDayOfWeek;
	size_t currentFriend;
	AgendaDef friend_agendas[AGENDA_NUMS-1];
};

}
#endif //AGENDA_DATA_H
