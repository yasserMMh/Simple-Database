#ifndef SIMPLEDB_H_INCLUDED
#define SIMPLEDB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char uint8;

extern bool  SDB_IsFull(void);
extern uint8 SDB_GetUsedSize(void);
extern bool  SDB_AddEntry(uint8, uint8, uint8*, uint8*);
extern void  SDB_DeleteEntry(uint8);
extern bool  SDB_ReadEntry(uint8, uint8*, uint8*, uint8*);
extern void  SDB_GetIdList(uint8*, uint8*);
extern bool  SDB_IsIdExist(uint8);

//! Extra useful functions
extern void  printDB(void);
extern void  clearDB(void);

#endif // SIMPLEDB_H_INCLUDED
