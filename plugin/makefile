GCCPATH="/home/rob/fyp/gcc/output/gcc"

SOURCE=plugin.c
PLUGINDIR:=$(shell $(GCCPATH)/xg++ -print-file-name=plugin)
FLAGS= -fPIC -I$(PLUGINDIR)/include 


plugin.so: $(SOURCE)
	$(GCCPATH)/xg++ -shared $^ -o $@ $(FLAGS) -g

clean:
	rm plugin.so
