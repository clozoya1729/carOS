#include "journal.h"
int journal_init(void){ return 0; }
int journal_append(const void *blob, size_t len){ (void)blob; (void)len; return 0; }
int journal_read(unsigned index, void *blob, size_t maxlen){ (void)index; (void)blob; (void)maxlen; return 0; }
