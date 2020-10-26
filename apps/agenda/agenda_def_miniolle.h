#ifndef APPS_AGENDA_MINIOLLE_DEF_H
#define APPS_AGENDA_MINIOLLE_DEF_H

#include "agenda_types.h"

const AgendaDef agenda_miniolle =
{
	.name = "Miniolle",
	.days = {
	// Monday Week A
	{
		{9, 10}, // Start Time
		1, // gapsCount
		{
			{{12,15}, // Eating gap
			 {12,40}}
		},
		{16, 50} // End Time
	},
	// Tuesday Week A
	{
		{9, 10}, // Start Time
		1, // gapsCount
		{
			{{12,15}, // Eating gap
			 {12,40}}
		},
		{16, 50} // End Time
	},
	// Wednesday Week A
	{
		{8, 10}, // Start Time
		2, // gapsCount
		{
			{{9, 10},
			 {11,20}},
			{{12, 15}, // Eating gap
			 {13,40}}
		},
		{14, 35} // End Time
	}
	}
};

#endif //APPS_AGENDA_MINIOLLE_DEF_H
