CC       = gcc-11
EXTRACFLAGS =
CFLAGS	 = -O0
WFLAGS	 = -std=gnu11 -Wall -Wextra -g
CPPFLAGS =
LDFLAGS	 = -lm

PROG	= dendritas
OBJS    = xoshiro.o core.o dendritas.o
SRCS    = $(shell echo *.c)

all: $(PROG)

dendritas: $(OBJS)
	$(CC) $(WFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(WFLAGS) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(PROG) *.o .depend

.depend: $(SRCS)
	$(CC) -MM $^ > $@

-include .depend

.PHONY: all clean

################################################################################
####################							COMENTARIOS
################################################################################
#
# Una variable ya declarada se llama con $() o con ${}.
#
# Variables reservadas para compilar con C:
#			* CC --> compilador de C
#			* CFLAGS --> flags para el compilador de C
#			* WFLAGS --> extrictamente sería CFLAGS, pero es para distinguir mejor
#			* CPPFLAGS --> flags para el preprocesador de C
#			* LDFLAGS --> flags para cuando C llama al linker
#
# PROG --> nombre de lo que quiero crear
# OBJS --> nombre de los object files
# shell --> fución que sale de make para hacer algo por fuera
# echo *.c --> en bash es pedir que imprima en terminal todo lo *.c
#
# Cuando corre make sin parámetros, corre la primera regla que aparece
# Las reglas son--> PROG: prerequisites y abajo tabulado los comandos
#
# Variables especiales:
#			* $@ --> sustituye por los PROG de la regla
#			* $^ --> sustituye por TODOS los prerequisites de la regla
#			* $< --> sustituye por EL PRIMER prerequisite de la regla
#
# Wildcards (comodines):
#			* * --> cualquier conjunto de caractéres siempre que tenga ese sufijo
#			* % --> permite definir reglas implícitas a partir de patrones
#							útil para generar object files (.o)
#
# Otras cosas:
#			* -c --> compila un source file de C (.c)
#			* -o --> genera un output con el nombre a continuación
#
# Un clásico de C (regla implícita - no hace falta escribir):
# %.o: %.c
# 	$(CC) $(WFLAGS) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
#
# Reglas de dependencias:
#		El compilador $(CC) al usar -MM printea las líneas con las reglas de
#		dependencia necesarias $^. Ahora están listas para ser usadas por make.
#		Estas reglas las imprime (>) en un archivo llamado según $@.
#		Para que make las tome, indicamos que llame al archivo $@ con -include.
#
# .depend: $(SRCS)
# 	$(CC) -MM $^ > $@
#
# -include .depend
#
# Phony previene que make confunda el phony target con un file de dicho nombre
#
# Función para especificar dónde encontrar un conjunto de prerequisitos:
# vpath <patron> <directorios separados por espacios>
