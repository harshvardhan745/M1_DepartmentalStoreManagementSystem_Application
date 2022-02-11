SRC= src/departmentalstoremanagementsystem_main.c src/departmentalstoremanagementsystem.c src/test_dsms.c src/unity.c
TEST_PROJ_NAME=DepartmentalStoreManagementSystem
ifdef OS
   RM = del /q
   FixPath = $(subst /,\,$1)
   EXEC = exe
else
   ifeq ($(shell uname), Linux)
      RM = rm -rf
      FixPath = $1
	  EXEC = out
   endif
endif

Build : $(SRC)
	gcc $(SRC) -Iinc -o $(call FixPath,$(TEST_PROJ_NAME).$(EXEC)) -lm

Run : Build
	$(call FixPath,$(TEST_PROJ_NAME).$(EXEC))

Static-analysis : 
    cppcheck --enable=all $(SRC)

dynamic-analysis : Build
    valgrind $(SRC) -Iinc -o $(call FixPath,$(TEST_PROJ_NAME).$(EXEC)) -lm

coverage :
    gcc -fprofile-arcs -ftest-coverage $(SRC) -Iinc -o $(call FixPath,$(TEST_PROJ_NAME).$(EXEC)) -lm
    ./$(call FixPath,$(TEST_PROJ_NAME).$(EXEC))
    gcov src/departmentalstoremanagementsystem_main.c src/departmentalstoremanagementsystem.c

Clean : 
	$(RM) $(call FixPath,$(BUILD_DIR)/*.out)