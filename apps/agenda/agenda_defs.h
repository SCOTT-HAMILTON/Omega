#ifndef APPS_AGENDA_DEFS_H
#define APPS_AGENDA_DEFS_H

#define AGENDA_NUMS 5

#include "agenda_types.h"
#include "agenda_def_scott.h"
#include "agenda_def_felix.h"
#include "agenda_def_miniolle.h"
#include "agenda_def_raph.h"
#include "agenda_def_mikl.h"

const size_t myAgenda = 0;

const AgendaDef agendas[AGENDA_NUMS] = {
	agenda_scott,
	agenda_felix,
	agenda_miniolle,
	agenda_raph,
	agenda_mikl
};

#endif
