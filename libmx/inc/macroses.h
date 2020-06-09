#pragma once

#define MX_SUM(x, y) ((x) + (y))
#define MX_SUB(x, y) ((x) - (y))
#define MX_MUL(x, y) ((x) * (y))
#define MX_DIV(x, y) ((x) / (y))

#define MX_ODD(x) ((x) & 1)
#define MX_ABS(x) ((x) < 0 ? -(x) : (x))

#define MX_MIN(x, y, type) (((type)x) < ((type)y) ? (x) : (y))
#define MX_MAX(x, y, type) (((type)x) > ((type)y) ? (x) : (y))

#define MX_STR(x) #x
