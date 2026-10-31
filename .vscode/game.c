#include <stdio.h>
#include <stdlib.h>//随机数
#include <time.h>//配合随机种子

#define ROWS 9 //行9
#define COLS 9 //列9
#define MINES 10//10个雷

void print(char board[ROWS][COLS])//打印棋盘
{
    printf("\n  ");
    for (int j = 0; j < COLS; j++)
        printf("%d ", j);
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%d ", i);
        for (int j = 0; j < COLS; j++) 
            printf("%c ", board[i][j]);
        printf("\n");
    }
}

int countMines(char mine[ROWS][COLS], int r, int c)//统计周围雷的数量
{
    int count = 0;

    for (int i = r - 1; i <= r + 1; i++)
        for (int j = c - 1; j <= c + 1; j++)
            if (i >= 0 && i < ROWS && j >= 0 && j < COLS &&
                mine[i][j] == '*')
                count++;

    return count;
}

void openCell(char mine[ROWS][COLS], char show[ROWS][COLS],//打开位置 (r, c)；opened 用来记录已经打开的格子数
              int r, int c, int *opened)
{
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS || show[r][c] != '#')//越界不处理
        return;

    int count = countMines(mine, r, c);// 打开位置 (r, c)；opened 用来记录已经打开的格子数
    show[r][c] = '0' + count;
    (*opened)++;

    if (count == 0)
        for (int i = r - 1; i <= r + 1; i++)
            for (int j = c - 1; j <= c + 1; j++)
                openCell(mine, show, i, j, opened);// 周围没有雷，自动打开周围的格子
}

int main(void)
{
    char mine[ROWS][COLS] = {0};
    char show[ROWS][COLS];
    int opened = 0;
    int r, c;

    srand((unsigned)time(NULL));//用当前时间做随机种子，否则每局雷的位置都一样

    for (int i = 0; i < ROWS; i++)//初始化棋盘
        for (int j = 0; j < COLS; j++)
            show[i][j] = '#';

    for (int i = 0; i < MINES; ) {
        r = rand() % ROWS;// 随机行号，范围是 0 到 ROWS-1
        c = rand() % COLS;// 随机列号，范围是 0 到 COLS-1
        if (mine[r][c] != '*') {
            mine[r][c] = '*';
            i++;
        }
    }

    while (opened < ROWS * COLS - MINES) {
        print(show);
        printf("请输入行和列：");

        if (scanf("%d%d", &r, &c) != 2) return 0;

        if (r < 0 || r >= ROWS || c < 0 || c >= COLS || show[r][c] != '#') {
            printf("输入无效，请重试。\n");
            continue;
        }

        if (mine[r][c] == '*') {
            show[r][c] = 'X';
            print(show);
            printf("你踩雷了！\n");
            return 0;
        }

        openCell(mine, show, r, c, &opened);//翻开周围格子
    }

    print(show);
    printf("恭喜你，扫雷成功！\n");
    return 0;
}