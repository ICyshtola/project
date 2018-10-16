#!/bin/bash
cd ../moduleA
make
cd ../moduleB/
make
ar -rsv ../release/libstu.a ../release/stu.o
ar -rsv ../release/libcourse.a ../release/course.o 
