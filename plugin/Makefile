GCCPATH=../gcc-native/bin/

SOURCE=plugin.c
PLUGINDIR:=$(shell $(GCCPATH)g++ -print-file-name=plugin)
FLAGS= -fPIC -shared -I$(PLUGINDIR)/include


plugin.so: $(SOURCE)
	$(GCCPATH)g++ $^ -o $@ $(FLAGS)

clean:
	rm plugin.so
