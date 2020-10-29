//
// Created by Dashik on 29.10.2020.
//

#include "DZ2/utils.h"

struct List *create_list(int size_of_data) {
    struct List *list = NULL;
    list = (struct List*)malloc(sizeof(struct List));
    if (list == NULL)
        return NULL;
    list->capacity = CAPACITY_OF_LIST;
    list->size = 0;
    list->element_size = size_of_data;
    list->data = (void **)malloc(CAPACITY_OF_LIST*sizeof(void*));
    if (!list->data)
        return NULL;
    return list;
};

struct List *create_database(FILE *file_inp){
    char string_helper_ptr[MAX_STRING_SIZE] = "";
    struct List *list = create_list(sizeof(struct Staffs));
    while (!feof(file_inp)){
        struct Staffs *new_staff = malloc(sizeof(struct Staffs));
        if (!new_staff)
            return NULL;
        new_staff->name = input_info_ptr(file_inp, string_helper_ptr);
        new_staff->surname = input_info_ptr(file_inp, string_helper_ptr);
        new_staff->gender = input_info_value(file_inp, string_helper_ptr);
        new_staff->age = input_info_value(file_inp, string_helper_ptr);
        new_staff->salary = input_info_int(file_inp, string_helper_ptr);
        new_staff->position = input_info_ptr(file_inp, string_helper_ptr);
        new_staff->experience = input_info_value(file_inp, string_helper_ptr);
        list = add_to_list(new_staff, list);
    }
    return list;
};

void remote_database(struct List *list){
    for (int i=0; i < list->size; ++i){
        struct Staffs *staffs = element_get(list, i);
        free(staffs->name);
        free(staffs->surname);
        free(staffs->position);
        free(staffs);
        staffs = NULL;
    }
    free(list->data);
    free(list);
};

void remote_index(struct List *list){
    for (int i = 0; i < list->size; ++i)
        free(list->data[i]);
    list->size = 0;
    free(list->data);
    free(list);
};

void remote_list(struct List *list){
    free(list->data);
    free(list);
}

char *input_info_ptr(FILE *file_inp, char* string_helper){
    if (!fscanf(file_inp, "%s", string_helper))
        return NULL;
    size_t size = strlen(string_helper);
    char* struct_el = (char*)calloc(size + 1, sizeof(char));
    if (!string_helper){
        return NULL;
    }
    strncpy(struct_el, string_helper, size);
    return struct_el;
};
char input_info_value(FILE *file_inp, char* string_helper){
    if (!fscanf(file_inp, "%s", string_helper))
        return 0;
    if (strcmp(string_helper, MALE) != 0 && strcmp(string_helper, FEMALE) != 0){
        size_t size = strlen(string_helper);
        int i = 0;
        int number = 0;
        while (i < size){
            number = 10 * number + (string_helper[i] - 48);
            ++i;
        }
        *string_helper = (char)number;
    }
    return *string_helper;
};

long input_info_int(FILE *file_inp, char* string_helper){
    char *end;
    if (!fscanf(file_inp, "%s", string_helper))
        return 0;
    return strtol(string_helper, &end, 10);
};

struct List *add_to_list(void *new_staff, struct List *list){
    if (!new_staff || !list)
        return NULL;
    if (list->size >= list->capacity)
        list_resize(list, 2 * list->capacity);
    list->data[list->size] = new_staff;
    list->size++;
    return list;
};

struct List *add_to_index(void *new_staff, struct List *list){
    if (!new_staff || !list)
        return NULL;
    if (list->size >= list->capacity)
        list_resize(list, 2 * list->capacity);
    list->data[list->size] = (void*)malloc(list->element_size);
    memcpy(list->data[list->size], new_staff, list->element_size);
    list->size++;
    return list;
};

void list_resize(struct List *list, int new_capacity){
    list->capacity = new_capacity;
    list->data = realloc(list->data, new_capacity * sizeof(void *));
}

void* element_get(struct List *list, int index){
    if (index < 0 || index > list->size - 1 || list->size <= 0)
        return NULL;
    return list->data[index];
}

void sorted_list(struct List *list){
    for (int i = 0; i < list->size - 1; ++i){
        for (int j = 0; j < list->size - i - 1; ++j){
            struct Staffs *curr_staff = element_get(list, j);
            struct Staffs *next_staff = element_get(list, j+1);
            if (strcmp(curr_staff->surname, next_staff->surname) > 0){
                struct Staffs *tmp = list->data[j];
                list->data[j] = list->data[j+1];
                list->data[j+1] = tmp;
            }
        }
    }
}

int is_position_was(struct Staffs *staff, struct List *list){
    for (int i = 0; i < list->size; ++i){
        char *curr_position = element_get(list, i);
        if (strcmp(staff->position, curr_position) == 0)
            return 0;
    }
    add_to_list(staff->position, list);
    return 1;
}

unsigned char compare_staff_max(unsigned char max, unsigned char age, int index, struct List **index_max){
    if (max == age) {
        int curr_index = index;
        add_to_index((void*)&curr_index, *index_max);
    }
    if (max < age) {
        max = age;
        remote_index(*index_max);
        *index_max = create_list(sizeof(int));
        int curr_index = index;
        add_to_index((void*)&curr_index, *index_max);
    }
    return max;
};

unsigned char compare_staff_min(unsigned char min, unsigned char age, int index, struct List **index_min){
    if (min == age) {
        int curr_index = index;
        add_to_index((void*)&curr_index, *index_min);
    }
    if (min > age) {
        min = age;
        remote_index(*index_min);
        *index_min = create_list(sizeof(int));
        int curr_index = index;
        add_to_index((void*)&curr_index, *index_min);
    }
    return min;
}

void create_crit_list(struct List *index_list, struct List *criterion_list, struct List *list){
    for (int i = 0; i < index_list->size; ++i){
        int *index = element_get(index_list, i);
        struct Staffs *max_staff = element_get(list, *index);
        criterion_list = add_to_list(max_staff, criterion_list);
    }
}

struct List* add_to_share_list(struct List *crit_list, struct List *share_list){
    share_list->element_size = crit_list->element_size;
    for (int i = 0; i < crit_list->size; ++i) {
        struct Staffs *staff = element_get(crit_list, i);
        memcpy(share_list->data[share_list->size], staff, share_list->element_size);
        share_list->size++;
    }
    return share_list;
}
