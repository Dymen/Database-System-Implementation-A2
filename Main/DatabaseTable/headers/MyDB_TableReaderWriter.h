
#ifndef TABLE_RW_H
#define TABLE_RW_H

#include <memory>
#include "MyDB_RecordIterator.h"
#include "../../Record/headers/MyDB_Record.h"
#include "../../Catalog/headers/MyDB_Table.h"
#include "../../BufferMgr/headers/MyDB_BufferManager.h"
#include "MyDB_PageReaderWriter.h"
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// create a smart pointer for the catalog
using namespace std;

class MyDB_PageReaderWriter;
class MyDB_TableReaderWriter;
typedef shared_ptr <MyDB_TableReaderWriter> MyDB_TableReaderWriterPtr;

class MyDB_TableReaderWriter {

public:

	// ANYTHING ELSE YOU NEED HERE

	// create a table reader/writer for the specified table, using the specified
	// buffer manager
	MyDB_TableReaderWriter (MyDB_TablePtr forMe, MyDB_BufferManagerPtr myBuffer);

	~MyDB_TableReaderWriter();

	// gets an empty record from this table
	MyDB_RecordPtr getEmptyRecord ();

	// append a record to the table
	void append (MyDB_RecordPtr appendMe);

	// return an itrator over this table... each time returnVal->next () is
	// called, the resulting record will be placed into the record pointed to
	// by iterateIntoMe
	MyDB_RecordIteratorPtr getIterator (MyDB_RecordPtr iterateIntoMe);

	// load a text file into this table... overwrites the current contents
	void loadFromTextFile (string fromMe);

	// dump the contents of this table into a text file
	void writeIntoTextFile (string toMe);

	// access the i^th page in this file
	MyDB_PageReaderWriter &operator [] (size_t i);

	// access the last page in the file
	MyDB_PageReaderWriter &last ();

private:
	MyDB_BufferManagerPtr _bufferMgr;
	MyDB_TablePtr _table;
	MyDB_RecordPtr _recordPtr;
	size_t _pageSize;
	size_t _numPage;
	MyDB_PageReaderWriter *_pageSelector;

	// ANYTHING YOU NEED HERE
};

#endif
