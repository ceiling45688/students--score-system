#include<stdio.h>
#define STU 30
#define COURSE 5
void Readscore(int score[][COURSE], long num[], int n);
void AverforStu(int score[][COURSE], int sumS[], float averS[], int n);
void AverforCourse(int score[][COURSE], int sumC[], float averC[], int n);
void Quicksort(int s[],long num[], int l, int r, int score[][COURSE], float averS[]);
void Numsort(int score[][COURSE], long num[], int n, int stuS[], float averS[]);
void SearchSTU(int score[][COURSE], long num[], int n);
void AnalysisSTU(int score[][COURSE], int n);
void Print(int score[][COURSE], long num[],int sumS[], float averS[],
           int sumC[], float averC[],  int n);

int main()
{
    int choice, i, n, x, score[STU][COURSE], sumS[STU], sumC[STU];
    float averS[STU], averC[STU];
    long num[STU];

    printf("Input the total number of the students(n <= 30):");
    scanf("%d", &n);
    printf("Please input students' ID and scores(courses = 5):\n");
    Readscore(score, num, n);
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
            AverforCourse(score, sumC, averC, n);
            for(i=0; i<COURSE; i++)
            {
                printf("Averscore forCourse %d is %f\n", i, averC[i]);
                printf("Total score for Course %d is %d\n", i, sumC[i]);
            }
            break;
        case 2:
            AverforStu(score, sumS, averS, n);
            for(i=0; i<n; i++)
            {
                printf("Averscore for student %d is %f\n", i, averS[i]);
                printf("Total score for student %d is %d\n", i, sumS[i]);
            }
            break;
        case 3:
            Quicksort(sumS, num, 0, n-1, score, averS);//ֻ��ѧ�ź�ѧ���ֽܷ��н�������
            printf("Datasort:\n");
            Print(score, num, sumS, averS, sumC, averC, n);
            break;
        case 4:
            Numsort(score, num, n, sumS, averS);
            printf("Numbersort:\n");
            Print(score, num, sumS, averS, sumC, averC, n);
            break;
        case 5:
            Numsort(score, num, n, sumS, averS);
            printf("Please input student's number:");
            scanf("%d", &x);
            SearchSTU(score, num, n);
            break;
        case 6:
            AnalysisSTU(score, n);
            break;
        case 7:
            Print(score, num, sumS, averS, sumC, averC, n);
        case 0:
            break;
        }
    }while(choice != 0);
    return 0;
}

/**************************************/

/* �������ܣ�����ѧ��ѧ�źͳɼ��������븺ֵʱ*/

void Readscore(int score[][COURSE], long num[], int n)
{
    int i , j;
    for(i=0; i<n; i++)
    {
        scanf("%ld", &num[i]);
        for (j=0; j<COURSE; j++)
        {
            scanf("%d", &score[i][j]);
        }
    }
    printf("\n");
}

/*�������ܣ�����ÿ��ѧ���γ��ֺܷ�ƽ����*/
void AverforStu(int score[][COURSE], int sumS[], float averS[], int n)
{
    int i, j;
    for (i=0; i<n; i++ )
    {
        sumS[i] = 0;
        for(j=0; j<COURSE; j++)
        {
            sumS[i] += score[i][j];
        }
        averS[i] = (float)sumS[i] / COURSE;
    }
}
/*�������ܣ�����ÿ�ſγ̵��ֺܷ�ƽ����*/
void AverforCourse(int score[][COURSE], int sumC[], float averC[], int n)
{
    int i, j;
    for (i=0; i<COURSE;i++)
    {
        sumC[i] = 0;
        for (j=0; j<n; j++)
        {
            sumC[j] += score[i][j];
        }
        averC[i] = (float)sumC[i] / n;
    }
}



