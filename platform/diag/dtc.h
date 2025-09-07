#ifndef DIAG_DTC_H
#define DIAG_DTC_H
int dtc_init(void);
int dtc_set(unsigned code);
int dtc_clear(unsigned code);
int dtc_get(unsigned code, int *present);
#endif
