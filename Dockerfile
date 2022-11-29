ARG ARCHITECTURE=amd64
FROM --platform=linux/${ARCHITECTURE} ubuntu:20.04

ENV TZ=Europe/Minsk
ENV DEBIAN_FRONTEND noninteractive
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt update && apt install -yq \
    sudo \
    git \
    tmux \
    wget \
    zsh \
    vim \
    tree \
    locales \
    gnupg \
    python3-pip

RUN python3 -m pip install conan

RUN mkdir -p /home/developer/
RUN locale-gen en_US.UTF-8
RUN git clone https://github.com/robbyrussell/oh-my-zsh /opt/oh-my-zsh && \
    cp /opt/oh-my-zsh/templates/zshrc.zsh-template .zshrc && \
    cp -r /opt/oh-my-zsh .oh-my-zsh && \
    cp /opt/oh-my-zsh/templates/zshrc.zsh-template /home/developer/.zshrc && \
    cp -r /opt/oh-my-zsh /home/developer/.oh-my-zsh && \
    sed  "s/robbyrussell/bira/" -i /home/developer/.zshrc && \
    echo "PROMPT=\$(echo \$PROMPT | sed 's/%m/%f\$IMAGE_NAME/g')" >> /home/developer/.zshrc && \
    echo "RPROMPT=''" >> /home/developer/.zshrc

# Build
RUN apt update && apt install -yq \
    cmake \
    cmake-curses-gui \
    ccache \
    g++ \
    gdb \
    clang \
    clang-format 

ARG USER_ID=1000
ENV USER_ID ${USER_ID}
RUN useradd --shell /bin/bash -u $USER_ID -o -c "" developer && \
    echo "developer ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers && \
    chown -R developer /home/developer &&\
    chgrp -R developer /home/developer

ENV HOME /home/developer
WORKDIR /home/developer
USER developer
# ENTRYPOINT ["/bin/zsh", "-e", "/usr/bin/entrypoint.sh"]
CMD ["/bin/zsh"]