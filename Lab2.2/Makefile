# Kay Sweebe
# CS370
# Lab 2.2
#
# Yacc outputs y.tab.h, y.tab.c 
# Lex  outputs lex.yy.c
# 
#  
all:
	yacc -d lab2docalc.y
	lex lab2docalc.l
	gcc y.tab.c -o lab2docalc
