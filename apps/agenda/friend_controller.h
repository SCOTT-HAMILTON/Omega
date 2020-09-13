#ifndef AGENDA_FRIEND_CONTROLLER_H
#define AGENDA_FRIEND_CONTROLLER_H 

#include <escher.h>
#include <apps/i18n.h>
#include "base_controller.hpp"
#include "friend_agenda_controller.h"
#include "common_gaps_controller.h"
#include "agenda_data.h"
#include "agenda_defs.h"

namespace Agenda {

class FriendController : public BaseController<AGENDA_NUMS+1, Cell> {
public:
	FriendController(Responder * parentResponder, FriendAgendaController* friendAgendaController, CommonGapsController* commonGapsController);
	void setAgendaData(AgendaData* agendaData);
	void willDisplayCellForIndex(HighlightCell * cell, int index) override;
	void didBecomeFirstResponder() override;
	bool handleEvent(Ion::Events::Event event) override;
private:
	AgendaData* m_agendaData;
	FriendAgendaController* m_friendAgendaController;
	CommonGapsController* m_commonGapsController;
};

}

#endif //AGENDA_FRIEND_CONTROLLER_H
