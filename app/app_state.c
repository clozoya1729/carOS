#include "app_state.h"
static app_state_t s_state = APP_STATE_INIT;
void app_state_init(void){ s_state = APP_STATE_INIT; }
void app_state_step(void){ /* user logic here */ }
app_state_t app_state_get(void){ return s_state; }
