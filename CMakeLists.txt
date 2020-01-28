cmake_minimum_required(VERSION 3.15)
project(Milestone_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Milestone_2 Main.cpp Solver.h ClientHandler.h
        MyTestClientHandler.cpp MyTestClientHandler.h StringReverser.cpp StringReverser.h Searcher.h
        Searchable.h State.h BFSAlgorithm.cpp BFSAlgorithm.h Matrix.cpp Matrix.h
        MatrixSearcher.cpp MatrixSearcher.h MatrixSolver.cpp MatrixSolver.h  CacheManager.h
        FileCacheManager.cpp FileCacheManager.h Server.h MySerialServer.h BestFSAlgorithm.cpp BestFSAlgorithm.h
        AstarAlgorithm.cpp AstarAlgorithm.h MyClientHandler.cpp MyClientHandler.h MySerialServer.cpp MyParallelServer.cpp
        MyParallelServer.h DFSAlgorithm.cpp DFSAlgorithm.h)
