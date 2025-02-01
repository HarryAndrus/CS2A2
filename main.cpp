#include <algorithm>
#include <iostream>

using namespace std;

// Function prototypes
float median(int *arr, int size);
int mean(const int *arr, int size);
int mode(int *arr, int size);
int *makeArray(int size);
void getMovieData(int arr[], int numStudents);

int main() {
  int numStudents = 0;
  int *students = nullptr;
  int count = 0;

  cout << "How many students were surveyed? " << endl;
  cin >> numStudents;
  students = makeArray(numStudents);
  getMovieData(students, numStudents);

  cout << "mean: " << mean(students, numStudents) << endl;
  cout << "median: " << median(students, numStudents) << endl;
  cout << "mode: " << mode(students, numStudents) << endl;

  delete[] students;
  students = nullptr;

  return 0;
}

int *makeArray(int size) {
  int *ptr;

  if (size <= 0) {
    throw invalid_argument("Array size must be positive.");
  }

  ptr = new int[size];

  return ptr;
}

void getMovieData(int arr[], int numStudents) {
  for (int count = 0; count < numStudents; count++) {
    cout << "How many movies did Student " << count + 1 << " watch this month?"
         << endl;
    cin >> *(arr + count);
  }
}

float median(int *arr, int size) {
  int *sortedPtr = new int[size];
  copy(arr, arr + size, sortedPtr);
  sort(sortedPtr, sortedPtr + size);

  float median = (size % 2 == 0)
                     ? static_cast<float>(*(sortedPtr + (size / 2 - 1)) +
                                          *(sortedPtr + (size / 2)) / 2.0)
                     : static_cast<float>(*(sortedPtr + (size / 2)));

  delete[] sortedPtr;
  sortedPtr = nullptr;

  return median;
}

int mean(const int *arr, int size) {
  float mean = 0;

  for (int i = 0; i < size; i++) {
    mean += *(arr + i);
  }

  return (mean / size);
}

int mode(int *arr, int size) {
  int *freq = nullptr;
  int highest = 0;
  int elem = 0;
  int count = 0;
  int result = 0;

  // Dynamically allocate an array to hold frequencies of each element in arr.
  freq = makeArray(size);

  for (count = 0; count < size; count++) {
    *(freq + count) = 0;
  }

  // Find Frequency of each element in arr.
  for (int count1 = 0; count1 < size; count1++) {
    for (int count2 = 0; count2 < size; count2++) {
      if (*(arr + count2) == *(arr + count1)) {
        (*(freq + count1))++;
      }
    }
  }

  // Find the element with the highest frequency.
  highest = *freq;
  elem = 0;

  for (count = 1; count < size; count++) {
    if (*(freq + count) > highest) {
      highest = *(freq + count);
      elem = count;
    }
  }

  // If there is no mode no element has a frequency > 1, return -1.
  // Otherwise return element with the highest frequency
  if (highest == 1) {
    result = -1;
  } else {
    result = *(arr + elem);
  }

  delete[] freq;
  freq = nullptr;

  return result;
}