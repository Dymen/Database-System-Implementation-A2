
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include <iostream>
#include <sys/fcntl.h>
#include "../headers/MyDB_PageReaderWriter.h"
#include "../headers/MyDB_TableReaderWriter.h"
#include "../headers/MyDB_TableRecIterator.h"

using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr forMe, MyDB_BufferManagerPtr myBuffer) {
	_bufferMgr = myBuffer;
	_table = forMe;
	_recordPtr = make_shared<MyDB_Record>(_table->getSchema());
	_pageSize = myBuffer->getPageSize();
	_numPage = 0;
	_pageSelector = new MyDB_PageReaderWriter();
}

MyDB_TableReaderWriter :: ~MyDB_TableReaderWriter(){
	_bufferMgr = nullptr;
	_table = nullptr;
	_recordPtr = nullptr;
	delete _pageSelector;
}

//Always return the reference of the same object, which is refreshed everty this function is called
MyDB_PageReaderWriter &MyDB_TableReaderWriter :: operator [] (size_t pageNo) {
	_pageSelector->reload(false, _pageSize, _bufferMgr->getPage(_table, pageNo), _recordPtr);
	return *(_pageSelector);
}

//Return a new recordPtr with a pecific schema
MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	return make_shared<MyDB_Record>(_table->getSchema());
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: last () {
	return (*this)[_numPage];
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr recordPtr) {
	MyDB_PageReaderWriter lastPage = last();
	MyDB_PageReaderWriterPtr newPagePtr;
	if (! lastPage.append(recordPtr)){
		_numPage ++;
		newPagePtr = make_shared<MyDB_PageReaderWriter>(true, _pageSize, _bufferMgr->getPage(_table, _numPage), _recordPtr);
		if (! newPagePtr->append(recordPtr)){
			cerr << "Record is too large to fit into one single page.\n";
			exit(1);
		}
		_table->setLastPage(_numPage);
	}
}

void MyDB_TableReaderWriter :: loadFromTextFile (string fileLoc) {
	ifstream fin(fileLoc, ios::in);
	char* curRec = new char[_pageSize];

	_numPage = 0;
	_table->setLastPage(_numPage);
	_pageSelector->reload(true, _pageSize, _bufferMgr->getPage(_table, _numPage), _recordPtr);
	while (fin.getline(curRec, _pageSize)){
		_recordPtr->fromString(curRec);
		append(_recordPtr);
	}
	fin.close();
	delete [] curRec;
}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr recordPtr) {
	MyDB_TableRecIterator* it = new MyDB_TableRecIterator(_bufferMgr, recordPtr, _table, _numPage, _pageSize);
	shared_ptr<MyDB_RecordIterator> ptr((MyDB_RecordIterator*)it);
	return ptr;
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string fileLoc) {
	MyDB_RecordIteratorPtr myIt = getIterator(_recordPtr);
	char* recBytes = new char[_pageSize];
	char delimiter[1];
	delimiter[0] = '\n';
	int fd = open (fileLoc.data(), O_TRUNC | O_CREAT | O_RDWR, 0666);

	while (myIt->hasNext()) {
		myIt->getNext();
		_recordPtr->toBinary(recBytes);
		write(fd, recBytes, _recordPtr->getBinarySize());
		write(fd, delimiter, 1);
	}
	close(fd);
	delete [] recBytes;
}

#endif

