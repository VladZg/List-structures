#include "Config.h"
#include <stdlib.h>
#include "Constants.h"
#include "List.h"

// #define NDEBUG

#ifndef NDEBUG

#define PushBack( value )        \
    ListPushBack(&list, value);  \
    ListTextDump(&list);         \

#define PushFront( value )       \
    ListPushFront(&list, value); \
    ListTextDump(&list);

#define Dump                     \
    ListTextDump(&list);         \
    ListPrint(&list);            \
    ListGraphDump(&list);

#else

#define PushBack( value )        \
    ListPushBack(&list, value);

#define PushFront( value )       \
    ListPushFront(&list, value);

#define Dump {}

#endif

int main()
{
    List list = {};
    ListCtor(&list);

    // ListTextDump(&list);
    // ListGraphDump(&list);

//     size_t i1 = ListInsertAfter(&list, 0, 'A');
//     Dump;
//
//     size_t i2 = ListInsertAfter(&list, i1, 'B');
//     Dump;
//
//     size_t i5 = ListInsertAfter(&list, i2, 'E');
//     Dump;
//
//     size_t i3 = ListInsertAfter(&list, i2, 'C');
//     Dump;
//
//     size_t i6 = ListInsertAfter(&list, i5, 'F');
//     Dump;
//
//     size_t i4 = ListInsertAfter(&list, i3, 'D');
//     Dump;
//
//     ListPushFront(&list, 'S');
//     Dump;
//
//     ListPushBack(&list, 'G');
//     Dump;
//
//     ListPushFront(&list, 's');
//     Dump;
//
//     ListErase(&list, i4);
//     Dump;

    // PushBack('A');
    // PushBack('b');
    // PushBack('C');
    // PushBack('d');
    // PushBack('E');
    // PushBack('f');
    // PushFront('O');
    ListInsertAfter(&list, 0, 'd');
    Dump;
    PushFront('b');
    // ListTextDump(&list);
    PushBack('e');
    PushFront('A');
    ListInsertAfter(&list, 2, 'c');
    PushFront('o');
    Dump;
    size_t ind_f = PushBack('f');
    ListInsertAfter(&list, ind_f, 'g');
    PushBack('h');

    ListPrint(&list);
    ListGraphDump(&list);

    ListDtor(&list);

    return 1;
}
