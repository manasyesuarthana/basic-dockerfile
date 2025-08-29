FROM alpine:latest

WORKDIR /app

COPY ./hello.c /app/hello.c

RUN apk add musl-dev build-base

RUN gcc /app/hello.c -o /app/hello

ENTRYPOINT ["/app/hello"]