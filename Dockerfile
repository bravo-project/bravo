FROM phusion/baseimage:0.9.19

#ARG BRAVOD_BLOCKCHAIN=https://example.com/bravod-blockchain.tbz2

ENV LANG=en_US.UTF-8

RUN \
    apt-get update && \
    apt-get install -y \
        autoconf \
        automake \
        autotools-dev \
        bsdmainutils \
        build-essential \
        cmake \
        doxygen \
        git \
        libboost-all-dev \
        libreadline-dev \
        libssl-dev \
        libtool \
        ncurses-dev \
        pbzip2 \
        pkg-config \
        python3 \
        python3-dev \
        python3-jinja2 \
        python3-pip \
        nginx \
        fcgiwrap \
        s3cmd \
        awscli \
        jq \
        wget \
        gdb \
    && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* && \
    pip3 install gcovr

ADD . /usr/local/src/bravo

RUN \
    cd /usr/local/src/bravo && \
    git submodule update --init --recursive && \
    mkdir build && \
    cd build && \
    cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_BRAVO_TESTNET=ON \
        -DLOW_MEMORY_NODE=OFF \
        -DCLEAR_VOTES=ON \
        -DSKIP_BY_TX_ID=ON \
        .. && \
    make -j$(nproc) chain_test test_fixed_string && \
    ./tests/chain_test && \
    ./programs/util/test_fixed_string && \
    cd /usr/local/src/bravo && \
    doxygen && \
    programs/build_helpers/check_reflect.py && \
    programs/build_helpers/get_config_check.sh && \
    rm -rf /usr/local/src/bravo/build

RUN \
    cd /usr/local/src/bravo && \
    git submodule update --init --recursive && \
    mkdir build && \
    cd build && \
    cmake \
        -DCMAKE_BUILD_TYPE=Debug \
        -DENABLE_COVERAGE_TESTING=ON \
        -DBUILD_BRAVO_TESTNET=ON \
        -DLOW_MEMORY_NODE=OFF \
        -DCLEAR_VOTES=ON \
        -DSKIP_BY_TX_ID=ON \
        -DCHAINBASE_CHECK_LOCKING=OFF \
        .. && \
    make -j$(nproc) chain_test && \
    ./tests/chain_test && \
    mkdir -p /var/cobertura && \
    gcovr --object-directory="../" --root=../ --xml-pretty --gcov-exclude=".*tests.*" --gcov-exclude=".*fc.*" --gcov-exclude=".*app*" --gcov-exclude=".*net*" --gcov-exclude=".*plugins*" --gcov-exclude=".*schema*" --gcov-exclude=".*time*" --gcov-exclude=".*utilities*" --gcov-exclude=".*wallet*" --gcov-exclude=".*programs*" --output="/var/cobertura/coverage.xml" && \
    cd /usr/local/src/bravo && \
    rm -rf /usr/local/src/bravo/build

RUN \
    cd /usr/local/src/bravo && \
    git submodule update --init --recursive && \
    mkdir build && \
    cd build && \
    cmake \
        -DCMAKE_INSTALL_PREFIX=/usr/local/bravod-default \
        -DCMAKE_BUILD_TYPE=Release \
        -DLOW_MEMORY_NODE=ON \
        -DCLEAR_VOTES=ON \
        -DSKIP_BY_TX_ID=ON \
        -DBUILD_BRAVO_TESTNET=OFF \
        .. \
    && \
    make -j$(nproc) && \
    make install && \
    cd .. && \
    ( /usr/local/bravod-default/bin/bravod --version \
      | grep -o '[0-9]*\.[0-9]*\.[0-9]*' \
      && echo '_' \
      && git rev-parse --short HEAD ) \
      | sed -e ':a' -e 'N' -e '$!ba' -e 's/\n//g' \
      > /etc/bravodversion && \
    cat /etc/bravodversion && \
    rm -rfv build && \
    mkdir build && \
    cd build && \
    cmake \
        -DCMAKE_INSTALL_PREFIX=/usr/local/bravod-full \
        -DCMAKE_BUILD_TYPE=Release \
        -DLOW_MEMORY_NODE=OFF \
        -DCLEAR_VOTES=OFF \
        -DSKIP_BY_TX_ID=ON \
        -DBUILD_BRAVO_TESTNET=OFF \
        .. \
    && \
    make -j$(nproc) && \
    make install && \
    rm -rf /usr/local/src/bravo

