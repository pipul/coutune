#ifndef __AE_H_
#define __AE_H_

#define AE_SETSIZE 10240	/* Max number of fd supported */
#define AE_OK 0
#define AE_ERR -1

#define AE_NONE 0
#define AE_READABLE 1
#define AE_WRITABLE 2

#define AE_BLOCK 1
#define AE_NO_BLOCK 2

#include <sys/epoll.h>

typedef struct epoll_event efire_t;

typedef void eProc(int fd, void *argv, int mask);

/* File event structure */
typedef struct efile {
	int mask;
	eProc *rProc;
	eProc *wProc;
	void *data;
} efile_t;

typedef struct eloop {
	int efd;
	int stop;
	efile_t ev[AE_SETSIZE];
	efire_t rd[AE_SETSIZE];
} EL;

/* prototypes */

EL *el_open(void);
int el_close(EL *el);
int el_stop(EL *el);
int el_start(EL *el, int flags);

int el_addFileEvent(EL *el, int fd, int mask, eProc *pro, void *data);
int el_delFileEvent(EL *el, int fd, int mask);

#endif
