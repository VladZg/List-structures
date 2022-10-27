#ifndef CONSTANTS_H
#define CONSTANTS_H

enum ListStatuses
{
    LIST_IS_OK_STATUS           = 1,
    LIST_IS_DESTRUCTED_STATUS   = 2,
    LIST_IS_NULL_STATUS         = 3,
    LIST_OVERFLOW_STATUS        = 4,
    HEAD_IND_WRONG_STATUS       = 5,
    TAIL_IND_WRONG_STATUS       = 6,
    LIST_FREE_WRONG_STATUS      = 7,
    LIST_IS_LINEAR_WRONG_STATUS = 8,
    LIST_DATA_IS_NULL_STATUS    = 9,
    LIST_IS_EMPTY_STATUS        = 10,
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
