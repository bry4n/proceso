#if defined(__linux) || defined(__LINUX__) || defined(__linux__)

#include "linux.h"
// const char *format = "%d %s %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %lu %lu %llu";

int rb_proc_ncpu() {
  int ncpu = 0;
  char buffer[120];
  FILE *fp;
  fp = fopen("/proc/cpuinfo","r");
  if(!fp)
    return 0;
  while(fgets(buffer,120,fp)){
    if(strncmp(buffer,"processor",9) == 0)
      ++ncpu;
  }
  fclose(fp);
  return ncpu;
}
int rb_proc_pid_rss(int pid) {
  const char *format = "%*d %*s %*c %*d %*d %*d %*d %*d %*lu %*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %*ld %*ld %*ld %*lu %*lu %ld";
  int rss_size = 0;
  char buffer[256];
  FILE *fp;
  sprintf(buffer, "/proc/%d/stat", pid);
  fp = fopen(buffer, "r");
  if (!fp)
    return 0;
  fscanf(fp, format, &rss_size);
  fclose(fp);
  return rss_size;
}

int rb_proc_pid_vsize(int pid) {
  const char *format = "%*d %*s %*c %*d %*d %*d %*d %*d %*lu %*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %*ld %*ld %*ld %*lu %lu";
  int vsize = 0;
  char buffer[256];
  FILE *fp;
  sprintf(buffer, "/proc/%d/stat", pid);
  fp = fopen(buffer, "r");
  if (!fp)
    return 0;
  fscanf(fp, format, &vsize);
  fclose(fp);
  return vsize;
}

float rb_proc_pid_stime(int pid) {
  const char *format = "%*d %*s %*c %*d %*d %*d %*d %*d %*lu %*lu %*lu %*lu %*lu %*lu %lu";
  int stime = 0;
  char buffer[256];
  FILE *fp;
  sprintf(buffer, "/proc/%d/stat", pid);
  fp = fopen(buffer, "r");
  if (!fp)
    return 0;
  fscanf(fp, format, &stime);
  fclose(fp);
  return stime / 1000000.0;
}

float rb_proc_pid_utime(int pid) {
  const char *format = "%*d %*s %*c %*d %*d %*d %*d %*d %*lu %*lu %*lu %*lu %*lu %lu";
  int utime = 0;
  char buffer[256];
  FILE *fp;
  sprintf(buffer, "/proc/%d/stat", pid);
  fp = fopen(buffer, "r");
  if (!fp)
    return 0;
  fscanf(fp, format, &utime);
  fclose(fp);
  return utime / 1000000.0;
}

char * rb_proc_pid_cmdline(int pid) {
  char buffer[512];
  FILE *fp;
  char *cmdline;
  size_t size = 0;
  sprintf(buffer, "/proc/%d/cmdline", pid);
  fp = fopen(buffer, "rb");
  if (!fp)
    return NULL;
  getdelim(&cmdline, &size, 0 , fp);
  fclose(fp);
  return cmdline;
}

#endif