RUN \
    apt-get remove -y \
        automake \
        autotools-dev \
        bsdmainutils \
        build-essential \
        cmake \
        doxygen \
        dpkg-dev \
        git \
        libboost-all-dev \
        libc6-dev \
        libexpat1-dev \
        libgcc-5-dev \
        libhwloc-dev \
        libibverbs-dev \
        libicu-dev \
        libltdl-dev \
        libncurses5-dev \
        libnuma-dev \
        libopenmpi-dev \
        libpython-dev \
        libpython2.7-dev \
        libreadline-dev \
        libreadline6-dev \
        libssl-dev \
        libstdc++-5-dev \
        libtinfo-dev \
        libtool \
        linux-libc-dev \
        m4 \
        make \
        manpages \
        manpages-dev \
        mpi-default-dev \
        python-dev \
        python2.7-dev \
        python3-dev \
    && \
    apt-get autoremove -y && \
    rm -rf \
        /var/lib/apt/lists/* \
        /tmp/* \
        /var/tmp/* \
        /var/cache/* \
        /usr/include \
        /usr/local/include

RUN useradd -s /bin/bash -m -d /var/lib/bravod bravod

RUN mkdir /var/cache/bravod && \
    chown bravod:bravod -R /var/cache/bravod

# add blockchain cache to image
#ADD $BRAVOD_BLOCKCHAIN /var/cache/bravod/blocks.tbz2

ENV HOME /var/lib/bravod
RUN chown bravod:bravod -R /var/lib/bravod

VOLUME ["/var/lib/bravod"]

# rpc service:
EXPOSE 8090
# p2p service:
EXPOSE 2001

# add seednodes from documentation to image
ADD doc/seednodes.txt /etc/bravod/seednodes.txt

# the following adds lots of logging info to stdout
ADD contrib/config-for-docker.ini /etc/bravod/config.ini
ADD contrib/fullnode.config.ini /etc/bravod/fullnode.config.ini

# add normal startup script that starts via sv
ADD contrib/bravod.run /usr/local/bin/bravo-sv-run.sh
RUN chmod +x /usr/local/bin/bravo-sv-run.sh

# add nginx templates
ADD contrib/bravod.nginx.conf /etc/nginx/bravod.nginx.conf
ADD contrib/healthcheck.conf.template /etc/nginx/healthcheck.conf.template

# add PaaS startup script and service script
ADD contrib/startpaasbravod.sh /usr/local/bin/startpaasbravod.sh
ADD contrib/paas-sv-run.sh /usr/local/bin/paas-sv-run.sh
ADD contrib/sync-sv-run.sh /usr/local/bin/sync-sv-run.sh
ADD contrib/healthcheck.sh /usr/local/bin/healthcheck.sh
RUN chmod +x /usr/local/bin/startpaasbravod.sh
RUN chmod +x /usr/local/bin/paas-sv-run.sh
RUN chmod +x /usr/local/bin/sync-sv-run.sh
RUN chmod +x /usr/local/bin/healthcheck.sh

# new entrypoint for all instances
# this enables exitting of the container when the writer node dies
# for PaaS mode (elasticbeanstalk, etc)
# AWS EB Docker requires a non-daemonized entrypoint
ADD contrib/bravodentrypoint.sh /usr/local/bin/bravodentrypoint.sh
RUN chmod +x /usr/local/bin/bravodentrypoint.sh
CMD /usr/local/bin/bravodentrypoint.sh
