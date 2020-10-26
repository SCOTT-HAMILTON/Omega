#include <assert.h>
#include "app.h"
#include "common.h"
#include "images/agenda_binomial_icon.h"
#include "images/agenda_uniform_icon.h"
#include "images/agenda_focused_binomial_icon.h"
#include "images/agenda_focused_uniform_icon.h"

namespace Agenda {

static I18n::Message sMessages[] = {
	I18n::Message::Monday,
	I18n::Message::Tuesday,
	I18n::Message::Wednesday,
	I18n::Message::Thursday,
	I18n::Message::Friday,
	I18n::Message::Saturday,
};

Agenda::DayOfWeekController::DayOfWeekController(Responder * parentResponder, FriendController* friendController) :
	BaseController(parentResponder, I18n::Message::ChooseDayOfWeek),
	m_friendController(friendController)
{
}

void Agenda::DayOfWeekController::setAgendaData(AgendaData* agendaData) {
	m_agendaData = agendaData;
}

void Agenda::DayOfWeekController::willDisplayCellForIndex(HighlightCell * cell, int index) {
	Cell * myCell = (Cell *)cell;
	char buffer[96];
	if (index < 6) {
		const char* messageStr = I18n::translate(sMessages[index]);
		strlcpy(buffer, messageStr, strlen(messageStr)+1);
		strcat(buffer, " A");
	} else {
		const char* messageStr = I18n::translate(sMessages[index-6]);
		strlcpy(buffer, messageStr, strlen(messageStr)+1);
		strcat(buffer, " B");
	}
	myCell->setText(buffer);
	const Image * images[k_totalNumberOfRows] = {
		ImageStore::AgendaBinomialIcon,
		ImageStore::AgendaUniformIcon,
	};
	const Image * focusedImages[k_totalNumberOfRows] = {
		ImageStore::AgendaFocusedBinomialIcon,
		ImageStore::AgendaFocusedUniformIcon,
	};
	myCell->setImage(images[index%2], focusedImages[index]);
	myCell->reloadCell();
}

void Agenda::DayOfWeekController::didBecomeFirstResponder() {
	App::app()->snapshot()->setActivePage(App::Snapshot::Page::DayOfWeekMenu);
	if (selectedRow() == -1) {
		selectCellAtLocation(0, 0);
	} else {
		selectCellAtLocation(selectedColumn(), selectedRow());
	}
	Container::activeApp()->setFirstResponder(&m_selectableTableView);
}

bool Agenda::DayOfWeekController::handleEvent(Ion::Events::Event event) {
	if (event == Ion::Events::OK || event == Ion::Events::EXE || event == Ion::Events::Right) {
		StackViewController * stack = (StackViewController *)parentResponder();
		m_agendaData->currentDayOfWeek = selectedRow();
		stack->push(m_friendController, Palette::BannerFirstText, Palette::BannerFirstBackground, Palette::BannerFirstBorder);
		return true;
	}
	return false;
}

}
