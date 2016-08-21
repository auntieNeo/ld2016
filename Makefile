num_cpus = $(shell grep -c "^processor" /proc/cpuinfo)
num_threads = $(shell echo $$(($(num_cpus) + 1)))

all: build-html

build: assimp bullet
	mkdir -p build \
	&& cd build \
	&& cmake \
		-DGLM_ROOT_DIR=./extern/glm \
		-DBULLET_ROOT=./extern/bullet3/install \
		.. \
	&& make -j $(num_threads)

build-html: assimp-js
	mkdir -p build-html install-html \
	&& cd build-html \
	&& emconfigure cmake \
		-DGLM_ROOT_DIR=./extern/glm \
		-DCMAKE_INSTALL_PREFIX=../install-html \
		.. \
	&& emmake make -j $(num_threads) \
	&& emmake make install

assimp:
	cd extern/assimp \
	&& mkdir -p build install \
	&& cd build \
	&& cmake \
		-DCMAKE_BUILD_TYPE=debug \
		-DCMAKE_INSTALL_PREFIX=../install \
		-DASSIMP_BUILD_TESTS=OFF \
		.. \
	&& make -j $(num_threads) \
	&& make install

assimp-js:
	cd extern/assimp \
	&& mkdir -p build-js install-js \
	&& cd build-js \
	&& emconfigure cmake \
		-DCMAKE_BUILD_TYPE=release \
		-DCMAKE_INSTALL_PREFIX=../install-js \
		-DASSIMP_BUILD_TESTS=OFF \
		.. \
	&& emmake make -j $(num_threads) all install

bullet:
	cd extern/bullet3 \
	&& mkdir -p build install \
	&& cd build \
	&& cmake \
		-DCMAKE_BUILD_TYPE=debug \
		-DBUILD_DEMOS=OFF \
		-DBUILD_UNIT_TESTS=OFF \
		-DCMAKE_INSTALL_PREFIX=../install \
		.. \
	&& make -j $(num_threads) \
	&& make install

bullet-js:
	cd extern/bullet3 \
	&& mkdir -p build-js install-js \
	&& cd build-js \
	&& emconfigure cmake \
		-DCMAKE_BUILD_TYPE=debug \
		-DBUILD_DEMOS=OFF \
		-DBUILD_UNIT_TESTS=OFF \
		-DCMAKE_INSTALL_PREFIX=../install-js \
		.. \
	&& emmake make -j $(num_threads) \
	&& emmake make install

clean:
	rm -rf extern/bullet3/{build,install}
	rm -rf extern/bullet3/{build-js,install-js}
	rm -rf extern/assimp/{build,install}
	rm -rf extern/assimp/{build-js,install-js}
	rm -rf build

