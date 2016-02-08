//
// Created by Dan Ye on 2/8/16.
//

#ifndef A2_MYDB_PAGEINFO_H
#define A2_MYDB_PAGEINFO_H

#include <stddef.h>

struct MyDB_PageInfo{
public:
    MyDB_PageInfo(size_t lastByte) {
        _lastByte = lastByte;
    }

    size_t _lastByte;
};
#endif //A2_MYDB_PAGEINFO_H
