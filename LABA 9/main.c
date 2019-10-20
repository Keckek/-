#pragma warning(disable : 4996) //необходимо для использования устаревших функций (scanf)
#include <stdio.h>

/*определение символических констант*/
#define YES 1
#define NO 0
#define MAXLINE 1024  // максимальная длина массива

int main(void)
{
	FILE *fpin;
	FILE *fpout;
	char line[MAXLINE];
	char mine[MAXLINE] = "";
	char *ptr;
	char *ptr2 = mine;

	fpin = fopen("C:\\Users\\ksal\\source\\repos\\LABA9\\file.txt", "rt");
		if (fpin == NULL)  
		return;  // ошибка при открытии файла 

	fpout = fopen("C:\\Users\\ksal\\source\\repos\\LABA9\\result.txt", "wt");
		if (fpout == NULL)
		return;  // ошибка при открытии файла 

		while (!feof(fpin))// цикл до конца файла  
		{
			ptr = fgets(line, MAXLINE, fpin); //чтение строки
			if (ptr == NULL)
				break; // файл исчерпан

			while (*ptr != '\0') // цикл до конца строки 
			{
				if (*ptr == '1' || *ptr == '2' || *ptr == '3' || *ptr == '4' || *ptr == '5' || *ptr == '6' || *ptr == '7' || *ptr == '8' || *ptr == '9' || *ptr == '0'  )
				{
					if (*ptr == '1')
					{
						*ptr2++ = 'O';
						*ptr2++ = 'n';
						*ptr2++ = 'e';
					}
					if (*ptr == '2')
					{
						*ptr2++ = 'T';
						*ptr2++ = 'w';
						*ptr2++ = 'o';

					}
					if (*ptr == '3')
					{
						*ptr2++ = 't';
						*ptr2++ = 'h';
						*ptr2++ = 'r';
						*ptr2++ = 'e';
						*ptr2++ = 'e';
					}
					if (*ptr == '4')
					{
						*ptr2++ = 'f';
						*ptr2++ = 'o';
						*ptr2++ = 'u';
						*ptr2++ = 'r';
					}
					if (*ptr == '5')
					{
						*ptr2++ = 'f';
						*ptr2++ = 'i';
						*ptr2++ = 'v';
						*ptr2++ = 'e';
					}
				}
				else 
				{
					ptr2 = *ptr;
				}
				*ptr2++;
				*ptr++;
			}
			fputs(mine, fpout); // запись строки 
		}
		fclose(fpin); // закрыть входной файл  
		fclose( fpout ); // закрыть выходной файл 
		return 0;
}			
