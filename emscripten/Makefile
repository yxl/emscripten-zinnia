EMSCRIPTEN_HOME=~/Develop/emscripten

.PHONY: all clean

all: libzinnia.js zh_Hans.model zh_Hant.model

libzinnia.js: ../zinnia/libzinnia.cpp ../zinnia/param.cpp \
	../zinnia/recognizer.cpp  ../zinnia/sexp.cpp ../zinnia/svm.cpp \
	../zinnia/feature.cpp ../zinnia/character.cpp
	em++ -DHAVE_CONFIG_H -O3 ../zinnia/libzinnia.cpp ../zinnia/param.cpp \
		../zinnia/recognizer.cpp ../zinnia/sexp.cpp ../zinnia/svm.cpp \
		../zinnia/feature.cpp ../zinnia/character.cpp -s \
		EXPORTED_FUNCTION="['_zinnia_recognizer_open']" -o $@

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
	rm -f *.o
	rm -f *.bc

