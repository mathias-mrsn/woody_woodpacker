#ifndef CONVERT_HEADERS_H
#define CONVERT_HEADERS_H
#include "exploit.h"

ELF32_FORMAT *convert64_32(ELF64_FORMAT *src);
ELF64_FORMAT *convert32_64(const ELF32_FORMAT *src);

#endif