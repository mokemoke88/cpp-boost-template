FROM debian:bullseye-slim

RUN apt update \
    && apt install -y sudo git python3 cmake curl build-essential \
      clang-format \
    && apt clean \
    && rm -rf /var/lib/apt/lists/*

ARG BOOST_URI=https://sourceforge.net/projects/boost/files/boost/1.77.0/boost_1_77_0.tar.bz2/download
ARG BOOST_VERSION_STRING=1_77_0
RUN mkdir -p /var/local/boost \
    && cd /var/local/boost \
    && curl -L $BOOST_URI > boost_${BOOST_VERSION_STRING}.tar.bz2 \
    && tar xjf boost_${BOOST_VERSION_STRING}.tar.bz2 \
    && cd boost_${BOOST_VERSION_STRING} \
    && ./bootstrap.sh --prefix=/usr/local/ \
    && ./b2 install \
    && cd / && rm -rf /var/local/boost

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME
