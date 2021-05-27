FROM ubuntu:20.04
RUN apt-get update && apt-get install -y software-properties-common

RUN apt-get update && apt-get install -y wget \
                       git \
                       g++ \
                       clang \
                       clang-format-11 \
                       clang-tidy-11 \
                       parallel \
                       make \
                       python3 \
                       python3-pip

RUN wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4-Linux-x86_64.tar.gz && \
    tar -xzvf cmake-3.18.4-Linux-x86_64.tar.gz -C /usr/local --strip-components=1

COPY cpp/scripts/setup-dependencies.sh /opt/

RUN CXX=/usr/bin/g++ CC=/usr/bin/gcc /opt/setup-dependencies.sh /usr/local

COPY requirements.txt /opt/

RUN pip3 install -r /opt/requirements.txt
