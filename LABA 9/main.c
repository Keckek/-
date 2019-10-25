#pragma warning(disable : 4996) //необходимо для использования устаревших функций (scanf)
#include <stdio.h>
#define MAXLINE 1024 // максимальная длина массива

int main(void)
{
	FILE *fpin;
	FILE *fpout;
	char line[MAXLINE];
	char mine[MAXLINE];
	char *ptr;
	char *ptr2 = mine;

	fpin = fopen("C:\\Users\\ksal\\source\\repos\\LABA9\\file.txt", "rt");
	if (fpin == NULL)
		return 0; // ошибка при открытии файла

	fpout = fopen("C:\\Users\\ksal\\source\\repos\\LABA9\\result.txt", "wt");
	if (fpout == NULL)
		return 0; // ошибка при открытии файла

	while (!feof(fpin))// цикл до конца файла
	{

		ptr = fgets(line, MAXLINE, fpin); //чтение строки
		
		if (ptr == NULL)
			break; // файл исчерпан
		

		while (*ptr != '\0') // цикл до конца строки
		{
			if (*ptr == '1' || *ptr == '2' || *ptr == '3' || *ptr == '4' || *ptr == '5' || *ptr == '6' || *ptr == '7' || *ptr == '8' || *ptr == '9' || *ptr == '0')
			{
				if (*ptr == '1')
				{
					*ptr2++ = 'O';
					*ptr2++ = 'n';
					*ptr2++ = 'e';
				}
				if (*ptr == '2')
				{
					*ptr2++= 'T';
					*ptr2++ = 'w';
					*ptr2++ = 'o';

				}
				if (*ptr == '3')
				{
					*ptr2++ = 'T';
					*ptr2++ = 'h';
					*ptr2++ = 'r';
					*ptr2++ = 'e';
					*ptr2++ = 'e';
				}
				if (*ptr == '4')
				{
					*ptr2++ = 'F';
					*ptr2++ = 'o';
					*ptr2++ = 'u';
					*ptr2++ = 'r';
				}
				if (*ptr == '5')
				{
					*ptr2++ = 'F';
					*ptr2++ = 'i';
					*ptr2++ = 'v';
					*ptr2++ = 'e';
				}
				if (*ptr == '6')
				{
					*ptr2++ = 'S';
					*ptr2++ = 'i';
					*ptr2++ = 'x';
				}
				if (*ptr == '7')
				{
					*ptr2++ = 'S';
					*ptr2++ = 'e';
					*ptr2++ = 'v';
					*ptr2++ = 'e';
					*ptr2++ = 'n';
				}
				if (*ptr == '8')
				{
					*ptr2++ = 'E';
					*ptr2++ = 'i';
					*ptr2++ = 'g';
					*ptr2++ = 'h';
					*ptr2++ = 't';
				}
				if (*ptr == '9')
				{
					*ptr2++ = 'N';
					*ptr2++ = 'i';
					*ptr2++ = 'n';
					*ptr2++ = 'e';
				}
				if (*ptr == '0')
				{
					*ptr2++ = 'Z';
					*ptr2++ = 'e';
					*ptr2++ = 'r';
					*ptr2++ = 'o';
				}
			}
			else
			{
				*ptr2= *ptr;
				*ptr2++;
			}
			
			ptr++;
		}
		*ptr2 = '\0';
		fputs(mine, fpout); // запись строки
		
		
	}
	fputs(mine, fpout); // запись строки
	fclose(fpin); // закрыть входной файл
	fclose(fpout); // закрыть выходной файл
	return 0;
}
