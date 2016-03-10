top-dir := $(CURDIR)
src-dir := $(top-dir)/src
inc-dir := $(top-dir)/inc
out-dir := $(top-dir)/out

out := protractor

obj := 
-include $(src-dir)/Makefile

real-obj := $(patsubst %,$(src-dir)/%,$(obj))
real-out := $(out-dir)/$(out)

ldflags  :=
cxxflags := -Wall -g -I$(inc-dir)

all: $(real-out)

clean:
	rm -f $(real-out)
	rm -f $(real-obj)

$(real-out): $(out-dir) $(real-obj)
	g++ -o $@ $(ldflags) $(real-obj)

%.o: %.cpp
	g++ -c -o $@ $(cxxflags) $<

$(out-dir):
	mkdir $@
