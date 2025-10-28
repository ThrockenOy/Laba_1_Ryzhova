#include <iostream>

void print_binary(unsigned value) {
    auto mask = 1u << 31;

    for (auto i = 1u; i <= 32; i++) {
        std::cout << ((value & mask) != 0);
        mask = mask >> 1;
        if (i % 4 == 0) std::cout << ' ';
        if (i % 8 == 0) std::cout << ' ';
    }
    std::cout << std::endl;
}

union FloatAndUnsigned {
    unsigned Unsigned;
    float Float;
};

int main() {
    std::cout << std::fixed;
    std::cout.precision(2);

    FloatAndUnsigned fu;
    fu.Float = 1e8f; // начало с большого числа

    int step = 0;

    while (step < 10) { // ограничение, чтобы не зациклиться
        std::cout << "Iteration "<< step << "fu.Float = " << fu.Float << std::endl;
        print_binary(fu.Unsigned);

        float old = fu.Float;
        fu.Float += 1.0f;

        step++;
    }
}

