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
  int mode = 0;

  cout << "How many students were surveyed? " << endl;
  cin >> numStudents;
  students = makeArray(numStudents);
  getMovieData(students, numStudents);

  cout << "mean: " << mean(students, numStudents) << endl;
  cout << "median: " << median(students, numStudents) << endl;
  const int mod = mode(students, numStudents);
  mod != -1 ? cout << "mode: " << to_string(mod) : "The data set has no mode."  << endl;

  delete[] students;
  students = nullptr;

  return 0;
}

int *makeArray(int size) {
  if (size <= 0) {
    throw invalid_argument("Array size must be positive.");
  }

  int* ptr = new int[size]();

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

int mode(int const *arr, int const size) {
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

  // for each index in arr
  for (int count1 = 0; count1 < size; count1++) {
    // for each index in arr, compare against all other indexes
    for (int count2 = 0; count2 < size; count2++) {
      // if values are equal, increment the index using count1
      if (*(arr + count2) == *(arr + count1)) {
        (*(freq + count1))++;
      }
    }
  }

  // highest = freq[0]
  highest = *freq;

  // for index in freq where freq[0] is initially compared
  for (count = 1; count < size; count++) {
    // if value at index is greater than value at index 0
    if (*(freq + count) > highest) {
      // highest frequency is the index with the greater value, index store in elem
      highest = *(freq + count);
      elem = count;
    }
  }

  delete[] freq;
  freq = nullptr;

  // If there is no mode no element has a frequency > 1, return -1.
  // Otherwise return element with the highest frequency
  return (highest == 1) ? result = -1 : result = *(arr + elem);
}