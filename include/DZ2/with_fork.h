//
// Created by Dashik on 27.10.2020.
//

#ifndef DZ2_WITH_FORK_H
#define DZ2_WITH_FORK_H

#include <sys/mman.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <unistd.h>


struct List *split_process(struct List *list);
#endif //DZ2_WITH_FORK_H
