#ifndef AGENDA_ENDS_WITH_ME_CONTROLLER_H
#define AGENDA_ENDS_WITH_ME_CONTROLLER_H 

#include <escher.h>
#include <apps/i18n.h>
#include "base_controller.hpp"
#include "friend_cell.h"
#include "agenda_data.h"
#include "agenda_defs.h"

namespace Agenda {

class EndsWithMeController : public BaseController<AGENDA_NUMS+1, FriendCell> {
public:
	EndsWithMeController(Responder * parentResponder);
	void setAgendaData(AgendaData* agendaData);
	void willDisplayCellForIndex(HighlightCell * cell, int index) override;
	void didBecomeFirstResponder() override;
	bool handleEvent(Ion::Events::Event event) override;
	void update();
	void reload();
private:
	AgendaData* m_agendaData;
	size_t m_withMeList[AGENDA_NUMS];
	size_t m_withMeCount;
};

}

#endif //AGENDA_ENDS_WITH_ME_CONTROLLER_H
