#include <stddef.h>
#include "app_tasks.h"
#include "app_state.h"
int main(void){
    app_state_init();
    (void)task_1ms; (void)task_10ms; (void)task_100ms;
    return 0;
}
