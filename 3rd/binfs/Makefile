all: build

build:
	mkdir -p build
	cd build && cmake -D CMAKE_BUILD_TYPE=RELEASE .. && make -j8

recompile:
	make clean
	make build

install:
	sudo cp build/binfs /usr/local/bin/binfs

clean:
	@rm -rf build

.PHONY: clean build
