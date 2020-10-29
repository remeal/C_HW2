//
// Created by Dashik on 23.10.2020.
//
#include "../include/DZ2/without_fork.h"
#include "../include/DZ2/utils.h"

struct List* select_the_most(struct List *list){
    int i = 0;
    if (!list)
        return NULL;
    struct List *criterion_list = create_list(sizeof(struct Staffs));
    struct List *position_list = create_list(sizeof(char*));
    while (i < list->size) {
        struct Staffs *curr_staff = element_get(list, i);
        if (is_position_was(curr_staff, position_list) == 1) {
            int j = i + 1;
            unsigned char max = curr_staff->age;
            unsigned char min = curr_staff->age;
            struct List *index_max = create_list(sizeof(int));
            struct List *index_min = create_list(sizeof(int));
            int curr_index = i;
            add_to_index((void*)&curr_index, index_max);
            add_to_index((void*)&curr_index, index_min);
            if (j < list->size) {
                while (j < list->size) {
                    struct Staffs *check_staff = element_get(list, j);
                    if (strcmp(curr_staff->position, check_staff->position) == 0) {
                        max = compare_staff_max(max, check_staff->age, j, &index_max);
                        min = compare_staff_min(min, check_staff->age, j, &index_min);
                    }
                    ++j;
                }
            }
            if (max == min){
                create_crit_list(index_max, criterion_list, list);
            }
            else{
                create_crit_list(index_max, criterion_list, list);
                create_crit_list(index_min, criterion_list, list);
            }
            remote_index(index_max);
            remote_index(index_min);
        }
        ++i;
    }
    remote_list(position_list);
    sorted_list(criterion_list);
    return criterion_list;
};

