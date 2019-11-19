ifeq ($(release), 1)
	build_directory=release
	build_type=Release
else
	build_directory=debug
	build_type=Debug
endif

ifneq ($(verbose), 1)
	verbose_redirect=> /dev/null
endif

ifndef (target)
	target=all
endif


.PHONY: build

ifneq ($(verbose), 1)
.SILENT:
endif


build:
	mkdir -p build/$(build_directory) && cd build/$(build_directory) && \
	cmake -DCMAKE_BUILD_TYPE=$(build_type) -DCMAKE_MAKE_PROGRAM=make ../.. $(verbose_redirect) && \
	make --no-print-directory $(target) $(verbose_redirect)

run: build
	./dist/$(build_directory)/$(target) $(args)

test: build
	./dist/$(build_directory)/$(target)-test $(args)

clean:
	rm -rf build/* && rm -rf dist
