#ifndef DIAG_UDS_H
#define DIAG_UDS_H
int uds_init(void);
int uds_handle_request(const void *req, int len, void *resp, int maxlen);
#endif
