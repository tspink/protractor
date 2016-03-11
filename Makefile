top-dir := $(CURDIR)
src-dir := $(top-dir)/src
inc-dir := $(top-dir)/inc
out-dir := $(top-dir)/out

out := protractor

obj :=
-include $(src-dir)/Makefile

real-obj := $(patsubst %,$(src-dir)/%,$(obj))
real-dep := $(patsubst %.o,%.d,$(real-obj))
real-out := $(out-dir)/$(out)

ldflags  :=
cxxflags := -Wall -g -I$(inc-dir) -std=gnu++14

all: $(real-out)

clean:
	rm -f $(real-out)
	rm -f $(real-obj)

$(real-out): $(out-dir) $(real-dep) $(real-obj)
	@echo "  LD    $(notdir $@)"
	@g++ -o $@ $(ldflags) $(real-obj)

%.o: %.cpp
	@echo "  C++   $(notdir $@)"
	@g++ -c -o $@ $(cxxflags) $<

%.d: %.cpp
	@g++ -M -MT $(@:.d=.o) -o $@ $(cxxflags) $<

$(out-dir):
	mkdir $@

-include $(real-dep)