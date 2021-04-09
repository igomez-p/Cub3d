#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int	main()
{
	// memset
	char str[50] = "Prueba número 1: memset original";
	memset(str, '$', 7);
	printf("memset string.h: %s\n", str);
	char str1[50] = "Prueba número 1: ft_memset";
	ft_memset(str1, '$', 7);
	printf("memset casero: %s\n\n", str1);

	// bzero
	bzero(str,(0));
	printf("bzero string.h n = 0: %s\n", str);
	char str2[50] = "Prueba número 1: memset original";
	bzero(str2, 4);
	printf("bzero string.h n = 4: %s\n", str2);

	ft_bzero(str1, (0));
	printf("bzero casero n = 0: %s\n", str1);
	ft_bzero(str1, 4);
	printf("bzero casero n = 4: %s\n\n", str1);

	// memcpy
	char x[50] = "Memcpy destino: prueba n3";
	char y[30] = "Memcpy origen";
	memcpy(x, y, 9);
	printf("memcpy string.h: %s\n", x);
	char z[50] = "Memcpy destino: prueba n3 casera";
	ft_memcpy(z, y, 9);
	printf("memcpy casera: %s\n\n", z);

	// memccpy
	char e[30] = "Esto va a cambiar";
	memccpy(e, "por esto", 't', 7);
	printf("memccpy string.h: %s\n", e);
	char t[30] = "Esto va a cambiar";
	ft_memccpy(t, "por esto", 't', 7);
	printf("memccpy casero: %s\n\n", t);

	// memmove
	char o[40] = "Memmove destino: prueba n4";
	memmove(o, y, 9);
	printf("memmove string.h: %s\n", o);
	char p[40] = "Memmove destino: prueba n4 casera";
	ft_memmove(p, y, 9);
	printf("memmove casera: %s\n\n", p);

	// memchr
	char *f = memchr(o, ':', 25);
	printf("memchr string.h: %s\n", f);
	f = memchr(str, 4, 5);
	printf("memchr string.h casonull: %s\n", f);
	char *f2 = ft_memchr(p, ':', 25);
	printf("memchr casero: %s\n", f2);
	f2 = ft_memchr(str1, 4, 5);
	printf("memchr casero casonull: %s\n\n", f2);

	// memcmp
	printf("memcmp string.h caso0: %d\n", memcmp("Otraprueba", "OtraPrueba", 3));
	printf("memcmp string.h: %d\n", memcmp("Otraprueba", "OtraPrueba", 6));
	printf("memcmp casera caso0: %d\n", ft_memcmp("Otraprueba", "OtraPrueba", 3));
	printf("memcmp casera: %d\n\n", ft_memcmp("Otraprueba", "OtraPrueba", 6));

	// strlen
	printf("strlen string.h: %lu\n", strlen("Prueba de longitud"));
	printf("strlen casera: %lu\n\n", ft_strlen("Prueba de longitud"));

	// isalpha
	printf("isalpha ctype.h: si %d, no %d\n", isalpha('a'), isalpha('3'));
	printf("isalpha casero: si %d, no %d\n\n", ft_isalpha('a'), ft_isalpha('3'));

	// isdigit
	printf("isdigit ctype.h: si %d, no %d\n", isdigit('2'), isdigit('a'));
	printf("isdigit casero: si %d, no %d\n\n", ft_isdigit('2'), ft_isdigit('a'));

	// isalnum
	printf("isalnum ctype.h: si %d, no %d\n", isalnum('f'), isalnum(' '));
	printf("isalnum casero: si %d, no %d\n\n", ft_isalnum('f'), ft_isalnum(' '));

	// isascii
	printf("isascii ctype.h: si %d\n", isascii('o'));
	printf("isascii casero: si %d\n\n", ft_isascii('o'));

	// isprint
	printf("isprint ctype.h: si %d, no %d\n", isprint('j'), isprint('\t'));
	printf("isprint casesro: si %d, no %d\n\n", ft_isprint('j'), ft_isprint('\t'));

	// toupper
	printf("toupper ctype.h: %c, %c, %c\n", toupper('a'), toupper('D'), toupper('1'));
	printf("toupper casero: %c, %c, %c\n\n", ft_toupper('a'), ft_toupper('D'), ft_toupper('1'));

	// tolower
	printf("tolower ctype.h: %c, %c, %c\n", tolower('U'), tolower('h'), tolower('3'));
	printf("tolower casero: %c, %c, %c\n\n", ft_tolower('U'), ft_tolower('h'), ft_tolower('3'));

	// strchr
	printf("strchr string.h: %s\n", strchr("42Madrid", 'p'));
	printf("strchr casero: %s\n\n", ft_strchr("42Madrid", 'p'));

	// strrchr
	printf("strrchr string.h: %s\n", strrchr("42Madrid", 'd'));
	printf("strrchr casero: %s\n\n", ft_strrchr("42Madrid", 'd'));

	// strncmp
	printf("strncmp string.h: %d\n", strncmp("abc", "ABC", 2));
	printf("strncmp casera: %d\n\n", ft_strncmp("abc", "ABC", 2));

	// strlcpy
	char ok[30] = "oaishdfa";
	char no[30] = "1233";
	strlcpy(ok, no, 3);
	printf("strlcpy string.h: %s\n", ok);
	char ok2[30] = "oaishdfa";
	ft_strlcpy(ok2, no, 3);
	printf("strlcpy casero: %s\n\n", ok2);

	// strlcat
	strlcat(no, "CONO", 9);
	printf("strlcat string.h: %s\n", no);
	char no2[30] = "1233";
	ft_strlcat(no2, "CONO", 9);
	printf("strlcat casero: %s\n\n", no2);

	// strnstr
	printf("strnstr string.h: %s\n", strnstr("42Madrid", "Mad", 6));
	printf("strnstr casero: %s\n\n", ft_strnstr("42Madrid", "Mad", 6));

	// atoi
	printf("atoi string.h: %d\n", atoi("1234"));
	printf("atoi casero: %d\n\n", ft_atoi("1234"));

	// calloc
	// strdup
	
	// substr
	char substrme[] = "     ";
	char setsubstr[] = " ";
	char *substrresult;
	substrresult = ft_substr(substrme, 18, 5);
	printf("substr!\n");
	free(substrresult);
	printf("%s\n", substrresult);
	// strjoin
	// strtrim
	char trimme[] = "     ";
	char settrim[] = " ";
	char *result;
	result = ft_strtrim(trimme, settrim);
	printf("TRIM!\n");
	free(result);
	printf("%s\n", result);
	// split
	char splitme[] = "     ";
	char setsplit[] = " ";
	char **splitresult;
	splitresult = ft_split(splitme, ' ');
	printf("split!\n");
	free(splitresult);
	printf("%s\n", result);
	// itoa
	// strmapi
	// putchar_ft
	// putstr_fd
	// putendl_fd
	// putnbr_fd

	return (0);
}
