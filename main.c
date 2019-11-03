/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:59:15 by yfarini           #+#    #+#             */
/*   Updated: 2019/11/02 23:48:12 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <stdio.h>
#include  <stdlib.h>
#include  <fcntl.h>
#include  <string.h>
#include "get_next_line.h"
#define   RED 		"\033[0;31m"
#define   GREEN 	"\033[0;32m"
#define   YELLOW 	"\033[0;33m"
#define   RST		"\033[0m"



int main()
{
	int		fp0 = open("TESTS",O_RDONLY);
	int		fp1 = open("OUT",O_RDONLY);
	int		fp2 = open("EXPECTED",O_RDONLY);
	FILE	*deepthought = fopen("deepthought","a+");
	int		k = 0;
	int		is_f = 0;
	char	*line0 = NULL;
	char	*line1 = NULL;
	char	*line2 = NULL;
	
	setbuf(stdout,NULL);
	if (!fp0 || !fp1 || !fp2)
	{
		printf("FAILED TO OPEN A ONE OF THE FILES!\n");
		return (0377);
	}
	while (get_next_line(fp0, &line0) > 0)
	{
		if (line0[0] == '-')
		{
			if (is_f)
				fprintf(deepthought, "------------------------------------------------------------------------------------------------\n\n\n");
			if(k)
				printf("\n");
			printf("\n%s%s%s\n",YELLOW,strchr(line0, '"'),RST);
			is_f = 0;
		}
		get_next_line(fp1, &line1);
		get_next_line(fp2 ,&line2);

		if (line0[0] != '-')
		{
			if (strcmp(line1, line2))
			{
				is_f = 1;
				fprintf(deepthought,"TESTED : %s\nprintf :    |%s\nft_printf : |%s\n\n",line0,line2,line1);
				printf("%sKO%s ",RED,RST);
				
			}
			else 
				printf("%sOK%s ",GREEN,RST);
		}
		k++;
	}
	return (0);
}