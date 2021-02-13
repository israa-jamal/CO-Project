#include <stdio.h>

typedef struct
{
    int priority;
    char data;
} Request;

typedef struct
{
    Request requests[20];
    int top;
} List;

int
request_cmp(Request a, Request b)
{
    if (a.priority < b.priority)
        return -1;

    if (a.priority > b.priority)
        return 1;

    // if same priority we compare based on data
    if (a.data < b.data)
        return -1;

    if (a.data == b.data)
        return 0;

    if (a.data > b.data)
        return 1;
}

void
list_insert(List* l, Request r)
{
    if (l->top == 20)
        return;

    l->requests[l->top] = r;
    ++l->top;
}

void
list_delete(List* l, int priority)
{
    int stride = 0;
    int first_found = -1;
    for (int i = 0; i < l->top; ++i)
    {
        if (l->requests[i].priority == priority)
        {
            if (first_found == -1)
                first_found = i;
            stride++;
        }
    }

    // there is nothing to remove
    if (first_found == -1)
        return;

    for (int i = first_found + stride; i < l->top; ++i)
    {
        l->requests[i - stride] = l->requests[i];
    }

    l->top -= stride;
}

void
list_clear(List* l)
{
    l->top = 0;
}

int
list_find(List* l, Request r, int begin, int end)
{
    if (begin == end)
        return -1; // nothing found

    int mid = begin + (end - begin) / 2;

    int cmp = request_cmp(r, l->requests[mid]);
    if (cmp == 0)
    {
        // request found
        return mid;
    }
    else if (cmp == -1)
    {
        // search on the left side
        return list_find(l, r, begin, mid);
    }
    else
    {
        // search on the right side
        return list_find(l, r, mid + 1, end);
    }
}

void
list_process(List* l, int priority)
{
    for (int i = 0; i < l->top; ++i)
    {
        if (l->requests[i].priority == priority)
        {
            printf("%c ", l->requests[i].data);
        }
    }

    printf("\n");
}

// sorting related functions

// returns the index of the pivot
void
list_swap_requests(List* l, int i, int j)
{
    Request tmp = l->requests[i];
    l->requests[i] = l->requests[j];
    l->requests[j] = tmp;
}

int
list_segment_partition(List* l, int begin, int end)
{
    Request pivot_request = l->requests[begin];

    for (int i = begin + 1; i < end; ++i)
    {
        if (request_cmp(l->requests[i], pivot_request) == -1)
            continue;

        for (int j = i+1; j < end; ++j)
        {
            if (request_cmp(l->requests[j], pivot_request) == -1)
            {
                list_swap_requests(l, i, j);
                break;
            }
        }
    }

    // put the pivot in the right position
    int pivot = begin;
    for (int i = begin + 1; i < end; ++i)
    {
        if (request_cmp(l->requests[i], pivot_request) != -1)
            break;

        list_swap_requests(l, pivot, i);
        pivot = i;
    }

    return pivot;
}

void
list_quick_sort(List* l, int begin, int end)
{
    if (end - begin < 2)
        return;

    int pivot = list_segment_partition(l, begin, end);
    list_quick_sort(l, begin, pivot);
    list_quick_sort(l, pivot + 1, end);
}

int main()
{
    List lists[4] = {0};

    Request r;

    r.data = 'c';
    r.priority = 1;
    list_insert(&lists[0], r);

    r.data = 'i';
    r.priority = 2;
    list_insert(&lists[0], r);

    r.data = 'j';
    r.priority = 3;
    list_insert(&lists[0], r);

    r.data = 'g';
    r.priority = 2;
    list_insert(&lists[0], r);

    r.data = 'p';
    r.priority = 4;
    list_insert(&lists[0], r);

    r.data = 'f';
    r.priority = 2;
    list_insert(&lists[0], r);

    r.data = 'z';
    r.priority = 4;
    list_insert(&lists[0], r);


    r.data = 'a';
    r.priority = 1;
    list_insert(&lists[0], r);


    r.data = 'u';
    r.priority = 4;
    list_insert(&lists[0], r);


    list_quick_sort(&lists[0], 0, lists[0].top);
    //list_process(&lists[0], 2);
    for(int i = 0; i < lists[0].top; ++i)
        printf("%d %c\n", lists[0].requests[i].priority, lists[0].requests[i].data);
 /*   r.data = 'i';
    list_sort(&lists[0]);
    int index = list_find(&lists[0], r, 0, lists[0].top);*/

    // list_delete(&lists[0], 2);

    return 0;
}
