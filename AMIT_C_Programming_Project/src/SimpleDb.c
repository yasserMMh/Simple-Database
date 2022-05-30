#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ENTRIES 10
#define NUMBER_SUBJECTS 3
#define MAX_GRADE 100
#define MIN_GRADE 0

typedef unsigned char uint8;

typedef struct st_Course
{
    uint8 ID;
    uint8 grade;
}Course;

typedef struct st_Student
{
    uint8 ID;
    uint8 year;
    Course courses[NUMBER_SUBJECTS];
}Student;

typedef struct st_Node
{
    Student student;
    struct st_Node* next;
}Node;

typedef struct st_Database
{
    Node* top;
    uint8 size;
}Database;

//! Extra useful functions
Node* getLocation(uint8);
void  printDB(void);
bool  isValidSubjects(uint8*);
void  clearDB(void);

//! Define database variable
/*!
  global: all functions can access it
  static: only current file can see it
*/
static Database database = {.top = NULL, .size = 0};

//! Check if the database is full
/*!
  Return: Return 1 if the the database is full, otherwise 0
*/
bool SDB_IsFull()
{
    return (database.size == MAX_ENTRIES) ? true : false;
}

//! Get the number of entries in the database
/*!
  Return: Return the number of entries
*/
extern uint8 SDB_GetUsedSize()
{
    return database.size;
}

