#include <iostream>
using namespace std;

const int RESIZE_FACTOR = 2;
const float SHRINK_LIMIT = 4;

class MattsVector {
    private:
    int size;
    int capacity;
    // This is a pointer to the first element in the array.
    // Need to rework this class taking this into account.
    int* currentArray;

    void resizeIfNeeded() {
        if (size == 0) {
            return;
        }

        if (size == capacity) {
            int newCapacity = capacity * RESIZE_FACTOR;
            int* newArray = new int[newCapacity];
            
            for (int i = 0; i < size; i++) {
                newArray[i] = currentArray[i];
            }

            delete[] currentArray;

            currentArray = newArray;
            capacity = newCapacity;
        } else if ((size * SHRINK_LIMIT) < capacity) {
            int newCapacity = capacity / RESIZE_FACTOR;
            int* newArray = new int[newCapacity];

            for (int i = 0; i < size; i++) {
                newArray[i] = currentArray[i];
            }

            delete[] currentArray;

            currentArray = newArray;
            capacity = newCapacity;
        }
    }

    public:
    MattsVector() {
        size = 0;
        capacity = 2;
        currentArray = new int[capacity];
    }
    ~MattsVector() {
        delete[] currentArray;
    }

    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }

    int isEmpty() {
        return size == 0;
    }

    int get(int index) {
        return currentArray[index];
    }

    void push(int item) {
        resizeIfNeeded();

        size++;

        currentArray[size - 1] = item;
    }

    void insert(int index, int item) {
        if (index == 0) {
            prepend(item);
            return;
        }

        if (index == size) {
            push(item);
            return;
        }

        resizeIfNeeded();
        size++;

        for (int i = size - 1; i >= index; i--) {
            currentArray[i] = currentArray[i - 1];
        }

        currentArray[index] = item;
    }

    void prepend(int item) {
        resizeIfNeeded();
        size++;

        for (int i = size - 1; i > 0; i--) {
            currentArray[i] = currentArray[i - 1];
        }

        currentArray[0] = item;
    }

    int pop() {
        size--;
        return currentArray[size];
    }

    void deleteIndex(int index) {
        size--;

        if (index == size) {
            return;
        }

        for (int i = index; i < size; i++) {
            currentArray[i] = currentArray[i + 1];
        }

        resizeIfNeeded();
    }

    void removeItem(int item) {
        int itemsFound = 0;
        for (int i = 0; i + itemsFound < size; i++) {
            while (currentArray[i + itemsFound] == item) {
                itemsFound++;
            }
            currentArray[i] = currentArray[i + itemsFound];
        }
        size -= itemsFound;
        resizeIfNeeded();
    }

    int find(int item) {
        for (int i = 0; i < size; i++) {
            if (currentArray[i] == item) {
                return i;
            }
        }

        return -1;
    }
};

class TestCases {
    int failedTests;
    int passedTests;

    public:
    TestCases() {
        failedTests = 0;
        passedTests = 0;
    }

    void runTestCases() {
        cout << "Starting Test Suite Run" << endl << endl;

        testPushAndResize();
        testInsertAndPrependAndResize();
        testPop();
        testDeleteAndResize();
        testRemoveItemAndResize();
        testFindItem();

        cout << endl << "Failed Test Count: " << failedTests << endl;
        cout << "Passed Test Count: " << passedTests << endl;
        cout << "Total Test Count: " << failedTests + passedTests << endl;
    }

    private:
    void testPushAndResize() {
        MattsVector testVector;

        testVector.push(1);
        testVector.push(6);
        testVector.push(3);

        // [1, 6, 3]
        bool isCapacityCorrect = testVector.getCapacity() == 4;
        bool isSizeCorrect = testVector.getSize() == 3;
        bool isOrderCorrect = testVector.get(0) == 1 && testVector.get(1) == 6 && testVector.get(2) == 3;
    
        if (isCapacityCorrect && isSizeCorrect && isOrderCorrect) {
            passedTests++;
            cout << "Test push and resize PASSED" << endl;
        } else {
            failedTests++;
            cout << "Test push and resize FAILED" << endl;
        }
    }

