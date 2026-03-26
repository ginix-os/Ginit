#include <string.h>
#include <syscall.h>

#define EXIT_FAILURE 1

#define LOG(x) ((void)write(1, x, strlen(x)));
#define LOG_EXIT(x) LOG(x); exit(EXIT_FAILURE);

#define NULL ((void*)(0))

void
check_mkdir_rc(
	const int rc
) {
	if(!rc) { return; }
#if 0
	switch (rc) {
		case EACCES		: LOG_EXIT("EACCES: / does not allow write permission to init.\n"			);
		case EDQUOT		: LOG_EXIT("EDQUOT: Block quota exhausted.\n"						);
		case EEXIST		: LOG_EXIT("EEXIST: This path already exists.\n"					);
		case EFAULT		: LOG_EXIT("EFAULT: Pathname outside addressable address space.\n"			);
		case EINVAL		: LOG_EXIT("EINVAL:.\n"									);
		case ELOOP		: LOG_EXIT("ELOOP:.\n"									);
		case EMLINK		: LOG_EXIT("EMLINK:.\n"									);
		case ENAMETOOLONG	: LOG_EXIT("ENAMETOOLONG: The path's name is too long.\n"				);
		case ENOENT		: LOG_EXIT("ENOENT: / does not exist.\n"						);
		case ENOMEM		: LOG_EXIT("ENOMEM: Insufficient kernel memory.\n"					);
		case ENOSPC		: LOG_EXIT("ENOSPC: Insufficient space for new directory.\n"				);
		case ENOTDIR		: LOG_EXIT("ENOTDIR: Component in pathname used as dir but is not dir.\n"		);
		case EPERM		: LOG_EXIT("EPERM: Filesystem containing pathname does not support dir creation.\n"	);
		case EROFS		: LOG_EXIT("EROFS: Filesystem is read-only.\n"						);
	}
#endif

  LOG_EXIT("An error occured; fix debugging!");
}

void
_start(
	void
) {

	int rc;

	/* rc = mkdir ("/dev"	, 0755	); check_mkdir_rc(rc); */
	rc = mkdir ("/sys"	, 0555	); check_mkdir_rc(rc);
	rc = mkdir ("/prc"	, 0555	); check_mkdir_rc(rc);
	rc = mkdir ("/tmp"	, 0755	); check_mkdir_rc(rc);
	rc = chmod ("/tmp"	, 01777	);
	rc = mkdir ("/proc"	, 0555	); check_mkdir_rc(rc);
	rc = mkdir ("/run"	, 0755	); check_mkdir_rc(rc);


	rc = mount (NULL	, "/tmp"	, "tmpfs"	, MS_NOEXEC	| MS_NODEV	| MS_NOSUID					, "mode=1777"	);

	rc = mkdir ("/tmp/run"	, 0755); check_mkdir_rc(rc);

	rc = mount (NULL		, "/dev"	, "devtmpfs"	, MS_NOEXEC			| MS_NOSUID	| MS_STRICTATIME	, NULL	);
	rc = mount (NULL		, "/sys"	, "sysfs"	, MS_NOEXEC	| MS_NODEV 	| MS_NOSUID	| MS_RDONLY		, NULL	);
	rc = mount (NULL		, "/prc"	, "proc"	, MS_NOEXEC	| MS_NODEV	| MS_NOSUID	| MS_RDONLY		, NULL	);
	rc = mount ("/tmp/run"		, "/run"	, NULL		, MS_NOEXEC	| MS_NODEV	| MS_NOSUID	| MS_BIND	| MS_REC, NULL	);
	rc = mount ("/prc"		, "/proc"	, NULL		, 						  MS_BIND	| MS_REC, NULL	);

 
  {
    int pid;

    char info[128] __attribute__((aligned(sizeof(long))));

    if((pid = fork()) != 0) {
      waitid(0x1, pid, info, 0x4, NULL);
    } else {
	char *argv[] = {"/bin/sh", NULL};
    	execve(argv[0], argv, NULL);
    }

  }
  reboot(0xfee1dead, 0x28121969, 0x4321FEDC, NULL);

}
