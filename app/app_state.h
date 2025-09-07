#ifndef APP_STATE_H
#define APP_STATE_H
typedef enum { APP_STATE_INIT, APP_STATE_RUN, APP_STATE_SAFE } app_state_t;
void app_state_init(void);
void app_state_step(void);
app_state_t app_state_get(void);
#endif
