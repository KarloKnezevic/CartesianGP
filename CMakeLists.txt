cmake_minimum_required(VERSION 3.6)
project(CartesianGP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    src/constants/constants.h
    src/fitness/fitness.c
    src/fitness/fitness.h
    src/functions/functions.c
    src/functions/functions.h
    src/mutation/mutation.c
    src/mutation/mutation.h
    src/reproduction/reproduction.c
    src/reproduction/reproduction.h
    src/selection/selection.c
    src/selection/selection.h
    src/cgp.c
    src/cgp.h
    src/chromosome.c
    src/chromosome.h
    src/dataset.c
    src/dataset.h
    src/functionset.c
    src/functionset.h
    src/node.c
    src/node.h
    src/parameters.c
    src/parameters.h
    src/results.c
    src/results.h
    src/util.c
    src/util.h
    main.c
    main.h)

add_executable(CartesianGP ${SOURCE_FILES})