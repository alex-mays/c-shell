#include <iostream>
#include <thread>
#include <time.h>

using namespace std;

// Readers and Writers Data
int numReaders, numWriters;
void reader(int rank);
void writer(int rank);

// The data structure they read and write
int myMoney[11]; // myMoney[10] = sum of myMoney[0-9]

int main(int c, char *argv[]) {
  // Read the commandline arguments
  numReaders = atoi(argv[1]);
  numWriters = atoi(argv[2]);
  cout << numReaders << " readers, " << numWriters << " writers." << endl;

  // Array to hold the thread objects
  thread readers[numReaders];
  thread writers[numWriters];

  // Create and launch the readers and writers
  srand(time(NULL)); // seed the random number generator
  int i;
  for (i = 0; i < numReaders; i++) {
    readers[i] = thread(reader, i);
  }
  for (i = 0; i < numWriters; i++) {
    writers[i] = thread(writer, i);
  }

  printf("Main Thread\n");

  // Wait for the threads to finish
  for (i = 0; i < numReaders; i++) {
    readers[i].join();
    // cout << "Reader #" << i << " done." << endl;
  }

  for (i = 0; i < numWriters; i++) {
    writers[i].join();
    // cout << "Writer #" << i << " done." << endl;
  }
}

// This is the "main" function for the reader threads
// Each reader checks for consistency 100 times
void reader(int rank) {
  for (int i = 0; i < 100; i++) {
    // Check consistency
    int sum = 0;
    for (int i = 0; i < 10; i++)
      sum += myMoney[i];
    if (sum != myMoney[10])
      cout << "Violation!!! by reader " << rank << endl;
    int sleeptime = rand() % 20; // sleep for up to 20ms
    this_thread::sleep_for(chrono::milliseconds(sleeptime));
  }
}

// This is the "main" function for the writer threads
// Each writer adds money 9 times
void writer(int rank) {
  for (int i = 0; i < 9; i++) {
    int sum = 0;
    for (int i = 0; i < 10; i++) {
      int deposit = rand() % 10;
      myMoney[i] += deposit;
      sum += deposit;
      this_thread::sleep_for(chrono::milliseconds(rand() % 10));
    }
    myMoney[10] += sum;

    int sleeptime = rand() % 1000;
    this_thread::sleep_for(chrono::milliseconds(sleeptime));
  }
}
