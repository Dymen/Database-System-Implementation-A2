//
// Created by Dan Ye on 2/7/16.
//
#ifndef A2_MYDB_TABLERECITERATOR_CC
#define A2_MYDB_TABLERECITERATOR_CC

#include "../headers/MyDB_TableRecIterator.h"

using namespace std;

MyDB_TableRecIterator::MyDB_TableRecIterator(MyDB_BufferManagerPtr bufferMgr, MyDB_RecordPtr recordPtr, MyDB_TablePtr table, size_t numPage, size_t pageSize) {
    _pageSize = pageSize;
    _recordPtr = recordPtr;
    _numPage = numPage;
    //TableIterator always starts with the first page
    _curPage = 0;
    _table = table;
    _bufferMgr = bufferMgr;
    _curPageRecIt = make_shared<MyDB_PageRecIterator>(_recordPtr, _bufferMgr->getPage(_table, 0), _pageSize);
}
MyDB_TableRecIterator::~MyDB_TableRecIterator(){
    _recordPtr = nullptr;
    _curPageRecIt = nullptr;
    _table = nullptr;
    _bufferMgr = nullptr;
}

void MyDB_TableRecIterator::getNext(){
    if (! _curPageRecIt->hasNext()) {
        if (_curPage == _table->lastPage()) {
            cerr << "getNext() reached outside the scope fo the record iterator.\n";
            exit(1);
        }
        _curPage++;
        _curPageRecIt = make_shared<MyDB_PageRecIterator>(_recordPtr, _bufferMgr->getPage(_table, _curPage), _pageSize);
    }
    if (_curPageRecIt->hasNext())
        _curPageRecIt->getNext();
}

bool MyDB_TableRecIterator::hasNext(){
    if (! _curPageRecIt->hasNext()) {
        if (_curPage == _table->lastPage())
            return false;
        _curPage++;
        _curPageRecIt = make_shared<MyDB_PageRecIterator>(_recordPtr, _bufferMgr->getPage(_table, _curPage), _pageSize);
    }
    return true;
}

#endif //A2_MYDB_TABLERECITERATOR_CC