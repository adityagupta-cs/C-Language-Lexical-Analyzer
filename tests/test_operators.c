int main() {
    int a = 10;
    int b = 5;

    a++;
    b--;

    int sum = a + b;
    int diff = a - b;
    int product = a * b;
    int division = a / b;

    if (a >= b && a != 0) {
        a += b;
    }

    return 0;
}