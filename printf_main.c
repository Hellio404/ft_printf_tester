/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 14:19:05 by yfarini           #+#    #+#             */
/*   Updated: 2020/01/30 18:45:36 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "ft_printf.h"
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
pid_t   pid;
int    	sign;
int		status;
FILE	*fp;
#define RED 	"\033[0;31m"
#define GREEN 	"\033[0;32m"
#define YELLOW 	"\033[0;33m"
#define RST	"\033[0m"


# define SEGF(func) do { \
	if ((pid = fork()) < 0) \
		exit(EXIT_FAILURE); \
	if (pid == 0) { \
		do { func; } while(0); \
		exit(EXIT_SUCCESS); \
	} else { \
		wait(&pid); \
		sign = WIFSIGNALED(pid); \
	} \
} while(0)

#define	SP(file,...)	do{\
					fp = fopen(file, "a+");\
					fprintf(fp,__VA_ARGS__);\
					fclose(fp);\
				}while(0)

#define T(...)	do{\
                    SEGF(printf("\tReturn: %d\n", ft_printf(__VA_ARGS__)));\
					if(sign)\
						printf("SEGV\n");\
					SP("EXPECTED","\tReturn: %d\n", fprintf(fp, __VA_ARGS__));\
					SP("TESTS","%s\n", #__VA_ARGS__);\
                }while(0)
int main()
{
	setbuf(stdout,NULL);
	printf("--> \"%%d\" SIMPLE\n");
	SP("EXPECTED","--> \"%%d\" SIMPLE\n");
	SP("TESTS","--> \"%%d\" SIMPLE\n");
    T("%d", 100);
	T("%d", INT32_MIN);
	T("%d", INT32_MAX + 95);
	T("%d", 0);
	T("a%da", 100);
	T("a%da", INT32_MIN);
	T("a%da", 0);
	
	printf("--> \"%%u\" SIMPLE\n");
	SP("EXPECTED","--> \"%%u\" SIMPLE\n");
	SP("TESTS","--> \"%%u\" SIMPLE\n");
    T("%u", 100);
	T("%u", UINT32_MAX);
	T("%u", UINT32_MAX + 95);
	T("%u", 0);
	T("a%ua", 100);
	T("a%ua", UINT32_MAX);
	T("a%ua", 0);
	
	printf("--> \"%%x && %%X\" SIMPLE\n");
	SP("EXPECTED","--> \"%%x && %%X\" SIMPLE\n");
	SP("TESTS","--> \"%%x && %%X\" SIMPLE\n");
    T("%x", 100);
	T("%x", UINT32_MAX);
	T("%x", UINT32_MAX + 95);
	T("%x", 0);
	T("a%xa", 100);
	T("a%xa", UINT32_MAX);
	T("a%xa", 0);
	T("%X", 100);
	T("%X", UINT32_MAX);
	T("%X", UINT32_MAX + 95);
	T("%X", 0);
	T("a%Xa", 100);
	T("a%Xa", UINT32_MAX);
	T("a%Xa", 0);

	printf("--> \"%%p\" SIMPLE\n");
	SP("EXPECTED","--> \"%%p\" SIMPLE\n");
	SP("TESTS","--> \"%%p\" SIMPLE\n");
    T("%p", (void *)0x100);
	T("%p", (void *)UINT64_MAX);
	T("%p", (void *)0x0);
	T("a%pa", (void *)0x100);
	T("a%pa", (void *)UINT64_MAX);
	T("a%pa", (void *)0);
	
	printf("--> \"%%s\" SIMPLE\n");
	SP("EXPECTED","--> \"%%s\" SIMPLE\n");
	SP("TESTS","--> \"%%s\" SIMPLE\n");
    T("%s", "Hello");
	T("%s", "");
	T("%s", NULL);
	T("a%sa", "Hello");
	T("a%sa", "");
	T("a%sa", NULL);
	T("%s", "%15d");
	
	printf("--> \"%%c\" SIMPLE\n");
	SP("EXPECTED","--> \"%%c\" SIMPLE\n");
	SP("TESTS","--> \"%%c\" SIMPLE\n");
    T("%c", 97);
	T("a%ca", 97);
	// T("%c", 0);  // TODO
	// T("a%ca", 0);	// TODO
	
	/*
	*******************************************
	*******************************************
	*/

	printf("--> \"%%d\" MIN_WIDTH\n");
	SP("EXPECTED","--> \"%%d\" MIN_WIDTH\n");
	SP("TESTS","--> \"%%d\" MIN_WIDTH\n");
    T("%2d", 100);
	T("%3d", 100);
	T("a%3da", 100);
	T("%4d", 100);
	T("%2d", -100);
	T("%3d", -100);
	T("%4d", -100);
	T("%4d", 0);
	T("%1d", 0);
	T("a%1da", 0);
	
	printf("--> \"%%p\" MIN_WIDTH\n");
	SP("EXPECTED","--> \"%%p\" MIN_WIDTH\n");
	SP("TESTS","--> \"%%p\" MIN_WIDTH\n");
	T("%2p", (void *)100);
	T("%3p", (void *)100);
	T("%4p", (void *)100);
	T("a%4pa", (void *)100);
	T("%6p", (void *)100);
    T("%4p", (void *)0x0);
	T("%1p", (void *)0x0);
	T("a%1pa", (void *)0x0);
	
	printf("--> \"%%s\" MIN_WIDTH\n");
	SP("EXPECTED","--> \"%%s\" MIN_WIDTH\n");
	SP("TESTS","--> \"%%s\" MIN_WIDTH\n");
    T("%2s", "ABC");
	T("%3s", "ABC");
	T("%4s", "ABC");
	T("a%4sa", "ABC");
	T("%1s", NULL);
	T("a%1sa", NULL);
	T("%6s", NULL);
	T("%7s", NULL);
	T("%4s", "");
	T("%1s", "");
	T("a%1sa", "");
	
	/*
	*******************************************
	*******************************************
	*/
	printf("--> \"%%d\" MIN_WIDTH AND -\n");
	SP("EXPECTED","--> \"%%d\" MIN_WIDTH AND -\n");
	SP("TESTS","--> \"%%d\" MIN_WIDTH AND -\n");
    T("%-2d", 100);
	T("%-3d", 100);
	T("a%-3da", 100);
	T("%-4d", 100);
	T("%-2d", -100);
	T("%-3d", -100);
	T("%-4d", -100);
	T("%-4d", 0);
	T("%-1d", 0);
	T("a%-1da", 0);
	
	printf("--> \"%%p\" MIN_WIDTH AND -\n");
	SP("EXPECTED","--> \"%%p\" MIN_WIDTH AND -\n");
	SP("TESTS","--> \"%%p\" MIN_WIDTH AND -\n");
	T("%-2p", (void *)100);
	T("%-3p", (void *)100);
	T("%-4p", (void *)100);
	T("a%-4pa", (void *)100);
	T("%-6p", (void *)100);
    T("%-4p", (void *)0x0);
	T("%-1p", (void *)0x0);
	T("a%-1pa", (void *)0x0);
	
	printf("--> \"%%s\" MIN_WIDTH AND -\n");
	SP("EXPECTED","--> \"%%s\" MIN_WIDTH AND -\n");
	SP("TESTS","--> \"%%s\" MIN_WIDTH AND -\n");
    T("%-2s", "ABC");
	T("%-3s", "ABC");
	T("%-4s", "ABC");
	T("a%-4sa", "ABC");
	T("%-1s", NULL);
	T("a%-1sa", NULL);
	T("%-6s", NULL);
	T("%-7s", NULL);
	T("%-4s", "");
	T("%-1s", "");
	T("a%-1sa", "");
	
	/*
	*******************************************
	*******************************************
	*/
	printf("--> \"%%d\" MIN_WIDTH AND 0\n");
	SP("EXPECTED","--> \"%%d\" MIN_WIDTH AND 0\n");
	SP("TESTS","--> \"%%d\" MIN_WIDTH AND 0\n");
    T("%02d", 100);
	T("%03d", 100);
	T("a%03da", 100);
	T("%04d", 100);
	T("%02d", -100);
	T("%03d", -100);
	T("%05d", -100);
	T("%04d", 0);
	T("%01d", 0);
	T("a%01da", 0);
	
	/*
	*******************************************
	*******************************************
	*/
	printf("--> \"%%d\" MIN_WIDTH AND .\n");
	SP("EXPECTED","--> \"%%d\" MIN_WIDTH AND .\n");
	SP("TESTS","--> \"%%d\" MIN_WIDTH AND .\n");
    T("%2.3d", 100);
	T("%3.3d", 100);
	T("a%3.3da", 100);
	T("%4.3d", 100);
	T("%2.3d", -100);
	T("%3.3d", -100);
	T("%4.3d", -100);
	T("%4.3d", 0);
	T("%1.3d", 0);
	T("a%1.3da", 0);
	T("%2.0d", 100);
	T("%3.0d", 100);
	T("a%3.0da", 100);
	T("%4.0d", 100);
	T("%2.0d", -100);
	T("%3.0d", -100);
	T("%4.0d", -100);
	T("%4.0d", 0);
	T("%1.0d", 0);
	T("%4.d", 100);
	T("%2.d", -100);
	T("%3.d", -100);
	T("%4.d", -100);
	T("%4.d", 0);
	T("%1.d", 0);
	T("a%1.0da", 0);
	T("%2.7d", 100);
	T("%15.7d", 100);
	T("a%3.7da", 100);
	T("%4.7d", 100);
	T("%2.7d", -100);
	T("%3.7d", -100);
	T("%15.7d", -100);
	T("%4.7d", 0);
	T("%1.7d", 0);
	T("a%1.7da", 0);
	/*
	printf("--> \"%%p\" MIN_WIDTH AND .\n");
	SP("EXPECTED","--> \"%%p\" MIN_WIDTH AND .\n");
	SP("TESTS","--> \"%%p\" MIN_WIDTH AND .\n");
	T("%2.3p", (void *)100);
	T("%3.3p", (void *)100);
	T("%4.3p", (void *)100);
	T("a%4.3pa", (void *)100);
	T("%6.3p", (void *)100);
    T("%4.3p", (void *)0x0);
	T("%1.3p", (void *)0x0);
	T("a%1.3pa", (void *)0x0);*/
	
	printf("--> \"%%s\" MIN_WIDTH AND .\n");
	SP("EXPECTED","--> \"%%s\" MIN_WIDTH AND .\n");
	SP("TESTS","--> \"%%s\" MIN_WIDTH AND .\n");
    T("%2.3s", "ABC");
	T("%3.3s", "ABC");
	T("%4.3s", "ABC");
	T("a%4.3sa", "ABC");
	T("%1.3s", NULL);
	T("a%1.3sa", NULL);
	T("%6.3s", NULL);
	T("%7.3s", NULL);
	T("%4.3s", "");
	T("%1.3s", "");
	T("a%1.3sa", "");
	T("%2.2s", "ABC");
	T("%3.2s", "ABC");
	T("%4.2s", "ABC");
	T("a%4.2sa", "ABC");
	T("%1.2s", NULL);
	T("a%1.2sa", NULL);
	T("%6.2s", NULL);
	T("%7.2s", NULL);
	T("%4.2s", "");
	T("%1.2s", "");
	T("a%1.2sa", "");
	T("%2.10s", "ABC");
	T("%3.10s", "ABC");
	T("%4.10s", "ABC");
	T("a%4.10sa", "ABC");
	T("%1.10s", NULL);
	T("a%1.10sa", NULL);
	T("%6.10s", NULL);
	T("%7.10s", NULL);
	T("%4.10s", "");
	T("%1.10s", "");
	T("a%1.10sa", "");
	T("%2.s", "ABC");
	T("%3.s", "ABC");
	T("%4.s", "ABC");
	T("a%4.sa", "ABC");
	T("%1.s", NULL);
	T("a%1.sa", NULL);
	T("%6.s", NULL);
	T("%7.s", NULL);
	T("%4.s", "");
	T("%1.s", "");
	T("a%1.sa", "");

	/*
	*******************************************
	*******************************************
	*/
	printf("--> \"%%d\" ONLY .\n");
	SP("EXPECTED","--> \"%%d\" ONLY .\n");
	SP("TESTS","--> \"%%d\" ONLY .\n");
    T("%.3d", 100);
	T("%.3d", 100);
	T("a%.3da", 100);
	T("%.3d", 100);
	T("%.3d", -100);
	T("%.3d", -100);
	T("%.3d", -100);
	T("%.3d", 0);
	T("%.3d", 0);
	T("a%.3da", 0);
	T("%.0d", 100);
	T("%.0d", 100);
	T("a%.0da", 100);
	T("%.0d", 100);
	T("%.0d", -100);
	T("%.0d", -100);
	T("%.0d", -100);
	T("%.0d", 0);
	T("%.0d", 0);
	T("%.d", 100);
	T("%.d", -100);
	T("%.d", -100);
	T("%.d", -100);
	T("%.d", 0);
	T("%.d", 0);
	T("a%.0da", 0);
	T("%.7d", 100);
	T("%5.7d", 100);
	T("a%.7da", 100);
	T("%.7d", 100);
	T("%.7d", -100);
	T("%.7d", -100);
	T("%5.7d", -100);
	T("%.7d", 0);
	T("%.7d", 0);
	T("a%.7da", 0);
	/*
	printf("--> \"%%p\" ONLY .\n");
	SP("EXPECTED","--> \"%%p\" ONLY .\n");
	SP("TESTS","--> \"%%p\" ONLY .\n");
	T("%.3p", (void *)100);
	T("%.3p", (void *)100);
	T("%.3p", (void *)100);
	T("a%.3pa", (void *)100);
	T("%.3p", (void *)100);
    T("%.3p", (void *)0x0);
	T("%.3p", (void *)0x0);
	T("a%.3pa", (void *)0x0);*/
	
	printf("--> \"%%s\" ONLY .\n");
	SP("EXPECTED","--> \"%%s\" ONLY .\n");
	SP("TESTS","--> \"%%s\" ONLY .\n");
    T("%.3s", "ABC");
	T("%.3s", "ABC");
	T("%.3s", "ABC");
	T("a%.3sa", "ABC");
	T("%.3s", NULL);
	T("a%.3sa", NULL);
	T("%.3s", NULL);
	T("%.3s", NULL);
	T("%.3s", "");
	T("%.3s", "");
	T("a%.3sa", "");
	T("%.2s", "ABC");
	T("%.2s", "ABC");
	T("%.2s", "ABC");
	T("a%.2sa", "ABC");
	T("%.2s", NULL);
	T("a%.2sa", NULL);
	T("%.2s", NULL);
	T("%.2s", NULL);
	T("%.2s", "");
	T("%.2s", "");
	T("a%.2sa", "");
	T("%.10s", "ABC");
	T("%.10s", "ABC");
	T("%.10s", "ABC");
	T("a%.10sa", "ABC");
	T("%.10s", NULL);
	T("a%.10sa", NULL);
	T("%.10s", NULL);
	T("%.10s", NULL);
	T("%.10s", "");
	T("%.10s", "");
	T("a%.10sa", "");
	T("%.s", "ABC");
	T("%.s", "ABC");
	T("%.s", "ABC");
	T("a%.sa", "ABC");
	T("%.s", NULL);
	T("a%.sa", NULL);
	T("%.s", NULL);
	T("%.s", NULL);
	T("%.s", "");
	T("%.s", "");
	T("a%.sa", "");
	
	/*
	*******************************************
	*******************************************
	*/
	printf("--> \"%%s\" *\n");
	SP("EXPECTED","--> \"%%s\" *\n");
	SP("TESTS","--> \"%%s\" *\n");
    T("%*.3s", 5, "ABC");
	T("%*.3s", 5, "ABC");
	T("%*.3s", 5, "ABC");
	T("a%*.3sa", 5, "ABC");
	T("%*.3s", 5, NULL);
	T("a%*.3sa", 5, NULL);
	T("%*.3s", 5, NULL);
	T("%*.3s", 5, NULL);
	T("%*.3s", 5, "");
	T("%*.3s", 5, "");
	T("a%*.3sa", 5, "");
	T("%*.2s", 5, "ABC");
	T("%*.2s", 5, "ABC");
	T("%*.2s", 5, "ABC");
	T("a%*.2sa", 5, "ABC");
	
	T("%*.3s", 0, "ABC");
	T("%*.3s", 0, "ABC");
	T("%*.3s", 0, "ABC");
	T("a%*.3sa", 0, "ABC");
	T("%*.3s", 0, NULL);
	T("a%*.3sa", 0, NULL);
	T("%*.3s", 0, NULL);
	T("%*.3s", 0, NULL);
	T("%*.3s", 0, "");
	T("%*.3s", 0, "");
	T("a%*.3sa", 0, "");
	T("%*.2s", 0, "ABC");
	T("%*.2s", 0, "ABC");
	T("%*.2s", 0, "ABC");
	T("a%*.2sa", 0, "ABC");

	T("%*.3s", -15, "ABC");
	T("%*.3s", -15, "ABC");
	T("%*.3s", -15, "ABC");
	T("a%*.3sa", -15, "ABC");
	T("%*.3s", -15, NULL);
	T("a%*.3sa", -15, NULL);
	T("%*.3s", -15, NULL);
	T("%*.3s", -15, NULL);
	T("%*.3s", -15, "");
	T("%*.3s", -15, "");
	T("a%*.3sa", -15, "");
	T("%*.2s", -15, "ABC");
	T("%*.2s", -15, "ABC");
	T("%*.2s", -15, "ABC");
	T("a%*.2sa", -15, "ABC");
	printf("--> \"%%s\" * part2 ;)\n");
	SP("EXPECTED","--> \"%%s\" * part2 ;)\n");
	SP("TESTS","--> \"%%s\" * part2 ;)\n");
	T("%.*s", 5, "ABC");
	T("%.*s", 5, "ABC");
	T("%.*s", 5, "ABC");
	T("a%.*sa", 5, "ABC");
	T("%.*s", 5, NULL);
	T("a%.*sa", 5, NULL);
	T("%.*s", 5, NULL);
	T("%.*s", 5, NULL);
	T("%.*s", 5, "");
	T("%.*s", 5, "");
	T("a%.*sa", 5, "");
	T("%.*s", 5, "ABC");
	T("%.*s", 5, "ABC");
	T("%.*s", 5, "ABC");
	T("a%.*sa", 5, "ABC");
	
	T("%.*s", -5, "ABC");
	T("%.*s", -5, "ABC");
	T("%.*s", -5, "ABC");
	T("a%.*sa", -5, "ABC");
	T("%.*s", -5, NULL);
	T("a%.*sa", -5, NULL);
	T("%.*s", -5, NULL);
	T("%.*s", -5, NULL);
	T("%.*s", -5, "");
	T("%.*s", -5, "");
	T("a%.*sa", -5, "");
	T("%.*s", -5, "ABC");
	T("%.*s", -5, "ABC");
	T("%.*s", -5, "ABC");
	T("a%.*sa", -5, "ABC");

	T("%*.*s", 7,2, "ABC");
	T("%*.*s", 7,2, "ABC");
	T("%*.*s", 7,2, "ABC");
	T("a%*.*sa", 7,2, "ABC");
	T("%*.*s", 7,2, NULL);
	T("a%*.*sa", 7,2, NULL);
	T("%*.*s", 7,2, NULL);
	T("%*.*s", 7,2, NULL);
	T("%*.*s", 7,2, "");
	T("%*.*s", 7,2, "");
	T("a%*.*sa", 7,2, "");
	T("%*.*s", 7,2, "ABC");
	T("%*.*s", 7,2, "ABC");
	T("%*.*s", 7,2, "ABC");
	T("a%*.*sa", 7,2, "ABC");
	printf("--> \"%%cspdiuxX\" LAST PART ;)\n");
	SP("EXPECTED","--> \"%%cspdiuxX\" LAST PART ;)\n");
	SP("TESTS","--> \"%%cspdiuxX\" LAST PART ;)\n");
	T("TEST TEST 0000%%%*.*s%%%-15.8dTEST%-15.8u0000000\t%%%15%%.3%", 7,5, "ABC",15,0);
	T("TEST TEST 0000%%%*.*s%%%-15.8dTEST%-15.8u0000000\t%%%15%%.3% %---15d %00015x", 7,5, "ABC",15,0,20,0x99);
	T("***************%*s%*d**************%*u*************", 10, "coucou", 10, 10, -50, 20);
	T("ultimate2 %*d %*s %*x %*X %*i %*u\n", 1, 5000, 1, "hey", 10, 54700, 1, 300, 10000, -55, 1, -60);
	T("ultimate3 %*.*d %*.*s\n", 1, 50, 5000, 1, 0, "hey");
	T("ultimate4 %*.*x %*.*X\n", 1, 50, 5000, 1, 0, 10);
}