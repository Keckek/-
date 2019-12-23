#define _CRT_SECURE_NO_WARNINGS // отключение вывода предупреждений в IDE
#include <stdio.h> // стандартные библиотеки ввода-вывода
#include <stdlib.h>
#include <string.h> // библиотека для работы со строками
#define LEN 100     // длина названия категории базы
#define MAXLEN 1000 // максимальная длина позиции
#define YES 1 // логические переменные:
#define NO 0 // да и нет
#define CATEGORIES 8 // количество категорий
typedef struct sNode // объявление структуры sNode
{
	int id;             // порядковый номер элемента базы типа целое число
	char name[LEN];     // название продукта в базе
	char category[LEN]; // названия категории в баще
	int cost;           // цена, целое число
	struct sNode *next; // указание на следующую структуру
} Node;
int showMenu() // функция показа меню
{
	int choice; // выбор пункта меню
	printf("1 - Add product\n"); // первая цифра -- команда добавления продукта
	printf("2 - Editing record \n"); // вторая цифра -- редактирование существующего продукта
	printf("3 - Delete record\n"); // третья цифра -- удаление существующего продукта
	printf("4 - Display the database on the screen in alphabetical order by product category or product name\n"); // четвертая цифра -- вывод базы данных по алфавитному порядку, отсортированному по имени категории или названия продукта
	printf("5 - Selection of the 'minimum basket' for a given list of products\n"); // пятая цифра -- выбор минимальной корзины для заданного списка продуктов
	printf("\nPress 0 and Enter if you want to quit.\n"); // выбор нуля -- выход
	scanf("%d", &choice); // сканирование ввода команды цифрой
	return choice; // возврат значения той команды, которая была выбрана
}
Node *init(int a) // узел инициализации базы данных
{
	Node *lst; // структура списка в памяти (объявление)
	lst = (Node *)malloc(sizeof(Node)); // выделение памяти под структуру
	lst->id = a;      // принимаем значение id во внутреннюю переменную a
	lst->next = NULL; // указатель на переход к следующему элементу со значением NULL
	return (lst); // возврат значения lst
}
Node *deleteHead(Node *head) // узел очистки заголовка
{
	Node *temp;        // объявление временного узла temp
	temp = head->next; // передача заголовка следующему узлу через переменную temp
	free(head);        // очистка заголовка
	return (temp);     // возврат данных заголовка из переменной temp
}
void deleteNode(Node *lst, Node *head) // функция удаления узла
{
	Node *temp;               // объявление временного узла temp
	temp = head;              // копирование заголовка в переменную temp
	while (temp->next != lst) // пока не пройден весь список
	{
		temp = temp->next; // очищать позицию из temp
	}
	temp->next = lst->next; // занесение в lst всех значений соответствующих temp
	free(lst); // очистка списка
}
void freeList(Node **head) // функция очистки списка
{
	Node *current = *head; // указатель узла current заносим в head
	Node *next = NULL; // указатель следующего элемента обнуляется
	do
	{
		next = current->next; // в переменную next заносим текущее значение указателя
		free(current); // освобождаем текущее значение
		current = next; // заносим в текущее значение следующий элемент
	} while (current != NULL); // до тех пор, пока текущий элемент не будет пустым
	free(current); // освобождаем текущий элемент
}
Node *Appendlist(Node **headRef) // узел привязки списка
{
	Node *current = *headRef; // загрузка узла
	Node *lst; // подключение указателя lst
	lst = (Node *)malloc(sizeof(Node)); // выделение памяти для lst
	lst->next = NULL; // обнуляем следующий элемент списка
	if (current == NULL) // если текущий элемент равен нулю
	{
		*headRef = lst; // перемещаемся в lst
	}
	else
	{
		while (current->next != NULL) // иначе если следующий элемент текущей переменной не равен нулю
		{
			current = current->next; // то идём дальше
		}
		current->next = lst; // в конце присваивая список
	}
	return (lst); // возвращаем значение списка
}
void alphSort(Node **headRef, int structType, int count) // функция алфавитной сортировки данных
{
	Node *current;      // загрузка узла current
	Node *next;         // указание на следующий узел
	int noSwap;         // логическая переменная проверки сортировки
	int iBuf;           // переменная буфера чисел
	char cBuf[MAXLEN];  // переменная буфера символов
	switch (structType) // выбор типа структуры
	{
	case 1: // в первом случае сортировка по названию продукта
		for (int i = count - 1; i >= 0; i--)
		{
			current = *headRef;
			next = current->next;
			noSwap = 1; // не меняем местами элементы
			for (int j = 0; j < i; j++) // проходим цикл по базе
			{
				if (strcmp(current->name, next->name) > 0) // если есть еще что сортировать по имени товара
				{
					iBuf = current->id;                // сортировка
					current->id = next->id;            // в алфавитном
					next->id = iBuf;                   // порядке
					strcpy(cBuf, current->name);       // перенос данных
					strcpy(current->name, next->name); // на новые
					strcpy(next->name, cBuf);          // позиции
					strcpy(cBuf, current->category);   // через буферную переменную
					strcpy(current->category, next->category); // переносим в текущую категорию категорию следующего элемента
					strcpy(next->category, cBuf); // перенос буфера в следующую категорию
					iBuf = current->cost; // занесение цены в буфер чисел
					current->cost = next->cost; // сортировка стоимостей текущего и следующего элемента
					next->cost = iBuf; // перенос стоимости из буфера чисел в переменную
					noSwap = 0; // сортировка окончена
				}
				current = current->next; // переход к следующему элементу
				next = current->next;
			}
			if (noSwap == 1) // если больше нечего сортировать
				break; // останавливаемся
		}
		break;
	case 2: // во втором случае сортировка категории
		for (int i = count - 1; i >= 0; i--)
		{
			current = *headRef; // переходим в начало
			next = current->next; // переходим к последовательному сканированию элементов
			noSwap = 1; // логическая переменная проверки сортировки
			for (int j = 0; j < i; j++)
			{
				if (strcmp(current->category, next->category) > 0) // если не отсортировали по категории товара
				{
					iBuf = current->id; // заносим номер позиции в числовой буфер
					current->id = next->id; // текущую позицию переносим в следующую (переходим к следующей)
					next->id = iBuf; // заносим следующий элемент id в буфер чисел
					strcpy(cBuf, current->name); // копируем в символьный буфер текущее название элемента
					strcpy(current->name, next->name); // копируем в текущее название следующее название
					strcpy(next->name, cBuf); // заносим в следующее значение имени символьный буфер
					strcpy(cBuf, current->category); // заносим в символьный буфер текущую категорию
					strcpy(current->category, next->category); // заносим в текущую категорию следующую категорию
					strcpy(next->category, cBuf); // заносим в следующую категорию символьный буфер
					iBuf = current->cost; // в буфер чисел заносим текущую стоимость
					current->cost = next->cost; // в текущую стоимость заносим стоимость следующего элемента
					next->cost = iBuf; // в стоимость следующего элемента заносим буфер чисел
					noSwap = 0; // флаг конца цикла сортировки
				}
				current = current->next; // идем к следующему элементу
				next = current->next;
			}
			if (noSwap == 1) // если сортировка закончена
				break; // останавливаемся
		}
		break;
	default: // поведение по-умолчанию — остановка
		break;
	}
}
void getData(Node **headRef, int *countItemsRet, int *itemNumRet) // функция получения данных из базы
{
	FILE *fpin;                    // объявление входного файла с данными базы
	FILE *finit;                   // объявление инициализирующего файла
	int dataNum;                   // переменная нумерации данных
	int itemNum = 0;               // переменная номера позиции
	int inItem = NO;               // логическая переменная наличия данных в скобках
	int countItems = 0;            // переменная количества позиций
	int i = 0;                     // переменная счетчика
	char line[MAXLEN];             // переменная строки данных
	Node *item_ptr = NULL;         // указатель на позицию
	fpin = fopen("C:\\Users\\Anastasia\\Desktop\\KUSRSOVA\\base.txt", "r"); // открытие базы данных из файла
	if (fpin == NULL)              // если файла не существует
	{
		finit = fopen("C:\\Users\\Anastasia\\Desktop\\KUSRSOVA\\base.txt", "w"); // создание пустого файла
		fclose(finit);                  // и закрытие записи в него
		fpin = fopen("C:\\Users\\Anastasia\\Desktop\\KUSRSOVA\\base.txt", "r");  // открытие файла на чтение
	}
	fscanf(fpin, "%d\n", &countItems); // сканирование количества позиций из файла
	while (!feof(fpin))
	{
		fscanf(fpin, "%s\n", line); // занесение данных из файла в переменную line
		if (line == NULL) // если данных нет
			break; // останавливаемся
		if (*line == '(') // нахождение данных в скобках
		{
			inItem = YES;     // если данные найдены
			itemNum++;        // считаем в переменную
			if (itemNum == 1) // если она имеет в себе элемент
			{
				item_ptr = *headRef; // возвращаем указатель в headRef
			}
			else // если данные не найдены
			{
				item_ptr = Appendlist(&(*headRef)); // присваиваем указателю список
			}
			dataNum = 0;
			continue;
		}
		if (*line == ')') // если нашли конец данных в скобках
		{
			inItem = NO; // не считаем это за дополнительные данные
			continue;
		}
		if (inItem) // если существуют данные в скобках
		{
			i = -1;    // присваиваем счетчику запас
			++dataNum; // наращиваем переменную количества данных
			switch (dataNum)
			{
			case 1:                        // обработка id данных
				item_ptr->id = atoi(line); // перемещение указателя id к строке данных
				break;
			case 2: // обработка категории данных
				do
				{
					i++;                             // увеличиваем счетчик
					item_ptr->category[i] = line[i]; // перемещение указателя категории к соответствующей строке с данными
				} while (line[i] != '\0');           // пока не найден конец строки
				break;
			case 3: // обработка названия товара
				do
				{
					i++;                         // увеличиваем счетчик
					item_ptr->name[i] = line[i]; // перемещение указателя названия к соответствующей строке с данными
				} while (line[i] != '\0');       // пока не найден конец строки
				break;
			case 4:                          // обработка стоимости товара
				item_ptr->cost = atoi(line); // перемещение указателя стоимости к строке данных
				break;
			}
		}
	}
	fclose(fpin);                // закрытие файла с данными
	*itemNumRet = itemNum;       // возврат номера в БД
	*countItemsRet = countItems; // возврат количества позиций в БД
}
void putData(Node **headRef, int itemNum) // функция записи данных в базу с аргументами в виде узла и номера позиции
{
	FILE *fpin;                     // объявление переменной файла с базой
	Node *current = *headRef;       // перемещение указателя в начало
	fpin = fopen("C:\\Users\\Anastasia\\Desktop\\KUSRSOVA\\base.txt", "w");  // открытие файла базы данных на запись
	fprintf(fpin, "%d", itemNum); // вывод номера позиции
	while (current != NULL)         // цикл по базе данных
	{
		fprintf(fpin, "(\n");                     // пустая строка
		fprintf(fpin, "%d", current->id);       // вывод порядкового номера данных
		fprintf(fpin, "%s", current->category); // вывод категории данных
		fprintf(fpin, "%s", current->name);     // вывод поля названия
		fprintf(fpin, "%d", current->cost);     // вывод поля стоимости
		fprintf(fpin, " ");                     // пустая строка
		current = current->next;                  // перемещение к следующей позиции
	}
	fclose(fpin); // закрытие файла
}
int main() // основной код
{
	Node *HeadPointer = init(0);                                                                                       // инициализация указателя заголовка
	Node *ItemPointer = NULL;                                                                                          // инициализации указателя позиции
	char WantedName[LEN];                                                                                              // переменная названия
	int itemNum;                                                                                                       // переменная номера позиции
	int countItems;                                                                                                    // перменная количества позиций
	int i = 0;                                                                                                         // счётчик
	int need_menu;                                                                                                     // переменная команды выбора меню
	int need_cost;                                                                                                     // ... выбора стоимости
	int need_item;                                                                                                     // ... выбора позицци
	int need_category;                                                                                                 // ... выбора категории
	int need_showCategory;                                                                                             // ... показа категории
	char categories[CATEGORIES][100] = { "Fruits", "Meat", "Milk", "Drinks", "Candy", "Vegetables", "Bread", "Bakery" }; // ... категории товаров
	int need_basketCategories[CATEGORIES + 1];                                                                         // переменная корзины товаров по категориям
	getData(&HeadPointer, &countItems, &itemNum);                                                                      // вызов функции считывания данных

	do
	{
		need_menu = showMenu(); // показ меню
		switch (need_menu) // переход по условиям
		{
		case 1:                     // вывод справки по навигации
			printf("1 - Fruits\n"); // каждая категория имеет свой номер, 1 - фрукты
			printf("2 - Meat\n"); // 2 - мясо
			printf("3 - Milk\n"); // 3 - молочные продукты
			printf("4 - Drinks\n"); // 4 - напитки
			printf("5 - Candy\n"); // 5 - конфеты
			printf("6 - Vegetables\n"); // 6 - овощи
			printf("7 - Bread\n"); // 7 - хлебные изделия
			printf("8 - Bakery\n"); // 8 - выпечка
			printf("Select product category : "); // вывод сообщения о выборе категории
			scanf("%d", &need_category); // ввод нужного номера категории
			printf("Enter the item name : "); // ввод названия элемента базы
			getchar(); // ввод названия продукта
			fgets(WantedName, LEN, stdin); // получаем наазвание ограниченой длины
			printf("Enter the price of the item : "); // ввод цены продукта
			scanf("%d", &need_cost); // ввод цены в need_cost
			printf("Product successfully added! \n"); // ввод цены продукта
			countItems++;     // считаем введённую позицию
			if (itemNum == 0) // если номер продукта нулевой
			{
				ItemPointer = HeadPointer; // перемещаемся в начало
			}
			else // иначе
			{
				ItemPointer = Appendlist(&HeadPointer); // перемещаемся к списку
			}
			ItemPointer->id = countItems;  // передаем введенные данные номера позиции
			ItemPointer->cost = need_cost; // и стоимости
			i = -1; // возвращаемся
			do
			{
				i++; // снова идём дальше
				ItemPointer->name[i] = WantedName[i]; // и названия позиции
			} while (WantedName[i] != '\0');          // пока не дошли до конца ввода
			i = -1; // возвращаемся
			do
			{
				i++; // снова идём дальше
				ItemPointer->category[i] = categories[need_category - 1][i]; // передаем категорию
			} while (categories[need_category - 1][i] != '\0');              // пока не дошли до конца ввода
			itemNum++;                                                       // наращиваем счетчик позиции
			break;
		case 2:

			if (!itemNum) // если данных о товаре нет
			{
				printf("There is no items here\n"); // говорим об этом

				break;
			}
			printf("Select the item you want to change : \n"); // что вы хотите изменить в базе?
			ItemPointer = HeadPointer; // идём в начало
			i = 1; // сбрасываем счётчик
			while (ItemPointer != NULL) // пока указатель на элемент базы не пуст
			{
				printf("%d - %s\n", i, ItemPointer->name); // меняем названия позиции
				i++;
				ItemPointer = ItemPointer->next; // переходим к следующей позиции
			}
			ItemPointer = HeadPointer; // перемещаемся в начало
			scanf("%d", &need_item);   // даём команду смены позицции
			for (i = 0; i < need_item - 1; i++) // цикл по позициям элементов базы
			{
				ItemPointer = ItemPointer->next; // перемещаемся к следующей позиции
			}
			printf("Old item type : %s\n\n", ItemPointer->category); // вывод категорий в формате таблицы
			for (i = 0; i < CATEGORIES; i++) // вывод их в цикле
			{
				printf("%d %s\n", i + 1, &categories[i]);
			}
			printf("Enter a new category of product : "); // ввод новой категории
			scanf("%d", &need_category);
			printf("Old product name : %s\nEnter new product name : ", ItemPointer->name); // замена названия продукт
			getchar();
			fgets(WantedName, LEN, stdin);
			getchar();
			printf("Old cost: %d\nEnter new cost : ", ItemPointer->cost); // замена стоимости продукта на новую
			scanf("%d", &need_cost);
			ItemPointer->cost = need_cost; // запись новых данных в базу
			i = -1; // идём назад по базе
			do
			{
				i++; //
				ItemPointer->name[i] = WantedName[i]; // теперь заменяем название продукта на то, которое указали
			} while (WantedName[i] != '\0'); // пока не дошли до конца данных
			i = -1;
			do
			{
				i++;
				ItemPointer->category[i] = categories[need_category - 1][i]; // то же самое с категорией
			} while (categories[need_category - 1][i] != '\0');

			break;
		case 3:
			if (!itemNum) // если не нашли позицию
			{
				printf("There is no items here\n");

				break;
			}
			printf("Select the item you want to remove : \n"); // обработка удаления позиции (продукта)
			ItemPointer = HeadPointer;                         // идём с начала
			i = 1;
			while (ItemPointer != NULL) // вывод данных о позициях
			{
				printf("%d %s\n", i, ItemPointer->name); // вывод названия позиции
				i++;
				ItemPointer = ItemPointer->next; // перемещение указателя позиции к следующей позицции
			}
			scanf("%d", &need_item); // выбираем, что хотим удалить
			ItemPointer = HeadPointer; // идём в начало
			for (i = 0; i < need_item - 1; i++) // запускаем цикл
			{
				ItemPointer = ItemPointer->next; // проходим по каждому элементу
			}
			if (need_item == 1) // если это первая позиция
			{
				HeadPointer = deleteHead(ItemPointer); // удаляем заголовок
			}
			else // иначе
			{
				deleteNode(ItemPointer, HeadPointer); // удаляем его по указателю
			}
			itemNum--;    // уменьшаем счетчик позиций
			if (!itemNum) // если позиций нет
			{
				HeadPointer = init(0); // очищаем заголовок
			}
			break;
		case 4:

			if (!itemNum) // если нет позиций
			{
				printf("There is no items here\n"); // говорим об этом
				break;
			}
			printf("Choose sorting method: \n"); // выбор данных по которым будет производиться сортировка
			printf("1 - Name\n2 - Category\n");  // имя либо категория
			scanf("%d", &need_showCategory);     // получаем выбор

			alphSort(&HeadPointer, need_showCategory, itemNum); // вызываем функцию сортировки
			ItemPointer = HeadPointer;                          // идём в начало списка данных
			i = 1;
			while (ItemPointer != NULL) // пока указатель не пуст
			{
				printf("      <%d>      \n", i);                 // выводим
				printf("ID: %d\n", ItemPointer->id);             // результат
				printf("Category: %s\n", ItemPointer->category); // сортировки
				printf("Name: %s\n", ItemPointer->name);         // по нужным
				printf("Cost: %d\n", ItemPointer->cost);         // полям
				i++;
				ItemPointer = ItemPointer->next; // идём дальше
			}
			break;
		case 5:
			if (!itemNum) // если нет данных
			{
				printf("There is no items here\n"); // говорим об этом
				break;
			}
			for (i = 0; i < CATEGORIES; i++)
			{
				printf("%d %s\n", i + 1, categories[i]); // вывод всех категорий
			}
			printf("Select the types of goods for the minimum basket.\nEnter by one type.When finished, enter 0\n"); // выбираем позиции для корзины
			i = 0;
			do
			{
				scanf("%d", &need_basketCategories[i]); // ввод данных в корзину
				if (i) // если существует счётчик
				{
					for (int j = 0; j < i; j++)                                   // цикл по корзине
						if (need_basketCategories[j] == need_basketCategories[i]) // если позиция уже в корзине
						{                                                         // говорим об этом
							printf("This type of product is already in the basket. Choose a different one or finish the selection.\n");
							i--; // идём назад
						}
				}
				i++; // идём вперёд
			} while (need_basketCategories[i - 1]); // пока не заполнили предыдущую категорию в корзине
			i = 0;
			while (need_basketCategories[i])
			{
				int max = 100000;          // задаем максимум данных в корзине
				Node *max_ptr = NULL;      // сброс максимального значния указателя
				ItemPointer = HeadPointer; // перемещение к началу
				while (ItemPointer != NULL) // пока указатель элемента не пуст
				{
					if (!strcmp(ItemPointer->category, categories[need_basketCategories[i] - 1])) // если указатель категории не совпадает с выбранной категорией
					{
						if (ItemPointer->cost < max) // если в текущем указателе стоимость меньше максимальной
						{
							max = ItemPointer->cost; // присваиваем переменной максимума стимость текущего элемента
							max_ptr = ItemPointer;   // и даём указателю информацию о положении максимальной стоимости
						}
					}
					ItemPointer = ItemPointer->next; // идём дальше
				}
				i++;
				if (!(max_ptr == NULL)) // если есть информация о позиции максимальной стоимости
				{
					printf("      <%d>      \n", i); // вывод данных
					printf("ID: %d\n", max_ptr->id); // вывод ID (максимального)
					printf("Category: %s\n", max_ptr->category); // вывод категории (из указателя элемента с максимальной стоимостью)
					printf("Name: %s\n", max_ptr->name); // так же имени элемента
					printf("Cost: %d\n", max_ptr->cost); // так же стоимости
				}
			}
			break;
		default:
			break;
		};
	} while (need_menu); // возврат к меню выбора команды
	if (itemNum)
	{
		putData(&HeadPointer, countItems); // запись данных
	}
	freeList(&HeadPointer); // очистка списка
	return 0;
}
