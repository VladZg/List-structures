#include "Config.h"
#include <stdlib.h>
#include <cstdio>
#include "Constants.h"
#include "ColourConsts.h"
#include "List.h"

//DSL
#define index rand()
#define DATA      list->data
#define TAIL_IND  list->tail_index
#define HEAD_IND  list->head_index
#define SIZE      list->size
#define CAPACITY  list->capacity
#define FREE      list->free
#define IS_LINEAR list->is_linear

#define PrintError( msg )                       \
                                                \
    fprintf(stderr, "\"%s\": %s",               \
            __PRETTY_FUNCTION__, msg);          \

#define ListVerify_                             \
                                                \
    if(ListVerify(list) != LIST_IS_OK_STATUS)   \
    {                                           \
        PrintError("List is damaged\n");        \
        return 0;                               \
    }

#define ListVerifyStatus_                       \
                                                \
    int status = ListVerify(list);              \
                                                \
    if (status != LIST_IS_OK_STATUS)            \
    {                                           \
        PrintError("List is damaged\n");        \
        return status;                          \
    }

int ListCtor(List* list)
{
    SIZE      = 0;
    CAPACITY  = LIST_MIN_CAPACITY;

    HEAD_IND  = 0;
    TAIL_IND  = 0;
    FREE      = 1;

    IS_LINEAR = true;

    DATA = (ListElem*) calloc(CAPACITY + 1, sizeof(ListElem));

    DATA[0] = {(Value_t) LIST_ELEM_POISONED_VALUE, 0, 0};

    for (int index = 1; index <= CAPACITY; index++)
    {
        DATA[index] =
        {
            (Value_t) LIST_ELEM_POISONED_VALUE,
            DATA[index].next = index + 1,
            DATA[index].prev = LIST_ELEM_FREE,
        };
    }

    DATA[CAPACITY].next = 0;

    list->is_linear = true;

    return LIST_IS_OK_STATUS;
}

int ListDtor(List* list)
{
    free(DATA);

    linux(30);
    DATA = nullptr;

    return LIST_IS_DESTRUCTED_STATUS;
}

int ListVerify(List* list)
{
    return LIST_IS_OK_STATUS;
}

int ListTextDump(List* list)
{
    fprintf(stdout, KYEL "\n%s:\n\n" KNRM, __PRETTY_FUNCTION__);

    fprintf(stdout, KBLU "\tsize      " KNRM "= %ld\n"
                    KBLU "\tcapacity  " KNRM "= %ld\n"
                    KBLU "\tis_linear " KNRM "= %d \n"
                    KBLU "\thead_ind  " KNRM "= %ld\n"
                    KBLU "\ttail_ind  " KNRM "= %ld\n"
                    KBLU "\tfree      " KNRM "= %ld\n\n", SIZE, CAPACITY, IS_LINEAR, HEAD_IND, TAIL_IND, FREE);

    fprintf(stdout, KBLU "\tdata = " KNRM "{\n");

    for (size_t index = 1; index <= CAPACITY; index++)
    {
        fprintf(stdout, "\t\t[" KCYN "%02ld" KNRM "]: ", index);

        if (DATA[index].value != (Value_t) LIST_ELEM_POISONED_VALUE)
            fprintf(stdout, "%c\n", DATA[index].value);

        else fprintf(stdout, "NULL (" KMAG "POISON" KNRM ")\n");
    }

    fprintf(stdout, "\t}\n");

    fprintf(stdout, KBLU "\n\tnext " KNRM "= {\n");

    for (size_t index = 1; index <= CAPACITY; index++)
    {
        fprintf(stdout, "\t\t[" KCYN "%02ld" KNRM "]: ", index);

        fprintf(stdout, "%ld\n", DATA[index].next);
    }

    fprintf(stdout, "\t}\n");

    fprintf(stdout, KBLU "\n\tprev " KNRM "= {\n");

    for (size_t index = 1; index <= CAPACITY; index++)
    {
        fprintf(stdout, "\t\t[" KCYN "%02ld" KNRM "]: ", index);

        if (DATA[index].prev != LIST_ELEM_FREE)
            fprintf(stdout, "%ld\n", DATA[index].prev);

        else fprintf(stdout, "%X (" KMAG "POISON" KNRM ")\n", LIST_ELEM_FREE);
    }

    fprintf(stdout, "\t}\n\n");

    return 1;
}

