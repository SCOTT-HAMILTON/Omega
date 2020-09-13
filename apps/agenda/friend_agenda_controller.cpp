#include <assert.h>
#include "app.h"
#include "common.h"

namespace Agenda {

Agenda::FriendAgendaController::FriendAgendaController(Responder * parentResponder) :
	BaseController(parentResponder, I18n::Message::ChooseFriend)
{
}

void Agenda::FriendAgendaController::setAgendaData(AgendaData* agendaData) {
	m_agendaData = agendaData;
	int day = m_agendaData->currentDayOfWeek;
	if (m_agendaData->currentWeek == 1) 
		day += 6;
	const Day& currentAgenda = m_agendaData->friend_agendas[m_agendaData->currentFriend].days[day];
	k_totalNumberOfRows = currentAgenda.gapsCount+2;
}

void Agenda::FriendAgendaController::willDisplayCellForIndex(HighlightCell * cell, int index) {
	FriendCell * myCell = (FriendCell *)cell;
	int day = m_agendaData->currentDayOfWeek;
	if (m_agendaData->currentWeek == 1) 
		day += 6;
	const Day* currentAgenda;
	if(m_agendaData->currentFriend == AGENDA_NUMS-1)
		currentAgenda = &agendas[myAgenda].days[day];
	else 
		currentAgenda = &m_agendaData->friend_agendas[m_agendaData->currentFriend].days[day];
	if (index == 0) {
		char buffer[10] = {'\0'};
		timeToString(buffer, currentAgenda->startTime);
		myCell->setText(buffer);
	} else if (index == static_cast<int>(k_totalNumberOfRows)-1) {
		char buffer[10] = {'\0'};
		timeToString(buffer, currentAgenda->endTime);
		myCell->setText(buffer);
	} else {
		char buffer[20] = {'\0'};
		gapToString(buffer, currentAgenda->gaps[index-1]);
		myCell->setText(buffer);
	}
	myCell->reloadCell();
}

void Agenda::FriendAgendaController::didBecomeFirstResponder() {
	App::app()->snapshot()->setActivePage(App::Snapshot::Page::FriendAgenda);
	if (selectedRow() == -1) {
		selectCellAtLocation(0, 0);
	} else {
		selectCellAtLocation(selectedColumn(), selectedRow());
	}
	Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

bool Agenda::FriendAgendaController::handleEvent(Ion::Events::Event event) {
	if (event == Ion::Events::Back || event == Ion::Events::Left) {
		/* m_agendaData->currentFriend = selectedRow(); */
		StackViewController * stack = (StackViewController *)parentResponder();
		stack->pop(); // Because of StackController max push count
		return true;
	}
	return false;
}

void Agenda::FriendAgendaController::reload() {
	m_contentView.reload();
}

}
