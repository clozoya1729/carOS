#ifndef DIAG_OBD_H
#define DIAG_OBD_H
int obd_init(void);
int obd_read_pid(unsigned pid, void *buf, int maxlen);
#endif
