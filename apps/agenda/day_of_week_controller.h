#ifndef AGENDA_DAY_OF_WEEK_CONTROLLER_H
#define AGENDA_DAY_OF_WEEK_CONTROLLER_H 

#include <escher.h>
#include <apps/i18n.h>
#include "base_controller.hpp"
#include "friend_controller.h"
#include "agenda_data.h"

namespace Agenda {

class DayOfWeekController : public BaseController<12, Cell> {
public:
	DayOfWeekController(Responder * parentResponder, FriendController* friendController);
	void setAgendaData(AgendaData* agendaData);
	void willDisplayCellForIndex(HighlightCell * cell, int index) override;
	void didBecomeFirstResponder() override;
	bool handleEvent(Ion::Events::Event event) override;
private:
	AgendaData* m_agendaData;
	FriendController* m_friendController;
};

}

#endif //AGENDA_DAY_OF_WEEK_CONTROLLER_H
