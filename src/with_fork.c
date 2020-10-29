//
// Created by Dashik on 27.10.2020.
//
#include "../include/DZ2/with_fork.h"
#include "DZ2/utils.h"

int get_process_number (const int size) {
    return size;
};

struct List *shared_memory(int size){
    struct List *addr = mmap(NULL, sizeof(struct List), PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    addr->data = mmap(NULL, size * sizeof(struct Staffs*), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    for (int i = 0; i < size; ++i)
        addr->data[i] = mmap(NULL, sizeof(struct Staffs), PROT_READ | PROT_WRITE,
                          MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == NULL)
        return NULL;
    return addr;
}

int create_processes (int processes_number, int* processes_name){
    int result = -1;
    for (int i = 0; i < processes_number; ++i){
        int pid = fork();
        if (pid == 0)
            return ++result;
        ++result;
        if (pid != -1)
            processes_name[i] = pid;
    }
    return -2;
}

struct List *select_the_most_fork(struct List *list, char *position_index){
    int i = 0;
    struct List *criterion_list = create_list(sizeof(struct Staffs));
    int bool = 0;
    while (i < list->size && !bool) {
        struct Staffs *curr_staff = element_get(list, i);
        if (strcmp(curr_staff->position, position_index) == 0) {
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
            bool = 1;
        }
        ++i;
    }
    return criterion_list;
};


struct List *split_process(struct List *list){
    struct List *position_list = create_list(sizeof(char*));
    int i = 0;
    int pos_count = 0;
    while (i < list->size){
        struct Staffs *curr_staff = element_get(list, i);
        pos_count += is_position_was(curr_staff, position_list);
        ++i;
    }
    struct List *share_list = shared_memory(list->size);
    int processes_number = get_process_number(pos_count);
    int *processes_names = (int*)malloc(processes_number * sizeof(int));
    if (processes_names == NULL)
        return NULL;
    int num_pid = create_processes(processes_number, processes_names);
    if (num_pid != -2){
        char *position_index = position_list->data[num_pid];
        struct List *crit_list = select_the_most_fork(list, position_index);
        add_to_share_list(crit_list, share_list);
        exit(0);
    }
    remote_list(position_list);
    for ( int num = 0; num != processes_number; ++num ) {
       while ( waitpid(processes_names[num], NULL, 0) > 0 ) {
        } }
    free(processes_names);
    sorted_list(share_list);
    return share_list;
};
