FROM alpine AS base
FROM base AS build
WORKDIR /src
RUN apk add g++ git make && \
	git clone https://github.com/hzeller/rpi-rgb-led-matrix --depth 1 && \
	cd rpi-rgb-led-matrix/lib && \
	make && \
	cp librgbmatrix.so.1 /usr/lib && \
	cd ../../ && \
	rm -rf rpi-rgb-led-matrix
COPY . .
RUN make

ENV HOST=ws.multilife.live
ENV PORT=31337
