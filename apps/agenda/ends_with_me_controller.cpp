#include <assert.h>
#include "app.h"
#include "common.h"

namespace Agenda {

Agenda::EndsWithMeController::EndsWithMeController(Responder * parentResponder) :
	BaseController(parentResponder, I18n::Message::EndingWithMe)
{
}

void Agenda::EndsWithMeController::setAgendaData(AgendaData* agendaData) {
	m_agendaData = agendaData;
	update();
}

void Agenda::EndsWithMeController::willDisplayCellForIndex(HighlightCell * cell, int index) {
	FriendCell * myCell = (FriendCell *)cell;
	if (index == 0) {
		size_t currentDay = m_agendaData->currentDayOfWeek;
		if (m_agendaData->currentWeek == 1) 
			currentDay += 6;
		const AgendaDef& me = agendas[myAgenda];
		char buffer[10];
		timeToString(buffer, me.days[currentDay].endTime);
		myCell->setText(buffer);
	} else 
		myCell->setText(m_agendaData->friend_agendas[m_withMeList[index]].name);
	myCell->reloadCell();
}

void Agenda::EndsWithMeController::didBecomeFirstResponder() {
	App::app()->snapshot()->setActivePage(App::Snapshot::Page::EndsWithMe);
	if (selectedRow() == -1) {
		selectCellAtLocation(0, 0);
	} else {
		selectCellAtLocation(selectedColumn(), selectedRow());
	}
	Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

bool Agenda::EndsWithMeController::handleEvent(Ion::Events::Event event) {
	if (event == Ion::Events::Back || event == Ion::Events::Left) {
		StackViewController* stack = (StackViewController *)parentResponder();
		stack->pop();
		return true;
	}
	return false;
}

void Agenda::EndsWithMeController::update() {
	size_t currentDay = m_agendaData->currentDayOfWeek;
	if (m_agendaData->currentWeek == 1) 
		currentDay += 6;
	const AgendaDef& me = agendas[myAgenda];
	m_withMeCount = 0;
	for (int i = 0; i < AGENDA_NUMS-1; ++i) {
		const AgendaDef& otherAgenda = m_agendaData->friend_agendas[i];
		if (otherAgenda.days[currentDay].endTime == me.days[currentDay].endTime)
			m_withMeList[m_withMeCount++] = i;
	}
	k_totalNumberOfRows = m_withMeCount+1;
}

void Agenda::EndsWithMeController::reload() {
	update();
	m_contentView.reload();
}

}
