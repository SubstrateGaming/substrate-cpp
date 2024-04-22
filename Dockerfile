#
# substrate-cpp
# This Dockerfile provides a simple and easy-to-use build environment for Linux builds.
#
# Usage
# docker build -t ajuna-build:latest .
# docker run -it -v .:/workspace ajuna-build:latest
# 
# In container do:
#
# $> cd /workspace
# $> ./build-linux.sh
#

# Use an official Ubuntu base image
FROM ubuntu:latest

# Set non-interactive installation mode
ENV DEBIAN_FRONTEND=noninteractive

# Install essential build tools and libraries
RUN apt-get update && apt-get install -y \
    build-essential \
    clang-14 \
    lsb-release \
    software-properties-common \
    python3 \
    python3-pip \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# Update alternatives to use Clang 14
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang-14 100 \
    && update-alternatives --set cc /usr/bin/clang-14 \
    && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-14 100 \
    && update-alternatives --set c++ /usr/bin/clang++-14 \
    && ln -s /usr/bin/clang-14 /usr/bin/clang \
    && ln -s /usr/bin/clang++-14 /usr/bin/clang++


# Install Conan package manager
RUN pip3 install conan

# Set the default command for the container
CMD [ "/bin/bash" ]
