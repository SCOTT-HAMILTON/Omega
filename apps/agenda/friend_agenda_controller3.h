#ifndef AGENDA_FRIEND_AGENDA_CONTROLLER_H
#define AGENDA_FRIEND_AGENDA_CONTROLLER_H 

#include <escher.h>
#include <apps/i18n.h>
#include <iostream>
#include "friend_cell.h"
#include "agenda_data.h"

namespace Agenda {

class FriendAgendaController : public ViewController, public SimpleListViewDataSource, public SelectableTableViewDataSource {
public:
	FriendAgendaController(Responder * parentResponder);
	View * view() override;
	void viewWillAppear() override;
	TELEMETRY_ID("FriendAgendaController");
	int numberOfRows() const override;
	KDCoordinate cellHeight() override;
	HighlightCell * reusableCell(int index) override;
	int reusableCellCount() const override;
	void setAgendaData(AgendaData* agendaData);
	void willDisplayCellForIndex(HighlightCell * cell, int index) override;
	void didBecomeFirstResponder() override;
	bool handleEvent(Ion::Events::Event event) override;
protected:
	I18n::Message * m_messages;
	size_t k_totalNumberOfRows;
	SelectableTableView m_selectableTableView;
private:
	class ContentView : public View {
	public:
		ContentView(SelectableTableView * selectableTableView, I18n::Message titleMessage) : 
			m_titleView(KDFont::SmallFont, titleMessage, 0.5f, 0.5f, Palette::SecondaryText, Palette::BackgroundApps),
			m_selectableTableView(selectableTableView)
		{}
		constexpr static KDCoordinate k_titleMargin = 8;
	private:
		int numberOfSubviews() const override {
			return 2;
		}
		View * subviewAtIndex(int index) override {
			assert(index >= 0 && index < numberOfSubviews());
			if (index == 0) {
				return &m_titleView;
			}
			return m_selectableTableView;
		}
		void layoutSubviews(bool force = false) override {
			std::cerr << "Layout Started\n";
			assert(KDFont::SmallFont->glyphSize().height() == 14); // otherwise, k_numberOfCells badly computed
			std::cerr << "Layout 1\n";
			KDCoordinate titleHeight = KDFont::SmallFont->glyphSize().height()+k_titleMargin;
			std::cerr << "Layout 2\n";
			m_titleView.setFrame(KDRect(0, 0, bounds().width(), titleHeight), force);
			std::cerr << "Layout 3\n";
			KDRect rect = KDRect(0, titleHeight, bounds().width(),  bounds().height()-titleHeight);
			std::cerr << "Layout 3.5\n";
			if (!m_selectableTableView)
				std::cerr << "is nullptr\n";
			m_selectableTableView->setFrame(rect, force);
			std::cerr << "Layout 4\n";
			std::cerr << "Layout Ended\n";
		}
		MessageTextView m_titleView;
		SelectableTableView * m_selectableTableView;
	};
	constexpr static KDCoordinate k_cellHeight = Metric::ParameterCellHeight;
	constexpr static int k_numberOfCells = (Ion::Display::Height - Metric::TitleBarHeight - 14 - ContentView::k_titleMargin) /k_cellHeight + 1 + 1; // 14 for the small font height, + 1 to get the upper rounding and + 1 for half-displayed rows
	FriendCell m_cells[k_numberOfCells];
	ContentView m_contentView;
	AgendaData* m_agendaData;
	static void timeToString(char* str, const AgendaTime& t);
	static void gapToString(char* str, const Gap& g);
	const Day& currentDay() const;
};
}

#endif //AGENDA_FRIEND_AGENDA_CONTROLLER_H
