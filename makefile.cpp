MAKE FILE

wget /*sITE*/
tar -xvzf Quest.tar.gz

Generate a make file and compile it using command make 

1. Generate userdefined variable in makefile by:

objects= AI.o main.o Single-player.o multi-player.o

To access objects, we do $(objects)

2. There are some predefined special variables. One of them is:
$(CC) which is equivalent to cc 

You can see list of all special variables using command: make -p in a directory not having any
make file

3. Automatic variables: 

$@ is the name of the file being generated, and $< the first prerequisite (usually the source file).


objects=main.o AI.o multi-player.o single-player.o
Quest: $(objects)
gcc -o Quest $(objects)

main.o:main.c defs.h
gcc -c $<

multi-player.o:multi-player.c
gcc -c $<
       
single-player.o:single-player.c AI.c
gcc -c $<

AI.o: AI.c
gcc -c $<
clean:
echo success

4. Pattern matching:

If we have multiple .o files, we can replace them by %.o and .c files by %.c 

objects=main.o AI.o multi-player.o single-player.o
Quest: $(objects)
gcc -o Quest $(objects)

main.o:main.c defs.h
gcc -c $<

%.o: %.c
gcc -c $<
       
single-player.o:single-player.c AI.c
gcc -c $<

clean:
echo success

5. How to know all prerequisites? Type following in terminal and you can do copy paste in your make file: 

gcc -M single-player.c
Output: single-player.o: single-player.c /usr/include/stdc-predef.h AI.h


gcc -MM single-player.c   //This omits prerequisites on system header files.
Output: single-player.o: single-player.c AI.h

6. We can define a variable in another makefile, but if we want to use that variable here, we can
include that make file in our current make file also: 

objects=main.o AI.o multi-player.o single-player.o
include a.mk
Quest: $(objects)
        gcc -o Quest $(objects)

main.o:main.c defs.h
        gcc -c $<

multi-player.o:multi-player.c
        gcc -c $<

single-player.o:single-player.c AI.c
        gcc -c $<

AI.o: $(ob)  
        gcc -c $<
clean:
        echo success

$(ob) is defined in a.mk

7. 
A function call resembles a variable reference. It can appear anywhere a variable reference can appear,
 and it is expanded using the same rules as variable references. A function call looks like this:

$(function arguments)


Here function is a function name; one of a short list of names that are part of make. 
You can also essentially create your own functions by using the call built-in function.
If the arguments themselves contain other function calls or variable references, it is wisest to use the same kind of 
delimiters for all the references; write ‘$(subst a,b,$(x))’, not ‘$(subst a,b,${x})’. 

It means that substitute pattern a with pattern b in string stored in variable x

8. Compiling a program is not the only thing you might want to write rules for. 
Makefiles commonly tell how to do a few other things besides compiling a program: for example, how to delete all 
the object files and executables so that the directory is ‘clean’.

You can use clean for other commands also apart from deleting files. For example:
clean: echo success

WHen we type make clean in terminal, it prints success

PHONY TARGETS: 
.PHONY : clean
clean :
        -rm edit $(objects)

This prevents make from getting confused by an actual file called clean and causes it to continue in spite of errors from rm. 

.PHONY: cleanall cleanobj cleandiff

cleanall : cleanobj cleandiff
        rm program

cleanobj :
        rm *.o

cleandiff :
        rm *.diff

9. 
objects=main.o AI.o multi-player.o single-player.o
Quest: $(objects)
	gcc -o Quest $(objects)

.DEFAULT: %.c
	$(CC) -c $<

main.o:main.c defs.h

multi-player.o:multi-player.c
       
single-player.o:single-player.c AI.c

AI.o: AI.c

clean:
	echo success

So here, .DEFAULT specifies the recipe for those targets and prerequisites for whom recipe isn't 
	defined in makefile. If recipe isn't defined, the make
command assumes the recipe specified in .DEFAULT to be the recipe for them

10. If you want to use a nonstandard name for your makefile, you can specify the makefile name with the ‘-f’ or ‘--file’ option. 
The arguments ‘-f name’ or ‘--file=name’ tell make to read the file name as the makefile. If you use more than one ‘-f’ or ‘--file’ option, 
you can specify several makefiles. All the makefiles are effectively concatenated in the order specified. https://docs.google.com/document/d/1QlsUx-QRNi9ErorrNs_7miLgjfSUXZ-RkMAcKBjVzrY/edit
The default makefile names GNUmakefile, makefile and Makefile are not checked automatically if you specify ‘-f’ or ‘--file’.

11. By default, running ‘make’ displays the commands being executed. To hide/silence them, use the ‘-s’ flag:
 make -s

12. The default shell used by a makefile to run its recipes is ‘/bin/sh’ i.e. the Bourne shell. Change it to ‘/bin/bash’ 
(the Bourne Again shell) using MAKESHELL, a special variable: 
MAKESHELL = /bin/bash

13. Create a new directory include: mkdir include 
Transfer all header files into include: mv *.h include 

Now type: vpath %.h include
In your makefile to search for header files in include directory

/*Using VPATH variable to search multiple directories*?

VPATH= dir1 dir2 ....
/*Means search any prerequisites or targets in dir1, dir2 and other directories specified apart from the current directory*/

Further,  rules may then specify the names of files in the prerequisite list as if they all existed in the current directory. 

For example, foo.o : foo.c
 Shall be treated same as: foo.o : /dir1/foo.c 

 Even though foo.c doesn't exist in your current working directory, but is is there in dir1 
	 (which has been included in our search using
 VPATH variable)


