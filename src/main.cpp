#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Print array values.
void printArray(const int data[], int size, const string& label) {
    cout << "\n" << label << " (size=" << size << "): ";
    for (int i = 0; i < size; ++i) {
        cout << data[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << "\n";
}

// Copy one array into another.
void copyArray(const int source[], int destination[], int size) {
    for (int i = 0; i < size; ++i) {
        destination[i] = source[i];
    }
}

// Sort array in ascending order (selection sort).
void selectionSort(int data[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        int smallestIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (data[j] < data[smallestIndex]) {
                smallestIndex = j;
            }
        }

        if (smallestIndex != i) {
            int temp = data[i];
            data[i] = data[smallestIndex];
            data[smallestIndex] = temp;
        }
    }
}

// Mean = sum / size.
double computeMean(const int data[], int size) {
    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }
    return static_cast<double>(sum) / size;
}

// Median from sorted array.
double computeMedian(const int sortedData[], int size) {
    if (size % 2 == 1) {
        return sortedData[size / 2];
    }

    int rightMiddle = size / 2;
    int leftMiddle = rightMiddle - 1;
    return (sortedData[leftMiddle] + sortedData[rightMiddle]) / 2.0;
}

// Range = max - min.
int computeRange(const int sortedData[], int size) {
    return sortedData[size - 1] - sortedData[0];
}

// Sample variance uses (n - 1).
double computeSampleVariance(const int data[], int size, double mean) {
    if (size < 2) {
        return 0.0;
    }

    double sumSquaredDiff = 0.0;
    for (int i = 0; i < size; ++i) {
        double diff = data[i] - mean;
        sumSquaredDiff += diff * diff;
    }

    return sumSquaredDiff / (size - 1);
}

// Standard deviation = sqrt(variance).
double computeSampleStdDev(double variance) {
    return sqrt(variance);
}

// Find mode(s) using a 2D value-frequency table.
void printModes(const int data[], int size) {
    int** modeTable = new int*[2];
    modeTable[0] = new int[size];
    modeTable[1] = new int[size];

    int filled = 0;

    for (int i = 0; i < size; ++i) {
        int currentValue = data[i];
        int foundIndex = -1;

        for (int j = 0; j < filled; ++j) {
            if (modeTable[0][j] == currentValue) {
                foundIndex = j;
                break;
            }
        }

        if (foundIndex >= 0) {
            modeTable[1][foundIndex] += 1;
        } else {
            modeTable[0][filled] = currentValue;
            modeTable[1][filled] = 1;
            filled += 1;
        }
    }

    int maxFrequency = modeTable[1][0];
    for (int i = 1; i < filled; ++i) {
        if (modeTable[1][i] > maxFrequency) {
            maxFrequency = modeTable[1][i];
        }
    }

    // If all frequencies are the same, there is no mode.
    bool allFrequenciesSame = true;
    for (int i = 1; i < filled; ++i) {
        if (modeTable[1][i] != modeTable[1][0]) {
            allFrequenciesSame = false;
            break;
        }
    }

    cout << "Mode: ";
    if (allFrequenciesSame) {
        cout << "[None]";
    } else {
        for (int i = 0; i < filled; ++i) {
            if (modeTable[1][i] == maxFrequency) {
                cout << "[" << modeTable[0][i] << "]";
            }
        }
    }
    cout << "\n";

    delete[] modeTable[0];
    delete[] modeTable[1];
    delete[] modeTable;
}

int main() {

    cout << "Descriptive Statistics Calculator\n";
    cout << "--------------------------------\n";

    // Ask for a valid size.
    int size = 0;
    while (size <= 0) {
        cout << "Enter number of data points: ";
        cin >> size;

        if (size <= 0) {
            cout << "Please enter a positive integer.\n";
        }
    }

    // Create main dataset.
    int* dataset = new int[size];

    // Input data values.
    cout << "\nEnter " << size << " integer values:\n";
    for (int i = 0; i < size; ++i) {
        cout << "d[" << i << "]: ";
        cin >> dataset[i];
    }

    // Copy and sort the copy.
    int* sortedCopy = new int[size];
    copyArray(dataset, sortedCopy, size);
    selectionSort(sortedCopy, size);

    // Show both arrays.
    printArray(dataset, size, "Original dataset");
    printArray(sortedCopy, size, "Sorted copy");

    // Compute statistics.
    double mean = computeMean(dataset, size);
    double median = computeMedian(sortedCopy, size);
    int range = computeRange(sortedCopy, size);
    double variance = computeSampleVariance(dataset, size, mean);
    double stdDev = computeSampleStdDev(variance);

    // Print with 4 decimal places.
    cout << fixed << setprecision(4);
    cout << "\nMean: " << mean << "\n";
    cout << "Median: " << median << "\n";
    cout << "Range: " << range << "\n";
    if (size < 2) {
        cout << "Sample Variance: 0.0000 (requires at least 2 values)\n";
        cout << "Sample Standard Deviation: 0.0000 (requires at least 2 values)\n";
    } else {
        cout << "Sample Variance: " << variance << "\n";
        cout << "Sample Standard Deviation: " << stdDev << "\n";
    }

    // Print mode(s).
    printModes(sortedCopy, size);

    // Free memory.
    delete[] dataset;
    delete[] sortedCopy;

    return 0;
}
