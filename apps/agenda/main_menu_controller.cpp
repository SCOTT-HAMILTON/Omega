#include <assert.h>
#include <iostream>
#include "app.h"
#include "images/agenda_binomial_icon.h"
#include "images/agenda_uniform_icon.h"
#include "images/agenda_focused_binomial_icon.h"
#include "images/agenda_focused_uniform_icon.h"

namespace Agenda {

static I18n::Message sMessages[] = {
	I18n::Message::WeekA,
	I18n::Message::WeekB,
};

Agenda::MainMenuController::MainMenuController(Responder * parentResponder, DayOfWeekController* dayOfWeekController) :
	BaseController(parentResponder, I18n::Message::ChooseWeek),
	m_dayOfWeekController(dayOfWeekController)
{
	m_messages = sMessages;
}

void Agenda::MainMenuController::willDisplayCellForIndex(HighlightCell * cell, int index) {
	Cell * myCell = (Cell *)cell;
	myCell->setLabel(m_messages[index]);
	// TODO: replace with right images
	const Image * images[k_totalNumberOfRows] = {
		ImageStore::AgendaBinomialIcon,
		ImageStore::AgendaUniformIcon,
	};
	const Image * focusedImages[k_totalNumberOfRows] = {
		ImageStore::AgendaFocusedBinomialIcon,
		ImageStore::AgendaFocusedUniformIcon,
	};
	myCell->setImage(images[index], focusedImages[index]);
	myCell->reloadCell();
}

void Agenda::MainMenuController::didBecomeFirstResponder() {
	App::app()->snapshot()->setActivePage(App::Snapshot::Page::MainMenu);
	if (selectedRow() == -1) {
		selectCellAtLocation(0, 0);
	} else {
		selectCellAtLocation(selectedColumn(), selectedRow());
	}
	Container::activeApp()->setFirstResponder(&m_selectableTableView);
}
bool Agenda::MainMenuController::handleEvent(Ion::Events::Event event) {
	if (event == Ion::Events::OK || event == Ion::Events::EXE || event == Ion::Events::Right) {
		std::cerr << "Received event, selected row : " << selectedRow() << '\n';
		m_agendaData->currentWeek = selectedRow();
		StackViewController * stack = (StackViewController *)parentResponder();
		/* stack->pop(); */
		stack->push(m_dayOfWeekController, Palette::BannerFirstText, Palette::BannerFirstBackground, Palette::BannerFirstBorder);
		return true;
	}
	return false;
}
void Agenda::MainMenuController::setAgendaData(AgendaData* agendaData) {
	m_agendaData = agendaData;
}

}
