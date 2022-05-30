#include "header/SimpleDb.h"

int main()
{

    return 0;
}

#ifdef TestCases
    //! random inputs to be used in the test cases
    uint8 course_IDs[][3] = {
                                {149, 201, 101},
                                {111, 211, 161},
                                {134, 201, 154},
                                {105, 128, 173},
                                {105, 105, 150} // wrong inputs for testing purpose (repeated IDs)
                            };
    uint8 grades[][3] = {
                            {10, 50, 70},
                            {50, 80, 53},
                            {66, 78, 85},
                            {87, 54, 45},
                            {-20, 100, 50}, // wrong inputs for testing purpose (grades < 0)
                            {120, 100, 50}  // wrong inputs for testing purpose (100 < grades)
                        };

    //! Test cases

    //! Test case 01
    /*!
        objective: test the return value of "SDB_IsFull()", when database has no entries
        expected result: 0
        status: passed
    */
    printf("Test case 01: Is DB full = %d\n", SDB_IsFull());

    //! Test case 02
    /*!
        objective: test the return value of "SDB_GetUsedSize()", when database has no entries
        expected result: 0
        status: passed
    */
    printf("Test case 02: Used size  = %d\n", SDB_GetUsedSize());

    //! Test case 03
    /*!
        objective: test the return value of "SDB_IsFull()", when database has 3 entries
        expected result: 0
        status: passed
    */
    SDB_AddEntry(1, 22, course_IDs[0], grades[0]);
    SDB_AddEntry(2, 19, course_IDs[1], grades[1]);
    SDB_AddEntry(3, 20, course_IDs[2], grades[2]);
    printf("Test case 03: Is DB full = %d\n", SDB_IsFull());

    //! Test case 04
    /*!
        objective: test the return value of "SDB_GetUsedSize()", when database has 3 entries
        expected result: 3
        status: passed
    */
    printf("Test case 04: Used size  = %d\n", SDB_GetUsedSize());

    //! Test case 05
    /*!
        objective: test the return value of "SDB_IsFull()", when database has [3 previous entries + 7 new entries] = 10 entries
        expected result: 1
        status: passed
    */
    SDB_AddEntry(11, 22, course_IDs[0], grades[0]);
    SDB_AddEntry(22, 19, course_IDs[1], grades[1]);
    SDB_AddEntry(13, 20, course_IDs[2], grades[2]);
    SDB_AddEntry(14, 22, course_IDs[0], grades[0]);
    SDB_AddEntry(28, 19, course_IDs[1], grades[1]);
    SDB_AddEntry(19, 20, course_IDs[2], grades[2]);
    SDB_AddEntry(73, 22, course_IDs[0], grades[0]);
    printf("Test case 05: Is DB full = %d\n", SDB_IsFull());

    //! Test case 06
    /*!
        objective: test the return value of "SDB_GetUsedSize()", when database has 10 entries
        expected result: 10
        status: passed
    */
    printf("Test case 06: Used size  = %d\n", SDB_GetUsedSize());

    //! Test case 07
    /*!
        objective: test the return value of "SDB_IsFull()", after clear DB
        expected result: 0
        status: passed
    */
    clearDB();
    printf("Test case 07: Is DB full = %d\n", SDB_IsFull());

    //! Test case 08
    /*!
        objective: test the return value of "SDB_GetUsedSize()", after clear DB
        expected result: 0
        status: passed
    */
    printf("Test case 08: Used size  = %d\n", SDB_GetUsedSize());

    //! Test case 09
    /*!
        objective: test the return value of "SDB_AddEntry()", if 0 <= grades <= 100
        expected result: 1
        status: passed
    */
    printf("Test case 09: Add entry  = %d\n", SDB_AddEntry(101, 22, course_IDs[0], grades[0]));

    //! Test case 10
    /*!
        objective: test the return value of "SDB_AddEntry()", if grades < 0
        expected result: 0
        status: passed
    */
    printf("Test case 10: Add entry  = %d\n", SDB_AddEntry(102, 22, course_IDs[0], grades[4]));

    //! Test case 11
    /*!
        objective: test the return value of "SDB_AddEntry()", if grades > 100
        expected result: 0
        status: passed
    */
    printf("Test case 11: Add entry  = %d\n", SDB_AddEntry(102, 22, course_IDs[0], grades[5]));

    //! Test case 12
    /*!
        objective: test the return value of "SDB_AddEntry()", if subjects ID are repeated
        expected result: 0
        status: passed
    */
    printf("Test case 12: Add entry  = %d\n", SDB_AddEntry(102, 22, course_IDs[4], grades[0]));

    //! Test case 13
    /*!
        objective: test the return value of "SDB_AddEntry()", if ID is already used (101)
        expected result: 0
        status: passed
    */
    printf("Test case 13: Add entry  = %d\n", SDB_AddEntry(101, 22, course_IDs[0], grades[0]));

    //! Test case 14
    /*!
        objective: test the return value of "SDB_AddEntry()", if Database is full
        expected result: 0
        status: passed
    */
    clearDB();
    SDB_AddEntry(1, 22, course_IDs[0], grades[0]);
    SDB_AddEntry(2, 19, course_IDs[1], grades[1]);
    SDB_AddEntry(3, 20, course_IDs[2], grades[2]);
    SDB_AddEntry(11, 22, course_IDs[0], grades[0]);
    SDB_AddEntry(22, 19, course_IDs[1], grades[1]);
    SDB_AddEntry(13, 20, course_IDs[2], grades[2]);
    SDB_AddEntry(14, 22, course_IDs[0], grades[0]);
    SDB_AddEntry(28, 19, course_IDs[1], grades[1]);
    SDB_AddEntry(19, 20, course_IDs[2], grades[2]);
    SDB_AddEntry(73, 22, course_IDs[0], grades[0]);
    printf("Test case 14: Add entry  = %d\n", SDB_AddEntry(101, 22, course_IDs[0], grades[0]));

    //! Test case 15
    /*!
        objective: test the return value of "SDB_DeleteEntry()", if ID exist
        expected result: void
        status: passed
    */
    printf("Test case 15: ");
    SDB_DeleteEntry(1);

    //! Test case 16
    /*!
        objective: test the return value of "SDB_DeleteEntry()", if ID does not exist
        expected result: void
        status: passed
    */
    printf("Test case 16: ");
    SDB_DeleteEntry(1);

    //! Test case 17
    /*!
        objective: test the return value of "SDB_ReadEntry()", if ID exist (ID = 73)
        expected result: Read entry = 1, year = 22, subjects = {149, 201, 101}, grades = {10, 50, 70}
        status: passed
    */
    uint8 output_year;
    uint8 output_subjects[3] = {0};
    uint8 output_grades[3]   = {0};
    bool r17 = SDB_ReadEntry(73, &output_year, output_subjects, output_grades);
    printf("Test case 17: Read entry = %d, year = %d, subjects = {%d, %d, %d}, grades = {%d, %d, %d}\n", r17, output_year, output_subjects[0], output_subjects[1], output_subjects[2], output_grades[0], output_grades[1], output_grades[2]);

    //! Test case 18
    /*!
        objective: test the return value of "SDB_ReadEntry()", if ID does not exist
        expected result: Read entry = 0, year = 0, subjects = {0, 0, 0}, grades = {0, 0, 0}
        status: passed
    */
    uint8 output_year18 = 0;
    uint8 output_subjects18[3] = {0};
    uint8 output_grades18[3]   = {0};
    bool r18 = SDB_ReadEntry(36, &output_year, output_subjects, output_grades);
    printf("Test case 18: Read entry = %d, year = %d, subjects = {%d, %d, %d}, grades = {%d, %d, %d}\n", r18, output_year18, output_subjects18[0], output_subjects18[1], output_subjects18[2], output_grades18[0], output_grades18[1], output_grades18[2]);

    //! Test case 19
    /*!
        objective: test the return value of "SDB_GetIdList()"
        expected result: count = 3, list = {146, 105, 101}
        status: passed
    */
    clearDB();
    SDB_AddEntry(101, 22, course_IDs[0], grades[0]);
    SDB_AddEntry(105, 19, course_IDs[1], grades[1]);
    SDB_AddEntry(146, 20, course_IDs[2], grades[2]);

    uint8 count  = 0;
    uint8 IDs[3] = {0};
    SDB_GetIdList(&count, IDs);
    printf("Test case 19: count = %d, list = {%d, %d, %d}\n", count, IDs[0], IDs[1], IDs[2]);

    //! Test case 20
    /*!
        objective: test the return value of "SDB_IsIdExist()", if ID exist
        expected result: 1
        status: passed
    */
    printf("Test case 20: Is ID exist = %d\n", SDB_IsIdExist(101));

    //! Test case 21
    /*!
        objective: test the return value of "SDB_IsIdExist()", if ID does not exist
        expected result: 0
        status: passed
    */
    printf("Test case 21: Is ID exist = %d\n", SDB_IsIdExist(108));
#endif // TestCases
