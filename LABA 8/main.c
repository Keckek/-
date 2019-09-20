#pragma warning(disable : 4996)
#include <stdio.h>
#define YES 1
#define NO 0
#define MAXLINE 1000

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
	int f = 0;// счетчик лишних символов
	int word = NO;//признак слова
	int symb = NO;//индикатор наличия лишних символов
	int vowel = 0;//счетчик гласных букв
	int conso = 0;// счетски согласных букв
	char *in_ptr; // указатель на текущий символ входной строки  
	char *out_ptr;   // указатель на текущий символn выходной строки  
	char *word_ptr; // указатель на начало слова 
	word_ptr = buffer;
	in_ptr = buffer;
	out_ptr = buffer;

	do
	{
		c = *in_ptr; // взять текущий символ из буфера
		if (c == ' ' || c == '.' || c == ',' || c == '\n' || c == '\0' || c == '?' || c == '!' || c == ';' || c == ':' ||
			c == '-' || c == '_' || c == '(' || c == ')' || c == '\t' || c == '/' || c == '&' || c == '"') // разделитель найден
		{
			if (symb == NO && word == YES && conso >= vowel)
			{
				while (word_ptr < in_ptr)

					*out_ptr++ = *word_ptr++; 
			}
			word = NO;
			symb = NO;
			conso = 0;
			vowel = 0;
			*out_ptr++ = c;
		}

		else
		{
			if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) // проверить не является ли этот символ лишним
			{
				symb = YES; // в слове есть лишний символ
				f++;
			}
			if (word == NO) // найдена первая буква слова
			{
				word_ptr = in_ptr; // запомнить позицию начала слова
			}
			if (c == 'e' || c == 'y' || c == 'u' || c == 'i' || c == 'o' || c == 'a' ||
				c == 'E' || c == 'Y' || c == 'U' || c == 'I' || c == 'O' || c == 'A') // если была найдена гл буква, то выполнить...
			{
				vowel++;
			}
			if (c == 'b' || c == 'c' || c == 'd' || c == 'f' || c == 'g' || c == 'h' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't'
				|| c == 'v' || c == 'w' || c == 'x' || c == 'z' || c == 'B' || c == 'C' || c == 'D' || c == 'F' || c == 'G' || c == 'H' || c == 'J' || c == 'K' || c == 'L' || c == 'M' || c == 'N' ||
				c == 'P' || c == 'Q' || c == 'R' || c == 'S' || c == 'T' || c == 'V' || c == 'W' || c == 'X' || c == 'Z')
			{
				conso++;
			}
			word = YES;
		}

		in_ptr++;
	} while (c != '\0'); // продолжать до конца строки
	if (f > 0)
		printf("words contain extra symbols, such words are deleted \n");
}
