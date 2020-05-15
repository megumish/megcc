#ifndef __MEGSYM_DYNAMIC_QUEUE_HEADER__
#define __MEGSYM_DYNAMIC_QUEUE_HEADER__
#include <stdio.h>
#include "megsym.h"

typedef struct DynamicQueue
{
    // 前はcharじゃなくてSymbolだったがとりあえずエラ〜メッセージが出ないようにcharにしておく
    char **array;
    size_t head;
    size_t tail;
    size_t length;
} DynamicQueue;

int dynamic_queue_init(DynamicQueue *const queue);

int dynamic_queue_enqueue(DynamicQueue *const queue, char *symbol);

int dynamic_queue_dequeue(DynamicQueue *const queue, char **symbol);

int dynamic_queue_is_empty(DynamicQueue *const queue);

#endif