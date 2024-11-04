#include <iostream>

int get_highest_score(){
    int n=0;
    int score=0;
    int highest_score=0;
    std::cin >> n;
    for (int i=0; i<n;++i){
        std::cin >> score;
        if (score > highest_score){
            highest_score = score;
        }
    }
    std::cout << highest_score << std::endl;
    return highest_score;

}

int main(){
    get_highest_score();
    return 0;
}