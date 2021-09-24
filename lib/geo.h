#include <string>

#ifndef LIB1_H_INCLUDED
#define LIB1_H_INCLUDED

#ifdef __cplusplus
    extern "C" {
#endif

std::string locationToWGS84 ( int x, int y );

#ifdef __cplusplus
    }
#endif

#endif /* LIB1_H_INCLUDED */
