typedef void (*func_t)(void);

void func1(void) {}

void func2(void) {}

void func3(void) {}

void func4(void) {}

void ofunc(void) {}

func_t lst[] = {func1, func2, ofunc, func3, func4};

void run(int num) {

    lst[num]();
}

int main(void) {

    run(2);
}