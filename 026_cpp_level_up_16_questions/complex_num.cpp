#include "complex_num.h"

complex_num::complex_num(double r, double i){
    // Write your code here
    this->r = r;
    this->i = i;
}

complex_num complex_num::operator +(complex_num w){
    complex_num z;
    // Write your code here
    z.r = this->r + w.r;
    z.i = this->i + w.i;
//    std::cout << "this->r = " << this->r << " this->i = " << this->i;
//    std::cout << " w.r = " << w.r << " w.i = " << w.i << std::endl;
    return z;
}

complex_num complex_num::operator -(complex_num w){
    complex_num z;
    // Write your code here
    z.r = this->r - w.r;
    z.i = this->i - w.i;
    return z;
}

complex_num complex_num::operator *(complex_num w){
    complex_num z;
    // Write your code here
    // (a+ib)*(c+id) = (ac-bd) + i(ad+bc)
    z.r = this->r * w.r - this->i * w.i;
    z.i = this->r * w.i + this->i * w.r;
    return z;
}

complex_num complex_num::operator /(complex_num w){
    complex_num z;
    // Write your code here
    // z/w = (a+ib)/(c+id) = ((ac+bd)/(c^2+d^2)) + i((bc-ad)/(c^2+d^2))
    z.r = (this->r * w.r + this->i * w.i)/(w.r * w.r + w.i * w.i);
    z.i = (this->i * w.r - this->r * w.i)/(w.r * w.r + w.i * w.i);
    return z;
}

void complex_num::print(std::ostream &os){
    // Write your code here
    if (this->i < 0){
        os << this->r << " - " << this->i*-1 << "*i";
    }
    else{
        os << this->r << " + " << this->i << "*i";
    }

}