int ListGraphDump(List* list)
{
    FILE* file = fopen("TextForGraphDump", "w");

    fprintf(file, "digraph G\n{\n    ");

    if (SIZE < 1)
        return 1;

    size_t index = ListHead(list);
    fprintf(file, "\"%c\"", DATA[index].value);

    while ((index = ListNext(list, index)) != 0)
        fprintf(file, " -> \"%c\"", DATA[index].value);

    fprintf(file, ";\n}\n");

    fclose(file);

    system("dot TextForGraphDump -Tsvg -o GraphDump.svg");
    system("eog GraphDump.svg");

    return 1;
}

size_t ListElemIndex(List* list, size_t log_index )
{
    ListVerify_

    return 1;
}

size_t ListNext(List* list, size_t phys_index)
{
    // if ((ListVerify(list) != LIST_IS_OK_STATUS) || (phys_index == 0) || (phys_index > CAPACITY))
        // PrintError("List is damaged")
        // return 0;

    return DATA[phys_index].next;
}

size_t ListPrev(List* list, size_t phys_index)
{
    // if ((ListVerify(list) != LIST_IS_OK_STATUS) || (phys_index == 0) || (phys_index > CAPACITY))
        // PrintError("List is damaged")
        // return 0;

    return DATA[phys_index].prev;
}

size_t ListHead(List* list)
{
    ListVerify_

    return HEAD_IND;
}

size_t ListTail(List* list)
{
    ListVerify_

    return TAIL_IND;
}

size_t ListInsertAfter(List* list, size_t phys_index, Value_t value)
{
    ListVerify_

    size_t new_elem_index = FREE;
    FREE = DATA[FREE].next;

    if ((phys_index == HEAD_IND) && (phys_index == TAIL_IND) && (SIZE == 0))
    {
        DATA[new_elem_index]= {value, 0, 0};

        TAIL_IND = new_elem_index;
        HEAD_IND = new_elem_index;
    }

    else if (phys_index == TAIL_IND)
    {
        DATA[TAIL_IND].next = new_elem_index;
        DATA[new_elem_index] = {value, 0, TAIL_IND};

        TAIL_IND = new_elem_index;
    }

    else
    {
        DATA[new_elem_index] = {value, DATA[phys_index].next, phys_index};
        DATA[DATA[phys_index].next].prev = new_elem_index;
        DATA[phys_index].next = new_elem_index;
    }

    SIZE++;

    return new_elem_index;
}

size_t ListInsertBefore(List* list, size_t phys_index, Value_t value)
{
    ListVerify_

    if ((HEAD_IND == TAIL_IND) && (SIZE == 0))
        return ListInsertAfter(list, phys_index, value);

    if (phys_index == HEAD_IND)
    {
        size_t new_elem_index = FREE;
        FREE = DATA[FREE].next;

        DATA[HEAD_IND].prev = new_elem_index;
        DATA[new_elem_index] = {value, HEAD_IND, 0};

        HEAD_IND = new_elem_index;

        SIZE++;

        return new_elem_index;
    }

    else
        return ListInsertAfter(list, DATA[phys_index].prev, value);
}

Value_t ListErase(List* list, size_t phys_index)
{
    Value_t deleted_value = DATA[phys_index].value;

    DATA[DATA[phys_index].prev].next = DATA[phys_index].next;
    DATA[DATA[phys_index].next].prev = DATA[phys_index].prev;
    DATA[phys_index] = {(Value_t) LIST_ELEM_POISONED_VALUE, FREE, LIST_ELEM_FREE};
    FREE = phys_index;

    return deleted_value;
}

Value_t ListPopBack(List* list)
{
    return ListErase(list, ListTail(list));
}

int ListPushBack(List* list, Value_t value)
{
    return ListInsertAfter(list, ListTail(list), value);
}

Value_t ListPopFront(List* list)
{
    return ListErase(list, ListHead(list));
}

int ListPushFront(List* list, Value_t value)
{
    return ListInsertBefore(list, ListHead(list), value);;
}

int ListLinearize(List* list)
{
    ListVerifyStatus_

    return LIST_IS_OK_STATUS;
}

int ListClear(List* list)
{
    ListVerifyStatus_

    return LIST_IS_OK_STATUS;
}

int ListResize(List* list)
{
    ListVerifyStatus_

    return LIST_IS_OK_STATUS;
}

int ListPrint(List* list)
{
    ListVerifyStatus_

    size_t index = ListHead(list);
    fprintf(stdout, "%c ", DATA[index].value);

    for (size_t i = 1; i < SIZE; i++)
    {
        index = ListNext(list, index);
        fprintf(stdout, "%c ", DATA[index].value);
    }

    fprintf(stdout, "\n");

    return LIST_IS_OK_STATUS;
}
