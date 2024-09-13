#include <iostream>
#include <vector>

class Pair {
    public:
        Pair(){};
        Pair(int x, int y){
            this->x = x;
            this->y = y;
        };

        int get_x(){
            return x;
        }

        int get_y(){
            return y;
        }

        void set_x(int x){
            this->x = x;
        }

        void set_y(int y){
            this->y = y;
        }

    private:
        int x;
        int y;

};

int main(){
//    std::vector<Pair> vec;
//    for (int i=0; i<10; ++i){
//        Pair p(i, i);
//        vec.push_back(p);
//    }
//    for (auto p:vec){
//        std::cout << p.get_x() << p.get_y() << std::endl;
//    }
    std::vector<Pair*> vec;
    for (int i=0; i<10; ++i){
        Pair* p = new Pair(i, i);
        std::cout << "p add = " << &p << std::endl;
        vec.push_back(p);
    }
    for (auto p:vec){
        std::cout << p->get_x() << p->get_y() << std::endl;
    }
}
