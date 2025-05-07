#include <cstdio>

template<typename T>
T add(T x, T y) {
    return x + y;
}

int main() {
    constexpr auto a = 1, b = 2;
    constexpr auto c = 2.0f, d = 2.0f;

    printf("Int: %d\n", add(a, b));
    printf("Float: %.1f\n", add(c, d));

    return 0;
}
