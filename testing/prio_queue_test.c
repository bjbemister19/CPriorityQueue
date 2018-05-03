
#include "prio_queue_test.h"
#include "../include/prio_queue.h"
#include "stdio.h"

int compare(void* c1, void* c2){
    int i1 = *(int*)c1;
    int i2 = *(int*)c2;
    if(i1 > i2){
        return 1;
    } else if(i1 < i2){
        return -1;
    } else {
        return 0;
    }
}

void prio_queue_test(void){
    printf("\nStarting prio_queue_test\n\n");
    struct prio_queue_handle *hnd = NULL;
    cst_err e =  prio_queue_init(&hnd, 4, &compare);
    if(e != CST_OK){
        printf("Init Fail\n");
        goto exit;
    }

    int dat[] = {23,267,5,7,1,1000,10,8};

    printf("Queue Size Initial: %d\n", prio_queue_size(hnd));

    prio_queue_insert(hnd, &dat[0]);
    prio_queue_insert(hnd, &dat[1]);
    prio_queue_insert(hnd, &dat[2]);
    prio_queue_insert(hnd, &dat[3]);

    cst_err insert_err = prio_queue_insert(hnd, &dat[4]);
    if(insert_err == CST_OK){
        printf("Something went wrong, should have failed\n");
        goto exit;
    }

    cst_err insert_err2 = prio_queue_resize(hnd, 20);
    if(insert_err2 != CST_OK){
        printf("Resize Failed\n");
        goto exit;
    }
    prio_queue_insert(hnd, &dat[4]);
    prio_queue_insert(hnd, &dat[5]);
    prio_queue_insert(hnd, &dat[6]);

    printf("Queue Size Inserted: %d\n", prio_queue_size(hnd));

    void* out[7];
    prio_queue_remove(hnd, &out[0]);
    prio_queue_remove(hnd, &out[1]);
    prio_queue_remove(hnd, &out[2]);
    prio_queue_remove(hnd, &out[3]);
    prio_queue_remove(hnd, &out[4]);
    prio_queue_remove(hnd, &out[5]);
    prio_queue_remove(hnd, &out[6]);

    printf("Printing values:\n");

    printf("[ %d , %d , %d , %d , %d , %d , %d ]\n", *(int*)out[0], *(int*)out[1], *(int*)out[2], *(int*)out[3], *(int*)out[4], *(int*)out[5], *(int*)out[6]);

    printf("Queue size final: %d\n", prio_queue_size(hnd));

exit:
    if(hnd) {
        prio_queue_free(hnd);
    }
}