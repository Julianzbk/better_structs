#include <stdio.h>
#include <stdlib.h>

struct Node
{
    void* data;
    struct Node* next;
};
typedef struct Node Node;

typedef struct 
{
    Node* head;
    size_t size;
} h_array;


h_array make_array()
{
    h_array arr = {.head = NULL, .size = 0};
    return arr;
}

#define T int

h_array make_array_from_array(int* data)
{
    h_array arr = {.head = NULL, .size = 0};
    return arr;
}

void push_array(h_array* arr, int data)
{
    Node* p;
    if (arr->head == NULL)
    {
        arr->head = malloc(sizeof(Node));
        p = arr->head;
    }
    else
    {
        p = arr->head;
        for (; p->next != NULL; p = p->next);
        p->next = malloc(sizeof(Node));
        p = p->next;
    }
    int* data_p = malloc(sizeof(data));
    *data_p = data;
    p->data = (void*) data_p;
    p->next = NULL;
    arr->size++;
}

void print_array(h_array arr)
{
    printf("[");
    for (Node* p = arr.head; p != NULL; p = p->next)
    {
        T* data_p = p->data;
        printf("%d ", *(data_p));
    }
    printf("]");
}

void destroy_array(h_array* arr)
{
    Node* next;
    for (Node* p = arr->head; p != NULL; p = next)
    {
        next = p->next;
        free(p->data);
        free(p);
    }
}

int main()
{
    h_array p = make_array();
    push_array(&p, 1);
    push_array(&p, -99);
    print_array(p);
    destroy_array(&p);
    return 0;
}