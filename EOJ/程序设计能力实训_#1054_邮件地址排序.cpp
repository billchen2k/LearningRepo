#include <iostream>
#include <string.h>
using namespace std;
typedef struct
{
    char username[1000000];
    char domain[1000000];
} email;
typedef struct
{
    char username[101];
    char domain[101];
} emailsmall;
int cmp(const void *pa, const void *pb)
{
    email *pta = (email *)pa;
    email *ptb = (email *)pb;
    if (strcmp(pta->domain, ptb->domain) != 0)
        return strcmp(pta->domain, ptb->domain);
    else
        return -strcmp(pta->username, ptb->username);
}
int cmpsmall(const void *pa, const void *pb)
{
    emailsmall *pta = (emailsmall *)pa;
    emailsmall *ptb = (emailsmall *)pb;
    if (strcmp(pta->domain, ptb->domain) != 0)
        return strcmp(pta->domain, ptb->domain);
    else
        return -strcmp(pta->username, ptb->username);
}
int main()
{
    int len;
    scanf("%d", &len);
    if (len >= 100000)
    {
        emailsmall data[len];
        while (cin.get() != '\n')
            continue;
        for (int i = 0; i < len; i++)
        {
            char temp[202] = {0};
            cin.getline(temp, 202);
            int j = 0;
            while (temp[j] != '@')
                j++;
            strncpy(data[i].username, temp, j);
            data[i].username[j] = '\0';
            strncpy(data[i].domain, temp + j + 1, strlen(temp) - j - 1);
            data[i].domain[strlen(temp) - j - 1] = '\0';
        }
        qsort(data, len, sizeof(data[0]), cmpsmall);
        for (int k = 0; k < len; k++)
            printf("%s@%s\n", data[k].username, data[k].domain);
    }
    else
    {
        email data[len];
        while (cin.get() != '\n')
            continue;
        for (int i = 0; i < len; i++)
        {
            char temp[1000000] = {0};
            cin.getline(temp, 1000000);
            int j = 0;
            while (temp[j] != '@')
                j++;
            strncpy(data[i].username, temp, j);
            data[i].username[j] = '\0';
            strncpy(data[i].domain, temp + j + 1, strlen(temp) - j - 1);
            data[i].domain[strlen(temp) - j - 1] = '\0';
        }
        qsort(data, len, sizeof(data[0]), cmp);
        for (int k = 0; k < len; k++)
            printf("%s@%s\n", data[k].username, data[k].domain);
    }
    return 0;
}