#ifndef ERROR_H
#define ERROR_H

#include "common/status.h"

void error_print(enum status status);
int error_exit_code(enum status status);

#endif
