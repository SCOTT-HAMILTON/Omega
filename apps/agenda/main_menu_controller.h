#ifndef AGENDA_MAIN_MENU_CONTROLLER_H
#define AGENDA_MAIN_MENU_CONTROLLER_H 

#include <escher.h>
#include <apps/i18n.h>
#include "base_controller.hpp"
#include "day_of_week_controller.h"
#include "agenda_data.h"

namespace Agenda {

class MainMenuController : public BaseController<2, Cell> {
public:
	MainMenuController(Responder * parentResponder, DayOfWeekController* dayOfWeekController);
	void willDisplayCellForIndex(HighlightCell * cell, int index) override;
	void didBecomeFirstResponder() override;
	bool handleEvent(Ion::Events::Event event) override;
	void setAgendaData(AgendaData* agendaData);

private:
	DayOfWeekController* m_dayOfWeekController;
	AgendaData* m_agendaData;
};

}

#endif //AGENDA_MAIN_MENU_CONTROLLER_H
