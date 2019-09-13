# include <stdio.h>
# define MAXLINE 1000
#define YES 1
#define NO 0

void process_line(char buffer[]);

int main(void)
{
	char line[MAXLINE];
	printf("please, enter some words \n");
	gets(line);
	process_line(line);
	puts(line);
	return 0;
}

void process_line(char buffer[])
{
	char c;// Текущий символ
	int i = 0;//счетчик всех букв
	int word = NO;//признак слова
	int symb = NO;//индикатор наличия лишних символов
	int cur = 0;//позиция текущего символа исходной строки
	int res = 0;//позиция текущего символа результирующей строк
	int start;
	int cnt = 0;
	int maximum = 0;
	int max = 0;//макимальное количество букв
	int b = 0;//адресс начала максимального слова 
	int j = 0;

	do
	{
		c = buffer[cur]; // взять текущий символ из буфера
		if (c == ' ' || c == '.' || c == ',' || c == '\n' || c == '\0' || c == '?' || c == '!' || c == ';' || c == ':' ||
			c == '-' || c == '_' || c == '(' || c == ')' || c == '\t' || c == '/' || c == '&' || c == '"') // разделитель найден
		{
			if (word == YES && symb == NO)
			{
				if (i > max)
				{
					max = i;
					b = start;
				}
			}
			word = NO;
			i = 0;
		}
		else
		{
			if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) // проверить не является ли этот символ лишним
			{
				symb = YES; // в слове есть лишний символ
			}
			if (word == NO) // найдена первая буква слова
			{
				start = cur; // запомнить позицию начала слова
			}
			word = YES;
			i++;
		}
		cur++;
	} while (c != '\0');
	for (j = 0; j <= cur; j++)
	{
		if (j == b)
		{
			j = j + max + 1;
		}
		buffer[res++] = buffer[j];
	}
}
