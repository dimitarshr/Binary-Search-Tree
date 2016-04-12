all: compile binary_tree

compile:
	cl /c test.cpp binary_tree.cpp
	lib binary_tree.obj
	link test.obj binary_tree.lib
	
binary_tree:
	cl /c test.cpp binary_tree.cpp
	lib binary_tree.obj
	link test.obj binary_tree.lib
	test
	
clean:
	del *.obj
	del *.exe
	del *.asm
	del *.lib