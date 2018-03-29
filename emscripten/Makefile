EMSCRIPTEN_HOME=~/Develop/emscripten

.PHONY: all clean test

all: emscripten_zinnia.js test

test: emscripten_zinnia_test.js
	node emscripten_zinnia_test.js

emscripten_zinnia.js: emscripten_zinnia.bc zh_Hans.model zh_Hant.model
	em++ emscripten_zinnia.bc -O3 --preload-file zh_Hans.model \
		--preload-file zh_Hant.model \
		-s EXPORTED_FUNCTIONS="['_CharacterRecognize', '_InitRecog', '_ExitRecog']" \
		-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
		-o $@

emscripten_zinnia_test.js: emscripten_zinnia.bc zh_Hans.model
	em++ emscripten_zinnia.bc -O3 --embed-file zh_Hans.model -o $@

emscripten_zinnia.bc: ../zinnia/libzinnia.cpp ../zinnia/param.cpp \
	../zinnia/recognizer.cpp  ../zinnia/sexp.cpp ../zinnia/svm.cpp \
	../zinnia/feature.cpp ../zinnia/character.cpp emscripten_zinnia.cpp
	em++ -DHAVE_CONFIG_H -O3 ../zinnia/libzinnia.cpp ../zinnia/param.cpp \
		../zinnia/recognizer.cpp ../zinnia/sexp.cpp ../zinnia/svm.cpp \
		../zinnia/feature.cpp ../zinnia/character.cpp emscripten_zinnia.cpp \
		-o $@

zh_Hans.s zh_Hant.s: all-utf8.tdic
	python2 generate_train_file.py all-utf8.tdic

zh_Hans.model: zh_Hans.s
	./build/bin/zinnia_learn zh_Hans.s $@
	./build/bin/zinnia_convert -c 0.01 $@.txt $@

zh_Hant.model: zh_Hant.s
	./build/bin/zinnia_learn zh_Hant.s $@
	./build/bin/zinnia_convert -c 0.01 $@.txt $@

clean:
	rm -f *.model* *.s
	rm -f *.bc
	rm -f *.js *.data *.js.map *.js.mem
	rm -f *.o
	rm -f ../zinnia/*.o

