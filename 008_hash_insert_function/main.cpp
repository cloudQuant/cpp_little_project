#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>

int insert(int value, std::vector<int> &table) {
    // Code to insert value into a hashed location in table
    // where table is a vector of length 1000.
    // Returns the number of collisions encountered when
    // trying to insert value into table.
    int num = 0;
    int index = value%1000;
    // std::cout << "value = " << value << " index = " << index <<" now_index_value =" <<table[index];
    for (int i=index;i<1000;i++){
        if (table[i]==-1){
            table[i]=value;
            //std::cout << " location = " << i << " num = " << num << std::endl;
            return num;
        }else{
            num++;
        }
    }
    for (int i=0;i<index;i++){
        if (table[i]==-1){
            table[i]=value;
            //std::cout << "index = " << index <<" now_index_value =" <<table[index]
            std::cout << "second run" << std::endl;
            return num;
        }else{
            num++;
        }
    }

    return 0;
}

int main() {
    // Prepare some random but distinct values
    int NUM_VALUES = 500;
    std::vector<int> value(NUM_VALUES);
    int prev_value = 0;
    for (int i = 0; i < NUM_VALUES; i++) {
        prev_value += rand()%25 + 1;
        value[i] = prev_value;
    }

    // Create hash table of size 1000 initialized with -1
    std::vector<int> table(1000,-1);

    // Insert values and track the maximum number of collisions
    int max_hit = 0, max_value = -1;
    for (int i = 0; i < NUM_VALUES; i++) {
        int hit = insert(value[i],table);
        if (hit > max_hit) {
            max_hit = hit;
            max_value = value[i];
        }
    }

    std::cout << "Inserting value " << max_value << " experienced " << max_hit << " collisions." << std::endl <<std::endl;

    // Print the table contents
    for (int j = 0; j < 1000; j += 10) {
        std::cout << std::setw(3) << j << ":";
        for (int i = 0; i < 10; i++) {
            if (table[j+i] == -1)
                std::cout << "      ";
            else
                std::cout << std::setw(6) << table[j+i];
        }
        std::cout << std::endl;
    }

    return 0;
}