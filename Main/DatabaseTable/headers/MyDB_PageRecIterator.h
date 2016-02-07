//
// Created by Dan Ye on 2/7/16.
//

#ifndef A2_MYDB_PAGERECITERATOR_H
#define A2_MYDB_PAGERECITERATOR_H

#include "MyDB_RecordIterator.h"
#include "../../BufferMgr/headers/MyDB_BufferManager.h"

class MyDB_PageRecIterator: MyDB_RecordIterator{
public:
    void getNext();
    bool hasNext();
    MyDB_PageRecIterator();
    ~MyDB_PageRecIterator();

private:

};


#endif //A2_MYDB_PAGERECITERATOR_H
