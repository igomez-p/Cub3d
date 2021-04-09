/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 13:36:24 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/16 16:04:48 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>
#include <stdarg.h>

int main ()
{
	int nb, nb1, nb2, nb3, nb4, nb5;
/*	int x;
	//int y;

	// Cadena sin conversiones
	x = printf("original\n");
	// Bytes escritos
	printf("%d\n", x);
*/
	ft_printf("---------------------------------\n");

	// Conversiones de caracter (c)
	ft_printf("CONVERSIONES DE CARACTER (c)\n");
		// la precisión no influye
		// flags 0 es ignorado cuando hay un flag - (Warning)
		// flag 0 -> undefined behavior
	ft_printf("%-0*cFIN\n", 4, 'x');		// añade (width - 1(char)) espacios a la dcha (ignora el 0)
	ft_printf("%0*cFIN\n", 4, 'x');		// añade (width - 1(char)) 0s a la izq
	ft_printf("%-*cFIN\n", 4, 'x');		// añade (width - 1(char)) espacios a la dcha
	ft_printf("%-cFIN\n", 'x');			// no influye el - sin otro flag
	ft_printf("%4c\n", 'x');				// añade * espacios a la izq - 1(char)
	ft_printf("%10c\n", 'x');				// añade * espacios a la izq - 1(char)

	ft_printf("---------------------------------\n");

	// Conversiones de string (s)
	ft_printf("CONVERSIONES DE STRING (s)\n");
		// flags 0 es ignorado cuando hay un flag - (Warning)
		// flag 0 -> undefined behavior
	ft_printf("%0*.7sFIN\n", 10, "hola");		// La precisión escoge solo los x primeros caracteres y el * añade el width
										// sobrante a la izq en forma de 0s
	ft_printf("%-0*.2sFIN\n", 4, "hola");		// La precisión escoge solo los x primeros caracteres y el * añade el width
										// sobrante a la dcha en forma de espacios
	ft_printf("%-*sFIN\n", 6, "hola");		// añade (width - len(char *)) a la dcha
	ft_printf("%-*.2sFIN\n", 4, "hola");	// . coge los 2 primeros char y añade (width - len(char *)) espacios a dcha
	ft_printf("%*.2sFIN\n", 4, "hola");	// . coge los 2 primeros char y añade (width - len(char *)) espacios a izq
	ft_printf("%*sFIN\n", 6, "hola");			// añade (width - len(char *)) espacios a la izq
	ft_printf("%-.2sFIN\n", "hola");
	ft_printf("%0.2sFIN\n", "hola");

		// Estos ejemplos de flags no influyen en la cadena
	ft_printf("X%-sFIN\n", "hola");
	ft_printf("X%0sFIN\n", "hola");
	ft_printf("X%-0sFIN\n", "hola");
	ft_printf("X%0.7sFIN\n", "hola");
	ft_printf("X%-.7sFIN\n", "hola");

	ft_printf("---------------------------------\n");

	// Conversiones de enteros (d)(i)
	ft_printf("CONVERSIONES DE ENTEROS (d)(i)\n");
		// flags 0 es ignorado cuando hay un flag - (Warning)
		// si el num dado como arg es de tipo double, añade tantos 0s como precisión o 1 si no está especificada
	ft_printf("%-0*.3dFIN\n", 4, 42);		// se cogen . int rellenando de 0s a la izq si fuera necesario completar
										// y el num sobrante rspcto al width se añade a la dcha en forma de espacio
	ft_printf("%0*.1dFIN\n", 4, -42);		// igual q el anterior pero el espacio se añade a la izq
	ft_printf("%-2.3dFIN\n", 42);			// se añade 0s a izq para completar la precisión y después se comprueba *
	ft_printf("%*dFIN\n", 4, -42);			// se añaden (width - len(int)) espacios a la izq, el - cuenta (len(-24) = 3)
	ft_printf("%-04.1dFIN\n", 42);			// se añaden (width - len(int)) espacios a la dcha, la precisión es menor q
										// len(int) por lo que no se rellena con 0s
	ft_printf("%-*.5dFIN\n", 7, -42);
	ft_printf("%*.5dFIN\n", 7, -42);
	ft_printf("%*.7dFIN\n", 5, 42);
	ft_printf("%0*dFIN\n", 4, -42);

			// Estos ejemplos de flags, no influyen en la impresión de la cadena
	ft_printf("%-dFIN\n", 42);
	ft_printf("%-0dFIN\n", 42);
	ft_printf("%0dFIN\n", 42);
	ft_printf("%*dFIN\n", 1, 42); // width < nº cifras
	ft_printf("%0*dFIN\n", 1, 42);
	ft_printf("%.1dFIN\n", 42);
	ft_printf("%-.1dFIN\n", 42);
	ft_printf("%-*.2dFIN\n", 2, 42);

	ft_printf("---------------------------------\n");


	// Conversiones de unsigned (u)
	nb = ft_printf("CONVERSIONES DE UNSIGNED (u)\n");
		// flags 0 es ignorado cuando hay un flag - (Warning)
		// argumentos negativos -> comportamiento indefinido
		// si el num dado como arg es de tipo double, añade tantos 0s como precisión o 1 si no está especificada
		// FUNCIONA COMO EL CASO DE ENTEROS
	nb1 = ft_printf("%0-*.3uFIN\n", 4, 42);		// El orden en presentar los flags 0 y - es indiferente
	nb2 = ft_printf("%0*.3uFIN\n", 4, -42);
	nb3 = ft_printf("%-4.3uFIN\n", 42);
	nb4 = ft_printf("%*uFIN\n", 4, 42);
	nb5 = ft_printf("%04.1uFIN\n", 42);
	ft_printf("%d %d %d %d %d %d\n", nb,  nb1, nb2, nb3, nb4, nb5);

	nb = ft_printf("---------------------------------\n");

	// Conversiones de hexadecimal sin signo (x)(X)
	nb1 = ft_printf("CONVERSIONES DE HEXADECIMAL SIN SIGNO (x)(X)\n");
		// ACTÚA COMO EL CASO NUMÉRICO PERO CONVIRTIENDO EL DECIMAL DADO A HEXADECIMAL
	nb2 = ft_printf("%-0*.3xFIN\n", 4, 42);
	nb3 = ft_printf("%0*.1XFIN\n", 4, 42);
	nb4 = ft_printf("%-*.3xFIN\n", 4, 42);
	nb5 = ft_printf("%*XFIN\n", 4, 42);
	ft_printf("%d %d %d %d %d %d\n", nb,  nb1, nb2, nb3, nb4, nb5);
	nb = ft_printf("%04.1XFIN\n", 42);

	nb1 = ft_printf("---------------------------------\n");
	ft_printf("%d %d\n", nb, nb1);


	// Conversiones de direcciones de memoria (p)
	ft_printf("CONVERSIONES DE DIRECCIONES DE MEMORIA(p)\n");
		// La conversión es como el caso hexadecimal, salvo que la cadena se compone por el nº
		// de la dirección de memoria (sin tener en cuenta el 0x). Por tanto, cuando hay que añadir
		// sólo precisión se hace entre 0x y el nº; al igual que si sólo se añade width. En el caso
		// de añadir precisión y width, la precisión se añade de dicha forma y el width en forma de
		// espacios (antes del 0x cuando se añaden a la izq).
		// Todo esto influye solo en los casos en los que la precisión y/o el width son > len(nº)

		// Solo -* y *
	char *ptr = ft_strdup("prueba puntero");

	nb = ft_printf("%pFIN\n", ptr);
	printf("%d \n", nb);
	ft_printf("%-pFIN\n", ptr);
	ft_printf("%0pFIN\n", ptr);
	ft_printf("%-0pFIN\n", ptr);

	ft_printf("%*pFIN\n", 20, ptr); // si
	ft_printf("%-*pFIN\n", 20, ptr); // si
	ft_printf("%0*pFIN\n", 20, ptr);
	ft_printf("%-0*pFIN\n", 20, ptr);

	ft_printf("%.3pFIN\n", ptr);
	ft_printf("%-.3pFIN\n", ptr);
	ft_printf("%0.3pFIN\n", ptr);
	ft_printf("%-0.3pFIN\n", ptr);
	// hasta aquí funciona incluso con undefined behavior
	ft_printf("%.17pFIN\n", ptr);
	ft_printf("%-.17pFIN\n", ptr);
	ft_printf("%0.17pFIN\n", ptr);
	ft_printf("%-0.17pFIN\n", ptr);

	ft_printf("%*.12pFIN\n", 20, ptr);
	ft_printf("%-*.3pFIN\n", 20, ptr);
	ft_printf("%0*.3pFIN\n", 20, ptr);
	ft_printf("%-0*.3pFIN\n", 20, ptr);

	// ARREGLAR ESTA PARTE (aunque no haría falta porque es undefined behavior)
	ft_printf("%*.17pFIN\n", 20, ptr);
	ft_printf("%-*.17pFIN\n", 20, ptr);
	ft_printf("%0*.17pFIN\n", 20, ptr);
	ft_printf("%-0*.17pFIN\n", 20, ptr);

	//printf("X%luX\n", &ptr);
	free(ptr);

	ft_printf("---------------------------------\n");
	// Carácter %
	ft_printf("CONVERSION CARACTER %%\n");
		// flags 0 es ignorado cuando hay un flag - (Warning)
	ft_printf("%-0*.3%FIN\n", 4); 			// añade un nº (*) - 1(tamaño char %) de espacios a la dcha
	ft_printf("%0*.3%\n", 4); 				// añade un nº (*) - 1(tamaño char %) de 0s a la izq
	ft_printf("%-04.3%FIN\n"); 			// añade un nº (*) - 1(tamaño char %) de espacios a la dcha
	ft_printf("%4.3%\n");					// añade un nº (*) - 1(tamaño char %) de espacios a la izq
	ft_printf("%10%\n");					// añade un nº (*) - 1(tamaño char %) de espacios a la izq

	return (0);
}
