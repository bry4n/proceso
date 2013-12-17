int rb_hw_ncpu() {
  return 0;
}

int rb_process_exists(int pid) {
  return 0;
}
int rb_process_info(int pid) {
  return 0;
}

int rb_process_memory_size(int pid, int flag) {
  return 0;
}

float rb_process_cpu_times(int pid, int flag) {
  return 0;
}

char * rb_process_command(int pid) {
  return NULL;
}

int rb_process_list(int **pids) {
  return 0;
}