cmake_minimum_required(VERSION 3.3)
project(A2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main/BufferMgr/headers/CheckLRU.h
    Main/BufferMgr/headers/MyDB_BufferManager.h
    Main/BufferMgr/headers/MyDB_Page.h
    Main/BufferMgr/headers/MyDB_PageHandle.h
    Main/BufferMgr/headers/PageCompare.h
    Main/BufferMgr/headers/TableCompare.h
    Main/BufferMgr/source/MyDB_BufferManager.cc
    Main/BufferMgr/source/MyDB_Page.cc
    Main/BufferTest/source/BufferQUnit.cc
    Main/Catalog/headers/MyDB_AttType.h
    Main/Catalog/headers/MyDB_Catalog.h
    Main/Catalog/headers/MyDB_PageType.h
    Main/Catalog/headers/MyDB_Schema.h
    Main/Catalog/headers/MyDB_Table.h
    Main/Catalog/source/MyDB_Catalog.cc
    Main/Catalog/source/MyDB_Schema.cc
    Main/Catalog/source/MyDB_Table.cc
    Main/DatabaseTable/headers/MyDB_PageReaderWriter.h
    Main/DatabaseTable/headers/MyDB_RecordIterator.h
    Main/DatabaseTable/headers/MyDB_TableReaderWriter.h
    Main/DatabaseTable/source/MyDB_PageReaderWriter.cc
    Main/DatabaseTable/source/MyDB_TableReaderWriter.cc
    Main/Qunit/headers/QUnit.h
    Main/Record/headers/MyDB_AttVal.h
    Main/Record/headers/MyDB_Record.h
    Main/Record/source/MyDB_AttVal.cc
    Main/Record/source/MyDB_Record.cc
    Main/RecordTest/source/RecordQUnit.cc Main/DatabaseTable/headers/MyDB_PageRecIterator.h Main/DatabaseTable/headers/MyDB_TableRecIterator.h Main/DatabaseTable/source/MyDB_PageRecIterator.cc Main/DatabaseTable/source/MyDB_TableRecIterator.cc Main/DatabaseTable/headers/MyDB_PageInfo.h)

add_executable(A2 ${SOURCE_FILES})