FROM ubuntu

RUN apt-get update && apt-get install -y \
    libpcre3 \
    libpcre3-dev
RUN apt-get install -y gcc
RUN apt-get install -y valgrind
RUN apt-get install -y make
RUN apt-get install -y vim
RUN apt-get install -y check
RUN apt-get install -y clang-format
RUN apt-get install -y lcov
RUN apt-get install -y libgtest-dev
RUN apt-get install -y git
RUN apt-get install -y g++



COPY . /project