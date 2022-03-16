cmake_minimum_required(VERSION 3.21)
project(family_tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(family_tree main.cpp FamilyMemberNode.h FamilyMemberNode.cpp FamilyTree.h FamilyTree.cpp)
