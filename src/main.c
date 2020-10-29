#include <stdio.h>
#include <time.h>
#include "DZ2/without_fork.h"
#include "DZ2/with_fork.h"
#include "DZ2/utils.h"



int main() {
    FILE* input_file = NULL;
    input_file = fopen("../test1.txt", "r+");
    if (!input_file){
        printf("%s", "Can`t open file!");
        return -1;
    }
    clock_t stop_tandeming, stop_parall;
    clock_t start_tandeming = clock();
    //clock_t start_parall = clock();
    struct List *list = create_database(input_file);
    fclose(input_file);
    struct List *c_list = select_the_most(list);
    for (int i = 0; i < c_list->size; ++i){
        struct Staffs *staff = element_get(c_list, i);
        printf("%s %s %c %d %d %s %d\n", staff->name, staff->surname, staff->gender,
               staff->age, staff->salary, staff->position, staff->experience);
    }
    remote_list(c_list);
    struct List *fork_list = split_process(list);
    for (int i = 0; i < fork_list->size; ++i){
        struct Staffs *staff = element_get(fork_list, i);
        printf("%s %s %c %d %d %s %d\n", staff->name, staff->surname, staff->gender,
               staff->age, staff->salary, staff->position, staff->experience);
    }
    remote_database(list);
    stop_tandeming = clock();
    printf("Loop required %ld seconds", (stop_tandeming - start_tandeming) / CLOCKS_PER_SEC);
}
