//
// Created by Dan Ye on 2/7/16.
//

#ifndef A2_MYDB_TABLERECITERATOR_H
#define A2_MYDB_TABLERECITERATOR_H

#include "MyDB_RecordIterator.h"
#include "../../Record/headers/MyDB_Record.h"
#include "MyDB_PageRecIterator.h"
#include "../../BufferMgr/headers/MyDB_BufferManager.h"
#include "MyDB_PageInfo.h"

class MyDB_TableRecIterator: MyDB_RecordIterator{
    public:
        void getNext();
        bool hasNext();
        MyDB_TableRecIterator(MyDB_BufferManagerPtr bufferManager, MyDB_RecordPtr recordPtr, MyDB_TablePtr table, size_t numPage, size_t pageSize);
        ~MyDB_TableRecIterator();

    private:
        size_t _curPage, _numPage, _pageSize;
        MyDB_RecordPtr _recordPtr;
        MyDB_PageRecIteratorPtr _curPageRecIt;
        MyDB_TablePtr _table;
        MyDB_BufferManagerPtr _bufferMgr;
};

#endif //A2_MYDB_TABLERECITERATOR_H