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
    // ListInsertAfter(&list, ListFindElemIndexByLogIndex(&list, 2), -1234);
    // PushFront(-12);
    // Dump;
    // PushBack(33);
    // ListInsertAfter(&list, ListFindElemIndexByLogIndex(&list, 5), 789);
    // PushBack(-12999);

    // PushBack("one");
    // PushBack("two");
    // PushBack("three");
    // PushFront("zero");
    // ListPopBack(&list);
    // ListTextDump(&list);
    // InsertAfter(2, "two point five");
    // InsertAfter(4, "zero point five");
    // PushFront("minus one");
    // ListTextDump(&list);

    // PushBack("four");
    // PushBack("five");
    // PushBack("six");
    // PushBack("seven");
    // PushBack("eight");
    // ListResize(&list, INCREASE_LIST_CAPACITY_MODE);
    // ListTextDump(&list);
    // ListClear(&list);
    // PushFront("new first!");

    // ListPrint(&list);
    // ListGraphDump(&list);

    // PushBack("new second");
    // PushBack("new last...");
    // PushFront("new zero");
    // PushBack("just new1");
    // PushBack("just new2");
    // PushFront("just new3");
    // PushBack("just new4");
    // PushBack("just new5");
    // PushFront("just new6");
    // PushBack("just new7");
    // PushFront("just new8");
    // PushBack("just new9");
    // ListTextDump(&list);
    // ListGraphDump(&list);

    // PushBack("1");
    // PushFront("2");
    // PushBack("3");
    // PushBack("4");
    // PushFront("5");
    // PushBack("6");
    // PushFront("7");
    // PushBack("8");
    // PushFront("9");
    // PushBack("10");
    // PushFront("0");
    // ListTextDump(&list);
    // ListLinearize(&list);
    // ListTextDump(&list);
    // ListPopFront(&list);
    // ListPopBack(&list);
    // ListPopBack(&list);
    // ListPopBack(&list);
    // ListPopBack(&list);
    // ListPopBack(&list);
    // ListPopBack(&list);
    // ListPopBack(&list);
    // ListErase(&list, 7);
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
    // ListPopBack(&list);
    // ListPopBack(&list);
    // ListPopBack(&list);
    // ListPopBack(&list);
    // ListGraphDump(&list, 1);
    // ListTextDump(&list);

    // ListTextDump(&list);
    PushFront("0");
    PushBack("-1");
    PushBack("-2");
    PushBack("-3");
    //  ListGraphDump(&list, 1);
    PushFront("-4");
    PushBack("-5");
    PushBack("-6");
    PushFront("-7");
    PushBack("-8");
    PushFront("-9");
    ListPopFront(&list);
    PushBack("-10");
    // ListTextDump(&list);
    PushBack("-11");
    ListClear(&list);
    // ListFullVerify(&list);
    // ListTextDump(&list);

    // ListTextDump(&list);
    // PushBack("-11");
    // ListPopFront(&list);
    // ListErase(&list, 9);
    // ListPopFront(&list);
    //  ListGraphDump(&list, 2);
    // ListTextDump(&list);
    // ListTextDump(&list);
    // ListClear(&list);
    // ListLinearize(&list);
    ListTextDump(&list);
    // ListResize(&list, INCREASE_LIST_CAPACITY_MODE);
    // ListResize(&list, INCREASE_LIST_CAPACITY_MODE);
    // ListResize(&list, INCREASE_LIST_CAPACITY_MODE);
    // ListErase(&list, 4);
    // ListPopFront(&list);
    // ListTextDump(&list);
    // ListClear(&list);
    // ListTextDump(&list);
    // ListResize(&list, INCREASE_LIST_CAPACITY_MODE);
    // ListTextDump(&list);
    // ListResize(&list, DECREASE_LIST_CAPACITY_MODE);
    // ListTextDump(&list);
    // PushBack("two");
    // PushBack("three");
    // PushBack("four");
    // ListErase(&list, 2);
    // PushFront("-4");
    // ListTextDump(&list);
    // ListInsertBefore(&list, 1, "ok");
    // InsertAfter(0, "op");
    // ListPopFront(&list);
    // ListPopFront(&list);
    // PushFront("zero");
    // InsertAfter(0, "zero");
    // PushFront("zero");
    // PushFront("-1");
    // PushFront("-2");
    // PushFront("-3");
    // ListPopBack(&list);
    // ListErase(&list, 0);
    // ListClear(&list);

    // ListTextDump(&list);
    // ListGraphDump(&list, 3);
    ListPrint(&list);

    ListDtor(&list);
    // ListDtor(&list);

    return 1;
}
