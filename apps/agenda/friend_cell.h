#ifndef AGENDA_APP_FRIEND_CELL_H
#define AGENDA_APP_FRIEND_CELL_H

#include <escher.h>

namespace Agenda {

class FriendCell : public HighlightCell {
public:
  FriendCell();
  void reloadCell() override;
  void setLabel(I18n::Message message);
  void setText(const char* text);
  void drawRect(KDContext * ctx, KDRect rect) const override;
private:
  constexpr static KDCoordinate k_iconWidth = 35;
  constexpr static KDCoordinate k_iconHeight = 19;
  constexpr static KDCoordinate k_iconMargin = 10;
  constexpr static KDCoordinate k_chevronWidth = 8;
  constexpr static KDCoordinate k_chevronMargin = 10;
  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
  void layoutSubviews(bool force = false) override;
  MessageTextView m_labelView;
  char owned_text[96];
};

}

#endif //AGENDA_APP_FRIEND_CELL_H
