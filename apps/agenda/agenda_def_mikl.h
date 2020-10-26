#ifndef APPS_AGENDA_MIKL_DEF_H
#define APPS_AGENDA_MIKL_DEF_H

#include "agenda_types.h"

const AgendaDef agenda_mikl =
{
	.name = "Mikl",
	.days = {
	// Monday Week A
	{
		{8, 10}, // Start Time
		1, // gapsCount
		{
			{{12, 15}, // Eating gap
			 {14, 35}}
		},
		{17, 45} // End Time AÏ coup dur
	},
	// Tuesday Week A
	{
		{9, 10}, // Start Time
		1, // gapsCount
		{
			{{12, 15}, // Eating gap
			 {13, 40}}
		},
		{18, 40} // End Time
	},
	// Wednesday Week A
	{
		{8, 10}, // Start Time
		0, // gapsCount
		{},
		{12, 15} // End Time
	}
	}
};

#endif //APPS_AGENDA_MIKL_DEF_H
