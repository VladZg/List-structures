#include "Config.h"
#include <stdlib.h>
#include "Constants.h"
#include "List.h"

#define NDEBUG

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

#define InsertAfter( phys_index, value )        \
    ListInsertAfter(&list, phys_index, value);  \
    ListTextDump(&list);

#else

#define PushBack( value )        \
    ListPushBack(&list, value);

#define PushFront( value )       \
    ListPushFront(&list, value);

#define InsertAfter( phys_index, value )    \
    ListInsertAfter(&list, phys_index, value);

#define Erase( phys_index )    \
    ListErase(&list, phys_index);

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
    // ListInsertAfter(&list, 0, 34);
    // Dump;
    // PushFront(1234);
    // // ListTextDump(&list);
    // PushBack(124908);
    // PushFront(21);
    // ListInsertAfter(&list, ListElemIndexByLogIndex(&list, 2), -1234);
    // PushFront(-12);
    // Dump;
    // PushBack(33);
    // ListInsertAfter(&list, ListElemIndexByLogIndex(&list, 5), 789);
    // PushBack(-12999);

    PushBack("one");
    PushBack("two");
    PushBack("three");
    PushFront("zero");
    ListPopBack(&list);
    ListTextDump(&list);
    InsertAfter(2, "two point five");
    InsertAfter(4, "zero point five");
    PushFront("minus one");
    ListTextDump(&list);

    // ListPrint(&list);
    // ListGraphDump(&list);

    // ListLinearize(&list);
    // ListClear(&list);
    // ListPopBack(&list);
    // ListGraphDump(&list);
    // Dump
    // ListPopFront(&list);
    // ListPrint(&list);
    // ListTextDump(&list);
    // ListClear(&list);
    // ListPrint(&list);
    // Dump
    // ListGraphDump(&list);

    ListDtor(&list);

    return 1;
}
