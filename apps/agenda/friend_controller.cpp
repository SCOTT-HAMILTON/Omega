#include <assert.h>
#include "app.h"
#include "images/agenda_binomial_icon.h"
#include "images/agenda_focused_binomial_icon.h"

namespace Agenda {

Agenda::FriendController::FriendController(
			Responder* parentResponder,
			FriendAgendaController* friendAgendaController,
			CommonGapsController* commonGapsController,
			StartsWithMeController* startsWithMeController,
			EndsWithMeController* endsWithMeController) : 
	BaseController(parentResponder, I18n::Message::ChooseFriend),
	m_friendAgendaController(friendAgendaController),
	m_commonGapsController(commonGapsController),
	m_startsWithMeController(startsWithMeController),
	m_endsWithMeController(endsWithMeController)
{
}

void Agenda::FriendController::setAgendaData(AgendaData* agendaData) {
	m_agendaData = agendaData;
	size_t ctr = 0;
	for (size_t i = 0; i < AGENDA_NUMS; ++i) {
		if (i == myAgenda) // skip your agenda
			continue;
		m_agendaData->friend_agendas[ctr++] = agendas[i];
	}
}

void Agenda::FriendController::willDisplayCellForIndex(HighlightCell * cell, int index) {
	Cell * myCell = (Cell *)cell;
	if (index == AGENDA_NUMS+2)
		myCell->setLabel(I18n::Message::EndingWithMe);
	else if (index == AGENDA_NUMS+1)
		myCell->setLabel(I18n::Message::StartingWithMe);
	else if (index == AGENDA_NUMS)
		myCell->setLabel(I18n::Message::CommonGaps);
	else if (index == AGENDA_NUMS-1)
		myCell->setLabel(I18n::Message::Me);
	else
		myCell->setText(m_agendaData->friend_agendas[index].name);
	myCell->setImage(ImageStore::AgendaBinomialIcon, ImageStore::AgendaFocusedBinomialIcon);
	myCell->reloadCell();
}

void Agenda::FriendController::didBecomeFirstResponder() {
	App::app()->snapshot()->setActivePage(App::Snapshot::Page::FriendMenu);
	if (selectedRow() == -1) {
		selectCellAtLocation(0, 0);
	} else {
		selectCellAtLocation(selectedColumn(), selectedRow());
	}
	Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

bool Agenda::FriendController::handleEvent(Ion::Events::Event event) {
	StackViewController * stack = (StackViewController *)parentResponder();
	if (event == Ion::Events::Left || event == Ion::Events::Back) {
		stack->pop();
		return true;
	}
	if (event == Ion::Events::OK || event == Ion::Events::EXE || event == Ion::Events::Right) {
		if (selectedRow() == AGENDA_NUMS+2) {
			m_endsWithMeController->reload();
			stack->push(m_endsWithMeController, Palette::BannerFirstText, Palette::BannerFirstBackground, Palette::BannerFirstBorder);
		} else if (selectedRow() == AGENDA_NUMS+2) {
			m_startsWithMeController->reload();
			stack->push(m_startsWithMeController, Palette::BannerFirstText, Palette::BannerFirstBackground, Palette::BannerFirstBorder);
		} else if (selectedRow() == AGENDA_NUMS+1) {
			m_startsWithMeController->reload();
			stack->push(m_startsWithMeController, Palette::BannerFirstText, Palette::BannerFirstBackground, Palette::BannerFirstBorder);
		} else if (selectedRow() == AGENDA_NUMS) {
			m_commonGapsController->reload();
			stack->push(m_commonGapsController, Palette::BannerFirstText, Palette::BannerFirstBackground, Palette::BannerFirstBorder);
		} else {
			m_agendaData->currentFriend = selectedRow();
			m_friendAgendaController->reload();
			stack->push(m_friendAgendaController, Palette::BannerFirstText, Palette::BannerFirstBackground, Palette::BannerFirstBorder);
		}
		return true;
	}
	return false;
}

}
