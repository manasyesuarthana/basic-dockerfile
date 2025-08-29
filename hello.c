#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MESSAGE "Hello, Captain!\n"

typedef struct {
    char *text;
} Greeting;

typedef void (*GreetingPrinter)(const Greeting*);

Greeting* createGreeting(const char* message) {
    Greeting* greeting = (Greeting*) malloc(sizeof(Greeting));
    if (greeting == NULL) {
        return NULL;
    }

    greeting->text = (char*) malloc(strlen(message) + 1);
    if (greeting->text == NULL) {
        free(greeting);
        return NULL;
    }

    strcpy(greeting->text, message);

    return greeting;
}

void printGreeting(const Greeting* greeting) {
    if (greeting != NULL && greeting->text != NULL) {
        printf("%s", greeting->text);
    }
}

void destroyGreeting(Greeting* greeting) {
    if (greeting != NULL) {
        free(greeting->text);
        free(greeting);
    }
}

int main() {
    Greeting* myGreeting = createGreeting(MESSAGE);

    if (myGreeting == NULL) {
        fprintf(stderr, "Failed to create greeting.\n");
        return 1;
    }

    GreetingPrinter printer = &printGreeting;
    printer(myGreeting);

    destroyGreeting(myGreeting);

    return 0;
}