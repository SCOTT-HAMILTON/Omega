apps += Agenda::App
app_headers += apps/agenda/app.h

app_agenda_src = $(addprefix apps/agenda/,\
  app.cpp \
  common.cpp \
  cell.cpp \
  friend_cell.cpp \
  friend_agenda_controller.cpp \
  common_gaps_controller.cpp \
  starts_with_me_controller.cpp \
  ends_with_me_controller.cpp \
  friend_controller.cpp \
  day_of_week_controller.cpp \
)

apps_src += $(app_agenda_src)

i18n_files += $(addprefix apps/agenda/,\
	base.de.i18n\
	base.en.i18n\
	base.es.i18n\
	base.fr.i18n\
	base.pt.i18n\
	base.it.i18n\
	base.nl.i18n\
	base.hu.i18n\
)

# Image dependencies
#
app_images = += apps/agenda/agenda_icon.png \
				apps/agenda/agenda_binomial_icon.png \
				apps/agenda/agenda_uniform_icon.png \
				apps/agenda/agenda_exponential_icon.png \
				apps/agenda/agenda_normal_icon.png \
				apps/agenda/agenda_focused_binomial_icon.png \
				apps/agenda/agenda_focused_uniform_icon.png \
				apps/agenda/agenda_focused_exponential_icon.png \
				apps/agenda/agenda_focused_normal_icon.png

$(eval $(call depends_on_image,apps/agenda/app.cpp,apps/agenda/agenda_icon.png))

$(eval $(call depends_on_image,apps/agenda/day_of_week_controller.cpp,$(addprefix apps/agenda/images/, \
agenda_binomial_icon.png \
agenda_uniform_icon.png \
agenda_exponential_icon.png \
agenda_normal_icon.png \
agenda_focused_binomial_icon.png \
agenda_focused_uniform_icon.png \
agenda_focused_exponential_icon.png \
agenda_focused_normal_icon.png \
)))

$(eval $(call depends_on_image,apps/agenda/friend_controller.cpp,$(addprefix apps/agenda/images/, \
agenda_binomial_icon.png \
agenda_focused_binomial_icon.png \
)))

$(eval $(call depends_on_image,apps/agenda/friend_agenda_controller.cpp,$(addprefix apps/agenda/images/, \
agenda_binomial_icon.png \
agenda_focused_binomial_icon.png \
)))
