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
	char *ptr;

	fpin = fopen("test.txt", "rt");
		if (fpin == NULL)   
		return;  // ошибка при открытии файла 

	fpout = fopen("result.txt", "wt");
		if (fpout == NULL)
		return;  // ошибка при открытии файла 

		while (!feof(fpin))// цикл до конца файла  
		{
			ptr = fgets(line, MAXLINE, fpin); //чтение строки
			if (ptr == NULL)
				break; // файл исчерпан

			while (*ptr != '\0') // цикл до конца строки 
			{
				if (*ptr == 1)
				{
					ptr = "one";
				}
				if (*ptr == 2)
				{
					ptr = "two";
				}
				if (*ptr == 3)
				{
					ptr = "three";
				}
				if (*ptr == 4)
				{
					ptr = "four";
				}
				ptr++;
			}
			fputs(line, fpout); // запись строки 
		}
		fclose(fpin); // закрыть входной файл  
		fclose( fpout ); // закрыть выходной файл 
		return 0;
}

