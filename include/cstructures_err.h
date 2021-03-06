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

#ifndef CSTRUCTURES_CSTRUCTURES_ERR_H
#define CSTRUCTURES_CSTRUCTURES_ERR_H

/**
 * \file cstructures_err.h
 * \brief Error handling for cbt.h
 *
 * @author Brandon Bemister
 */

typedef enum {
    CST_EMPTY,
    CST_PARAM_ERR,
    CST_OVERFLOW,
    CST_MEM_ERR,
    CST_FAIL,
    CST_OK = 0
}cst_err;

#endif //CSTRUCTURES_CSTRUCTURES_ERR_H
