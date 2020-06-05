cmake_minimum_required(VERSION 3.15)
project(QuemQuerSerMilionarioProj C)

set(CMAKE_C_STANDARD 99)

add_executable(QuemQuerSerMilionarioProj main.c FuncoesJogo.c FuncoesJogo.h conio.c conio.h ListaPlayers.c ListaQuestion.c)