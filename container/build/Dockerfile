FROM ubuntu:20.04
RUN apt-get update && apt-get install -y software-properties-common

RUN apt-get update && apt-get install -y wget \
                       git \
                       g++ \
                       clang \
                       cmake \
                       make \
                       python3 \
                       python3-pip

COPY cpp/scripts/setup-dependencies.sh /opt/

RUN CXX=/usr/bin/g++ CC=/usr/bin/gcc /opt/setup-dependencies.sh /opt/deps

RUN pip3 install pytest