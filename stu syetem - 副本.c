#include<stdio.h>
#define STU 30
#define COURSE 3
void Readscore(int score[][COURSE], long num[], int n, int c);
void AverforStu(int score[][COURSE], int sumS[], float averS[], int n, int c);
void AverforCourse(int score[][COURSE], int sumC[], float averC[], int n, int c);
void Quicksort(int s[],long num[], int l, int r, int score[][COURSE], float averS[], int c);
void Numsort(int score[][COURSE], long num[], int n, int stuS[], float averS[], int c);
void SearchSTU(int score[][COURSE], long num[], int n, int c);
void AnalysisSTU(int score[][COURSE], int n, int c);
void Print(int score[][COURSE], long num[],int sumS[], float averS[],
           int sumC[], float averC[],  int n, int c);

int main()
{
    int choice, i, n,c, x, score[STU][COURSE], sumS[STU], sumC[STU];
    float averS[STU], averC[STU];
    long num[STU];

    printf("Input the total number of the students(n <= 30):");
    scanf("%d", &n);
    printf("\nInput how many courses(c <= 5):");
    scanf("%d", &c);
    printf("Please input students' ID and scores:\n");
    Readscore(score, num, n, c);
    do
    {
        printf("1.Caculate total and average score of every course\n");
        printf("2.Caculate total and average score of every student\n");
        printf("3.Sort in descending order by total score of every student\n");
        printf("4.Sort in ascending order by number\n");
        printf("5.Search by number\n");
        printf("6.Statistic analysis for every course\n");
        printf("7.List record\n");
        printf("0.Exit\n");
        printf("Please enter your choice:");

        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            AverforCourse(score, sumC, averC, n, c);
            for(i=0; i<c; i++)
            {
                printf("Averscore forCourse %d is %4.1f\n", i+1, averC[i]);
                printf("Total score for Course %d is %d\n", i+1, sumC[i]);
            }
            break;
        case 2:
            AverforStu(score, sumS, averS, n, c);
            for(i=0; i<n; i++)
            {
                printf("Averscore for student %d is %4.1f\n", i+1, averS[i]);
                printf("Total score for student %d is %d\n", i+1, sumS[i]);
            }
            break;
        case 3:
            Quicksort(sumS, num, 0, n-1, score, averS, c);//只对学号和学生总分进行降序排序
            printf("Datasort:\n");
            Print(score, num, sumS, averS, sumC, averC, n, c);
            break;
        case 4:
            Numsort(score, num, n, sumS, averS, c);
            printf("Numbersort:\n");
            Print(score, num, sumS, averS, sumC, averC, n, c);
            break;
        case 5:
            Numsort(score, num, n, sumS, averS, c);
            printf("Please input student's number:");
            scanf("%d", &x);
            SearchSTU(score, num, n, c);
            break;
        case 6:
            AnalysisSTU(score, n, c);
            break;
        case 7:
            Print(score, num, sumS, averS, sumC, averC, n, c);
        case 0:
            break;
        }
    }while(choice != 0);
    return 0;
}

/**************************************/

/* 函数功能：输入学生学号和成绩，当输入负值时*/

void Readscore(int score[][COURSE], long num[], int n, int c)
{
    int i , j;
    for(i=0; i<n; i++)
    {
        scanf("%ld", &num[i]);
        for (j=0; j<c; j++)
        {
            scanf("%d", &score[i][j]);
        }
    }
    printf("\n");
}

/*函数功能：计算每个学生课程总分和平均分*/
void AverforStu(int score[][COURSE], int sumS[], float averS[], int n, int c)
{
    int i, j;
    for (i=0; i<n; i++ )
    {
        sumS[i] = 0;
        for(j=0; j<c; j++)
        {
            sumS[i] += score[i][j];
        }
        averS[i] = (float)sumS[i] / c;
    }
}
/*函数功能：计算每门课程的总分和平均分*/
void AverforCourse(int score[][COURSE], int sumC[], float averC[], int n, int c)
{
    int i, j;
    for (j=0; j<c;j++)
    {
        sumC[j] = 0;
        for (i=0; i<n; i++)
        {
            sumC[j] += score[i][j];
        }
        averC[j] = (float)sumC[j] / n;
    }
}



