/*
 * Priority Queue Implementation
 *
 * Copyright (c) 2017 Brandon Bemister. All rights reserved.
 * https://github.com/
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

#ifndef CSTRUCTURES_HEAP_H
#define CSTRUCTURES_HEAP_H

/**
 * @file prio_queue.h
 * @brief A Priority Queue Implementation for c.
 *
 * @author Brandon Bemister
 */

#include "cstructures_err.h"
#include "cstructures_config.h"
#include <stddef.h>

#define PRIO_QUEUE_RESIZE_ENABLED CSTRUCTURES_GLOBAL_RESIZE_ENABLE

/** @brief A handle for the priority queue. */
struct prio_queue_handle;

/** 
 * \brief Initializes a new priority queue.
 * 
 * @param hnd The handle which will be initialized.
 * @param max_size The maximum size of the the priority queue.
 * @param comparator A pointer to the callback function which will compare the data.
 * 
 * @return CST_OK if successful.
 */
cst_err prio_queue_init(struct prio_queue_handle** hnd, size_t max_size,  int (comparator)(void* c1, void* c2));

/** 
 * @brief Frees an allocated priority queue.
 * 
 * @param hnd The priority queue handle which is to be freed.
 */
void prio_queue_free(struct prio_queue_handle* hnd);

/**
 * @brief Insert new data into the priority queue.
 * 
 * @param hnd The priority queue in which you would like to insert the data.
 * @param data A pointer to the data which is to be inserted.
 * 
 * @return CST_OK if successful.
 */
cst_err prio_queue_insert(struct prio_queue_handle* hnd, void* data);

/** 
 * @brief Remove the next item from the priority queue.
 * 
 * @param hnd The queue from which you would like to remove the data.
 * @param data The data which you would like to remove.
 * 
 * @return CST_OK if successful.
 */
cst_err prio_queue_remove(struct prio_queue_handle* hnd, void** data);

/**
 * @brief Get the current size of the priority queue.
 * 
 * @param hnd The queue to get the size of.
 * 
 * @return The size of the queue.
 */
int prio_queue_size(struct prio_queue_handle* hnd);

#if PRIO_QUEUE_RESIZE_ENABLED

/**
 * @brief Will attempt to resize the priority queue maximum.
 * 
 * @param hnd The queue which needs to be resized.
 * @param new_size The new size of the queue.
 * 
 * @return CST_OK if successful.
 */
cst_err prio_queue_resize(struct prio_queue_handle* hnd, size_t new_size);

#endif

#endif //CSTRUCTURES_HEAP_H
