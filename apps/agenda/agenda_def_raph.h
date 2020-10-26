#ifndef APPS_AGENDA_RAPH_DEF_H
#define APPS_AGENDA_RAPH_DEF_H

#include "agenda_types.h"

const AgendaDef agenda_raph =
{
	.name = "Raph",
	.days = {
	// Monday Week A
	{
		{9, 10}, // Start Time
		2, // gapsCount
		{
			{{10, 20}, // Eating gap
			 {12,40}},
			{{13, 40}, // Gap du galérien
			 {15, 50}}
		},
		{18, 40} // End Time AÏ coup dur
	},
	// Tuesday Week A
	{
		{8, 10}, // Start Time
		2, // gapsCount
		{
			{{12, 15}, // Eating gap
			 {12,40}},
			{{15, 50}, // Gap du galérien
			 {16, 10}}
		},
		{18, 40} // End Time AÏ coup dur
	},
	// Wednesday Week A
	{
		{9, 10}, // Start Time
		0, // gapsCount
		{},
		{12, 15}
	}
	}
};

#endif //APPS_AGENDA_RAPH_DEF_H