    void testInsertAndPrependAndResize() {
        MattsVector testVector;

        testVector.push(5);
        testVector.push(7); 
        testVector.push(9);

        testVector.insert(0, 1);
        testVector.insert(4, 5);
        testVector.insert(2, 4);

        // [1, 5, 4, 7, 9 , 5]
        bool isCapacityCorrect = testVector.getCapacity() == 8;
        bool isSizeCorrect = testVector.getSize() == 6;
        bool isOrderCorrect = testVector.get(0) == 1 && testVector.get(1) == 5 && testVector.get(2) == 4 && testVector.get(3) == 7 && testVector.get(4) == 9 && testVector.get(5) == 5;

        if (isCapacityCorrect && isSizeCorrect && isOrderCorrect) {
            passedTests++;
            cout << "Test insert and prepend and resize PASSED" << endl;
        } else {
            failedTests++;
            cout << "Test insert and prepend and resize FAILED" << endl;
        }
    }

    void testPop() {
        MattsVector testVector;

        testVector.push(4);
        testVector.push(1);
        testVector.push(5);
        testVector.push(3);

        int firstPop = testVector.pop();
        int secondPop = testVector.pop();
        int thirdPop = testVector.pop();
        int fourthPop = testVector.pop();

        if (firstPop == 3 && secondPop == 5 && thirdPop == 1 && fourthPop == 4) {
            passedTests++;
            cout << "Test pop PASSED" << endl;
        } else {
            failedTests++;
            cout << "Test pop FAILED" << endl;
        }
    }

    void testDeleteAndResize() {
        MattsVector testVector;

        testVector.push(4);
        testVector.push(8);
        testVector.push(3);
        testVector.push(1);
        testVector.push(2);
        testVector.push(9);
        testVector.push(10);
        testVector.push(12);
        testVector.push(120);

        testVector.deleteIndex(0);
        testVector.deleteIndex(1);
        testVector.deleteIndex(4);
        testVector.deleteIndex(1);
        testVector.deleteIndex(2);
        testVector.deleteIndex(1);
        testVector.deleteIndex(2);

        // [8, 12]

        bool isCapacityCorrect = testVector.getCapacity() == 8;
        bool isSizeCorrect = testVector.getSize() == 2;
        bool isOrderCorrect = testVector.get(0) == 8 && testVector.get(1) == 12;

        if (isCapacityCorrect && isSizeCorrect && isOrderCorrect) {
            passedTests++;
            cout << "Test delete index and resize PASSED" << endl;
        } else {
            failedTests++;
            cout << "Test delete index and resize FAILED" << endl;
        }
    }

    void testRemoveItemAndResize() {
        MattsVector testVector;

        testVector.push(4);
        testVector.push(8);
        testVector.push(4);
        testVector.push(3);
        testVector.push(9);
        testVector.push(9);
        testVector.push(10);
        testVector.push(12);
        testVector.push(9);

        testVector.removeItem(9);
        testVector.removeItem(4);
        testVector.removeItem(10);
        testVector.removeItem(3);

        // [8, 12]

        bool isCapacityCorrect = testVector.getCapacity() == 8;
        bool isSizeCorrect = testVector.getSize() == 2;
        bool isOrderCorrect = testVector.get(0) == 8 && testVector.get(1) == 12;

        if (isCapacityCorrect && isSizeCorrect && isOrderCorrect) {
            passedTests++;
            cout << "Test remove item and resize PASSED" << endl;
        } else {
            failedTests++;
            cout << "Test remove item and resize FAILED" << endl;
        }
    }

    void testFindItem() {
        MattsVector testVector;

        testVector.push(4);
        testVector.push(8);
        testVector.push(4);
        testVector.push(3);
        testVector.push(9);
        testVector.push(9);
        testVector.push(10);
        testVector.push(12);
        testVector.push(123);

        int isFirstElementCorrect = testVector.find(4) == 0;
        int isLastElementCorrect = testVector.find(123) == 8;
        int isMiddleElementCorrect = testVector.find(3) == 3;
        int isNotPresentElementCorrect = testVector.find(0) == -1;

        if (isFirstElementCorrect && isLastElementCorrect && isMiddleElementCorrect && isNotPresentElementCorrect) {
            passedTests++;
            cout << "Test find item PASSED" << endl;
        } else {
            failedTests++;
            cout << "Test find item FAILED" << endl;
        }
    }
};

int main() {
    cout << "Welcome To Matts Vector Testing Ground" << endl;

    TestCases testCases;
    testCases.runTestCases();

    return 0;
}
