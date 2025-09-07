#include "dtc.h"
int dtc_init(void){ return 0; }
int dtc_set(unsigned code){ (void)code; return 0; }
int dtc_clear(unsigned code){ (void)code; return 0; }
int dtc_get(unsigned code, int *present){ (void)code; if(present) *present = 0; return 0; }