/*函数功能：从高到低快速排序*/
void Quicksort(int s[],long num[], int l, int r, int score[][COURSE], float averS[], int c)
{
    int i, j, m, q, key[8];
    if (l < r)
    {
        i = l;
        j = r;
        /*这里key值这样设置有问题。但是不清楚问题所在？*/
        key[0] = s[i]; key[1] = num[i]; key[2] = averS[i];
        for(q=3; q<8; q++, i++) key[q] = score[0][i];

        while(i < j)
        {
            while(i < j && s[j] < key)
                j--;/*从右向左查找第一个比关键字大的数*/
            if(i < j)
            {
                s[i] = s[j];
                num[i] = num[j];
                averS[i] = averS[j];
                for(m=0; m<c; m++)
                {
                    score[i][m] = score[j][m];
                }
                i++;
            }
            while(i < j && s[i] > key)
                i++;/*从左向右查找第一个比关键字小的数*/
            if(i < j)
            {
                s[j] = s[i];
                num[j] = num[i];
                averS[j] = averS[i];
                for(m=0; m<c; m++)
                {
                    score[j][m] = score[i][m];
                }
                j--;
            }
        }
        s[i] = key;
        Quicksort(s,num, l, i-1, score, averS, c);
        Quicksort(s,num, i+1, r, score, averS, c);
    }
}

/*函数功能：按学号升序排序*/
void Numsort(int score[][COURSE], long num[], int n, int sumS[], float averS[], int c)
{
    int i, j, k, m, temp2, temp3;
    long temp1;
    float temp4;
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if (num[j]<num[k])
            {
                k=j;
            }
        }
        if(k!=i)
        {
            temp1=num[k];num[k]=num[i];num[i]=temp1;
            for (m=0; m<c; m++)
            {
                temp2=score[k][m]; score[k][m]=score[i][m]; score[i][m]=temp2;
            }
            temp3=sumS[k]; sumS[k]=sumS[i]; sumS[i]=temp3;
            temp4=averS[k]; averS[k]=averS[i]; averS[i]=temp4;
        }
    }
}

/*函数功能：顺序查找学生学号，返回学生排名和成绩*/
void SearchSTU(int score[][COURSE], long num[], int n, int c)
{
    int i=0,j;
    long x;
    printf("Please input the number you want to search:");
    scanf("%ld", &x);
    for(i=0; i<n; i++)
    {
       if (num[i] == x)
       {
            printf("The ranking of students is %d\n", i+1);
            printf("The scores are\t:");
            for(j=0; j<c; j++)
            {
                printf("%d\t", score[i][j]);
            }
            printf("\n");
       }
    }
     printf("\nNot found!\n");
}

/*函数功能：按成绩对学生分类，统计每一类别人数，计算百分比*/
void AnalysisSTU(int score[][COURSE], int n, int c)
{
    int mark, i, j;
    int a=0, b=0, cc=0, d=0, e=0;
    for (j=0; j<c; j++)
    {
        for(i=0; i<n; i++)
        {
            mark = score[i][j]/10;
            switch(mark)
            {
            case 10:
            case 9: a++; break;
            case 8: b++; break;
            case 7: cc++; break;
            case 6: d++; break;
            case 5:
            case 4:
            case 3:
            case 2:
            case 1:
            case 0: e++; break;
            default: printf("error!");exit(0);
            }
        }
        printf("The number of grades for Course %d in Category A is %d, accounting for %4.1f%%\n", j+1, a, (float)a/n*100);
        printf("The number of grades for Course %d in Category B is %d, accounting for %4.1f%%\n", j+1, b, (float)b/n*100);
        printf("The number of grades for Course %d in Category C is %d, accounting for %4.1f%%\n", j+1, c, (float)cc/n*100);
        printf("The number of grades for Course %d in Category D is %d, accounting for %4.1f%%\n", j+1, d, (float)d/n*100);
        printf("The number of grades for Course %d in Category E is %d, accounting for %4.1f%%\n", j+1, e, (float)e/n*100);
    }
}

/*函数功能：输出每个学生的学号，每门课程的成绩，学生总分和平均分，课程总分和平均分*/
void Print(int score[][COURSE], long num[],int sumS[], float averS[],
           int sumC[], float averC[],  int n, int c)
{
    int i, j;
    printf("Student's ID\t  SCORE\t  SUM\t AVER\n");
    for(i=0; i<n; i++)
    {
        printf("%12ld\t", num[i]);
        for(j=0; j<c; j++)
        {
            printf("%4d\t", score[i][j]); /*打印每门课成绩*/
        }
        printf("%4d\t %5.1f\n", sumS[i], averS[i]);
    }
    printf("Sum of Course\t");
    for(j=0; j<c; j++)
    {
        printf("%4d\t", sumC[j]);
    }
    printf("\n Aver of Course\t");
    for(j=0; j<c; j++)
    {
        printf("%4.1f\t", averC[j]);
    }
    printf("\n");
}

/*函数功能：打印排序后学生学号和成绩
void Printscore(int score[], long num[], int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf("%12ld\t, %4d\n", num[i], score[i]);
    }
}*/
