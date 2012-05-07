#ifndef _TRINITY_H
#define _TRINITY_H 1

#include <stdio.h>
#include <setjmp.h>
#include <sys/types.h>

#include "constants.h"

#define FALSE 0
#define TRUE 1

#ifndef S_SPLINT_S
#define __unused__ __attribute((unused))
#else
#define __unused__ /*@unused@*/
#endif

extern unsigned char debug;

extern jmp_buf ret_jump;

void syscall_list(void);
void main_loop(void);
int child_process(void);

void do_syscall_from_child();

void regenerate_random_page(void);

void seed_from_tod();

extern unsigned int fds_left_to_create;

extern unsigned int socks;
extern unsigned int specific_proto;
void open_sockets();

extern unsigned int fd_idx;

void open_files();
void close_files();
void open_fds(const char *dir);

struct arglist {
	unsigned int num;
	unsigned int values[1024];
};

struct syscall {
	void (*sanitise)(
		unsigned long *,
		unsigned long *,
		unsigned long *,
		unsigned long *,
		unsigned long *,
		unsigned long *);
	void (*post)(int);

	unsigned int number;
	const char name[80];
	unsigned int num_args;
	unsigned int flags;

	unsigned int arg1type;
	unsigned int arg2type;
	unsigned int arg3type;
	unsigned int arg4type;
	unsigned int arg5type;
	unsigned int arg6type;

	const char *arg1name;
	const char *arg2name;
	const char *arg3name;
	const char *arg4name;
	const char *arg5name;
	const char *arg6name;

	unsigned int low1range, hi1range;
	unsigned int low2range, hi2range;
	unsigned int low3range, hi3range;
	unsigned int low4range, hi4range;
	unsigned int low5range, hi5range;
	unsigned int low6range, hi6range;

	struct arglist arg1list;
	struct arglist arg2list;
	struct arglist arg3list;
	struct arglist arg4list;
	struct arglist arg5list;
	struct arglist arg6list;

	unsigned int group;
	int rettype;
};

#define RET_BORING		-1
#define RET_NONE		0
#define RET_ZERO_SUCCESS	1
#define RET_FD			2
#define RET_KEY_SERIAL_T	3
#define RET_PID_T		4
#define RET_PATH		5
#define RET_NUM_BYTES		6
#define RET_GID_T		7
#define RET_UID_T		8

#define GROUP_NONE	0
#define GROUP_VM	1

struct syscalltable {
	struct syscall *entry;
};
extern struct syscalltable *syscalls;
extern struct syscalltable *syscalls_32bit;
extern struct syscalltable *syscalls_64bit;

extern unsigned int page_size;
extern unsigned long long syscallcount;
extern unsigned int max_nr_syscalls;
extern unsigned int max_nr_32bit_syscalls;
extern unsigned int max_nr_64bit_syscalls;
extern unsigned int rep;
extern unsigned char do_specific_proto;
extern unsigned char do_specific_syscall;
extern unsigned long specific_syscall;
extern unsigned char dopause;
extern long struct_fill;
extern unsigned char logging;
extern unsigned char extrafork;

extern unsigned char biarch;

extern unsigned long syscalls_per_child;

extern char *page_zeros;
extern char *page_0xff;
extern char *page_rand;
extern char *page_allocs;

struct map {
	struct map *next;
	void *ptr;
	char *name;
};
void setup_maps();
void destroy_maps();
void * get_map();

#define RED	"[1;31m"
#define GREEN	"[1;32m"
#define YELLOW	"[1;33m"
#define BLUE	"[1;34m"
#define MAGENTA	"[1;35m"
#define CYAN	"[1;36m"
#define WHITE	"[1;37m"

extern unsigned char quiet;
void synclogs();
void output(const char *fmt, ...);
void open_logfiles();
void close_logfiles();

extern unsigned char do_check_tainted;
int check_tainted(void);

#define __stringify_1(x...)     #x
#define __stringify(x...)       __stringify_1(x)

#endif	/* _TRINITY_H */
