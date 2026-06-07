static inline void func1(void) {
}

static inline void func2(void) {
}

static inline void func3(void) {
}

static inline void func4(void) {
}

static inline void ofunc(void) {}

int main(void) {

    int num = 1;

    if(num == 1)
        func1();
    else if(num == 2)
        func2();
    else if(num == 3)
        func3();
    else if(num == 4)
        func4();
}