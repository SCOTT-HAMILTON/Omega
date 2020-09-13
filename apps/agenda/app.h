#ifndef AGENDA_APP_H
#define AGENDA_APP_H

#include <escher.h>
#include "day_of_week_controller.h"
#include "friend_controller.h"
#include "friend_agenda_controller.h"
#include "common_gaps_controller.h"
#include "agenda_data.h"
#include "../shared/text_field_delegate_app.h"

namespace Agenda {

class App : public Shared::TextFieldDelegateApp {
public:
	class Descriptor : public ::App::Descriptor {
	public:
		I18n::Message name() override;
		I18n::Message upperName() override;
		App::Descriptor::ExaminationLevel examinationLevel() override;
		const Image * icon() override;
	};
	class Snapshot : public ::App::Snapshot {
	public:
		enum class Page {
			MainMenu,
			DayOfWeekMenu,
			FriendMenu,
			FriendAgenda,
			CommonGaps
		};
		Snapshot();
		~Snapshot();
		App * unpack(Container * container) override;
		Descriptor * descriptor() override;
		void reset() override;
		Page activePage();
		void setActivePage(Page activePage);

	private:
		Page m_activePage;
	};
	static App * app() {
		return static_cast<App *>(Container::activeApp());
	}
	Snapshot * snapshot() const { return static_cast<Snapshot *>(::App::snapshot()); }
	TELEMETRY_ID("Agenda");
private:
	App(Snapshot * snapshot);
	FriendAgendaController m_friendAgendaController;
	CommonGapsController m_commonGapsController;
	FriendController m_friendController;
	DayOfWeekController m_dayOfWeekController;
	StackViewController m_stackViewController;
	AgendaData m_agendaData;
};

}

#endif //AGENDA_APP_H
