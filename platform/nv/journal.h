#ifndef NV_JOURNAL_H
#define NV_JOURNAL_H
#include <stddef.h>
int journal_init(void);
int journal_append(const void *blob, size_t len);
int journal_read(unsigned index, void *blob, size_t maxlen);
#endif
