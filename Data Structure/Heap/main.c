#include "MaxHeap.h"

#include <assert.h>
#include <stdio.h>

void MaxHeapTest(void)
{
    heap_t *heap = MaxHeap_Create();
    assert(MaxHeap_Size(heap) == 0);
    assert(MaxHeap_IsEmpty(heap) == true);

    MaxHeap_Push(heap, 1);
    MaxHeap_Push(heap, 2);
    MaxHeap_Push(heap, 4);
    MaxHeap_Push(heap, 3);
    MaxHeap_Push(heap, 9);
    MaxHeap_Push(heap, 0);
    assert(MaxHeap_Size(heap) == 6);
    assert(MaxHeap_IsEmpty(heap) == false);
    assert(MaxHeap_Top(heap) == 9);

    assert(MaxHeap_Pop(heap) == 9);
    assert(MaxHeap_Pop(heap) == 4);
    assert(MaxHeap_Pop(heap) == 3);
    assert(MaxHeap_Pop(heap) == 2);
    assert(MaxHeap_Pop(heap) == 1);
    assert(MaxHeap_Pop(heap) == 0);
    assert(MaxHeap_Size(heap) == 0);
    assert(MaxHeap_IsEmpty(heap) == true);

    MaxHeap_Destroy(heap);

    printf("Max Heap Test OK.\n");
}

int main(void)
{
    MaxHeapTest();

    return 0;
}
