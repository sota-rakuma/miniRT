FROM ubuntu:latest
RUN apt update && \
	DEBIAN_FRONTEND=noninteractive apt install -y build-essential libssl-dev curl git xorg zlib1g-dev libbsd-dev libxext-dev xdotool
ENV DISPLAY=172.22.1.6:0
RUN mkdir -p /home/miniRT/src && mkdir -p /home/miniRT/include
WORKDIR /home/miniRT/src