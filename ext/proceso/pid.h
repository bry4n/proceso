int iv2pid(VALUE self);

static VALUE proceso__process_init(VALUE self, VALUE pid);
static VALUE proceso__process_running(VALUE self);
static VALUE proceso__process_command(VALUE self);
static VALUE proceso__process_rss(VALUE self);
static VALUE proceso__process_vms(VALUE self);
static VALUE proceso__process_user_cpu(VALUE self);
static VALUE proceso__process_system_cpu(VALUE self);
static VALUE proceso__process_cpu_usage(VALUE self);