#define FCPU_USR 0
#define FCPU_SYS 1

int rb_hw_ncpu();
int rb_process_exists(int pid);
int rb_process_info(int pid);

int rb_process_memory_size(int pid, int flag);

float rb_process_cpu_times(int pid, int flag);

char * rb_process_command(int pid);

int rb_process_list(int **pids);