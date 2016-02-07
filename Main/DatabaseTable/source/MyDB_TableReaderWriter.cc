
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include "../headers/MyDB_PageReaderWriter.h"
#include "../headers/MyDB_TableReaderWriter.h"

using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr, MyDB_BufferManagerPtr) {
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: operator [] (size_t) {
	static MyDB_PageReaderWriter temp;
	//Refresh content on i_th page each time it's called, because the content is dynamic
	return temp;	
}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	return nullptr;
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: last () {
	return (*this)[0];
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr) {
}

void MyDB_TableReaderWriter :: loadFromTextFile (string) {
}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr) {
	return nullptr;
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string) {
}

#endif
