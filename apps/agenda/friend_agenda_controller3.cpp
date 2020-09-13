#include <assert.h>
#include <iostream>
#include "app.h"

namespace Agenda {

Agenda::FriendAgendaController::FriendAgendaController(Responder * parentResponder) :
		ViewController(parentResponder),
		m_selectableTableView(this),
		m_contentView(&m_selectableTableView, I18n::Message::ChooseFriend),
		k_totalNumberOfRows(2)
{
		m_selectableTableView.setTopMargin(Metric::CommonTopMargin-ContentView::k_titleMargin);
}
View* Agenda::FriendAgendaController::view() {
	return &m_contentView;
}
void Agenda::FriendAgendaController::viewWillAppear() {
	ViewController::viewWillAppear();
	selectRow(0);
}
int Agenda::FriendAgendaController::numberOfRows() const {
	return k_totalNumberOfRows;
}
KDCoordinate Agenda::FriendAgendaController::cellHeight() {
	return k_cellHeight;
}
HighlightCell* Agenda::FriendAgendaController::reusableCell(int index) {
	assert(index >= 0);
	assert(index < k_numberOfCells);
	return &m_cells[index];
}
int Agenda::FriendAgendaController::reusableCellCount() const {
	return k_numberOfCells;
}
void Agenda::FriendAgendaController::setAgendaData(AgendaData* agendaData) {
	m_agendaData = agendaData;
	const Day& currentAgenda = currentDay();
	k_totalNumberOfRows = currentAgenda.gapsCount+2;
}

void Agenda::FriendAgendaController::willDisplayCellForIndex(HighlightCell * cell, int index) {
	std::cerr << "Still 1\n";
	FriendCell * myCell = (FriendCell *)cell;
	std::cerr << "Still 2\n";
	const Day& currentAgenda = currentDay();
	std::cerr << "Still 3\n";
	if (index == 0) {
		char buffer[7];
		timeToString(buffer, currentAgenda.startTime);
		std::cerr << "startTime : " << buffer << '\n';
		/* myCell->setText(buffer); */
	} else if (index == k_totalNumberOfRows-1) {
		char buffer[7];
		timeToString(buffer, currentAgenda.endTime);
		std::cerr << "endTime : " << buffer << '\n';
		/* myCell->setText(buffer); */
	} else {
		char buffer[7];
		gapToString(buffer, currentAgenda.gaps[index-1]);
		std::cerr << "gap : " << buffer << '\n';
		/* myCell->setText(buffer); */
	}
	std::cerr << "Still 4\n";
	myCell->reloadCell();
	std::cerr << "Still 5\n";
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
		StackViewController * stack = (StackViewController *)parentResponder();
		stack->pop();
	}
	return false;
}
void Agenda::FriendAgendaController::timeToString(char* str, const AgendaTime& t) {
	sprintf(str, "%d:%d", t.hours, t.minutes);
}
void Agenda::FriendAgendaController::gapToString(char* str, const Gap& g) {
	sprintf(str, "%d:%d -> %d:%d", g.start.hours, g.start.minutes, g.end.hours, g.end.minutes);
}

const Day& Agenda::FriendAgendaController::currentDay() const {
	int day = m_agendaData->currentDayOfWeek;
	if (m_agendaData->currentWeek == 1) 
		day += 6;
	return m_agendaData->friend_agendas[m_agendaData->currentFriend].days[day];
}

}
