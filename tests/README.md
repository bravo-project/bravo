# Automated Testing Documentation

## To Create Test Environment Container

From the root of the repository:

    docker build --rm=false \
        -t bravocoininc/ci-test-environment:latest \
        -f tests/scripts/Dockerfile.testenv .

## To Run The Tests

(Also in the root of the repository.)

    docker build --rm=false \
        -t bravocoininc/bravo-test \
        -f Dockerfile.test .

## To Troubleshoot Failing Tests

    docker run -ti \
        bravocoininc/ci-test-environment:latest \
        /bin/bash

Then, inside the container:

(These steps are taken from `/Dockerfile.test` in the
repository root.)

    git clone https://github.com/bravocoin/bravo.git \
        /usr/local/src/bravo
    cd /usr/local/src/bravo
    git checkout <branch> # e.g. 123-feature
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake \
        -DCMAKE_BUILD_TYPE=Debug \
        -DBUILD_BRAVO_TESTNET=ON \
        -DLOW_MEMORY_NODE=OFF \
        -DCLEAR_VOTES=ON \
        ..
    make -j$(nproc) chain_test
    ./tests/chain_test
    cd /usr/local/src/bravo
    doxygen
    programs/build_helpers/check_reflect.py
