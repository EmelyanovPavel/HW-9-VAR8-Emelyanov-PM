#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

//task 1.
//Bubble sorting function
template<typename T>
void bubbleSort(std::vector<T>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

//A function for sorting by selection
template<typename T>
void selectionSort(std::vector<T>& vec) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(vec[i], vec[min_idx]);
    }
}

//Function for sorting by inserts
template<typename T>
void insertionSort(std::vector<T>& vec) {
    int n = vec.size();
    for (int i = 1; i < n; i++) {
        T key = vec[i];
        int j = i - 1;

        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}

//Template sorting function with method selection
template<typename T>
void sortVector(std::vector<T>& vec, int variant) {

    switch (variant % 3) {
    case 0:
        bubbleSort(vec);
        break;
    case 1:
        selectionSort(vec);
        break;
    case 2:
        insertionSort(vec);
        break;
    default:
        std::cerr << "Error..." << std::endl;
        break;
    }
}

// Using example
void task1() {
    std::vector<int> numbers = { 5, 2, 8, 1, 9, 3 };
    int variant = 0; // Example of an option number

    std::cout << "Source array: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    sortVector(numbers, variant);

    std::cout << "Sorted array: ";

    //outputting the sorted array
    for (int num : numbers) {
        std::cout << num << " ";
    }
}
//Task 2. 
//In the file input.txt contains information about a group of students in the format :
//— number of students;
//— the record of each student in the group contains the following information : last name,
//first name, patronymic, date of birth, grades in five subjects.
//Save information about students in structures.
//Overwrite file data input.txt to the file output.txt by sorting them :
//8)by date of birth in ascending order.

//Structure for storing student data
struct Student {
    std::string surname;    // surname
    std::string name;      // name
    std::string patronymic;// middle name
    std::string birthDate; // Birth date (format - dd.mm.yyyy)
    std::vector<int> grades;// Grades in 5 subjects
};

//Function for comparing dates of birth
bool compareByDate(const Student& a, const Student& b) {
    return a.birthDate < b.birthDate;
}

void task2() {
    //opening files
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    if (!in.is_open()) {
        std::cout << "Error opening input.txt file" << std::endl;
        
    }

    if (!out.is_open()) {
        std::cout << "Error opening output.txt file" << std::endl;
       
    }

    //Read a students number
    int studentCount;
    in >> studentCount;

    // Creating a vector for storing students
    std::vector<Student> students(studentCount);

    //  read the data of all students
    for (int i = 0; i < studentCount; i++) {
        in >> students[i].surname;
        in >> students[i].name;
        in >> students[i].patronymic;
        in >> students[i].birthDate;

        // read a grades
        for (int j = 0; j < 5; j++) {
            int grade;
            in >> grade;
            students[i].grades.push_back(grade);
        }
    }

    // Sorting students by date of birth
    std::sort(students.begin(), students.end(), compareByDate);

    // Writing the sorted data to output.txt
    out << studentCount << std::endl;

    for (const auto& student : students) {
        out << student.surname << " ";
        out << student.name << " ";
        out << student.patronymic << " ";
        out << student.birthDate << " ";

        for (int grade : student.grades) {
            out << grade << " ";
        }
        out << std::endl;
    }

    // Closing files
    in.close();
    out.close();

    
}

int main()
{
    task1();
    task2();

    return 0;
}
