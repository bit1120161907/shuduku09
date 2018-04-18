#include "stdafx.h"

int sudo[9][9] = {             //构造新数独棋盘的原始棋盘
	{ 1, 6, 2, 5, 9, 3, 4, 7, 8 },
	{ 5, 9, 7, 1, 8, 4, 6, 3, 2 },
	{ 4, 8, 3, 2, 6, 7, 1, 9, 5 },
	{ 6, 3, 5, 7, 1, 8, 9, 2, 4 },
	{ 8, 7, 9, 6, 4, 2, 3, 5, 1 },
	{ 2, 4, 1, 3 ,5 ,9 ,7 ,8, 6 },
	{ 9, 2 ,6 ,4, 7, 5, 8, 1, 3 },
	{ 7, 5, 4, 8, 3, 1, 2, 6, 9 },
	{ 3, 1, 8, 9, 2, 6, 5, 4, 7 }
};

int check(int a[10][10], int tei[9][10], int tej[9][10], int tek[9][10], int dgt[50][3], int dgtc)
{
	dgtc--;
	if (dgtc == 0)
	{
		FILE *fp;
		errno_t err;
		if ((err = fopen_s(&fp, "shuduku.txt", "w")) == NULL) {    /* 打开文件 */
			printf("File open error!\n");
			exit(0);
		}
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
				fprintf(fp, "%d  ", a[r][c]);
			fprintf(fp, "\n");
		}
		fprintf(fp, "\n");
	}
	int i, j;
	i = dgt[dgtc][0];
	j = dgt[dgtc][1];
	int k;
	if (i >= 0 && i < 3 && j >= 0 && j < 3) k = 0;
	if (i >= 0 && i < 3 && j >= 3 && j < 6) k = 1;
	if (i >= 0 && i < 3 && j >= 6 && j < 9) k = 2;
	if (i >= 3 && i < 6 && j >= 0 && j < 3) k = 3;
	if (i >= 3 && i < 6 && j >= 3 && j < 6) k = 4;
	if (i >= 3 && i < 6 && j >= 6 && j < 9) k = 5;
	if (i >= 6 && i < 9 && j >= 0 && j < 3) k = 6;
	if (i >= 6 && i < 9 && j >= 3 && j < 6) k = 7;
	if (i >= 6 && i < 9 && j >= 6 && j < 9) k = 8;
	for (int s = 1; s < 10; s++)
	{
		if (tei[i][s] == 1 && tej[j][s] == 1 && tek[k][s] == 1)
		{
			a[i][j] = s;
			tei[i][s] = 2;
			tej[j][s] = 2;
			tek[k][s] = 2;
			if (!check(a, tei, tej, tek, dgt, dgtc))
			{
				a[i][j] = 0;
				tei[i][s] = 1;
				tej[j][s] = 1;
				tek[k][s] = 1;
			}
		}
	}
	return 0;
}

void solute(int a[10][10])
{
	FILE *fp;
	errno_t err;
	if ((err = fopen_s(&fp, "shuduku.txt", "w")) == NULL) {    /* 打开文件 */
		printf("File open error!\n");  
		exit(0);
	}
	int dgt[50][3];
	int dgtc = 0;
	int tei[9][10];
	int tej[9][10];
	int tek[9][10];
	int k;
	memset(tei, 0, sizeof(tei[0][0]));
	memset(tej, 0, sizeof(tej[0][0]));
	memset(tek, 0, sizeof(tek[0][0]));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (a[i][j] == 0)
			{
				dgt[dgtc][0] = i;
				dgt[dgtc][1] = j;
				dgtc++;
			}
			else
			{
				tei[i][a[i][j]] ++;
				tej[j][a[i][j]]++;
				if (i >= 0 && i < 3 && j >= 0 && j < 3) k = 0;
				if (i >= 0 && i < 3 && j >= 3 && j < 6) k = 1;
				if (i >= 0 && i < 3 && j >= 6 && j < 9) k = 2;
				if (i >= 3 && i < 6 && j >= 0 && j < 3) k = 3;
				if (i >= 3 && i < 6 && j >= 3 && j < 6) k = 4;
				if (i >= 3 && i < 6 && j >= 6 && j < 9) k = 5;
				if (i >= 6 && i < 9 && j >= 0 && j < 3) k = 6;
				if (i >= 6 && i < 9 && j >= 3 && j < 6) k = 7;
				if (i >= 6 && i < 9 && j >= 6 && j < 9) k = 8;
				tek[k][a[i][j]]++;
			}
		}
	}
	check(a, tei, tej, tek, dgt, dgtc);
}

int main(int argc, char* argv[])
{
	FILE *fp;
	errno_t err;
	if ((err = fopen_s(&fp,"shuduku.txt", "w")) == NULL) {    /* 打开文件 */
		printf("File open error!\n");
		exit(0);
	}
	if (strcmp(argv[1], "-c") == 1)
	{
		int cnt = 0;
		int n = strlen(argv[2]);
		for (; n >= 0; n--)cnt += (argv[2][n] - '48') * pow(10, n);
		int shift[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		char row[10] = "812345679";
		for (int k = 0; k < 40320 && cnt; k++)
		{
			if (k) next_permutation(row + 1, row + 9);
			for (int i = 0; i < 6 && cnt; i++)
			{
				if (i)
				{
					next_permutation(shift + 3, shift + 6);
					shift[6] = 6, shift[7] = 7, shift[8] = 8;
				}
				for (int j = 0; j < 6 && cnt; j++)
				{
					if (j) next_permutation(shift + 6, shift + 9);
					for (int r = 0; r < 9; r++)
					{
						for (int c = 0; c < 9; c++)
							//cout << row[sudo[shift[r]][c] - 1] << ' ';
							fprintf(fp, "%d  ", row[sudo[shift[r]][c] - 1]);
						//cout << endl;
						fprintf(fp, "\n");
					}
					cnt--;
					//cout << endl;
					fprintf(fp, "\n");
				}
			}
		}
	}
	if (strcmp(argv[1], "-s") == 1)
	{
		FILE *fp;
		errno_t err;
		if ((err = fopen_s(&fp, argv[2], "w")) == NULL) {    /* 打开文件 */
			printf("File open error!\n");
			exit(0);
		}
		char CmdLine[10];
		int temsodu[10][10];
		int j = 0;
		while (fscanf_s(fp, "%[^\n]", CmdLine) != EOF)
		{
			fgetc(fp);
			for (int i = 0; i < 9; i++)
			{
				temsodu[j][i] = CmdLine[i] - '48';
			}
			j++;
			if (j == 9)
			{
				fgetc(fp);
				j = 0;
				solute(temsodu);
			}
		}
	}
	if (fclose(fp)) {                         /* 关闭文件 */
		printf("Can not close the file!\n");
		exit(0);
	}
	return 0;
}
