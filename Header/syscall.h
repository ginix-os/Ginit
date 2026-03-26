int write(unsigned int fd, const char *buf, unsigned long long count);
int exit(int rc);
int mkdir(char *path, int mode);
int mount(char *device, char *dir, char *type, unsigned long flags, void *data);
int fork();
int execve(char *path, char **argv, char **envp);
int waitid(int which, int pid, void *info, int options, void *rusage);
int chmod(char *path, int mode);
int reboot(int magic1, int magic2, unsigned int cmd, void *arg);

enum MS
{

  MS_RDONLY = 1,
  MS_NOSUID = 2,
  MS_NODEV  = 4,
  MS_NOEXEC = 8,
  MS_NOSYMFOLLOW = 256,
  MS_NOATIME = 1024,
  MS_BIND = 4096,
  MS_MOVE = 8192,
  MS_REC = 16384,
  MS_STRICTATIME = (1<<24)
};
