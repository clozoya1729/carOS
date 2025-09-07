#include "os_task.h"
int os_task_create(os_task_fn_t fn, void *arg, unsigned prio, unsigned period_ms){ (void)fn; (void)arg; (void)prio; (void)period_ms; return 0; }
int os_task_delete(int task_id){ (void)task_id; return 0; }
