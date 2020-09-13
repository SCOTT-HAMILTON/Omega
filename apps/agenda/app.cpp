#include "app.h"
#include <apps/i18n.h>
#include "agenda_icon.h"

using namespace Shared;

namespace Agenda {

I18n::Message App::Descriptor::name() {
	return I18n::Message::AgendaApp;
}

I18n::Message App::Descriptor::upperName() {
	return I18n::Message::AgendaAppCapital;
}

App::Descriptor::ExaminationLevel App::Descriptor::examinationLevel() {
	return App::Descriptor::ExaminationLevel::Strict;
}

const Image * App::Descriptor::icon() {
	return ImageStore::AgendaIcon;
}

App::Snapshot::Snapshot() :
	m_activePage(Page::MainMenu)
{
}

App::Snapshot::~Snapshot() {
}

App * App::Snapshot::unpack(Container * container) {
	return new (container->currentAppBuffer()) App(this);
}

App::Descriptor * App::Snapshot::descriptor() {
	static Descriptor descriptor;
	return &descriptor;
}

void App::Snapshot::reset() {
	m_activePage = Page::MainMenu;
}

void App::Snapshot::setActivePage(Page activePage) {
	m_activePage = activePage;
}

App::Snapshot::Page App::Snapshot::activePage() {
	return m_activePage;
}

App::App(Snapshot * snapshot) :
	TextFieldDelegateApp(snapshot, &m_stackViewController),
	m_friendAgendaController(&m_stackViewController),
	m_commonGapsController(&m_stackViewController),
	m_friendController(&m_stackViewController, &m_friendAgendaController, &m_commonGapsController),
	m_dayOfWeekController(&m_stackViewController, &m_friendController),
	m_stackViewController(&m_modalViewController, &m_dayOfWeekController)
{
	m_agendaData.currentWeek = 0;
	m_agendaData.currentDayOfWeek = 0;
	m_agendaData.currentFriend = 0;
	m_dayOfWeekController.setAgendaData(&m_agendaData);
	m_friendController.setAgendaData(&m_agendaData);
	m_commonGapsController.setAgendaData(&m_agendaData);
	m_friendAgendaController.setAgendaData(&m_agendaData);

	switch (snapshot->activePage()) {
		case Snapshot::Page::MainMenu:
			m_stackViewController.push(&m_dayOfWeekController, Palette::BannerFirstText, Palette::BannerFirstBackground, Palette::BannerFirstBorder);
			break;
		default:
			break;
	}
}


}
