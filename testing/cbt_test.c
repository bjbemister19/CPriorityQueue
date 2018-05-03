
#include "cbt_test.h"
#include "../include/cbt.h"

#include <stdio.h>

void test_cbt(){

    // Init tree
    struct cbt_handle *hnd = NULL;
    if(cbt_init(&hnd, 7)){
        printf("Something Bad happened");
    }
    printf("Tree Initialized\n");

    // Insert some data
    int dat[] = {1,2,3,4,5,6,7,8};

    cbt_insert(hnd, &dat[0]);
    cbt_insert(hnd, &dat[1]);
    cbt_insert(hnd, &dat[2]);
    cbt_insert(hnd, &dat[3]);
    cbt_insert(hnd, &dat[4]);
    cbt_insert(hnd, &dat[5]);
    cbt_insert(hnd, &dat[6]);

    printf("Tree Size: %d\n", cbt_size(hnd));

    // Test root
    struct cbt_node* root = cbt_get_root(hnd);

    struct cbt_node* root_parent = cbt_get_parent(hnd, root);
    if(root_parent == NULL){
        printf("All good, root shouldnt have parent\n");
    }

    printf("Root: %d\n", *(int*)cbt_get_data(root));

    // Test Level 2 Child/Parent functions
    struct cbt_node* lvl2_l = cbt_get_child_left(hnd, root);
    struct cbt_node* lvl2_r = cbt_get_child_right(hnd, root);

    printf("lvl2_l: %d\n", *(int*)cbt_get_data(lvl2_l));
    printf("lvl2_r: %d\n", *(int*)cbt_get_data(lvl2_r));

    struct cbt_node* lvl2_l_p = cbt_get_parent(hnd, lvl2_l);
    struct cbt_node* lvl2_r_p = cbt_get_parent(hnd, lvl2_r);

    printf("lvl2_l parent (should be root): %d\n", *(int*)cbt_get_data(lvl2_l_p));
    printf("lvl2_r parent (should be root): %d\n", *(int*)cbt_get_data(lvl2_r_p));

    // Test Level 3 Child/Parent functions
    struct cbt_node* lvl3_ll = cbt_get_child_left(hnd, lvl2_l);
    struct cbt_node* lvl3_lr = cbt_get_child_right(hnd, lvl2_l);

    printf("lvl3_ll: %d\n", *(int*)cbt_get_data(lvl3_ll));
    printf("lvl3_lr: %d\n", *(int*)cbt_get_data(lvl3_lr));

    struct cbt_node* lvl3_ll_p = cbt_get_parent(hnd, lvl3_ll);
    struct cbt_node* lvl3_lr_p = cbt_get_parent(hnd, lvl3_lr);

    printf("lvl3_ll_p parent (should be 2): %d\n", *(int*)cbt_get_data(lvl3_ll_p));
    printf("lvl3_lr_p parent (should be 2): %d\n", *(int*)cbt_get_data(lvl3_lr_p));

    struct cbt_node* lvl3_rl = cbt_get_child_left(hnd, lvl2_r);
    struct cbt_node* lvl3_rr = cbt_get_child_right(hnd, lvl2_r);

    printf("lvl3_rl: %d\n", *(int*)cbt_get_data(lvl3_rl));
    printf("lvl3_rr: %d\n", *(int*)cbt_get_data(lvl3_rr));

    struct cbt_node* lvl3_rl_p = cbt_get_parent(hnd, lvl3_rl);
    struct cbt_node* lvl3_rr_p = cbt_get_parent(hnd, lvl3_rr);

    printf("lvl3_rl_p parent (should be 3): %d\n", *(int*)cbt_get_data(lvl3_rl_p));
    printf("lvl3_rr_p parent (should be 3): %d\n", *(int*)cbt_get_data(lvl3_rr_p));

    // Test set data
    cst_err set_e = cbt_set_data(lvl3_rr, &dat[7]);
    if(set_e != CST_OK){
        printf("fail");
        return;
    }

    struct cbt_node* set_child = cbt_get_child_right(hnd, lvl3_rr_p);
    if(set_child == NULL){
        printf("fail");
        return;
    }
    printf("lvl3_rr: %d\n", *(int*)cbt_get_data(set_child));

    // Test remove
    int* ptr = NULL;
    cst_err e = cbt_remove(hnd, (void**)&ptr);
    if(ptr == NULL){
        printf("fail");
        return;
    }
    if(e != CST_OK){
        printf("fail");
        return;
    }
    printf("removed %d\n", *ptr);

    struct cbt_node* rm_tst = cbt_get_child_right(hnd, lvl2_r);
    if(rm_tst != NULL){
        printf("fail");
        return;
    }

    cbt_remove(hnd, (void**)&ptr);
    cbt_remove(hnd, (void**)&ptr);
    cbt_remove(hnd, (void**)&ptr);
    cbt_remove(hnd, (void**)&ptr);
    cbt_remove(hnd, (void**)&ptr);
    cbt_remove(hnd, (void**)&ptr);
    cst_err e2 = cbt_remove(hnd, (void**)&ptr);
    if(e2 != CST_FAIL){
        printf("fail");
        return;
    }

    cbt_free(hnd);
}