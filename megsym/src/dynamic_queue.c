#include "../include/dynamic_queue.h"
#include "../include/megsym.h"
#include <string.h>
#include <stdlib.h>
#define APPEND_QUEUE_SIZE 0x1000

int dynamic_queue_init(DynamicQueue *const queue)
{
    queue->head = 0;
    queue->tail = 0;
    if (!(queue->array = calloc(APPEND_QUEUE_SIZE, sizeof(char *))))
    {
        puts("calloc failed");
        return 0;
    }
    queue->length = APPEND_QUEUE_SIZE;
    return 1;
}

int dynamic_queue_enqueue(DynamicQueue *const queue, char *symbol)
{
    if (queue->tail == queue->length)
    {
        if (!queue->head)
        {
            char **new_array = calloc(queue->length + APPEND_QUEUE_SIZE, sizeof(char *));
            if (!new_array)
            {
                puts("calloc failed");
                return 0;
            }
            memcpy(new_array, queue->array, queue->length);
            free(queue->array);
            queue->array = new_array;
            queue->length += APPEND_QUEUE_SIZE;
        }
        else
        {
            char **new_array = calloc(queue->tail - queue->head, sizeof(char *));
            if (!new_array)
            {
                puts("calloc failed");
                return 0;
            }
            memcpy(new_array, queue->array + queue->head, queue->length - queue->head);
            free(queue->array);
            queue->array = new_array;
        }
    }

    queue->array[queue->tail] = symbol;
    ++queue->tail;
    return 1;
}

int dynamic_queue_dequeue(DynamicQueue *const queue, char **symbol)
{
    if (queue->head == queue->tail)
    {
        puts("queue is empty");
        return 0;
    }

    *symbol = queue->array[queue->head];
    ++queue->head;
    return 1;
}

int dynamic_queue_is_empty(DynamicQueue *const queue)
{
    return queue->head == queue->tail;
}