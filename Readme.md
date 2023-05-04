# ListStructure

Библиотека структуры данных двусвязного списка.

## Реализация

Основная структура ``List`` задана в файле ``./Include/List.h``:

```C++
    struct ListElem
    {
        Value_t value;
        size_t  next;
        size_t  prev;
    };

    struct List
    {
        ListElem* data;

        size_t  head_index;
        size_t  tail_index;

        size_t  size;
        size_t  capacity;
        size_t  free;

        bool    is_linear;

        int     status;
    };
```

Тип данных, содержащихся в списке, задан в файле ``./Config.h``:
```C++
    typedef const char* Value_t;
```

Принципиальной в реализации является модель ``cache-friendly``, благодаря которой добавление, добавление и удаление элемента происходит за O(1), а поиск за O(n).

## Функционал

Функции описанной структуры также объявлены в файле ``./Include/List.h``:

```C++
    int ListCtor (List* list);                                              // <-- конструктор
    int ListDtor (List* list);                                              // <-- деструктор

    int ListVerify     (List* list);                                        // <-- быстрый верификатор
    int ListFullVerify (List* list);                                        // <-- полный верификатор
    int ListTextDump   (List* list, FILE* file = stdout);                   // <-- текстовая распечатка структуры списка
    int ListGraphDump  (List* list, const char* head_text);                 // <-- графическая визуализация структуры списка

    size_t ListFindElemIndexByLogIndex (List* list, size_t log_index );     // <-- поиск физического индекса элемента по его логическому индексу

    size_t ListNext (List* list, size_t phys_index);                        // <-- физический индекс следующего элемента
    size_t ListPrev (List* list, size_t phys_index);                        // <-- физический индекс предыдущего элемента

    size_t  ListHead (List* list);                                          // <-- физический индекс "головы" списка
    size_t  ListTail (List* list);                                          // <-- физический индекс "хвоста" списка

    size_t  ListInsertAfter  (List* list, size_t phys_index, Value_t value);    // <-- вставка элемента после заданного
    size_t  ListInsertBefore (List* list, size_t phys_index, Value_t value);    // <-- вставка элемента перед заданным
    Value_t ListErase        (List* list, size_t phys_index);                   // <-- удаление элемента по физ. индексу

    Value_t ListPopBack   (List* list);                                     // <-- удаление элемента из конца списка
    int     ListPushBack  (List* list, Value_t value);                      // <-- добавление элемента в конец списка
    Value_t ListPopFront  (List* list);                                     // <-- удаление элемента из начала списка
    int     ListPushFront (List* list, Value_t value);                      // <-- добавление элемента в начало списка

    int ListLinearize (List* list);                                         // <-- линеаризация списка

    int ListClear  (List* list);                                            // <-- очищстка списка (удаление всех элементов)
    int ListResize (List* list, int resize_mode);                           // <-- изменение размера списка (увеличение/уменьшение)

    int ListPrint (List* list);                                             // <-- печать списка в логическом порядке следования элементов

    size_t FindInList(const List* list, Value_t value);                     // <-- поиск физического индекса элемента списка по значению
```

## Визуализация структуры двусвязного списка

Функция ``ListGraphDump`` добавляет в html-файл ``./ListDump/FullDump.html`` картинку новой распечатки списка. По завершению программы, все вызовы функции распечатки отображены в этом файле и могут быть просмотрены, например, в браузере. Тестовая программа в папке ``./Test`` аатоматически открывает файл с распечатками, если они производились.

## Сборка и запуск

Клонируйте репозиторий проекта, для компиляции запустите ``make`` из его корневой папки, создатся исполняемый файл ``./test``. Настройки (выбор режима распечатки, отладки и т.д.) можно задать в файле ``./Config.h``. Для запуска тестовой программы (файла ``./Test/test.cpp``) запустите ``make run_test`` в корневой папке с уже скомпилированным проектом.
