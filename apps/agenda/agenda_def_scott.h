#ifndef APPS_AGENDA_SCOTT_DEF_H
#define APPS_AGENDA_SCOTT_DEF_H

#include "agenda_types.h"

const AgendaDef agenda_scott =
{
    .name = "Scott",
    .days = {
    // Monday Week A
    {
        {8,45}, // Start Time
        1, // gapsCount
        {
            {{12,15},
             {13,40}}
        },
        {17,45} // End Time
    },
    // Tuesday Week A
    {
        {9,15}, // Start Time
        2, // gapsCount
        {
            {{13,15},
             {13,40}},
            {{15,50},
             {16,20}}
        },
        {18,45} // End Time
    }
    }
};

#endif //APPS_AGENDA_SCOTT_DEF_H
