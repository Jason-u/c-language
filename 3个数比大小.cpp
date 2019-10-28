#include <stdio.h>
#include<conio.h> 
#include <stdlib.h>
#include <Windows.h>    // �����Ի���
/*
    0: �յ�
    1: Ŀ�ĵ�   ��
    2: ǽ��     �� 
    4: ����     ��
    8: ���     ��
    16: ���ӵ���Ŀ�ĵ�  ��
*/
int map[13][14] = {
    {0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0},
    {0, 2, 2, 2, 2, 0, 0, 4, 4, 2, 2, 2, 2, 2},
    {0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2},
    {0, 2, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 2},
    {0, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 4, 2, 2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 4, 0, 2, 0, 0, 0, 8, 0, 0, 2},
    {2, 0, 4, 0, 4, 0, 2, 0, 2, 2, 2, 2, 2, 2},
    {2, 2, 0, 0, 4, 0, 2, 0 ,2, 1, 1, 1, 2, 0},
    {0, 2, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 2, 0},
    {0, 2, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 2, 0},
    {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0}
};
// Ŀ���
int tarPos[][2] = {
    {9, 9},
    {9, 10},
    {9, 11},
    {10, 9},
    {10, 10},
    {10, 11},
    {11, 8},
    {11, 9},
    {11, 10},
    {11, 11}
};
char key = 0;   // �洢�û��İ���
int row = 0, column = 0;    // �����ڵڼ��У��ڼ���
int oldType = 0;    // ����վ�ŵĵط�ԭ����ʲô����
int oldBoxType = 0; // ����վ�ŵĵط�ԭ����ʲô���� 
// ����ͼ����
void DrawMap() {
    for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++)
    {
        for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++)
        {
            switch (map[i][j])
            {
            case 0:
                printf("  ");
                break;
            case 1:
                printf("��");
                break;
            case 2:
                printf("��");
                break;
            case 4:
                printf("��");
                break;
            case 8:
                printf("��");
                row = i;
                column = j;
                break;
            case 16:
                printf("��");
                break;
            }
        }
        printf("\n");
    }
}
void Move(int r, int c)
{
    if (map[row + r][column + c] != 2)  // ���ǰ�治��ǽ�ڵĻ����Ϳ����ƶ�
    {
        if (map[row + r][column + c] == 4 || map[row + r][column + c] == 16)    // ����������ӵĴ���취
        {
            if (map[row + 2 * r][column + 2 * c] != 2 && map[row + 2 * r][column + 2 * c] != 4 && map[row + 2 * r][column + 2 * c] != 16)   // ���Ӻ��治��ǽ�ں�����
            {
                // �ƶ�����
                if (map[row + r][column + c] == 16)
                {
                    oldBoxType = 1;
                }
                else if (map[row + r][column + c] == 4)
                {
                    oldBoxType = 0;
                }
                map[row + r][column + c] = oldBoxType;
                if (map[row + 2 * r][column + 2 * c] == 1)
                {
                    map[row + 2 * r][column + 2 * c] = 16;
                }
                else
                {
                    map[row + 2 * r][column + 2 * c] = 4;
                }
            }
            else {
                return; // ������Ӻ�����ǽ�ڣ���ôֹͣ�ƶ�
            }
        }
        map[row][column] = oldType; // �������߹��ĵط���Ϊԭ���ĵ�������
        oldType = map[row + r][column + c]; // �洢���������Ҫ�ߵĵط��ĵ�������
        map[row + r][column + c] = 8;   // ���ƶ���λ�÷����仯
    }
}
void resultCheck()
{
    bool result = true;
    for (int i = 0; i < sizeof(tarPos) / sizeof(tarPos[0]); i++)
    {
        if (map[tarPos[i][0]][tarPos[i][1]] != 16)
        {
            result = false;
        }
    }
    if (result)
    {
        MessageBox(NULL, TEXT("��Ӯ��!!"), TEXT("��Ϸ����"), MB_OK);
        exit(0);
    }
}
int main(void)
{
    DrawMap();
    while (true)
    {
        key = getch();    //_gettch()���������������̰���
        switch (key)
        {
        case 'a':
            Move(0, -1);
            break;
        case 'd':
            Move(0, 1);
            break;
        case 'w':
            Move(-1, 0);
            break;
        case 's':
            Move(1, 0);
            break;
        }
        resultCheck();  // ����Ƿ����
        system("cls");  // �����Ļ
        DrawMap();  // ���»�ͼ
    }
    return 0;
}
