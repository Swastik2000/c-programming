#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    double value;               
    struct list *next, *prev;   
} List;

List *create(double value);

List *insert(List *list, double value, int pos);

List *delete(List *list, int pos);

int search(List *list, double value);

void print(List *list);

void example();

List *create(double value)
{
    List *new_list = (List *)malloc(sizeof(List));
    new_list->value = value;
    new_list->next = NULL;
    new_list->prev = NULL;
    return new_list;
}

List *insert(List *list, double value, int pos)
{
    if (list == NULL)
    {
        list = create(value);
        return list;
    }

    if (pos > 0)
    {
        List *cpy = list, *tmp = cpy;
        int flag = 1, index = 1, size = 0;

        while (tmp != NULL)
        {
            size++;
            tmp = tmp->next;
        }

        if (pos == 1)
        {
            List *new_node = create(value);
            new_node->next = cpy;
            cpy->prev = new_node;
            list = new_node;
            return list;
        }

        if (size + 2 > pos)
        {
            while (cpy->next != NULL && index < pos)
            {
                flag++;
                index++;
                cpy = cpy->next;
            }

            List *new_node = (List *)malloc(sizeof(List));
            new_node->value = value;

            if (flag == pos)
            {
                cpy->prev->next = new_node;
                new_node->next = cpy;
                new_node->prev = cpy->prev;
                cpy->prev = new_node;
            }

            if (flag < pos)
            {
                new_node->next = cpy->next;
                new_node->prev = cpy;
                cpy->next = new_node;
            }
        }
        return list;
    }
}

List *delete(List *list, int pos)
{
    if (list == NULL)
        return list;

    if (pos > 0)
    {
        List *cpy = list, *tmp = cpy;
        int flag = 1, index = 1, size = 0;

        while (tmp != NULL)
        {
            size++;
            tmp = tmp->next;
        }

        if (pos == 1)
        {
            if (size == 1)
                return NULL;
            cpy = cpy->next;
            cpy->prev = NULL;
            return cpy;
        }

        if (size + 2 > pos)
        {
            while (cpy->next != NULL && index < pos)
            {
                flag++;
                index++;
                cpy = cpy->next;
            }

            if (flag == pos)
            {
                if (cpy->next != NULL)
                {
                    cpy->prev->next = cpy->next;
                    cpy->next->prev = cpy->prev;
                }

                else
                    cpy->prev->next = NULL;
            }
        }
        return list;
    }
}

int search(List *list, double value)
{
    if (list == NULL)
        return 0;
    if (list->value == value)
        return 1;
    search(list->next, value);
}

void print(List *list)
{
    if (list != NULL)
    {
        printf("%f\t", list->value);
        print(list->next);
    }
}

void example()
{
    List *my_list = NULL;
    double node_value = 0;
    int searching;

    my_list = create(node_value);
    my_list = insert(my_list, 3, 1);
    my_list = insert(my_list, 5, 3);
    my_list = insert(my_list, 10, 3);
    my_list = insert(my_list, 20, 3);

    print(my_list);
    searching = search(my_list, 20);
    printf("\n%d\n", searching);

    my_list = delete (my_list, 1);
    my_list = delete (my_list, 1);
    my_list = delete (my_list, 1);
    my_list = delete (my_list, 1);

    print(my_list);
    searching = search(my_list, 20);
    printf("\n%d\n", searching);
}
