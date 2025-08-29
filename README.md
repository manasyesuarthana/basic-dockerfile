# Basic Dockerfile
This project involves writing a basic dockerfile that creates an image for a container that will print a statement and exits. Pretty **basic** stuff right here frfr...

This README.md will lay out the steps I took to achieve this and how the reader can do the same. 

This project is a part of the roadmap.sh DevOps Projects series specifically [Basic Dockerfile](https://roadmap.sh/projects/basic-dockerfile)

## Pre-requisites:
- Make sure **Docker Engine** is installed in your computer. If not you can follow the steps from the documentation: [Install Docker Engine](https://docs.docker.com/engine/install/).

Test if docker is installed by running:
```bash
docker
```
If the output is:
```
Usage:  docker [OPTIONS] COMMAND

A self-sufficient runtime for containers

Common Commands:
  run         Create and run a new container from an image
  exec        Execute a command in a running container
  ps          List containers
  build       Build an image from a Dockerfile
  pull        Download an image from a registry
  push        Upload an image to a registry
  images      List images
  login       Authenticate to a registry
  logout      Log out from a registry
  search      Search Docker Hub for images
  version     Show the Docker version information
  info        Display system-wide information

  ...
  ...
```
Docker is already installed and you are set. If not, go ahead and install!

## Project Completion Steps

### 1. Writing a Program to print out the statement.
The statement that will be printed by the container is `Hello, Captain!`. I will be using an over-engineered C code to do this 😂

Below is the C program I used, which uses sophisticated concepts like `malloc()`, `free()`, and pointers. All of this just to print one statement :v 

**hello.c**
```c
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
```

### 2. Create the Dockerfile
The next step is to write a Dockerfile that can create an image that compiles this code and runs it, resulting in the output statement. 

Below is the **Dockerfile** I wrote:

```Dockerfile
FROM alpine:latest

WORKDIR /app

COPY ./hello.c /app/hello.c

RUN apk add musl-dev build-base

RUN gcc /app/hello.c -o /app/hello

ENTRYPOINT ["/app/hello"]
```

What each line does:
- `FROM alpine:latest`: Uses the Alpine Linux distribution for the container with the version being the latest.
- `WORKDIR /app`: Uses **/app** in the container as its working directory (where the files of the program will be located).
- `COPY ./hello.c /app/hello.c`: Copies the hello.c in our directory to the working directory in the container.
- `RUN apk add musl-dev build-base`: Installs the necessary libraris for C code compilation. 
- `RUN gcc /app/hello.c -o /app/hello`: Compiles the C code in the working directory.
- `ENTRYPOINT ["/app/hello"]` Runs the compiled program as the entrypoint as soon as the container is started from the image. 

Remember that /app will be created inside the container and once the image is run, not in our system. 

## Starting the container
Below are the steps to start the container with the above files.

1. Clone the repository
```bash
git clone https://github.com/manasyesuarthana/basic-dockerfile.git
cd basic-dockerfile
```

2. Build the Docker Image
```bash
docker build . -t hello-captain
```
In this case, I gave the image name "hello-captain", you can change it to whatever you want.

3. After docker finishes building, start a container from the image
```bash
docker run hello-captain
```

4. Make sure the image is built
```
$ docker images | grep hello-captain
hello-captain   latest    be3771d6aeac   22 seconds ago   358MB
```

5. Start a container from the image
```bash
docker run hello-captain
```
## Output
After starting the image, the statement should be displayed in the terminal:

```
$ docker run hello-captain
Hello, Captain!
```

Following this, the container will stop and exit. 
