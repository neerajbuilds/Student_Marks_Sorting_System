/*
 * ============================================================
 *  Student Marks Sorting System
 *  Course  : Design and Analysis of Algorithms (DAA)
 *  Language: C++
 * ============================================================
 *
 *  Features:
 *    1. Enter student names and marks
 *    2. Display all student records
 *    3. Sort students by marks using Bubble Sort
 *    4. Sort students by marks using Quick Sort
 *    5. Search a student by name (Linear Search)
 *    6. Display highest and lowest marks
 *    7. Measure and display time taken by each sort
 *
 *  Menu Options:
 *    1. Display Students
 *    2. Bubble Sort by Marks
 *    3. Quick Sort by Marks
 *    4. Search Student
 *    5. Highest Marks
 *    6. Lowest Marks
 *    7. Exit
 * ============================================================
 */

#include <iostream>   // For input/output
#include <string>     // For string handling
#include <chrono>     // For measuring time
#include <algorithm>  // For std::swap
#include <iomanip>    // For setw() formatting

using namespace std;
using namespace std::chrono;

// ============================================================
//  STRUCTURE: Student
//  Holds the name and marks of one student
// ============================================================
struct Student {
    string name;   // Student's full name
    float  marks;  // Marks obtained (out of 100)
};

// ============================================================
//  CONSTANTS
// ============================================================
const int MAX_STUDENTS = 100;  // Maximum number of students allowed

// ============================================================
//  GLOBAL ARRAY & COUNT
// ============================================================
Student students[MAX_STUDENTS];  // Array to store all students
int     totalStudents = 0;       // Tracks how many students are entered

// ============================================================
//  FUNCTION PROTOTYPES (declarations)
// ============================================================
void    inputStudents();
void    displayStudents(Student arr[], int n);
void    bubbleSort(Student arr[], int n);
void    quickSort(Student arr[], int low, int high);
int     partition(Student arr[], int low, int high);
int     linearSearch(Student arr[], int n, const string& name);
void    findHighestMarks(Student arr[], int n);
void    findLowestMarks(Student arr[], int n);
void    copyArray(Student src[], Student dest[], int n);
void    printDivider();

// ============================================================
//  MAIN FUNCTION – Menu-Driven Interface
// ============================================================
int main() {

    cout << "\n";
    cout << "  =====================================================\n";
    cout << "       STUDENT MARKS SORTING SYSTEM                   \n";
    cout << "       Design and Analysis of Algorithms (DAA)        \n";
    cout << "  =====================================================\n\n";

    // Step 1: Get student data from user
    inputStudents();

    if (totalStudents == 0) {
        cout << "\n  No students entered. Exiting program.\n";
        return 0;
    }

    int choice;

    // ---- Menu Loop ----
    do {
        printDivider();
        cout << "\n  MAIN MENU\n";
        printDivider();
        cout << "  1. Display Students\n";
        cout << "  2. Bubble Sort by Marks\n";
        cout << "  3. Quick Sort by Marks\n";
        cout << "  4. Search Student by Name\n";
        cout << "  5. Highest Marks\n";
        cout << "  6. Lowest Marks\n";
        cout << "  7. Exit\n";
        printDivider();
        cout << "  Enter your choice: ";
        cin  >> choice;
        cin.ignore();  // Clear newline from buffer

        switch (choice) {

            // --------------------------------------------------
            case 1:  // Display all students
            // --------------------------------------------------
                cout << "\n  [Current Student Records]\n";
                displayStudents(students, totalStudents);
                break;

            // --------------------------------------------------
            case 2:  // Bubble Sort
            // --------------------------------------------------
            {
                // Work on a copy so original data is preserved
                Student temp[MAX_STUDENTS];
                copyArray(students, temp, totalStudents);

                // Start timer
                auto start = high_resolution_clock::now();

                bubbleSort(temp, totalStudents);

                // Stop timer
                auto stop     = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n  [Students Sorted by Marks - Bubble Sort]\n";
                displayStudents(temp, totalStudents);
                cout << "\n  >> Time taken by Bubble Sort : "
                     << duration.count() << " microseconds\n";
            }
            break;

            // --------------------------------------------------
            case 3:  // Quick Sort
            // --------------------------------------------------
            {
                // Work on a copy so original data is preserved
                Student temp[MAX_STUDENTS];
                copyArray(students, temp, totalStudents);

                // Start timer
                auto start = high_resolution_clock::now();

                quickSort(temp, 0, totalStudents - 1);

                // Stop timer
                auto stop     = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "\n  [Students Sorted by Marks - Quick Sort]\n";
                displayStudents(temp, totalStudents);
                cout << "\n  >> Time taken by Quick Sort  : "
                     << duration.count() << " microseconds\n";
            }
            break;

            // --------------------------------------------------
            case 4:  // Linear Search by Name
            // --------------------------------------------------
            {
                string searchName;
                cout << "\n  Enter student name to search: ";
                getline(cin, searchName);

                int index = linearSearch(students, totalStudents, searchName);

                if (index != -1) {
                    cout << "\n  [Student Found]\n";
                    printDivider();
                    cout << "  Name  : " << students[index].name  << "\n";
                    cout << "  Marks : " << students[index].marks << "\n";
                    printDivider();
                } else {
                    cout << "\n  Student \"" << searchName
                         << "\" not found in records.\n";
                }
            }
            break;

            // --------------------------------------------------
            case 5:  // Highest Marks
            // --------------------------------------------------
                findHighestMarks(students, totalStudents);
                break;

            // --------------------------------------------------
            case 6:  // Lowest Marks
            // --------------------------------------------------
                findLowestMarks(students, totalStudents);
                break;

            // --------------------------------------------------
            case 7:  // Exit
            // --------------------------------------------------
                cout << "\n  Thank you! Exiting the program.\n\n";
                break;

            // --------------------------------------------------
            default:
            // --------------------------------------------------
                cout << "\n  Invalid choice. Please enter a number 1-7.\n";
        }

    } while (choice != 7);

    return 0;
}

