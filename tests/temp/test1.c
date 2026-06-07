
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

    switch(num) {
        case 1: func1(); break;
        case 2: func2(); ofunc(); break;
        case 3: func3(); break;
        case 4: func4(); break;
    }
}