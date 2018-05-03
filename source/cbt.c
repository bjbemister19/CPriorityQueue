/*
 * Complete Binary Tree Implementation
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

#include "../include/cbt.h"
#include <stdlib.h>

#if CBT_RESIZE_ENABLED
#include "string.h"
#endif //CBT_RESIZE_ENABLED

#define CBT_DEBUG 0

#if CBT_DEBUG

#include <stdio.h>

#define cbt_printf(x, ...) printf(x, ##__VA_ARGS__)
#define cbt_printfln(x, ...) do{ printf(x, ##__VA_ARGS__); printf("\n"); } while(0);

#else

#define cbt_printf(x, ...) //printf(x, ##__VA_ARGS__)
#define cbt_printfln(x, ...) //do{ printf(x, ##__VA_ARGS__); printf("\n"); } while(0);

#endif

#define CBT_ALLOC(x) malloc(x);
#define CBT_FREE(x) free(x);

struct cbt_node{
    void* data;
    int index;
};

struct cbt_handle{
    struct cbt_node* tree_data;
    size_t max_data;
    int end;
};

cst_err cbt_init(struct cbt_handle **hnd, size_t max_size){
    cbt_printfln("Initializing %d", (int)max_size);
    // Alloc handle and data
    *hnd = CBT_ALLOC(sizeof(struct cbt_handle))
    (*hnd)->tree_data = CBT_ALLOC(sizeof(struct cbt_node) * max_size);
    (*hnd)->max_data = max_size;
    // Do memory checks
    if(*hnd == NULL){
        cbt_printfln("Alloc Error");
        return CST_MEM_ERR;
    }
    if((*hnd)->tree_data == NULL){
        CBT_FREE(*hnd);
        cbt_printfln("Alloc Error");
        return CST_MEM_ERR;
    }

    (*hnd)->end = 0;

    return CST_OK;
}

cst_err cbt_free(struct cbt_handle *hnd){
    // Safety check
    if(!hnd){
        cbt_printfln("Null Handle");
        return CST_FAIL;
    }

    CBT_FREE(hnd->tree_data)
    CBT_FREE(hnd);
}

struct cbt_node* cbt_insert(struct cbt_handle *hnd, void* data){
    // Safety check
    if(!hnd){
        cbt_printfln("Null Handle");
        return NULL;
    }

    // Check size
    if(hnd->end == hnd->max_data){
        cbt_printfln("No Room");
        return NULL;
    }

    // Insert data
    (hnd->tree_data)[hnd->end].data = data;
    (hnd->tree_data)[hnd->end].index = hnd->end;
    hnd->end++;

    return &((hnd->tree_data)[hnd->end - 1]);
}

cst_err cbt_remove(struct cbt_handle *hnd, void** data){
    // Safety check
    if(!hnd){
        cbt_printfln("Null Handle");
        return CST_FAIL;
    }

    if(hnd->end == 0){
        cbt_printfln("Nothing to remove");
        return CST_FAIL;
    }
    hnd->end--;
    *data = hnd->tree_data[hnd->end].data;
    hnd->tree_data[hnd->end].data = NULL;
    return CST_OK;
}

int cbt_size(struct cbt_handle *hnd){
    // Safety check
    if(!hnd){
        cbt_printfln("Null Handle");
        return CST_FAIL;
    }

    return hnd->end;
}

cst_err cbt_swap(struct cbt_node* n1, struct cbt_node* n2){
    void* tmp = n1->data;
    n1->data = n2->data;
    n2->data = tmp;
    return CST_OK;
}

struct cbt_node* cbt_get_root(struct cbt_handle *hnd){
    // Safety check
    if(!hnd){
        cbt_printfln("Null Handle");
        return NULL;
    }

    if(cbt_size(hnd) == 0){
        cbt_printfln("Empty");
        return NULL;
    }

    return &hnd->tree_data[0];
}

struct cbt_node* cbt_get_child_left(struct cbt_handle *hnd, struct cbt_node* node){
    // Safety check
    if(!hnd || !node){
        cbt_printfln("Null Handle");
        return NULL;
    }

    // Calculate the location of the child in the array
    int index = (2 * node->index) + 1;
    if(index >= hnd->end){
        cbt_printfln("Too Small");
        return NULL;
    }

    return &hnd->tree_data[index];
}

struct cbt_node* cbt_get_child_right(struct cbt_handle *hnd, struct cbt_node* node){
    // Safety check
    if(!hnd || !node){
        cbt_printfln("Null Handle");
        return NULL;
    }

    // Calculate the location of the child in the array
    int index = (2 * node->index) + 2;
    if(index >= hnd->end){
        cbt_printfln("Too Small");
        return NULL;
    }

    return &hnd->tree_data[index];
}

struct cbt_node* cbt_get_parent(struct cbt_handle *hnd, struct cbt_node* node){
    // Safety check
    if(!hnd || !node){
        cbt_printfln("Null Handle");
        return NULL;
    }

    // Check if node is root
    if(node->index == 0){
        cbt_printfln("Is Root");
        return NULL;
    }

    // Calculate the location of the parent in the array
    int index = (node->index - 1) / 2;

    return &hnd->tree_data[index];
}

void* cbt_get_data(struct cbt_node* node){
    // Safety check
    if(!node){
        cbt_printfln("Null Handle");
        return NULL;
    }

    return node->data;
}

cst_err cbt_set_data(struct cbt_node* node, void* data){
    // Safety check
    if(!node){
        cbt_printfln("Null Handle");
        return CST_PARAM_ERR;
    }
    node->data = data;
    return CST_OK;
}

#if CBT_RESIZE_ENABLED

cst_err cbt_resize(struct cbt_handle *hnd, size_t new_size){
    // Safety check
    if(!hnd){
        cbt_printfln("Null Handle");
        return CST_FAIL;
    }

    if(new_size > hnd->max_data){
        struct cbt_node *tmp = CBT_ALLOC(sizeof(struct cbt_node) * new_size);
        if(tmp == NULL){
            cbt_printfln("Failed to Alloc");
            return CST_MEM_ERR;
        }

        memcpy(tmp, hnd->tree_data, (sizeof(struct cbt_node) * hnd->max_data));

        CBT_FREE(hnd->tree_data);

        hnd->max_data = new_size;
        hnd->tree_data = tmp;
    } else {
        if(new_size <= cbt_size(hnd)){
            cbt_printfln("Contains too many items to shrink");
            return CST_FAIL;
        }

        struct cbt_node *tmp = CBT_ALLOC(sizeof(struct cbt_node) * new_size);
        if(tmp == NULL){
            cbt_printfln("Failed to Alloc");
            return CST_MEM_ERR;
        }

        memcpy(tmp, hnd->tree_data, (sizeof(struct cbt_node) * hnd->max_data));

        CBT_FREE(hnd->tree_data);

        hnd->max_data = new_size;
        hnd->tree_data = tmp;
    }
    return CST_OK;
}

#endif //CBT_RESIZE_ENABLED