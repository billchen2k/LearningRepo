#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#include "kernel/list.h"

struct process_file {
	struct file* ptr;
	int fd;
	struct list_elem elem;
};

void syscall_init (void);
void clean_all_files(struct list* files);

#endif /* userprog/syscall.h */
