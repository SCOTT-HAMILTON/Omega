#ifndef APPS_AGENDA_DEFS_H
#define APPS_AGENDA_DEFS_H

#define AGENDA_NUMS 4

#include "agenda_types.h"

const size_t myAgenda = 0;

const AgendaDef agendas[AGENDA_NUMS] = {
	{
		.name = "Scott",
		.days = {
		// Monday Week A
		{
			{8,10}, // Start Time
			1, // gapsCount
			{
				{{12,15}, // Eating gap
				 {13,40}}
			},
			{15, 50} // End Time
		}
		}
	},
	{
		.name = "Felix",
		.days = {
		// Monday Week A
		{
			{10, 20}, // Start Time
			1, // gapsCount
			{
				{{12,15}, // Eating gap
				 {12,40}}
			},
			{16, 50} // End Time
		}
		}
	},
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
		}
		}
	},
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
				{{13, 40}, // Eating gap
				 {15, 50}}
			},
			{18, 40} // End Time
		}
		}
	}
};

#endif
