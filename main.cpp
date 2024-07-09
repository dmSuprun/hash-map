#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;
const double constVal = (sqrt(5) - 1) / 2;


template<typename keyType, typename valType>
struct HashMap {
    struct listNode {
        keyType keyVal;
        valType data;
        listNode *next;

        listNode(keyType keyVal, valType value) {
            this->keyVal = keyVal;
            this->data = value;
            next = nullptr;

        }
    };

    int tableSize;
    int numAddedEl;
    listNode **arrayPointer;


    HashMap(int size) {
        this->tableSize = size;
        arrayPointer = new listNode *[size];
        for (int i = 0; i < size; i++) {
            arrayPointer[i] = nullptr;
        }
        numAddedEl = 0;
    }


    int getHash(int key) {
        return abs((int) tableSize * ((key * constVal) - (int) (key * constVal)));

    }

    int getHash(double key) {
        return abs((int) (key * 10e+6) / tableSize);

    }

    int getHash(char key) {
        return abs((int)key % tableSize);

    }

    int getHash(string key) {
        unsigned long int hashSum = 0;
        for (int i = 0; i < key.size(); i++) {
            hashSum += getHash((int) key[i]);
        }
        return hashSum % tableSize;

    }

    void rellocMemory() {
        if ((numAddedEl / tableSize) >= 0.75) {
            listNode ** arrayPointerTemp;
            int newSize = tableSize*1.6;
            arrayPointerTemp = new listNode *[newSize];


        } else {
            return;
        }

    }

    int getMaxSize() {
        return tableSize;
    }

    int getSize() {
        return numAddedEl;

    }

    void addEllement(keyType key, valType value) {
        int index = getHash(key);
        listNode *t = arrayPointer[index];
        if (t) {
            while (t->next) {
                t = t->next;
            }
            t->next = new listNode(key, value);
            numAddedEl++;

        } else {
            arrayPointer[index] = new listNode(key, value);
            numAddedEl++;
        }


    }

    listNode *get(keyType key) {
        int index = getHash(key);
        listNode *temp = arrayPointer[index];
        while ((temp->keyVal != key) && temp->next) {
            temp = temp->next;
        }
        return temp;

    }

    valType getVal(keyType key) {
        return get(key)->data;
    }

    void update(keyType key, valType newVal) {
        listNode *node = get(key);
        if (node) {
            node->data = newVal;

        } else {
            cout << "fff";
            addEllement(key, newVal);
        }
    }

    void destroyMap() {
        for (int i = 0; i < tableSize; i++) {
            listNode *t = arrayPointer[i];
            while (t) {
                arrayPointer[i] = arrayPointer[i]->next;
                delete t;
                t = arrayPointer[i];
            }
        }
        delete[] arrayPointer;


    }

    void view() {
        for (int i = 0; i < tableSize; i++) {
            listNode *t = arrayPointer[i];
            cout << i << ": ";
            while (t) {
                cout << t->data << " ";
                t = t->next;
            }
            cout << endl;


        }
    }


    void testcase() {
        ifstream fin("C:\\Users\\Dima\\CLionProjects\\HashMap\\test.txt");
        valType dat;
        for (int i = 0; i < tableSize; i++) {
            fin >> dat;
            addEllement(i, dat);

        }
        fin.close();

    }

    void createTestMap() {
        string mas[] = {
                "apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew",
                "kiwi", "lemon", "mango", "nectarine", "orange", "papaya", "quince", "raspberry",
                "strawberry", "tangerine", "ugli", "vanilla", "watermelon", "xigua", "yam", "zucchini",
                "apricot", "blackberry", "cantaloupe", "dragonfruit", "eggplant", "feijoa", "guava", "huckleberry",
                "imbe", "jackfruit", "kumquat", "lime", "mulberry", "nectarine", "olive", "plum"
        };

        for (int i = 0; i < tableSize; i++) {
            addEllement(mas[i], mas[i]);

        }

    }


    ~HashMap() {
        if (arrayPointer) {
            destroyMap();
            arrayPointer = nullptr;
        }


    }
};


int main() {
    HashMap<unsigned char, string> map(1000);
    map.testcase();
    //map.update("petro", "dmytr");
//    cout<<map.getHash((char)300);
    map.view();

    return 0;
}
