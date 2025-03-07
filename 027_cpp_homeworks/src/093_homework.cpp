
#include <iostream>
#include <vector>
using namespace std;

//add class definitions below this line
class Person{
public:
    Person(string n, int a, string o){
        this->name = n;
        this->age = a;
        this->occupation = o;
    }
    string GetName(){
        return name;
    }
    void SetName(string n){
        name = n;
    }
    int GetAge(){
        return age;
    }
    void SetAge(int a){
        age = a;
    }
    string GetOccupation(){
        return occupation;
    }
    void SetOccupation(string o){
        occupation = o;
    }


private:
    string name;
    int age;
    string occupation;
};


//add class definitions above this line


int main() {

    //DO NOT EDIT CODE BELOW THIS LINE

    Person p("Citra Curie", 16, "student");
    cout << p.GetName() << endl;
    p.SetName("Rowan Faraday");
    cout << p.GetAge() << endl;
    p.SetAge(18);
    cout << p.GetOccupation() << endl;
    p.SetOccupation("plumber");
    cout << p.GetName() << endl;
    cout << p.GetAge() << endl;
    cout << p.GetOccupation() << endl;

    //DO NOT EDIT CODE ABOVE THIS LINE

    return 0;

}