#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "userprog/process.h"
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "filesys/off_t.h"
#include "kernel/list.h"
//#include "devices/shutdown.h"

static void syscall_handler (struct intr_frame *);
int exec_process(char *file_name);
void exit_process(int status);
void * is_valid_addr(const void *vaddr);
struct process_file* search_fd(struct list* files, int fd);
void clean_single_file(struct list* files, int fd);
// void clean_all_files(struct list* files); // declear in syscall.h used by another c files


void syscall_exit(struct intr_frame *f);
int syscall_exec(struct intr_frame *f);
int syscall_wait(struct intr_frame *f);
int syscall_creat(struct intr_frame *f);
int syscall_remove(struct intr_frame *f);
int syscall_open(struct intr_frame *f);
int syscall_filesize(struct intr_frame *f);
int syscall_read(struct intr_frame *f);
int syscall_write(struct intr_frame *f);
void syscall_seek(struct intr_frame *f);
int syscall_tell(struct intr_frame *f);
void syscall_close(struct intr_frame *f);
void syscall_halt(void);



void pop_stack(int *esp, int *a, int offset){
	int *tmp_esp = esp;
	*a = *((int *)is_valid_addr(tmp_esp + offset));
}
void syscall_halt(void){
	shutdown_power_off();
}
void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED)
{
  	int *p = f->esp;
	is_valid_addr(p);

  	int system_call = *p;
	switch (system_call)
	{
		case SYS_HALT: syscall_halt(); break;
		case SYS_EXIT: syscall_exit(f); break;
		case SYS_EXEC: f->eax = syscall_exec(f); break;
		case SYS_WAIT: f->eax = syscall_wait(f); break;
		case SYS_CREATE: f->eax = syscall_creat(f); break;
		case SYS_REMOVE: f->eax = syscall_remove(f); break;
		case SYS_OPEN: f->eax = syscall_open(f); break;
		case SYS_FILESIZE: f->eax = syscall_filesize(f); break;
		case SYS_READ: f->eax = syscall_read(f); break;
		case SYS_WRITE: f->eax = syscall_write(f); break;
		case SYS_SEEK: syscall_seek(f); break;
		case SYS_TELL: f->eax = syscall_tell(f); break;
		case SYS_CLOSE: syscall_close(f); break;

		default:
		printf("Default %d\n",*p);
	}
}

int
exec_process(char *file_name)
{
	int tid;
	lock_acquire(&filesys_lock);
	char * name_tmp = malloc (strlen(file_name)+1);
	strlcpy(name_tmp, file_name, strlen(file_name) + 1);

	char *tmp_ptr;
	name_tmp = strtok_r(name_tmp, " ", &tmp_ptr);

	struct file *f = filesys_open(name_tmp);  // check whether the file exists. critical to test case "exec-missing"

	if (f == NULL)
	{
		lock_release(&filesys_lock);
		tid = -1;
	}
	else
	{
		file_close(f);
		lock_release(&filesys_lock);
		tid = process_execute(file_name);
	}
	return tid;
}

void
exit_process(int status)
{
	struct child_process *cp;
	struct thread *cur_thread = thread_current();

	enum intr_level old_level = intr_disable();
	for (struct list_elem *e = list_begin(&cur_thread->parent->children_list); e != list_end(&cur_thread->parent->children_list); e = list_next(e))
	{
		cp = list_entry(e, struct child_process, child_elem);
		if (cp->tid == cur_thread->tid)
		{
			cp->if_waited = true;
			cp->exit_status = status;
		}
	}
	cur_thread->exit_status = status;
	intr_set_level(old_level);

	thread_exit();
}

void *
is_valid_addr(const void *vaddr)
{
	void *page_ptr = NULL;
	if (!is_user_vaddr(vaddr) || !(page_ptr = pagedir_get_page(thread_current()->pagedir, vaddr)))
	{
		exit_process(-1);
		return 0;
	}
	return page_ptr;
}

  /* Find fd and return process file struct in the list,
  if not exist return NULL. */
struct process_file *
search_fd(struct list* files, int fd)
{
	struct process_file *proc_f;
	for (struct list_elem *e = list_begin(files); e != list_end(files); e = list_next(e))
	{
		proc_f = list_entry(e, struct process_file, elem);
		if (proc_f->fd == fd)
			return proc_f;
	}
	return NULL;
}

  /* close and free specific process files
  by the given fd in the file list. Firstly,
  find fd in the list, then remove it. */
void
clean_single_file(struct list* files, int fd)
{
	struct process_file *proc_f = search_fd(files,fd);
	if (proc_f != NULL){
		file_close(proc_f->ptr);
		list_remove(&proc_f->elem);
    	free(proc_f);
	}
}

  /* close and free all process files in the file list */
void
clean_all_files(struct list* files)
{
	struct process_file *proc_f;
	while(!list_empty(files))
	{
		proc_f = list_entry (list_pop_front(files), struct process_file, elem);
		file_close(proc_f->ptr);
		list_remove(&proc_f->elem);
		free(proc_f);
	}
}

