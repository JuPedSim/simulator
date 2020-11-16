#! /bin/bash
set -ex

pybind11_version=2.5.0
googletest_version=1.10.0
fmt_version=7.1.2

install_path=/usr/local
if [ ${1} ]; then
    install_path=${1}
fi

function setup_pybind11 {
    root=$(pwd)
    temp_folder=$(mktemp -d)
    cd ${temp_folder}

    wget https://github.com/pybind/pybind11/archive/v${pybind11_version}.tar.gz
    tar xf v${pybind11_version}.tar.gz
    cd pybind11-${pybind11_version}
    mkdir build
    cd build
    cmake .. \
        -DCMAKE_INSTALL_PREFIX=${install_path} \
        -DCMAKE_BUILD_TYPE=Release \
        -DPYBIND11_TEST=Off
    cmake --build . -j $(nproc)
    cmake --install .
    cd ${root}
    rm -rf ${temp_folder}
}

function setup_googletest {
    root=$(pwd)
    temp_folder=$(mktemp -d)
    cd ${temp_folder}

    wget https://github.com/google/googletest/archive/release-${googletest_version}.tar.gz
    tar xf release-${googletest_version}.tar.gz
    cd googletest-release-${googletest_version}
    mkdir build
    cd build
    cmake .. \
        -DCMAKE_INSTALL_PREFIX=${install_path} \
        -DCMAKE_BUILD_TYPE=Release
    cmake --build . -j $(nproc)
    cmake --install .
    cd ${root}
    rm -rf ${temp_folder}
}

function setup_fmt {
    root=$(pwd)
    temp_folder=$(mktemp -d)
    cd ${temp_folder}

    wget https://github.com/fmtlib/fmt/archive/${fmt_version}.tar.gz
    tar xf ${fmt_version}.tar.gz
    cd fmt-${fmt_version}
    mkdir build
    cd build
    cmake .. \
        -DFMT_DOC=OFF \
        -DFMT_TEST=OFF \
        -DCMAKE_INSTALL_PREFIX=${install_path} \
        -DCMAKE_BUILD_TYPE=Release
    cmake --build . -j $(nproc)
    cmake --install .
    cd ${root}
    rm -rf ${temp_folder}
}

setup_pybind11
setup_googletest
setup_fmt
