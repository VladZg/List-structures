#include "Config.h"
#include <stdlib.h>
#include <cstdio>
#include "Constants.h"
#include "ColourConsts.h"
#include "Assert.h"
#include "List.h"

//DSL
#define DATA      list->data
#define TAIL_IND  list->tail_index
#define HEAD_IND  list->head_index
#define SIZE      list->size
#define CAPACITY  list->capacity
#define FREE      list->free
#define IS_LINEAR list->is_linear

#define PrintError( msg )                           \
                                                    \
    fprintf(stderr, KYEL "\"%s\"" KNRM ": %s\n",    \
            __PRETTY_FUNCTION__, msg);              \

#define ListVerify_                                 \
                                                    \
    if(ListVerify(list) != LIST_IS_OK_STATUS)       \
    {                                               \
        PrintError("List is damaged\n");            \
        return 0;                                   \
    }

#define ListVerifyStatus_                           \
                                                    \
    int status = ListVerify(list);                  \
                                                    \
    if (status != LIST_IS_OK_STATUS)                \
    {                                               \
        PrintError("List is damaged");              \
        return status;                              \
    }

#define PhysIndexVerify_                                \
                                                        \
    if (((phys_index == 0) && (phys_index != HEAD_IND)) \
          || (phys_index > CAPACITY))                   \
    {                                                   \
        PrintError("Wrong index")                       \
        return 0;                                       \
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
    ASSERT(DATA != nullptr);

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

    ListVerifyStatus_

    return LIST_IS_OK_STATUS;
}

int ListDtor(List* list)
{
    ListVerifyStatus_

    free(DATA);

    DATA = nullptr;

    return LIST_IS_DESTRUCTED_STATUS;
}

int ListVerify(List* list)
{
    int list_status = LIST_IS_OK_STATUS;

    if (list == nullptr)
        list_status = LIST_IS_NULL_STATUS;

    if (DATA == nullptr)
        list_status = LIST_DATA_IS_NULL_STATUS;

    if (SIZE > CAPACITY)
        list_status = LIST_OVERFLOW_STATUS;

    if (HEAD_IND > CAPACITY)
        list_status = HEAD_IND_WRONG_STATUS;

    if (TAIL_IND > CAPACITY)
        list_status = TAIL_IND_WRONG_STATUS;

    if (FREE > CAPACITY)
        list_status = LIST_FREE_WRONG_STATUS;

    if (IS_LINEAR > 1)
        list_status = LIST_IS_LINEAR_WRONG_STATUS;

    if (list_status != LIST_IS_OK_STATUS)
        return list_status;

    // for (int i = 1; i <= SIZE; i++)
    // {
    //     if (ListNext)
    //     return
    // }

    return LIST_IS_OK_STATUS;
}

static int IsListEmpty(List* list)
{
    if (SIZE)
        return LIST_IS_OK_STATUS;

    return LIST_IS_EMPTY_STATUS;
}

static void PrintListElemValue(FILE* file, int value)
{
    fprintf(file, "%d", value);
}

static void PrintListElemValue(FILE* file, char value)
{
    fprintf(file, "%c", value);
}

static void PrintListElemValue(FILE* file, double value)
{
    fprintf(file, "%lf", value);
}

static void PrintListElemValue(FILE* file, const char* value)
{
    fprintf(file, "%s", value);
}

static void PrintListElemValue(FILE* file, float value)
{
    fprintf(file, "%f", value);
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
            PrintListElemValue(stdout, DATA[index].value);

        else fprintf(stdout, "NULL (" KMAG "POISON" KNRM ")");

        fprintf(stdout, "\n");
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
    if (IsListEmpty(list) == LIST_IS_EMPTY_STATUS)
    {
        PrintError("List is empty");
        return LIST_IS_EMPTY_STATUS;
    }

    FILE* file = fopen("TextForGraphDump", "w");

    fprintf(file, "digraph G\n{\n    ");

    if (SIZE < 1)
        return 1;

    size_t index = ListHead(list);
    fprintf(file, "\"");
    PrintListElemValue(file, DATA[index].value);
    fprintf(file, "\"");

    while ((index = ListNext(list, index)) != 0)
    {
        fprintf(file, " -> \"");
        PrintListElemValue(file, DATA[index].value);
        fprintf(file, "\"");
    }

    fprintf(file, ";\n}\n");

    fclose(file);

    system("dot TextForGraphDump -Tsvg -o GraphDump.svg");
    system("eog GraphDump.svg");

    return LIST_IS_OK_STATUS;
}

size_t ListElemIndexByLogIndex(List* list, size_t log_index)
{
    ListVerify_

    if ((log_index == 0) || (log_index > SIZE))
    {
        PrintError("Wrong index");
        return 0;
    }

    if (IS_LINEAR)
        return HEAD_IND + log_index - 1;

    size_t phys_index = HEAD_IND;
    int    elem_i_index = 1;

    while (elem_i_index++ < log_index)
        phys_index = DATA[phys_index].next;

    return phys_index;
}

size_t ListNext(List* list, size_t phys_index)
{
    ListVerify_
    PhysIndexVerify_

    return DATA[phys_index].next;
}

