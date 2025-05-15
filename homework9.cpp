#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

//task 1.
//Write a template vector sorting function (std::vector). The sorting method for tasks 1 
//and 2 is selected according to the rule(option number) % 3:
//0 – bubble sorting
//1 – sorting by choice
//2 – sorting by inserts

//Bubble sorting function
template<typename T>
void bubbleSort(std::vector<T>& vec) 
{
    int n = vec.size();

    for (size_t i = 0; i < n - 1; i++) 
    {
        for (size_t j = 0; j < n - i - 1; j++) 
        {
            if (vec[j] > vec[j + 1]) 
            {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

//A function for sorting by selection
template<typename T>
void selectionSort(std::vector<T>& vec) 
{
    int n = vec.size();
    for (size_t i = 0; i < n; i++)
    {
        int min_idx = i;

        for (size_t j = i + 1; j < n; j++)
        {
            if (vec[j] < vec[min_idx]) 
            {
                min_idx = j;
            }
        }
        std::swap(vec[i], vec[min_idx]);
    }
}

//Function for sorting by inserts
template<typename T>
void insertionSort(std::vector<T>& vec) 
{

    int n = vec.size();
    for (size_t i = 1; i < n; i++)
    {
        T key = vec[i];
        int j = i - 1;

        while (j >= 0 && vec[j] > key) 
        {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }

}

//Template sorting function with method selection
template<typename T>
void sortVector(std::vector<T>& vec, int variant) 
{

    switch (variant % 3) 
    {
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
        std::cerr << "Error...";
        break;
    }
}

// Using example
void task1() 
{
    std::vector<int> numbers = { 5, 2, 8, 1, 9, 3 };
    int variant = 2; // Example of an option number

    std::cout << "Source array: ";
    for (int num : numbers) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    sortVector(numbers, variant);

    std::cout << "Sorted array: ";

    //outputting the sorted array
    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    
    std::cout << std::endl;
}

//Task 2. 
//In the file input.txt contains information about a group of students in the format :
//— number of students;
//— the record of each student in the group contains the following information : last name, first name, patronymic, date of birth, grades in five subjects.
//Save information about students in structures.
//Overwrite file data input.txt to the file output.txt by sorting them :
//8)by date of birth in ascending order.

// Structure for storing student data
struct Student 
{
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    std::string birthDate;
    std::vector<int> grades;
};

// Function for comparing dates of birth
bool isMore(const std::string& date1, const std::string& date2) 
{
    // Breaking the date into parts
    std::istringstream ss1(date1);
    std::istringstream ss2(date2);

    int day1, month1, year1;
    int day2, month2, year2;
    char dash;

    ss1 >> year1 >> dash >> month1 >> dash >> day1;
    ss2 >> year2 >> dash >> month2 >> dash >> day2;

    // Comparing dates
    if (year1 != year2) 
    {
        return year1 < year2;
    }

    if (month1 != month2) 
    {
        return month1 < month2;
    }
    
    return day1 < day2;
}

// Function for bubble sorting
void bubbleSort(std::vector<Student>& students) 
{

    for (size_t i = 0; i < students.size(); i++) 
    {
        for (size_t j = 0; j < students.size() - i - 1; j++) 
        {

            if (!isMore(students[j].birthDate, students[j + 1].birthDate)) 
            {
                std::swap(students[j], students[j + 1]);
            }
        }
    }
}

// Function for sorting by selection
void selectionSort(std::vector<Student>& students) 
{
    for (size_t i = 0; i < students.size(); i++) 
    {
        size_t min_idx = i;

        for (size_t j = i + 1; j < students.size(); j++) 
        {

            if (isMore(students[j].birthDate, students[min_idx].birthDate)) 
            {
                min_idx = j;
            }
        }
        std::swap(students[i], students[min_idx]);
    }
}

// Function for sorting by inserts
void insertionSort(std::vector<Student>& students) 
{
    for (size_t i = 1; i < students.size(); i++) 
    {
        Student key = students[i];
        size_t j = i - 1;

        while (j >= 0 && !isMore(students[j].birthDate, key.birthDate)) 
        {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = key;
    }
}

void task2() 
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    if (!in.is_open()) 
    {
        std::cerr << "File opening error input.txt!\n";
    }

    size_t count;
    in >> count;
    in.ignore(); //Skipping the newline character
    
    //Checking for an invalid value
    if (count == static_cast<size_t>(-1)) {
        std::cerr << "Error: unacceptable number of students!!!\n";
    }
    
    std::vector<Student> students(count);

    //reading the data of all students
    for (int i = 0; i < count; i++) 
    {
        out << student.lastName << " ";
        out << student.firstName << " ";
        out << student.patronymic << " ";
        out << student.birthDate << " ";

        for (int j = 0; j < 5; j++) 
        {
            int grade;
            in >> grade;

            students[i].grades.push_back(grade);

            if (j < 4) 
            {
                in.ignore(); //Skipping the separators
            }
        }
        in.ignore(); //Skipping the newline character
    }

    //Choosing a sorting method
    int variant = 2; //Option number

    switch (variant % 3) 
    { 
    case 0: 
        bubbleSort(students); 
        break;

    case 1: 
        selectionSort(students); 
        break;

    case 2: 
        insertionSort(students); 
        break;
    }

    // Writing sorted data
    out << count << "\n";
    
    for (const auto& student : students) {
        out << student.lastName << ";";
        out << student.firstName << ";";
        out << student.patronymic << ";";
        out << student.birthDate << ";";

        for (size_t j = 0; j < student.grades.size(); j++) {
            out << student.grades[j];
            if (j < 4) {
                out << " ";
            }
        }
        out << "\n";
    }
    in.close();
    out.close();
}

int main()
{

    task1();
    task2();

    return 0;
}
