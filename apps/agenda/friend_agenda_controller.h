#ifndef AGENDA_FRIEND_AGENDA_CONTROLLER_H
#define AGENDA_FRIEND_AGENDA_CONTROLLER_H 

#include <escher.h>
#include <apps/i18n.h>
#include "base_controller.hpp"
#include "friend_cell.h"
#include "agenda_data.h"
#include "agenda_defs.h"

namespace Agenda {

class FriendAgendaController : public BaseController<20, FriendCell> {
public:
	FriendAgendaController(Responder * parentResponder);
	void setAgendaData(AgendaData* agendaData);
	void willDisplayCellForIndex(HighlightCell * cell, int index) override;
	void didBecomeFirstResponder() override;
	bool handleEvent(Ion::Events::Event event) override;
	void reload();
private:
	AgendaData* m_agendaData;
};

}

#endif //AGENDA_FRIEND_AGENDA_CONTROLLER_H
