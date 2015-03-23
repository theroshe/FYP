GCCPATH="/home/rob/fyp/install/bin"

SOURCE=plugin.c
PLUGINDIR:=$(shell $(GCCPATH)/g++ -print-file-name=plugin)
FLAGS= -fPIC -I$(PLUGINDIR)/include 


plugin.so: $(SOURCE)
	$(GCCPATH)/g++ -shared $^ -o $@ $(FLAGS) -g

clean:
	rm plugin.so
