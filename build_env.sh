#!/bin/sh

# User define:
export PROJECT_ROOT=/home/huangwei/study/computer_graphics/learning_computer_graphics

export PROJECT_INCLUDE_DIR=$PROJECT_ROOT/include
export PROJECT_LIB_DIR=$PROJECT_ROOT/lib

export REDBOOK_DIR=$PROJECT_ROOT/redbook_example
export REDBOOK_INCLUDE_DIR=$REDBOOK_DIR/include
# use define
export REDBOOK_LIB_DIR=$PROJECT_ROOT/tmp/build_redbook_examples/lib

export SB7_DIR=$PROJECT_ROOT/sb7code
export SB7_INCLUDE_DIR=$SB7_DIR/include
# user define 
export SB7_LIB_DIR=$SB7_DIR/build/lib

cp $SB7_INCLUDE_DIR $PROJECT_INCLUDE_DIR/sb7_include -r
cp $SB7_LIB_DIR/* $PROJECT_LIB_DIR/ -r
