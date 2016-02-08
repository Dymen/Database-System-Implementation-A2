//
// Created by Dan Ye on 2/7/16.
//

#ifndef A2_MYDB_PAGERECITERATOR_H
#define A2_MYDB_PAGERECITERATOR_H

#include "MyDB_RecordIterator.h"
#include "../../BufferMgr/headers/MyDB_BufferManager.h"
#include "../../Record/headers/MyDB_Record.h"
#include "MyDB_PageReaderWriter.h"
class MyDB_PageRecIterator;
typedef shared_ptr<MyDB_PageRecIterator> MyDB_PageRecIteratorPtr;

class MyDB_PageRecIterator: MyDB_RecordIterator{
public:
    void getNext();
    bool hasNext();
    MyDB_PageRecIterator(MyDB_RecordPtr recordPtr, MyDB_PageHandle pageHandle, size_t pageSize);
    ~MyDB_PageRecIterator();

private:
    size_t _curOffset, _pageSize;
    MyDB_PageHandle _pageHandle;
    MyDB_RecordPtr _recordPtr;
};


#endif //A2_MYDB_PAGERECITERATOR_H
