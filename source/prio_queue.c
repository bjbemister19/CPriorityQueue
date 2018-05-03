/*
 * Priority Queue Implementation
 *
 * Copyright (c) 2017 Brandon Bemister. All rights reserved.
 * https://github.com/bjbemister19/CPriorityQueue
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Brandon Bemister
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "../include/prio_queue.h"
#include "../include/cbt.h"

#define PRIO_QUEUE_DEBUG 0

#if PRIO_QUEUE_DEBUG

#include <stdio.h>

#define prio_printf(x, ...) printf(x, ##__VA_ARGS__)
#define prio_printfln(x, ...) do{ printf(x, ##__VA_ARGS__); printf("\n"); } while(0);

#else

#define prio_printf(x, ...) //printf(x, ##__VA_ARGS__)
#define prio_printfln(x, ...) //do{ printf(x, ##__VA_ARGS__); printf("\n"); } while(0);

#endif

#include "stdlib.h"

#define PRIO_ALLOC(x) malloc(x);
#define PRIO_FREE(x) free(x);

struct prio_queue_handle{
    struct cbt_handle* cbt_hnd;
    int (*comparator)(void* c1, void* c2);
};

static cst_err __prio_queue_bubble_up(struct prio_queue_handle* hnd, struct cbt_node* node);

static cst_err __prio_queue_trickle_down(struct prio_queue_handle* hnd, struct cbt_node* root);

cst_err prio_queue_init(struct prio_queue_handle ** hnd, size_t max_size, int (comparator)(void* c1, void* c2)){
    *hnd = PRIO_ALLOC(sizeof(struct prio_queue_handle));
    if(*hnd == NULL){
        prio_printfln("Alloc Failed");
        return CST_MEM_ERR;
    }

    cst_err init_e = cbt_init(&((*hnd)->cbt_hnd), max_size);
    if(init_e != CST_OK){
        PRIO_FREE(*hnd);
        *hnd = NULL;
        return CST_FAIL;
    }

    (*hnd)->comparator = comparator;

    return CST_OK;
}

void prio_queue_free(struct prio_queue_handle* hnd){
    // Safety check
    if(hnd == NULL){
        prio_printfln("Null Handle")
        return;
    }
    cbt_free(hnd->cbt_hnd);
    PRIO_FREE(hnd);
}

cst_err prio_queue_insert(struct prio_queue_handle* hnd, void* data){
    // Safety check
    if(hnd == NULL){
        prio_printfln("Null Handle")
        return CST_FAIL;
    }

    struct cbt_node* new = cbt_insert(hnd->cbt_hnd, data);
    if(!new){
        prio_printfln("Insert Failed");
        return CST_OVERFLOW;
    }
    if(__prio_queue_bubble_up(hnd, new) != CST_OK){
        prio_printfln("Bubble Up Fail");
        return CST_FAIL;
    }
    return CST_OK;
}

cst_err prio_queue_remove(struct prio_queue_handle* hnd, void** data){
    // Safety check
    if(hnd == NULL){
        prio_printfln("Null Handle")
        return CST_FAIL;
    }

    struct cbt_node* root = cbt_get_root(hnd->cbt_hnd);
    if(root == NULL){
        // Nothing to remove
        return CST_EMPTY;
    }

    *data = cbt_get_data(root);
    void* tmp = NULL;
    cbt_remove(hnd->cbt_hnd, &tmp);
    if(tmp == NULL){
        return CST_FAIL;
    }

    cbt_set_data(root, tmp);

    if(__prio_queue_trickle_down(hnd, root) != CST_OK){
        prio_printfln("Trickle Down Fail");
        return CST_FAIL;
    }

    return CST_OK;
}

int prio_queue_size(struct prio_queue_handle* hnd){
    // Safety check
    if(hnd == NULL){
        prio_printfln("Null Handle")
        return CST_FAIL;
    }

    return cbt_size(hnd->cbt_hnd);
}

#if PRIO_QUEUE_RESIZE_ENABLED

cst_err prio_queue_resize(struct prio_queue_handle* hnd, size_t new_size){
    // Safety check
    if(hnd == NULL){
        prio_printfln("Null Handle")
        return CST_FAIL;
    }

    return cbt_resize(hnd->cbt_hnd, new_size);
}

#endif

static cst_err __prio_queue_bubble_up(struct prio_queue_handle* hnd, struct cbt_node* node){
    struct cbt_node* child = node;
    struct cbt_node* parent = cbt_get_parent(hnd->cbt_hnd, child);
    while(parent != NULL){
        int cmp = hnd->comparator(cbt_get_data(parent), cbt_get_data(child));
        if(cmp == 0){
            // Nodes equal and done break loop.
            break;
        } else if (cmp < 0){
            // Don't swap and done, break loop.
            break;
        } else if (cmp > 0) {
            // Swap
            cbt_swap(parent, child); // Note the parent node now holds the child nodes data and vice versa.
            child = parent;
            parent = cbt_get_parent(hnd->cbt_hnd, child);
        }
    }
    return CST_OK;
}

static cst_err __prio_queue_trickle_down(struct prio_queue_handle* hnd, struct cbt_node* root){
    struct cbt_node* parent = root;
    struct cbt_node* child_left = cbt_get_child_left(hnd->cbt_hnd, parent);
    struct cbt_node* child_right = cbt_get_child_right(hnd->cbt_hnd, parent);

    while(!((child_left == NULL) && (child_right == NULL))){
        if((child_left != NULL) && (child_right != NULL)){
            int cmp = hnd->comparator(cbt_get_data(child_left), cbt_get_data(child_right));
            if (cmp > 0) {
                // check right
                int rcmp = hnd->comparator(cbt_get_data(parent), cbt_get_data(child_right));
                if (rcmp > 0) {
                    // If parent larger swap and loop
                    cbt_swap(parent, child_right);
                    parent = child_right;
                    child_left = cbt_get_child_left(hnd->cbt_hnd, parent);
                    child_right = cbt_get_child_right(hnd->cbt_hnd, parent);
                    continue;
                } else {
                    // If parent equal or smaller stop and break
                    break;
                }
            } else {
                // check left
                int lcmp = hnd->comparator(cbt_get_data(parent), cbt_get_data(child_left));
                if (lcmp > 0) {
                    // If parent larger swap and loop
                    cbt_swap(parent, child_left);
                    parent = child_left;
                    child_left = cbt_get_child_left(hnd->cbt_hnd, parent);
                    child_right = cbt_get_child_right(hnd->cbt_hnd, parent);
                    continue;
                } else {
                    // If parent equal or smaller stop and break
                    break;
                }
            }
        } else {
            if(child_left != NULL){
                int cmp = hnd->comparator(cbt_get_data(parent), cbt_get_data(child_left));
                if (cmp > 0) {
                    // If parent larger swap and loop
                    cbt_swap(parent, child_left);
                    parent = child_left;
                    child_left = cbt_get_child_left(hnd->cbt_hnd, parent);
                    child_right = cbt_get_child_right(hnd->cbt_hnd, parent);
                    continue;
                } else {
                    // If parent equal or smaller stop and break
                    break;
                }
            }
        }
    }
    return CST_OK;
}