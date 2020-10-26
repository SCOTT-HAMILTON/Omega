#include <assert.h>
#include <algorithm>
#include "app.h"
#include "common.h"

namespace Agenda {

Agenda::CommonGapsController::CommonGapsController(Responder * parentResponder) :
	BaseController(parentResponder, I18n::Message::ChooseFriend)
{
}

void Agenda::CommonGapsController::setAgendaData(AgendaData* agendaData) {
	m_agendaData = agendaData;
	k_totalNumberOfRows = calculateCommonGaps(commonGaps)*2;
}

void Agenda::CommonGapsController::willDisplayCellForIndex(HighlightCell * cell, int index) {
	FriendCell * myCell = (FriendCell *)cell;
	char buffer[96] = {'\0'};
	if (index % 2 == 0)
		strlcpy(buffer, commonGaps[index/2].name, strlen(commonGaps[index/2].name)+1);
	else {
		Gap gap = {commonGaps[index/2].start, commonGaps[index/2].end};
		gapToString(buffer, gap);
	}
	myCell->setText(buffer);
	myCell->reloadCell();
}

void Agenda::CommonGapsController::didBecomeFirstResponder() {
	App::app()->snapshot()->setActivePage(App::Snapshot::Page::CommonGaps);
	if (selectedRow() == -1) {
		selectCellAtLocation(0, 0);
	} else {
		selectCellAtLocation(selectedColumn(), selectedRow());
	}
	Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

bool Agenda::CommonGapsController::handleEvent(Ion::Events::Event event) {
	if (event == Ion::Events::Left || event == Ion::Events::Back) {
		StackViewController * stack = (StackViewController *)parentResponder();
		stack->pop();
		return true;
	}
	return false;
}

void Agenda::CommonGapsController::reload() {
	k_totalNumberOfRows = calculateCommonGaps(commonGaps)*2;
	m_contentView.reload();
}

const Day& Agenda::CommonGapsController::currentDay() {
	int day = m_agendaData->currentDayOfWeek;
	if (m_agendaData->currentWeek == 1) 
		day += 6;
	return m_agendaData->friend_agendas[m_agendaData->currentFriend].days[day];
}
size_t Agenda::CommonGapsController::calculateCommonGaps(CommonGap* commonGaps) const {
	size_t currentDay = m_agendaData->currentDayOfWeek;
	if (m_agendaData->currentWeek == 1) 
		currentDay += 6;
	const AgendaDef& me = agendas[myAgenda];	
	const Gap* myGaps = me.days[currentDay].gaps;
	size_t myGapsCount = me.days[currentDay].gapsCount;
	size_t commonGapsCounter = 0;
	for (int i = 0; i < AGENDA_NUMS-1; ++i) {
		const AgendaDef& otherAgenda = m_agendaData->friend_agendas[i];
		const Gap* otherGaps = otherAgenda.days[currentDay].gaps;
		size_t otherGapsCount = m_agendaData->friend_agendas[i].days[currentDay].gapsCount;
		for (size_t j = 0; j < myGapsCount; ++j) {
			const Gap& myGap = myGaps[j];
			for (size_t k = 0; k < otherGapsCount; ++k) {
				const Gap& otherGap = otherGaps[k];
				if (myGap.end < otherGap.start) {
					break;
				}
				if (myGap.start <= otherGap.start) {
					// There is a common gap
					CommonGap newGap = {otherAgenda.name, otherGap.start, std::min(otherGap.end, myGap.end)};
					if (newGap.start == newGap.end) {
						continue;
					}
					commonGaps[commonGapsCounter] = newGap;
					++commonGapsCounter;
				}
				else if (myGap.start > otherGap.start && myGap.start < otherGap.end) {
					// There is a common gap
					CommonGap newGap = {otherAgenda.name, myGap.start, std::min(otherGap.end, myGap.end)};
					if (newGap.start == newGap.end) {
						continue;
					}
					commonGaps[commonGapsCounter] = newGap;
					++commonGapsCounter;
				}
			}
		}
	}
	return commonGapsCounter;
}

}