/*�������ܣ��Ӹߵ��Ϳ�������*/
void Quicksort(int s[],long num[], int l, int r, int score[][COURSE], float averS[])
{
    int i, j, m, key;
    if (l < r)
    {
        i = l;
        j = r;
        key = s[i];
        while(i < j)
        {
            while(i < j && s[j] < key)
                j--;/*����������ҵ�һ���ȹؼ��ִ����*/
            if(i < j)
            {
                s[i++] = s[j];
                num[i++] = num[j];
                averS[i++] = averS[j];
                for(m=0; m<COURSE; m++)//??????????????????
                {
                    score[i++][m] = score[j][m];
                }

            }
            while(i < j && s[i] > key)
                i++;/*�������Ҳ��ҵ�һ���ȹؼ���С����*/
            if(i < j)
            {
                s[j--] = s[i];
                num[j--] = num[i];
                averS[j--] = averS[i];
                for(m=0; m<COURSE; m++)//??????????????????
                {
                    score[j--][m] = score[i][m];
                }
            }
        }
        s[i] = key;
        Quicksort(s,num, l, i-1, score, averS);
        Quicksort(s,num, i+1, r, score, averS);
    }
}

/*�������ܣ���ѧ����������*/
void Numsort(int score[][COURSE], long num[], int n, int sumS[], float averS[])
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
            for (m=0; m<COURSE; m++)
            {
                temp2=score[k][m]; score[k][m]=score[i][m]; score[i][m]=temp2;
            }
            temp3=sumS[k]; sumS[k]=sumS[i]; sumS[i]=temp3;
            temp4=averS[k]; averS[k]=averS[i]; averS[i]=temp4;
        }
    }
}

/*�������ܣ�˳�����ѧ��ѧ�ţ�����ѧ�������ͳɼ�*/
void SearchSTU(int score[][COURSE], long num[], int n)
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
            for(j=0; j<COURSE; j++)
            {
                printf("%d\t", score[i][j]);
            }
            printf("\n");
       }
    }
     printf("\nNot found!\n");
}

/*�������ܣ����ɼ���ѧ�����࣬ͳ��ÿһ�������������ٷֱ�*/
void AnalysisSTU(int score[][COURSE], int n)
{
    int mark, i, j;
    int a=0, b=0, c=0, d=0, e=0;
    for (j=0; j<COURSE; j++)
    {
        for(i=0; i<n; i++)
        {
            mark = score[i][j]/10;
            switch(mark)
            {
            case 10:
            case 9: a++; break;
            case 8: b++; break;
            case 7: c++; break;
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
        printf("The number of grades for Course %d in Category C is %d, accounting for %4.1f%%\n", j+1, c, (float)c/n*100);
        printf("The number of grades for Course %d in Category D is %d, accounting for %4.1f%%\n", j+1, d, (float)d/n*100);
        printf("The number of grades for Course %d in Category E is %d, accounting for %4.1  f%%\n", j+1, e, (float)e/n*100);
    }
}

/*�������ܣ����ÿ��ѧ����ѧ�ţ�ÿ�ſγ̵ĳɼ���ѧ���ֺܷ�ƽ���֣��γ��ֺܷ�ƽ����*/
void Print(int score[][COURSE], long num[],int sumS[], float averS[],
           int sumC[], float averC[],  int n)
{
    int i, j;
    printf("Student's ID\t  SCORE\t  SUM\t AVER\n");
    for(i=0; i<n; i++)
    {
        printf("%12ld\t", num[i]);
        for(j=0; j<COURSE; j++)
        {
            printf("%4d\t", score[i][j]); /*��ӡÿ�ſγɼ�*/
        }
        printf("%4d\t %5.1f\n", sumS[i], averS[i]);
    }
    printf("Sum of Course\t");
    for(j=0; j<COURSE; j++)
    {
        printf("%4d\t", sumC[j]);
    }
    printf("\n Aver of Course\t");
    for(j=0; j<COURSE; j++)
    {
        printf("%4.1f\t", averC[j]);
    }
    printf("\n");
}

/*�������ܣ���ӡ�����ѧ��ѧ�źͳɼ�
void Printscore(int score[], long num[], int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf("%12ld\t, %4d\n", num[i], score[i]);
    }
}*/
