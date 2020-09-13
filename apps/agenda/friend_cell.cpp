#include "friend_cell.h"
#include <assert.h>

namespace Agenda {

FriendCell::FriendCell() :
	HighlightCell(),
	m_labelView(KDFont::LargeFont, (I18n::Message)0, 0, 0.5, Palette::PrimaryText, Palette::BackgroundHard)
{
}

int FriendCell::numberOfSubviews() const {
	return 1;
}

View * FriendCell::subviewAtIndex(int index) {
	assert(index == 0);
	return &m_labelView;
}

void FriendCell::layoutSubviews(bool force) {
	KDCoordinate width = bounds().width();
	KDCoordinate height = bounds().height();
	m_labelView.setFrame(KDRect(1+k_iconWidth+2*k_iconMargin, 1, width-2-k_iconWidth-2*k_iconMargin - k_chevronWidth, height-2), force);
}

void FriendCell::reloadCell() {
	HighlightCell::reloadCell();
	KDColor backgroundColor = isHighlighted()? Palette::ListCellBackgroundSelected : Palette::ListCellBackground;
	m_labelView.setBackgroundColor(backgroundColor);
}

void FriendCell::setLabel(I18n::Message message) {
	m_labelView.setMessage(message);
}

void FriendCell::setText(const char* text) {
	strlcpy(owned_text, text, strlen(text)+1);
	m_labelView.setText(owned_text);
	markRectAsDirty(bounds());
	setFrame(bounds(), true);
}

void FriendCell::drawRect(KDContext * ctx, KDRect rect) const {
	KDCoordinate width = bounds().width();
	KDCoordinate height = bounds().height();
	KDColor backgroundColor = isHighlighted() ? Palette::ListCellBackgroundSelected : Palette::ListCellBackground;
	ctx->fillRect(KDRect(1, 1, width-2, height-1), backgroundColor);
	ctx->fillRect(KDRect(0, 0, width, 1), Palette::ProbabilityCellBorder);
	ctx->fillRect(KDRect(0, 1, 1, height-1), Palette::ProbabilityCellBorder);
	ctx->fillRect(KDRect(width-1, 1, 1, height-1), Palette::ProbabilityCellBorder);
	ctx->fillRect(KDRect(0, height-1, width, 1), Palette::ProbabilityCellBorder);
}

}