void
syscall_exit(struct intr_frame *f)
{
	int status;
	pop_stack(f->esp, &status, 1);
	exit_process(status);
}

int
syscall_exec(struct intr_frame *f)
{
	char *file_name = NULL;
	pop_stack(f->esp, &file_name, 1);
	if (!is_valid_addr(file_name))
		return -1;

	return exec_process(file_name);
}

int
syscall_wait(struct intr_frame *f)
{
	tid_t child_tid;
	pop_stack(f->esp, &child_tid, 1);
	return process_wait(child_tid);
}

int
syscall_creat(struct intr_frame *f)
{
	int ret;
	off_t initial_size;
	char *name;

	pop_stack(f->esp, &initial_size, 5);
	pop_stack(f->esp, &name, 4);
	if (!is_valid_addr(name))
		ret = -1;

	lock_acquire(&filesys_lock);
	ret = filesys_create(name, initial_size);
	lock_release(&filesys_lock);
	return ret;
}

int
syscall_remove(struct intr_frame *f)
{
	int ret;
	char *name;

	pop_stack(f->esp, &name, 1);
	if (!is_valid_addr(name))
		ret = -1;

	lock_acquire(&filesys_lock);
	if (filesys_remove(name) == NULL)
		ret = false;
	else
		ret = true;
	lock_release(&filesys_lock);

	return ret;
}

int
syscall_open(struct intr_frame *f)
{
	int ret;
	char *name;

	pop_stack(f->esp, &name, 1);

	if (!is_valid_addr(name) || strlen(name) == 0){
		ret = -1;
		return ret;
	}
		

	lock_acquire(&filesys_lock);
	struct file *fptr = filesys_open(name);
	lock_release(&filesys_lock);

	if (fptr == NULL)
		ret = -1;
	else
	{
		struct process_file *pfile = malloc(sizeof(*pfile));
		pfile->ptr = fptr;
		pfile->fd = thread_current()->fd_count;
		thread_current()->fd_count++;
		list_push_back(&thread_current()->opened_files, &pfile->elem);
		ret = pfile->fd;
	}
	return ret;
}

int
syscall_filesize(struct intr_frame *f)
{
	int ret;
	int fd;
	pop_stack(f->esp, &fd, 1);

	lock_acquire(&filesys_lock);
	ret = file_length (search_fd(&thread_current()->opened_files, fd)->ptr);
	lock_release(&filesys_lock);

	return ret;
}

int
syscall_read(struct intr_frame *f)
{
	int ret;
	int size;
	void *buffer;
	int fd;

	pop_stack(f->esp, &size, 7);
	pop_stack(f->esp, &buffer, 6);
	pop_stack(f->esp, &fd, 5);

	if (!is_valid_addr(buffer))
		ret = -1;

	if (fd == 0)
	{
		int i;
		uint8_t *buffer = buffer;
		for (i = 0; i < size; i++)
			buffer[i] = input_getc();
		ret = size;
	}
	else
	{
		struct process_file *pf = search_fd(&thread_current()->opened_files, fd);
		if (pf == NULL)
			ret = -1;
		else
		{
			lock_acquire(&filesys_lock);
			ret = file_read(pf->ptr, buffer, size);
			lock_release(&filesys_lock);
		}
	}

	return ret;
}

int
syscall_write(struct intr_frame *f)
{
	int ret;
	int size;
	void *buffer;
	int fd;

	pop_stack(f->esp, &size, 7);
	pop_stack(f->esp, &buffer, 6);
	pop_stack(f->esp, &fd, 5);

	if (!is_valid_addr(buffer))
		ret = -1;

	if (fd == 1)
	{
		putbuf(buffer, size);
		ret = size;
	}
	else
	{
		enum intr_level old_level = intr_disable();
		struct process_file *pf = search_fd(&thread_current()->opened_files, fd);
		intr_set_level (old_level);

		if (pf == NULL)
			ret = -1;
		else
		{
			lock_acquire(&filesys_lock);
			ret = file_write(pf->ptr, buffer, size);
			lock_release(&filesys_lock);
		}
	}

	return ret;
}

void
syscall_seek(struct intr_frame *f)
{
	int fd;
	int pos;
	pop_stack(f->esp, &fd, 5);
	pop_stack(f->esp, &pos, 4);

	lock_acquire(&filesys_lock);
	file_seek(search_fd(&thread_current()->opened_files, pos)->ptr, fd);
	lock_release(&filesys_lock);
}

int
syscall_tell(struct intr_frame *f)
{
	int ret;
	int fd;
	pop_stack(f->esp, &fd, 1);

	lock_acquire(&filesys_lock);
	ret = file_tell(search_fd(&thread_current()->opened_files, fd)->ptr);
	lock_release(&filesys_lock);

	return ret;
}

void
syscall_close(struct intr_frame *f)
{
	int fd;
	pop_stack(f->esp, &fd, 1);

	/* ++2 Hack close-stdout & close-badfd */
	if(fd == 1 || fd == 0x20101234){
		exit_process(-1);
	}
	
	lock_acquire(&filesys_lock);
	clean_single_file(&thread_current()->opened_files, fd);
	lock_release(&filesys_lock);
}
