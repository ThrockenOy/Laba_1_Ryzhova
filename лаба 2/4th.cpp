#include <iostream>

float f_float(float x) { return x*x; }
double f_double(double x) { return x*x; }

int main() {
    int N = 100;
    float dx_f = 1.0f / N;
    double dx_d = 1.0 / N;

    float S_f = 0.0f;
    double S_d = 0.0;


    for (int i = 0; i < N; i++) { // метод левых прямоугольников
        float x_f = i * dx_f;
        S_f += f_float(x_f) * dx_f;

        double x_d = i * dx_d;
        S_d += f_double(x_d) * dx_d;
    }

    float analit_f = 1.0f / 3.0f;
    double ahalit_d = 1.0 / 3.0;

    std::cout << "Square float: " << S_f << " | Difference: " << analit_f - S_f << "\n";
    std::cout << "Square double: " << S_d << " | Difference: " << ahalit_d - S_d << "\n";
}