//! Checks if the the provided student ID exists
/*!
  Return: Return 1 if ID exists in the database, otherwise 0
*/
bool SDB_IsIdExist(uint8 ID)
{
    if(getLocation(ID) == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//! Add new entry to the database
/*!
  Assume that the caller will always provide the 3 subjects with their grades

  Input Parameter - id: Student ID
  Input Parameter - year: Student Year
  Input Parameter - subjects: Pointer to 3 subject IDs, with each subject id is a uint8 value
  Input Parameter - grades: Pointer to 3 grades, with each grade is a uint8 value
  The allowed range for the grade is only from 0 to 100
  Return: Return 1 if the new entry is successfully added; otherwise 0
*/
bool SDB_AddEntry(uint8 id, uint8 year, uint8* subjects, uint8* grades)
{
    /* check if there is space to add more entries or not */
    if(SDB_IsFull())
    {
        /* Inform the user that Database is full */
        printf("Error: Failed to add entry of ID = %d. Database is full. \n", id);
        return false;
    }

    /* check if the subjects array is a null pointer */
    if(subjects == NULL)
    {
        /* Inform the user that subjects array is null */
        printf("Error: Failed to add entry of ID = %d. subjects are not available. \n", id);
        return false;
    }

    /* check if the grades array is a null pointer */
    if(grades == NULL)
    {
        /* Inform the user that grades array is null */
        printf("Error: Failed to add entry of ID = %d. grades are not available. \n", id);
        return false;
    }

    /* check if student ID is already exists return false */
    if(SDB_IsIdExist(id))
    {
        /* Inform the user that given ID already exist */
        printf("Error: Failed to add entry. ID = %d is already used \n", id);
        return false;
    }

    /* check if there are repeated subjects ID, return false */
    if(!isValidSubjects(subjects))
    {
        /* Inform the user that multiple subjects have same ID */
        printf("Error: Failed to add entry. Two or more subjects have the same ID \n");
        return false;
    }

    Node* node = (Node*) malloc(sizeof(Node));

    /* The return value of malloc() function is NULL if no enough storage is available, or if size was specified as zero*/
    if(node == NULL)
    {
        /* Inform the user that malloc() failed to allocate memory */
        printf("Error: malloc() failed. \n");
        return false;
    }

    node->next = NULL;
    node->student.ID = id;
    node->student.year = year;

    for(int i = 0; i < NUMBER_SUBJECTS; i++)
    {
        /* if any grade is greater than 100 or less than 0 return false and terminate */
        if(grades[i] > MAX_GRADE || grades[i] < MIN_GRADE)
        {
            /* Inform the user that one of the grads is outside the range */
            printf("Error: Failed to add entry. one of the grades is greater than 100 or less than 0\n");
            /* cancel the operation and free the created node */
            free(node);
            return false;
        }

        node->student.courses[i].ID    = subjects[i];
        node->student.courses[i].grade = grades[i];
    }

    node->next = database.top;
    database.top = node;

    /* Increment size of Database by 1 */
    database.size++;

    return true;
}

//! Delete the entry with the given ID
/*!
  Input Parameter - id: ID of the entry to be deleted
*/
void SDB_DeleteEntry(uint8 id)
{
    Node* cur = database.top;
    Node* prev = cur;
    for(int i = 0; i < database.size; i++)
    {
        if(cur->student.ID == id)
        {
            /* if i = 0, then prev = cur = database.top */
            if(i == 0)
            {
                database.top = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }

            /* Deallocate the allocated memory */
            free(cur);

            /* Inform the user that ID found and deleted */
            printf("Data, associated with ID = %d, has been deleted successfully \n", id);

            /* decrement size of Database by 1 */
            database.size--;

            /* Entry was successfully deleted, terminate the function */
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    /* Inform the user that ID does not exist in the database */
    printf("Error: Failed to delete entry, ID = %d does not exist. \n", id);
}

//! Read an entry matching the provided ID
/*!
  Input  Parameter - id: Student ID
  Output Parameter - year: Pointer to the student year
  Output Parameter - subjects: Pointer to the subjects
  Output Parameter - grades: Pointer to the grades
  Return: Return 1 if the entry exist, otherwise 0
*/
bool SDB_ReadEntry(uint8 id, uint8* year, uint8* subjects, uint8* grades)
{
    Node* node = getLocation(id);
    if(node == NULL)
    {
        /* Inform the user that ID does not exist in the database */
        printf("Error: Failed to read entry. Student ID = %d does not exist in the database \n", id);
        return false;
    }
    else
    {
        *year     = node->student.year;
        for(int i = 0; i < NUMBER_SUBJECTS; i++)
        {
            subjects[i] = node->student.courses[i].ID;
            grades[i]   = node->student.courses[i].grade;
        }
        return true;
    }

}

//! Get the list of IDs of the students
/*!
  Output Parameter - count: Pointer to the number of entries currently exists in the database
  Output Parameter - list: Pointer to the list of IDs
*/
void SDB_GetIdList(uint8* count, uint8* list)
{
    *count = database.size;

    Node* cur = database.top;
    uint8 i = 0;
    while(i < database.size)
    {
        list[i] = cur->student.ID;
        cur = cur->next;

        i++;
    }

}

//! Get the pointer of specified ID
/*!
  Return: Return pointer to data, if ID exists in the database, otherwise Null
*/
Node* getLocation(uint8 ID)
{
    Node* cur = database.top;
    uint8 i = 0;
    while(i < database.size)
    {
        if(cur->student.ID == ID)
        {
            return cur;
        }
        cur = cur->next;
        i++;
    }
    return NULL;
}

//! Print all entries in the Database
/*!
  Return: NO return
*/
void printDB()
{
    Node* cur = database.top;
    for(int i = 0; i < database.size; i++)
    {
        printf("student ID = %3d, year = %3d, {%3d, %3d}, {%3d, %3d}, {%3d, %3d}\n", cur->student.ID, cur->student.year, cur->student.courses[0].ID, cur->student.courses[0].grade, cur->student.courses[1].ID, cur->student.courses[1].grade, cur->student.courses[2].ID, cur->student.courses[2].grade);
        cur = cur->next;
    }
}

//! Checks if subjects have different IDs
/*!
  Return: true if all subjects have different IDs, otherwise return false
*/
bool isValidSubjects(uint8* subjects)
{
    return (subjects[0] == subjects[1] || subjects[0] == subjects[2] || subjects[1] == subjects[2]) ? false : true;
}

//! Clear Database
/*!
  Return: void
*/
void clearDB(void)
{
    Node* cur  = database.top;
    Node* next;
    uint8 i = 0;
    while(i < database.size)
    {
        if(cur->next != NULL)
        {
            next = cur->next;
        }
        free(cur);
        cur = next;
        database.size--;
    }
}
