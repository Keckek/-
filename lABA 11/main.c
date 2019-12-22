#pragma warning(disable : 4996)
#include <stdio.h>
#include <windows.h>
#define MAXLEN 40

void main(void)
{
	HANDLE hStdout; // дескриптор консольного окна
	FILE *fpin;
	char line[MAXLEN]; // строчка из файла

	char *begin = NULL;
	char *end = NULL;
	int flag = 0;
	int prec;
	char *ptr = NULL; // указатель на строчку

	WORD foregroundColor; // цвет символа
	WORD backgroundColor; // цвет фона
	WORD foregroundColor1; // цвет символа1
	WORD backgroundColor1; // цвет фона1
	WORD textAttribute; // атрибут текста - цвет символа и фона
	foregroundColor = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
	backgroundColor = BACKGROUND_INTENSITY | BACKGROUND_RED;
	foregroundColor1 = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
	backgroundColor1 = BACKGROUND_INTENSITY | BACKGROUND_BLUE;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	textAttribute = foregroundColor | backgroundColor;
	SetConsoleTextAttribute(hStdout, textAttribute);

	fpin = fopen("test.txt", "r");

	while (!feof(fpin))
	{
		ptr = fgets(line, MAXLEN, fpin);
		if (ptr == NULL)
			break;

		while (*ptr != '\0')//цикл до конца строки
		{
			if (*ptr == '=') {//как только находим равно
				printf("%c", *ptr);//выводим на экран с нужным цветом
				ptr++;//считываем следующийсимвол
				if (*ptr == ' ') {//если следующий оказался пробелом
					printf("%c", *ptr);//выводим на экарн с нужным цветом
					ptr++;//берем следующий символ
				}

				if (*ptr == '0') {//если следующий символ 0
					begin = &*ptr;//запомниаем его место
					do {//циклично просматриваем все цифры "ожидаемого числа"
						*ptr++;//берем след символ
						switch (*ptr) { //определяем константность текста
						case '0': flag = 1; break;
						case '1': flag = 1; break;
						case '2': flag = 1; break;
						case '3': flag = 1; break;
						case '4': flag = 1; break;
						case '5': flag = 1; break;
						case '6': flag = 1; break;
						case '7': flag = 1; break;
						case ';': flag = 2; end = &*ptr; break;//как только находим завершающий символ - запоминаем его и выходим
						default:  flag = 0;
						}
					} while ((flag != 0)&(flag != 2));


					//если мы вышли с хорошим завершением флаг=2, то значит мы нашли нужно число
					if (flag == 2) { //покраска цветами и вывод на экран
						//вывод от начала числа до конца нужным цветом
						for (ptr = begin; *ptr != *end; *ptr++) {
							if (ptr == begin) { //цвет констант
								textAttribute = foregroundColor1 | backgroundColor1;
								SetConsoleTextAttribute(hStdout, textAttribute);
							}
							printf("%c", *ptr);//вывод на экран
						}// замена на обычный цвет
						textAttribute = foregroundColor | backgroundColor;
						SetConsoleTextAttribute(hStdout, textAttribute);
						printf("%c", *ptr);
					}
					//если вышли из цикла с плохи завершением флаг=0
					else {// вывод текста, что не константа, оыбчным цветом текста
						ptr++;
						for (; begin != ptr; *begin++)
							printf("%c", *begin);
						ptr--;
					}
				}
				else printf("%c", *ptr);
			}
			else printf("%c", *ptr);

			//свиг на след символ и обнуление
			prec = *ptr;
			*ptr++;
			flag = 0;
			end = NULL;
			begin = NULL;
		}
	}
	fclose(fpin);
}
