include $(CONTRIB_DIR)/packages.mak
TARBALLS_DIR := $(CONTRIB_DIR)/tarballs
UNPACK_DIR := $(CONTRIB_DIR)/unpacked 


ifeq ($(shell curl --version >/dev/null 2>&1 || echo FAIL),)
download = curl -f -L -- "$(1)" > "$@.tmp" && touch $@.tmp &&\
	   mv $@.tmp $@
else ifeq ($(shell wget --version >/dev/null 2>&1 || echo FAIL),)
download = rm -f $@.tmp && \
	wget --passive -c -p -O $@.tmp "$(1)" && \
	touch $@.tmp && \
	mv $@.tmp $@
else ifeq ($(which fetch >/dev/null 2>&1 || echo FAIL),)
download = rm -f $@.tmp && \
	fetch -p -o $@.tmp "$(1)" && \
	touch $@.tmp && \
	mv $@.tmp $@
else
download = $(error Neither curl nor wget found!)
endif

UNPACK=mkdir -p $2 && tar xvf $1 --strip-components=1 --directory=$2

gsl-latest.tar.gz:
	$(call download,$(GSL_URL))

gsl: gsl-latest.tar.gz
	$(call UNPACK,gsl-latest.tar.gz,gsl)

.buildgsl: gsl
	cd gsl && ./configure  && make -j$(nproc) && sudo  make install
	cd $(CONTRIB_DIR) && touch .buildgsl

cfitsio-4.2.0.tar.gz:
	$(call download,$(CFITSIO_URL))

cfitsio: cfitsio-4.2.0.tar.gz
	$(call UNPACK,cfitsio-4.2.0.tar.gz,cfitsio)

.buildcfitsio: cfitsio
	cd cfitsio && ./configure  && make -j$(nproc) && sudo  make install
	cd $(CONTRIB_DIR) && touch .buildcfitsio

libgit2-1.6.3.tar.gz:
	$(call download,$(LIBGIT2_URL))

libgit2: libgit2-1.6.3.tar.gz
	$(call UNPACK,libgit2-1.6.3.tar.gz,libgit2)

.buildlibgit2: libgit2
	cd libgit2 && mkdir -p build && cd build && cmake .. &&\
	sudo cmake --build . --target install &&\
	cd $(CONTRIB_DIR) && touch .buildlibgit2

.buildwcslib:
.buildlibtiff:
.buildlibjpeg:
.buildgslcblas:
.buildds9:
.buildtopcat:
