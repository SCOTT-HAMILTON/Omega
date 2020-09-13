#ifndef AGENDA_COMMON_GAPS_CONTROLLER_H
#define AGENDA_COMMON_GAPS_CONTROLLER_H 

#include <escher.h>
#include <apps/i18n.h>
#include "base_controller.hpp"
#include "friend_cell.h"
#include "agenda_data.h"
#include "agenda_defs.h"
#include "agenda_types.h"

namespace Agenda {

class CommonGapsController : public BaseController<AGENDA_NUMS*AGENDA_MAX_GAPS*2, FriendCell> {
public:
	CommonGapsController(Responder * parentResponder);
	void setAgendaData(AgendaData* agendaData);
	const Day& currentDay();
	void willDisplayCellForIndex(HighlightCell * cell, int index) override;
	void didBecomeFirstResponder() override;
	bool handleEvent(Ion::Events::Event event) override;
	void reload();

private:
	size_t calculateCommonGaps(CommonGap* commonGaps) const;
	CommonGap commonGaps[AGENDA_NUMS*AGENDA_MAX_GAPS];
	AgendaData* m_agendaData;
};

bool operator==(const Gap& g1, const Gap &g2);
bool operator>(const AgendaTime& t1, const AgendaTime &t2);
bool operator==(const AgendaTime& t1, const AgendaTime &t2);
bool operator<=(const AgendaTime& t1, const AgendaTime &t2);

}
bool operator<(const CommonGap& g1, const CommonGap &g2);
bool operator<(const AgendaTime& t1, const AgendaTime &t2);

#endif //AGENDA_COMMON_GAPS_CONTROLLER_H
