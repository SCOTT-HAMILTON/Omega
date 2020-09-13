#include <assert.h>
#include <iostream>
#include "app.h"

namespace Agenda {

Agenda::FriendAgendaController::FriendAgendaController(Responder * parentResponder) :
	BaseController(parentResponder, I18n::Message::ChooseFriend)
{
}

void Agenda::FriendAgendaController::setAgendaData(AgendaData* agendaData) {
	std::cerr << "Lol A\n";
	m_agendaData = agendaData;
	const Day& currentAgenda = currentDay();
	k_totalNumberOfRows = currentAgenda.gapsCount+2;
	std::cerr << "Lol Aend\n";
}

void Agenda::FriendAgendaController::willDisplayCellForIndex(HighlightCell * cell, int index) {
	Cell * myCell = (Cell *)cell;
	const Day& currentAgenda = currentDay();
	if (index == 0) {
		char buffer[7];
		timeToString(buffer, currentAgenda.startTime);
		myCell->setText("test");
	} else if (index == k_totalNumberOfRows-1) {
		char buffer[7];
		timeToString(buffer, currentAgenda.endTime);
		myCell->setText("test 2");
	} else {
		char buffer[7];
		gapToString(buffer, currentAgenda.gaps[index-1]);
		myCell->setText("test 3");
	}
	myCell->reloadCell();
}

void Agenda::FriendAgendaController::didBecomeFirstResponder() {
	std::cerr << "Lol B\n";
	App::app()->snapshot()->setActivePage(App::Snapshot::Page::MainMenu);
	if (selectedRow() == -1) {
		selectCellAtLocation(0, 0);
	} else {
		selectCellAtLocation(selectedColumn(), selectedRow());
	}
	Container::activeApp()->setFirstResponder(&m_selectableTableView);
	std::cerr << "Lol Bend\n";
}

bool Agenda::FriendAgendaController::handleEvent(Ion::Events::Event event) {
	std::cerr << "Lol C\n";
	if (event == Ion::Events::OK || event == Ion::Events::EXE || event == Ion::Events::Right) {
		/* m_agendaData->currentFriend = selectedRow(); */
		/* StackViewController * stack = (StackViewController *)parentResponder(); */
		/* stack->push(m_dayOfWeekController, Palette::BannerFirstText, Palette::BannerFirstBackground, Palette::BannerFirstBorder); */
		std::cerr << "AgendaData : " << m_agendaData->currentWeek << " | " << m_agendaData->currentDayOfWeek << " | " << m_agendaData->currentFriend << '\n';
		/* return true; */
	}
	std::cerr << "Lol Cend\n";
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
