#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h> 

//В txt файле формат записи

struct wordNoun {//Структура для хранения существительных и их длинны 
	char* mass;//Само слово
	int size;//Размер
}*massNoun;

struct wordVerb {//Для глаголов
	char* mass;
	int size;
}*massVerb;

int main() {
	int sizeNoun = 0;//Кол-во существительных
	int sizeVerb = 0;//Кол-во глаголов
	char line[20];//Строка для считывания слова
	char* ptr;//Для перемещения по строке
	massNoun = (struct wordNoun*)malloc(sizeof(struct wordNoun) * 1);
	massVerb = (struct wordVerb*)malloc(sizeof(struct wordVerb) * 1);//Создаём по одному элементу на существительное и глагол
	FILE *fin;//Входной файл
	fin = fopen("base.txt", "rt");//Открываем файлы с соответствующими модификаторами 
	if (fin == NULL) {//Тут проверяем открытие
		printf("Не удалось открыть файл");
		system("pause");
		return 1;
	}
	while (!feof(fin)) {
		fgets(line, 20, fin);//Считываем строку 
		ptr = line;//Указатель на начало
		if (*ptr == '#' && *(ptr + 1) == 'n') {//Если дошли до #noun, то начинаем считывать существительное
			fgets(line, 20, fin);//Опять считали строку
			ptr = line;//На начало
			while (*ptr != '#') {//Продолжаем чтение, пока не дойдём до следующей подгруппы слов
				massNoun = (struct wordNoun*)realloc(massNoun, sizeof(struct wordNoun) * (sizeNoun + 1));//Перераспределяем память с учётом кол-ва уже имеющихся слов
				massNoun[sizeNoun].size = 0;//Т.к. длина слова пока не известно, то присваиваем ей 0
				while (*ptr != '\n' && *ptr != '\0') {//Узнаём длину слова
					massNoun[sizeNoun].size++;
					ptr++;
				}
				massNoun[sizeNoun].mass = (char*)malloc(sizeof(char) * massNoun[sizeNoun].size + 1);//Создаём строку под это слово + 1 элемент под '\0'
				ptr -= massNoun[sizeNoun].size;//Уходим в начало строки
				for (int i = 0; i < massNoun[sizeNoun].size; i++) {//Записываем слово в стуктуру 
					massNoun[sizeNoun].mass[i] = *ptr;
					ptr++;
				}
				massNoun[sizeNoun].mass[massNoun[sizeNoun].size] = '\0';//В конце слова ставим '\0'
				sizeNoun++;//Увеличиваем кол-во существительных
				fgets(line, 20, fin);//Считываем новую строку
				ptr = line;//Указатль на начало
			}
		}
		if (*ptr == '#' && *(ptr + 1) == 'v') {//То же самое, только для глаголов 
			fgets(line, 20, fin);
			ptr = line;
			while (*ptr != '#') {
				massVerb = (struct wordVerb*)realloc(massVerb, sizeof(struct wordVerb) * (sizeVerb + 1));
				massVerb[sizeVerb].size = 0;
				while (*ptr != '\n' && *ptr != '\0') {
					massVerb[sizeVerb].size++;
					ptr++;
				}
				massVerb[sizeVerb].mass = (char*)malloc(sizeof(char) * massVerb[sizeVerb].size + 1);
				ptr -= massVerb[sizeVerb].size;
				for (int i = 0; i < massVerb[sizeVerb].size; i++) {
					massVerb[sizeVerb].mass[i] = *ptr;
					ptr++;
				}
				massVerb[sizeVerb].mass[massVerb[sizeVerb].size] = '\0';
				sizeVerb++;
				fgets(line, 20, fin);
				ptr = line;
			}
		}
	}
	srand(time(NULL));//Для разнообразия значений без перезапуска IDE
	char** res;//Массив для предложений
	int size;//Длина предложения
	int sizeR;//Кол-во слов
	int iR1;//Выбор между сущ и гл
	int iR2;//Выбор слова
	res = (char**)malloc(sizeof(char*) * 1);
	for (int i = 0; i < sizeNoun; i++) {//Кол-во предложений = кол-ву сущ
		res[i] = (char*)malloc(sizeof(char) * 1);
		sizeR = rand() % 6 + 2;//Генерируем кол-во слов в предложении
		size = 0;//Размер обнуляем
		for (int j = 0; j < sizeR; j++) {
			iR1 = rand() % 2 + 1;//Генерируем выбор между сущ и гл
			if (iR1 == 1) {//Если существительное
				iR2 = rand() % sizeNoun + 1;//Выбираем слово
				res[i] = (char*)realloc(res[i], sizeof(char) * (size + 1 + massNoun[iR2 - 1].size));//Выделяем под него память. Тут есть момент, что нам нужно выделить память в таком формате длинны слов + кол-во слов, это нужно чтобы тавить пробелы между словами, а в конце потавить \0
				for (int a = 0; a < massNoun[iR2 - 1].size; a++)//Переписываем слово
					res[i][a + size] = massNoun[iR2 - 1].mass[a];
				size += massNoun[iR2 - 1].size;//Увеличиваем длину на кол-во символов этого слова
			}
			if (iR1 == 2) {//То же самое, но для глаголов
				iR2 = rand() % sizeVerb + 1;
				res[i] = (char*)realloc(res[i], sizeof(char) * (size + 1 + massVerb[iR2 - 1].size));
				for (int a = 0; a < massVerb[iR2 - 1].size; a++)
					res[i][a + size] = massVerb[iR2 - 1].mass[a];
				size += massVerb[iR2 - 1].size;
			}
			res[i][size] = ' ';//После каждого слова добовляем пробел
			size++;//И увеличиваем размер
		}
		res[i][size] = '\0';//В конце \0
	}
	for (int i = 0; i < sizeNoun; i++) //Выводим неотсортированные предложения
		printf("%s\n", res[i]);
	printf("\n");
	for (int i = 0; i < sizeNoun; i++)//Сортировка
		for (int j = 0; j < sizeNoun - 1; j++)
			if (strcmp(res[j], res[j + 1]) > 0) {
				ptr = res[j];
				res[j] = res[j + 1];
				res[j + 1] = ptr;
			}
	for (int i = 0; i < sizeNoun; i++) //Вывод отсортированных предложений
		printf("%s\n", res[i]);
	system("pause");
}
