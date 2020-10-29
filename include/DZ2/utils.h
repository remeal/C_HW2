//
// Created by Dashik on 29.10.2020.
//

#ifndef DZ2_UTILS_H
#define DZ2_UTILS_H

#define CAPACITY_OF_LIST 10
#define MAX_STRING_SIZE 20
#define MALE "m"
#define FEMALE "f"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Staffs{
    char* position; //8 bytes
    char* surname; //8 bytes
    unsigned char age; // 1 bytes - не используем size_t так
    // как хотим упаковать максимально эффективно
    unsigned char experience; //1 bytes
    char gender; //1 bytes
    unsigned int salary; //4 bytes
    char* name; //8 bytes
};


struct List{
    void** data; //8 bytes
    int size; //4 bytes
    int capacity; //4 bytes
    size_t element_size; //8 bytes
};

struct List *create_list(int size_of_data);
struct List *add_to_list(void *data, struct List *list);
struct List *create_database(FILE *file_inp);
void list_resize(struct List *list, int new_capacity);
void* element_get(struct List *list, int index);
int is_position_was(struct Staffs *staff, struct List *list);
void sorted_list(struct List *list);
char *input_info_ptr(FILE *file_inp, char* string_helper);
char input_info_value(FILE *file_inp, char* string_helper);
long input_info_int(FILE *file_inp, char* string_helper);
void remote_database(struct List *list);
void remote_list(struct List *list);
struct List *add_to_index(void *new_staff, struct List *list);
unsigned char compare_staff_max(unsigned char max, unsigned char age, int index, struct List **index_max);
unsigned char compare_staff_min(unsigned char min, unsigned char age, int index, struct List **index_min);
void create_crit_list(struct List *index_list, struct List *criterion_list, struct List *list);
void remote_index(struct List *list);
struct List* add_to_share_list(struct List *crit_list, struct List *share_list);


#endif //DZ2_UTILS_H