size_t ListPrev(List* list, size_t phys_index)
{
    ListVerify_
    PhysIndexVerify_

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

    if (phys_index > CAPACITY)
    {
        PrintError("Wrong index");
        return 0;
    }

    // if (FREE == 0)
        // ListResize(list, 2);

    if (phys_index != TAIL_IND)
        IS_LINEAR = false;

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
        if (FREE != TAIL_IND + 1)
            IS_LINEAR = false;

        DATA[TAIL_IND].next = new_elem_index;
        DATA[new_elem_index] = {value, 0, TAIL_IND};

        TAIL_IND = new_elem_index;
    }

    else
    {
        IS_LINEAR = false;

        DATA[new_elem_index] = {value, DATA[phys_index].next, phys_index};
        DATA[DATA[phys_index].next].prev = new_elem_index;
        DATA[phys_index].next = new_elem_index;
    }

    SIZE++;

    ListVerify_

    return new_elem_index;
}

size_t ListInsertBefore(List* list, size_t phys_index, Value_t value)
{
    ListVerify_
    PhysIndexVerify_

    if ((HEAD_IND == TAIL_IND) && (SIZE == 0))
        return ListInsertAfter(list, phys_index, value);

    if (phys_index != HEAD_IND || HEAD_IND != FREE + 1 || FREE == 0)
        IS_LINEAR = false;

    // if (FREE == 0)
        // ListResize(list, 2);

    if (phys_index == HEAD_IND)
    {
        IS_LINEAR = false;

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
    ListVerify_
    PhysIndexVerify_

    if (SIZE == 0)
    {
        PrintError("List is empty, can't delete element");
        return (Value_t) LIST_ELEM_POISONED_VALUE;
    }

    Value_t deleted_value = DATA[phys_index].value;

    if (phys_index == HEAD_IND)
    {
        size_t new_head_ind = DATA[HEAD_IND].next;

        DATA[new_head_ind].prev  = 0;
        DATA[HEAD_IND] = {(Value_t) LIST_ELEM_POISONED_VALUE, FREE, LIST_ELEM_FREE};

        FREE = HEAD_IND;
        HEAD_IND = new_head_ind;
    }

    else if (phys_index == TAIL_IND)
    {
        size_t new_tail_ind = DATA[TAIL_IND].prev;

        DATA[new_tail_ind].next = 0;
        DATA[TAIL_IND] = {(Value_t) LIST_ELEM_POISONED_VALUE, FREE, LIST_ELEM_FREE};

        FREE = TAIL_IND;
        TAIL_IND = new_tail_ind;
    }

    else
    {
        IS_LINEAR = false;

        DATA[DATA[phys_index].prev].next = DATA[phys_index].next;
        DATA[DATA[phys_index].next].prev = DATA[phys_index].prev;
        DATA[phys_index] = {(Value_t) LIST_ELEM_POISONED_VALUE, FREE, LIST_ELEM_FREE};
        FREE = phys_index;
    }

    SIZE--;

    // if (SIZE <= CAPACITY / 2)
        // ListResize(list, 2);

    return deleted_value;
}

Value_t ListPopBack(List* list)
{
    return ListErase(list, TAIL_IND);
}

int ListPushBack(List* list, Value_t value)
{
    return ListInsertAfter(list, TAIL_IND, value);
}

Value_t ListPopFront(List* list)
{
    return ListErase(list, HEAD_IND);
}

int ListPushFront(List* list, Value_t value)
{
    return ListInsertBefore(list, HEAD_IND, value);;
}

int ListLinearize(List* list)
{
    ListVerifyStatus_

    if (!IS_LINEAR)
    {
        ListElem* new_data = (ListElem*) calloc(CAPACITY + 1, sizeof(ListElem));
        ASSERT(new_data != nullptr);

        new_data[0] = {(Value_t) LIST_ELEM_POISONED_VALUE, 0, 0};
        FREE = 0;

        size_t data_index = ListHead(list);
        fprintf(stdout, "\n%ld\n", data_index);

        for (size_t new_index = 1; new_index <= CAPACITY; new_index++)
        {
            if (data_index != 0)
            {
                new_data[new_index] = {DATA[data_index].value, ListNext(list, data_index), ListPrev(list, data_index)};
            }

            else
            {
                if (FREE == 0) FREE = new_index;

                new_data[new_index] = {(Value_t) LIST_ELEM_POISONED_VALUE, (new_index == CAPACITY ? 0 : new_index + 1), LIST_ELEM_FREE};
            }

            data_index = ListNext(list, data_index);
            fprintf(stdout, "\n%ld\n", data_index);
        }

        free(DATA);

        DATA = new_data;
        IS_LINEAR = true;
        HEAD_IND = (SIZE == 0 ? 0 : 1);
        TAIL_IND = (SIZE == 0 ? 0 : SIZE);
    }

    return LIST_IS_OK_STATUS;
}

int ListClear(List* list)
{
    ListVerifyStatus_

    while (SIZE > 0)
        ListPopBack(list);

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

    if (IsListEmpty(list) == LIST_IS_EMPTY_STATUS)
    {
        PrintError("List is empty");
        return LIST_IS_EMPTY_STATUS;
    }

    size_t index = ListHead(list);
    fprintf(stdout, "List: \"");
    PrintListElemValue(stdout, DATA[index].value);
    fprintf(stdout, "\"");

    for (size_t i = 1; i < SIZE; i++)
    {
        index = ListNext(list, index);
        fprintf(stdout, ", \"");
        PrintListElemValue(stdout, DATA[index].value);
        fprintf(stdout, "\"");
    }

    fprintf(stdout, "\n");

    return LIST_IS_OK_STATUS;
}