// ============================================================
//  FUNCTION: inputStudents
//  Purpose : Takes student name and marks from the user
// ============================================================
void inputStudents() {
    cout << "  How many students do you want to enter? ";
    cin  >> totalStudents;

    // Validate count
    if (totalStudents <= 0 || totalStudents > MAX_STUDENTS) {
        cout << "  Invalid count. Must be between 1 and " << MAX_STUDENTS << ".\n";
        totalStudents = 0;
        return;
    }

    cin.ignore();  // Clear leftover newline from buffer

    cout << "\n  Enter student details below:\n";
    printDivider();

    for (int i = 0; i < totalStudents; i++) {
        cout << "  Student " << (i + 1) << ":\n";

        cout << "    Name  : ";
        getline(cin, students[i].name);  // Read full name with spaces

        cout << "    Marks : ";
        cin  >> students[i].marks;
        cin.ignore();  // Clear buffer after reading float

        // Validate marks range
        while (students[i].marks < 0 || students[i].marks > 100) {
            cout << "    [Error] Marks must be between 0 and 100. Re-enter: ";
            cin  >> students[i].marks;
            cin.ignore();
        }

        cout << "\n";
    }

    cout << "  Data entered successfully!\n";
}

// ============================================================
//  FUNCTION: displayStudents
//  Purpose : Prints a formatted table of student records
// ============================================================
void displayStudents(Student arr[], int n) {
    printDivider();
    cout << "  " << left << setw(5)  << "No."
                         << setw(25) << "Name"
                         << setw(10) << "Marks" << "\n";
    printDivider();

    for (int i = 0; i < n; i++) {
        cout << "  " << left << setw(5)  << (i + 1)
                             << setw(25) << arr[i].name
                             << setw(10) << arr[i].marks << "\n";
    }
    printDivider();
}

