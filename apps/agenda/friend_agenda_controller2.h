#ifndef AGENDA_FRIEND_AGENDA_CONTROLLER_H
#define AGENDA_FRIEND_AGENDA_CONTROLLER_H 

#include <escher.h>
#include <apps/i18n.h>
#include "agenda_data.h"
#include "agenda_types.h"


namespace Agenda {

class FriendAgendaController : public BaseController<18> {
public:
	FriendAgendaController(Responder * parentResponder);
	void setAgendaData(AgendaData* agendaData);
	void willDisplayCellForIndex(HighlightCell * cell, int index) override;
	void didBecomeFirstResponder() override;
	bool handleEvent(Ion::Events::Event event) override;
private:
	AgendaData* m_agendaData;
	static void timeToString(char* str, const AgendaTime& t);
	static void gapToString(char* str, const Gap& g);
	const Day& currentDay() const;
};

}

#endif //AGENDA_FRIEND_AGENDA_CONTROLLER_H
