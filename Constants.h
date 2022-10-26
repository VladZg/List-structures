#ifndef CONSTANTS_H
#define CONSTANTS_H

enum ListStatuses
{
    LIST_IS_OK_STATUS         = 1,
    LIST_IS_DESTRUCTED_STATUS = 2,
};

enum ListElemConstants
{
    // LIST_ELEM_POISONED_VALUE = 0xBADDED,
    LIST_ELEM_FREE = 0xBAAAAD,
};

#define LIST_ELEM_POISONED_VALUE NULL

enum ListConstants
{
    LIST_MIN_CAPACITY = 20,
    LIST_MAXSIZE      = 100,
};

#endif
