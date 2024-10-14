#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

class Animal {
public:
    virtual ~Animal() = default;  // 为了多态，虚析构函数是必要的
};

class Dog : public Animal {};
class Cat : public Animal {};

void printTypeInfo(Animal* animal) {
    // 使用 typeid 获取对象的实际类型
    const std::type_info& type = typeid(*animal);
    std::cout << "Animal pointer points to an object of type: " << type.name() << std::endl;
}


int main(){
    auto a = 8;
    auto b = 12345678901;
    auto c = 3.14f;
    auto d = 3.14;
    auto e = true;
    auto f = 'd';
    auto g = "C++ rocks!";

    std::cout << "The type of a is " << typeid(a).name() << std::endl;
    std::cout << "The type of b is " << typeid(b).name() << std::endl;
    std::cout << "The type of c is " << typeid(c).name() << std::endl;
    std::cout << "The type of d is " << typeid(d).name() << std::endl;
    std::cout << "The type of e is " << typeid(e).name() << std::endl;
    std::cout << "The type of f is " << typeid(f).name() << std::endl;
    std::cout << "The type of g is " << typeid(g).name() << std::endl;

    std::cout << std::endl << std::endl;
    std::cout << "-----------------------------------------------------------------" << std::endl;
    // before(const type_info& rhs): 比较两个 type_info 对象的顺序。
    // 如果当前类型在 rhs 类型之前，则返回 true，否则返回 false。这个顺序是实现定义的。
    std::cout << "typeid(int).before(typeid(double)) = " << typeid(int).before(typeid(double)) << std::endl;  // 输出可能是 0 或 1
    // operator==(const type_info& rhs): 比较两个 type_info 对象是否表示相同的类型
    std::cout << "(typeid(int) == typeid(double)) = " << (typeid(int) == typeid(double)) << std::endl;  // 输出 0 (false)
    // operator!=(const type_info& rhs): 比较两个 type_info 对象是否表示不同的类型
    std::cout << "(typeid(int) != typeid(double)) = " << (typeid(int) != typeid(double)) << std::endl;  // 输出 1 (true)
    // 如果 typeid 应用于多态对象（即指向基类的指针或引用，且基类有虚函数），typeid 将返回实际对象的类型信息，而不是指针或引用的静态类型。
    Base* ptr = new Derived;
    std::cout << "typeid(*ptr).name() = " << typeid(*ptr).name() << std::endl;  // 输出可能是 "Derived"
    delete ptr;

    std::cout << "-----------------------------------------------------------------" << std::endl;
    Dog myDog;
    Cat myCat;

    Animal* animal1 = &myDog;
    Animal* animal2 = &myCat;

    printTypeInfo(animal1);  // 检查 animal1 的实际类型
    printTypeInfo(animal2);  // 检查 animal2 的实际类型

    // 检查类型是否相同
    if (typeid(*animal1) == typeid(*animal2)) {
        std::cout << "Both animals are of the same type." << std::endl;
    } else {
        std::cout << "The animals are of different types." << std::endl;
    }
    return (0);
}