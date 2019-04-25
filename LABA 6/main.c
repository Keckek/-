#pragma warning(disable : 4996)
#include <stdio.h>
#define K 5
#define N 5

int main(void)
{
	int x[K][N];
	int i;//строки
	int j;//столбцы
	int max;//максимальное значение
	int sum;//сумма в диаогнале
	int maxi = 0;
	int maxj = 0;
	int maxk;
	int k;
	int maxjo;
	int maxio;
	max = 0;
	sum = 0;

	srand(time(NULL));
	for (i = 0; i < N; i++)//задаем массив
	{
		for (j = 0; j < K; j++)
		{
			x[i][j] = 0 + rand() % 10;
		}
	}

	for (i = 0; i < N; i++)//выводим массив
	{
		for (j = 0; j < K; j++)
		{
			printf("%-2d ", x[i][j]);
		}
		printf("\n");
	}

	for (k = N-1, j = 0; k >=0;k--, sum = 0, j=0)//считаем диагонали слева на право ниже главной оси
	{
		for (i = k; i < N ; i++)
		{
			sum = x[i][j] + sum;
			j++;
		}
		if (sum > max)
		{
			max = sum;
			maxi = i;
			maxj = j;
			maxk = N - 1;
			maxjo = 0;
		}
		sum = 0;
	}
	
	for (k = 1, i=0; k < N; k++, sum = 0,i=0)//считаем диагонали слева на право выше главной оси
	{
		for (j = k; j < N; j++)
		{
			sum = x[i][j] + sum;
			i++;
		}
		if (sum > max)
		{
			max = sum;
			max = sum;
			maxi = i;
			maxj = j;
			maxk = 1;
			maxio = 0;
		}
	}

	for (k = N - 1, j = N - 1; k >= 0; k--, j = N - 1, sum = 0)//считаем диагонали справа на лево ниже главной оси
	{
		for (i = k; i < N; i++)
		{
			sum = x[i][j] + sum ;
			j--;
		}
		if (sum > max)
		{
			max = sum;
			max = sum;
			maxi = i;
			maxj = j;
			maxk = k;
			maxjo = N - 1;
		}
	}

	for (k = N-2 , i = 0; k >= 0; k--, i = 0, sum = 0)//считаем диагонали справа на лево выше главной оси
	{
		for (j = k; j >=0; j--)
		{
			sum = x[i][j] + sum;
			i++;
		}
		if (sum > max)
		{
			max = sum;
			max = sum;
			maxi = i;
			maxj = j;
			maxk = k;
			maxio = 0;
		}
	}
)


	printf("%d", max);


}