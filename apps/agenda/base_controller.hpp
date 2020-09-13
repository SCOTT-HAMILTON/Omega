#ifndef AGENDA_BASE_CONTROLLER_H
#define AGENDA_BASE_CONTROLLER_H 

#include <escher.h>
#include <apps/i18n.h>
#include "cell.h"

namespace Agenda {

template<size_t totalRowCount, class CellType>
class BaseController : public ViewController, public SimpleListViewDataSource, public SelectableTableViewDataSource {
public:
	BaseController(Responder * parentResponder, I18n::Message titleMessage) : 
		ViewController(parentResponder),
		m_selectableTableView(this),
		m_contentView(&m_selectableTableView, titleMessage)
	{
		m_selectableTableView.setTopMargin(Metric::CommonTopMargin-ContentView::k_titleMargin);
	}
	View * view() override { return &m_contentView; }
	void viewWillAppear() override {
		ViewController::viewWillAppear();
		// TODO: set right current row With MainMenu data object
		selectRow(0);
	}
	/* TELEMETRY_ID("Agenda"); */
	int numberOfRows() const override {
		return k_totalNumberOfRows; }
	KDCoordinate cellHeight() override {
		return k_cellHeight; }
	HighlightCell * reusableCell(int index) override {
		assert(index >= 0);
		assert(index < k_numberOfCells);
		return &m_cells[index];
	}
	int reusableCellCount() const override {
		return k_numberOfCells; }
protected:
	class ContentView : public View {
	public:
		ContentView(SelectableTableView * selectableTableView, I18n::Message titleMessage) :
			m_titleView(KDFont::SmallFont, titleMessage, 0.5f, 0.5f, Palette::SecondaryText, Palette::BackgroundApps),
			m_selectableTableView(selectableTableView)
	{}
		constexpr static KDCoordinate k_titleMargin = 8;
		void reload() {
			layoutSubviews(true);
		}
	private:
		int numberOfSubviews() const override {
			return 2; }
		View * subviewAtIndex(int index) override {
			assert(index >= 0 && index < numberOfSubviews());
			if (index == 0) {
				return &m_titleView;
			}
			return m_selectableTableView;
		}
		void layoutSubviews(bool force = false) override {
			assert(KDFont::SmallFont->glyphSize().height() == 14); // otherwise, k_numberOfCells badly computed
			KDCoordinate titleHeight = KDFont::SmallFont->glyphSize().height()+k_titleMargin;
			m_titleView.setFrame(KDRect(0, 0, bounds().width(), titleHeight), force);
			m_selectableTableView->setFrame(KDRect(0, titleHeight, bounds().width(),  bounds().height()-titleHeight), force);
		}
		MessageTextView m_titleView;
		SelectableTableView * m_selectableTableView;
	};
	I18n::Message * m_messages;
	size_t k_totalNumberOfRows = totalRowCount;
	SelectableTableView m_selectableTableView;
	CellType m_cells[totalRowCount];
	ContentView m_contentView;
private:
	constexpr static KDCoordinate k_cellHeight = Metric::ParameterCellHeight;
	constexpr static int k_numberOfCells = (Ion::Display::Height - Metric::TitleBarHeight - 14 - ContentView::k_titleMargin) /k_cellHeight + 1 + 1; // 14 for the small font height, + 1 to get the upper rounding and + 1 for half-displayed rows
};
}

#endif //AGENDA_BASE_CONTROLLER_H
