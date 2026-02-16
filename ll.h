#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. ประกาศโครงสร้างและ Pointer
struct Node {
    int id;               
    char name[50];        
    struct Node *nextPtr; 
    struct Node *pPtr;    
};

typedef struct Node LLnode;
typedef LLnode *LLPtr;

// ---------------------------------------------------------
// ย้ายฟังก์ชัน isEmpty มาไว้ด้านบนสุด เพื่อให้ฟังก์ชันอื่นรู้จัก
// ---------------------------------------------------------
int isEmpty( LLPtr sPtr ){
    return sPtr == NULL;
}

// ---------------------------------------------------------
// ฟังก์ชันการทำงานอื่นๆ
// ---------------------------------------------------------
void instructions( void ){
    puts( "Enter your choice:\n"
       "   1 to insert an element into the list.\n"
       "   2 to delete an element from the list.\n"
       "   3 to end." );
}

void insert( LLPtr *sPtr, int id, char name[] ){
    LLPtr newPtr = (LLPtr) malloc( sizeof( LLnode ) ); 

    if ( newPtr != NULL ) { 
        newPtr->id = id; 
        strcpy(newPtr->name, name); 
        newPtr->nextPtr = NULL; 
        newPtr->pPtr = NULL;    
        
        LLPtr previousPtr = NULL;
        LLPtr currentPtr = *sPtr;

        while ( currentPtr != NULL && id > currentPtr->id ) {
            previousPtr = currentPtr; 
            currentPtr = currentPtr->nextPtr; 
        } 

        if ( previousPtr == NULL ) {
            newPtr->nextPtr = *sPtr;
            if ( *sPtr != NULL ) {
                (*sPtr)->pPtr = newPtr; 
            }
            *sPtr = newPtr;
        } 
        else { 
            previousPtr->nextPtr = newPtr;
            newPtr->pPtr = previousPtr; 
            newPtr->nextPtr = currentPtr;
            if ( currentPtr != NULL ) {
                currentPtr->pPtr = newPtr; 
            }
        } 
    } 
    else {
        printf( "%d not inserted. No memory available.\n", id );
    } 
}

int deletes( LLPtr *sPtr, int id ){
    // ตอนนี้คอมไพเลอร์รู้จัก isEmpty แล้ว เพราะเราย้ายไปไว้ด้านบน
    if ( isEmpty( *sPtr ) ) return 0; 

    if ( id == ( *sPtr )->id ) {
        LLPtr tempPtr = *sPtr; 
        *sPtr = ( *sPtr )->nextPtr; 
        if ( *sPtr != NULL ) {
            (*sPtr)->pPtr = NULL; 
        }
        free( tempPtr ); 
        return id;
    } 
    else {
        LLPtr previousPtr = *sPtr;
        LLPtr currentPtr = ( *sPtr )->nextPtr;

        while ( currentPtr != NULL && currentPtr->id != id ) {
            previousPtr = currentPtr; 
            currentPtr = currentPtr->nextPtr; 
        } 

        if ( currentPtr != NULL ) {
            LLPtr tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            if ( currentPtr->nextPtr != NULL ) {
                currentPtr->nextPtr->pPtr = previousPtr; 
            }
            free( tempPtr );
            return id;
        } 
    } 
    return 0;
}

void printList( LLPtr currentPtr ){
    if ( isEmpty( currentPtr ) ) {
        puts( "List is empty." );
    } 
    else {
        puts( "The list is:" );
        LLPtr tempPtr = currentPtr;
        while ( tempPtr != NULL ) {
            printf( "%d %s --> ", tempPtr->id, tempPtr->name );
            tempPtr = tempPtr->nextPtr;
        } 
        puts( "NULL" );
    } 
}

void printListR( LLPtr currentPtr ){
    // แก้ชื่อให้ตรงกับที่ไฟล์ main เรียกใช้ (printListR)
    if ( !isEmpty( currentPtr ) ) {
        LLPtr tempPtr = currentPtr;
        while ( tempPtr->nextPtr != NULL ) {
            tempPtr = tempPtr->nextPtr;
        } 
        while ( tempPtr != NULL ) {
            printf( "%d %s --> ", tempPtr->id, tempPtr->name );
            tempPtr = tempPtr->pPtr; 
        } 
        puts( "NULL" );
    } 
}

void clearList( LLPtr *sPtr ){
    if ( !isEmpty( *sPtr ) ) {
        puts( "Clear all nodes" ); 
        LLPtr tempPtr;
        while ( *sPtr != NULL ) {
            tempPtr = *sPtr;
            printf( "delete %d\n", tempPtr->id );
            *sPtr = ( *sPtr )->nextPtr;
            free( tempPtr );
        }
    }
}

#endif // LL_H