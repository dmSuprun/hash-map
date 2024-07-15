#include <iostream>
#include <string>
#include "hashMapWithOpenAddressing.h"
using namespace std;


void testcase() {
    hashMapWithOpenAddressing<int , string >map(30);
    string values[] = {
            "apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew",
            "kiwi", "lemon", "mango", "nectarine", "orange", "papaya", "quince", "raspberry",
            "strawberry", "tangerine", "ugli", "vanilla", "watermelon", "xigua", "yam", "zucchini",
            "apricot", "blackberry", "cantaloupe", "dragonfruit", "eggplant", "feijoa", "guava", "huckleberry",
            "imbe", "jackfruit", "kumquat", "lime", "mulberry", "nectarine", "olive", "plum"
    };
    for(int i=0; i<30;i++){
        map.addElement( i, values[i]);
    }
    map.viewMap();


}


int main() {
       testcase();
        return 0;
    }