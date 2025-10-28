#include <iostream>

void print_binary(unsigned value){
    auto mask = 1u << 31;

    for (auto i = 1u; i <= 32; i++){
        std::cout << ((value & mask) !=0);
        mask = mask >> 1;
        if (i%4==0) std::cout<< ' ';
        if (i%8==0) std::cout<< ' ';
    }

        std::cout << std::endl;

}

union FloatAndUnsigned {
    unsigned Unsigned;
    float Float;

};



int main(){
    FloatAndUnsigned fu;
    std::cin >> fu.Float;
    print_binary(fu.Unsigned);


}
