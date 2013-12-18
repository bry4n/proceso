int rb_hw_ncpu();
int rb_process_info(int pid, int flavor, void *pti, int size);
float rb_process_cpu_times(int pid, int flag);
int rb_sysctl_kern_argmax();
int rb_sysctl_kern_procargs2(int pid, char **process_name, int argmax, size_t buf_size);
char * rb_process_command(int pid);
int rb_process_memory_size(int pid, int flag);
int rb_process_list(int **pids);