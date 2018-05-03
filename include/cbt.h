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

#ifndef CSTRUCTURES_CBT_H
#define CSTRUCTURES_CBT_H

/**
 * @file cbt.h
 * @brief A Complete Binary Tree Implementation for c.
 *
 * @author Brandon Bemister
 */

#include <stddef.h>
#include "cstructures_err.h"
#include "cstructures_config.h"

#define CBT_RESIZE_ENABLED CSTRUCTURES_GLOBAL_RESIZE_ENABLE

/** @brief A handle for the complete binary tree. */
struct cbt_handle;

/** @brief A complete binary tree node. */
struct cbt_node;

/**
 * @brief Initializes a new complete binary tree handle to a given size.
 *  
 * @param hnd A pointer to a newly allocated tree handle will be placed here if successful.
 * @param max_size The maximum number of items you want your tree to hold.
 * 
 * @return CST_OK if successful.
 */
cst_err cbt_init(struct cbt_handle **hnd, size_t max_size);

/**
 * @brief Frees a complete binary tree given the handle.
 * 
 * @param hnd The cbt handle.
 * 
 * @return CST_OK if successful.
 */
cst_err cbt_free(struct cbt_handle *hnd);

/**
 * @brief Inserts some data into the next position of the complete binary tree.
 * 
 * @param hnd The cbt handle.
 * @param data A pointer to the data associated with this node.
 * 
 * @return CST_OK if successful.
 */
struct cbt_node* cbt_insert(struct cbt_handle *hnd, void* data);

/**
 * @brief Removes the last node from the tree.
 * 
 * @param hnd The cbt handle.
 * @param data The data pointed to by the removed node.
 * 
 * @return CST_OK if successful.
 */
cst_err cbt_remove(struct cbt_handle *hnd, void** data);

/**
 * @brief Get the number of items currently in the tree.
 * 
 * @param hnd The tree in which to get the size.
 * 
 * @return The number of items in the tree.
 */
int cbt_size(struct cbt_handle *hnd);

/**
 * @brief Swaps two nodes in the tree.
 * 
 * @param n1 The first node.
 * @param n2 The second node
 * 
 * @return CST_OK if successful.
 */
cst_err cbt_swap(struct cbt_node* n1, struct cbt_node* n2);

/** 
 * @brief Gets the root node of the complete binary tree.
 * 
 * @param hnd The cbt handle.
 * 
 * @return The root node of the tree, NULL if an error occurred.
 */
struct cbt_node* cbt_get_root(struct cbt_handle *hnd);

/**
 * @brief Gets the left child of a given node.
 * 
 * @param hnd The cbt handle.
 * @param node The parent node to the child you want to get.
 * 
 * @return The left child node, NULL if an error occurred.
 */
struct cbt_node* cbt_get_child_left(struct cbt_handle *hnd, struct cbt_node* node);

/** 
 * @brief Gets the right child of a given node.
 * 
 * @param hnd The cbt handle.
 * @param node The parent node to the child you want to get.
 * 
 * @return The right child node, NULL if an error occurred.
 */
struct cbt_node* cbt_get_child_right(struct cbt_handle *hnd, struct cbt_node* node);

/**
 * @brief Gets the parent node of a given child.
 * 
 * @param hnd The cbt handle.
 * @param node The child node of the parent you want to get.
 * 
 * @return The parent node, NULL if an error occurred.
 */
struct cbt_node* cbt_get_parent(struct cbt_handle *hnd, struct cbt_node* node);

/** 
 * @brief Gets the data from a given node.
 * 
 * @param node The node ot get the data from.
 * 
 * @return A pointer to the data.
 */
void* cbt_get_data(struct cbt_node* node);

/** 
 * @brief Sets new data for a given cbt node.
 * 
 * @param node The node to set the data for.
 * @param data A pointer to the new data to be set.
 * 
 * @return CST_OK if the data was properly set.
 */
cst_err cbt_set_data(struct cbt_node* node, void* data);

#if CBT_RESIZE_ENABLED

/**
 * @brief Will attempt to resize the Complete Binary Trees Maximum Size
 * 
 * @param hnd The tree which you would like to resize;
 * @param new_size The new size of the tree.
 * 
 * @return CST_OK if tree was correctly resized.
 */
cst_err cbt_resize(struct cbt_handle *hnd, size_t new_size);

#endif //CBT_RESIZE_ENABLED

#endif //CSTRUCTURES_CBT_H
