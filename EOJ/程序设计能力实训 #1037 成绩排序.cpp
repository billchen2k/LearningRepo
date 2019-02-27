//2019.2.28
#include <iostream>
#include <cstring>
using namespace std;
struct student
{
    char ID[12];
    long int mark;
    int solvedq;
};
int cmp(const void *pa, const void *pb)
{
    struct student *pta = (struct student *)pa;
    struct student *ptb = (struct student *)pb;
    if (pta->mark != ptb->mark)
    {
        return ptb->mark - pta->mark;
    }
    else
    {
        return strcmp(pta->ID, ptb->ID);
    }
}

int main()
{
    int len;
    cin >> len;
    int i = 0, j = 0, k = 0;
    for (i = 0; i < len; i++)
    {
        int N, M, G;
        int markperq[10] = {0};
        cin >> N >> M >> G;
        for (j = 0; j < M; j++)
            cin >> markperq[j];
        struct student stu[500];
        for (j = 0; j < N; j++)
        {
            stu[j].mark = 0;
            //scanf("%ld %d", &stu[j].ID, &stu[j].solvedq);
            cin >> stu[j].ID >> stu[j].solvedq;
            for (k = 0; k < stu[j].solvedq; k++)
            {
                int temp;
                cin >> temp;
                stu[j].mark += markperq[temp - 1];
            }
        }
        struct student stuPassed[500];
        for (j = 0, k = 0; j < N; j++)
        {
            if (stu[j].mark >= G)
            {
                strcpy(stuPassed[k].ID, stu[j].ID);
                stuPassed[k].mark = stu[j].mark;
                stuPassed[k].solvedq = stu[j].solvedq;
                k++;
            }
        }
        cout << "case #" << i << ":\n";
        if (k == 0)
        {
            cout << "0" << endl;
        }
        else
        {
            qsort(stuPassed, k, sizeof(stu[0]), cmp);
            cout << k << endl;
            for (j = 0; j < k; j++)
            {
                cout << stuPassed[j].ID << " " << stuPassed[j].mark << endl;
            }
        }
    }
    return 0;
}