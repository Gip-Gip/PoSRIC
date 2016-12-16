cpp=cpp
cc=cc
ar=ar
ld=cc
cppargs=-E -Wall
ccargs=-g -Wall -c --std=c89
arargs=-c
ldargs=-g -lm -Wall
buildargs=
cppext=.i
ccext=.o
includearg=-I
outputarg=-o
addarg=-q
targetarg=-T
mainobj=main.o
bin=bin/posric
tccbuildf=posric.pjr
includes=$(includearg)common/include $(includearg)write/include \
$(includearg)read/include

all: clean makebdir
	rm $(tccbuildf)

	for file in common/*.c write/*.c read/*c; do \
		echo $$file >> $(tccbuildf); \
		echo $(cpp) $(cppargs) $(includes) \
        "$$file" $(outputarg) "$$file$(cppext)" | tee /dev/stderr | sh; \
	done

	for file in common/*$(cppext) write/*$(cppext) read/*$(cppext); do \
		echo $(cc) $(ccargs) "$$file" $(outputarg) "$$file$(ccext)" \
			| tee /dev/stderr | sh; \
	done

	for file in common/*$(ccext) write/*$(ccext) read/*$(ccext); do \
		echo $(ar) $(arargs) $(mainobj) $(addarg) "$$file" \
			| tee /dev/stderr | sh; \
	done

	$(ld) $(ldargs) $(mainobj) $(outputarg) $(bin)

clean:
	if [ -f $(mainobj) ]; then rm $(mainobj); fi
	if [ -f $(bin) ]; then rm $(bin); fi
	for file in  common/*$(cppext) common/*$(ccext) read/*$(cppext) \
                 read/*$(ccext) write/*$(cppext) write/*$(ccext); do\
                 if [ -f $$file ]; then rm $$file; fi; done


makebdir:
	if [ ! -d bin ]; then mkdir bin; fi
