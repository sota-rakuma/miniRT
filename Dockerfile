FROM ubuntu:latest
RUN apt update && \
	DEBIAN_FRONTEND=noninteractive apt install -y build-essential libssl-dev curl git
ENV DISPLAY=172.22.1.6:0
RUN mkdir -p /miniRT/src
RUN mkdir -p /miniRT/include
WORKDIR /miniRT/src
RUN git clone https://github.com/42Paris/minilibx-linux.git