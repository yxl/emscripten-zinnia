EMSCRIPTEN_HOME=~/Develop/emscripten

.PHONY: all clean test

all: emscripten_zinnia.js test

test: emscripten_zinnia_test.js
	node emscripten_zinnia_test.js

emscripten_zinnia.js: emscripten_zinnia.bc
	em++ -O3 emscripten_zinnia.bc -o $@

emscripten_zinnia_test.js: emscripten_zinnia.bc zh_Hans.model
	em++ -O3 emscripten_zinnia.bc --embed-file zh_Hans.model -o $@

emscripten_zinnia.bc: ../zinnia/libzinnia.cpp ../zinnia/param.cpp \
	../zinnia/recognizer.cpp  ../zinnia/sexp.cpp ../zinnia/svm.cpp \
	../zinnia/feature.cpp ../zinnia/character.cpp emscripten_zinnia.cpp \
	zh_Hans.model zh_Hant.model
	em++ -DHAVE_CONFIG_H -O3 ../zinnia/libzinnia.cpp ../zinnia/param.cpp \
		../zinnia/recognizer.cpp ../zinnia/sexp.cpp ../zinnia/svm.cpp \
		../zinnia/feature.cpp ../zinnia/character.cpp emscripten_zinnia.cpp \
		-o $@

zh_Hans.s zh_Hant.s: all-utf8.tdic
	python generate_train_file.py all-utf8.tdic

zh_Hans.model: zh_Hans.s
	./build/bin/zinnia_learn zh_Hans.s $@
	./build/bin/zinnia_convert -c 0.01 $@.txt $@

zh_Hant.model: zh_Hant.s
	./build/bin/zinnia_learn zh_Hant.s $@
	./build/bin/zinnia_convert -c 0.01 $@.txt $@

clean:
	rm -f *.model* *.s
	rm -f *.bc
	rm -f *.js
	rm -f *.o
	rm -f ../zinnia/*.o