// ============================================================
//  FUNCTION: bubbleSort
//  Purpose : Sorts students by marks in ascending order
//
//  Algorithm - Bubble Sort:
//    Repeatedly compares adjacent elements and swaps them
//    if they are in the wrong order. The largest element
//    "bubbles up" to its correct position in each pass.
//
//  Time Complexity:
//    Best Case    : O(n)      - already sorted
//    Average Case : O(n^2)
//    Worst Case   : O(n^2)
//  Space Complexity: O(1)    - in-place sorting
// ============================================================
void bubbleSort(Student arr[], int n) {
    bool swapped;  // Optimization: stop early if already sorted

    for (int i = 0; i < n - 1; i++) {
        swapped = false;

        // Each pass moves the largest unsorted element to its place
        for (int j = 0; j < n - i - 1; j++) {
            // Compare adjacent elements
            if (arr[j].marks > arr[j + 1].marks) {
                // Swap if left element is greater than right
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no swaps were made in a pass, array is already sorted
        if (!swapped) break;
    }
}

// ============================================================
//  FUNCTION: partition
//  Purpose : Helper for Quick Sort – partitions array around pivot
//
//  How it works:
//    Chooses the LAST element as pivot.
//    Rearranges elements so all smaller elements are on the
//    left and larger elements are on the right of pivot.
//    Returns the final index of the pivot.
// ============================================================
int partition(Student arr[], int low, int high) {
    float pivot = arr[high].marks;  // Choose last element as pivot
    int   i     = low - 1;         // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j].marks <= pivot) {
            i++;                    // Move boundary of smaller elements
            swap(arr[i], arr[j]);   // Swap to put smaller element on left
        }
    }

    // Place pivot in its correct sorted position
    swap(arr[i + 1], arr[high]);
    return i + 1;  // Return pivot index
}

// ============================================================
//  FUNCTION: quickSort
//  Purpose : Sorts students by marks in ascending order
//
//  Algorithm - Quick Sort:
//    A divide-and-conquer algorithm.
//    Picks a pivot, partitions the array around it, then
//    recursively sorts the sub-arrays on either side.
//
//  Time Complexity:
//    Best Case    : O(n log n) - pivot always near middle
//    Average Case : O(n log n)
//    Worst Case   : O(n^2)    - pivot is always min or max
//  Space Complexity: O(log n) - recursive call stack
// ============================================================
void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        // Partition the array and get pivot index
        int pivotIndex = partition(arr, low, high);

        // Recursively sort elements before the pivot
        quickSort(arr, low, pivotIndex - 1);

        // Recursively sort elements after the pivot
        quickSort(arr, pivotIndex + 1, high);
    }
}

// ============================================================
//  FUNCTION: linearSearch
//  Purpose : Searches for a student by name
//
//  Algorithm - Linear Search:
//    Checks each element one by one from start to end.
//    Stops when a match is found or list is exhausted.
//
//  Time Complexity:
//    Best Case  : O(1)  - found at first position
//    Worst Case : O(n)  - found at last or not found
// ============================================================
int linearSearch(Student arr[], int n, const string& name) {
    for (int i = 0; i < n; i++) {
        // Case-sensitive name comparison
        if (arr[i].name == name) {
            return i;   // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}

// ============================================================
//  FUNCTION: findHighestMarks
//  Purpose : Finds and displays the student with highest marks
// ============================================================
void findHighestMarks(Student arr[], int n) {
    int maxIndex = 0;  // Assume first student has highest marks

    for (int i = 1; i < n; i++) {
        if (arr[i].marks > arr[maxIndex].marks) {
            maxIndex = i;  // Update index if higher marks found
        }
    }

    cout << "\n  [Student with Highest Marks]\n";
    printDivider();
    cout << "  Name  : " << arr[maxIndex].name  << "\n";
    cout << "  Marks : " << arr[maxIndex].marks << "\n";
    printDivider();
}

// ============================================================
//  FUNCTION: findLowestMarks
//  Purpose : Finds and displays the student with lowest marks
// ============================================================
void findLowestMarks(Student arr[], int n) {
    int minIndex = 0;  // Assume first student has lowest marks

    for (int i = 1; i < n; i++) {
        if (arr[i].marks < arr[minIndex].marks) {
            minIndex = i;  // Update index if lower marks found
        }
    }

    cout << "\n  [Student with Lowest Marks]\n";
    printDivider();
    cout << "  Name  : " << arr[minIndex].name  << "\n";
    cout << "  Marks : " << arr[minIndex].marks << "\n";
    printDivider();
}

// ============================================================
//  FUNCTION: copyArray
//  Purpose : Copies one Student array into another
//            Used to keep original data intact while sorting
// ============================================================
void copyArray(Student src[], Student dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];  // Copy each student record
    }
}

// ============================================================
//  FUNCTION: printDivider
//  Purpose : Prints a visual separator line for readability
// ============================================================
void printDivider() {
    cout << "  ----------------------------------------------------\n";
}
