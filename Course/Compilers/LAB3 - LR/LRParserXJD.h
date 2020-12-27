//
// LR Parser By XJD
//

#ifndef C_LR_PARSER_LRPARSERXJD_H
#define C_LR_PARSER_LRPARSERXJD_H


#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
/* 不要修改这个标准输入函数 */
void read_prog(string& prog)
{
    char c;
    while(scanf("%c",&c)!=EOF&&c!='$'){
        prog += c;
    }
}
/* 你可以添加其他函数 */
map<string,string> a[30];
map<string,string> p;
int Max;
int cal(string x)
{
    return x[0]-'A';
}
void init()
{
    a[cal("A")]["{"]="B";
    a[cal("B")]["{"]="{G}";
    a[cal("C")]["w"]="E";
    a[cal("C")]["y"]="D";
    a[cal("C")]["{"]="B";
    a[cal("C")]["["]="F";
    a[cal("D")]["y"]="y(H)vCuC";
    a[cal("E")]["w"]="w(H)C";
    a[cal("F")]["["]="[=L;";
    a[cal("G")]["w"]="CG";
    a[cal("G")]["y"]="CG";
    a[cal("G")]["{"]="CG";
    a[cal("G")]["}"]="@";
    a[cal("G")]["["]="CG";
    a[cal("H")]["("]="LNL";
    a[cal("H")]["["]="LNL";
    a[cal("H")]["]"]="LNL";
    a[cal("I")]["z"]="@";
    a[cal("I")]["x"]="@";
    a[cal("I")]["."]="@";
    a[cal("I")][")"]="@";
    a[cal("I")]["<"]="@";
    a[cal("I")]["+"]="+JI";
    a[cal("I")]["-"]="-JI";
    a[cal("I")][";"]="@";
    a[cal("I")]["!"]="@";
    a[cal("I")]["}"]="@";
    a[cal("J")]["("]="KM";
    a[cal("J")]["["]="KM";
    a[cal("J")]["]"]="KM";
    a[cal("K")]["("]="(L)";
    a[cal("K")]["["]="[";
    a[cal("K")]["]"]="]";
    a[cal("L")]["("]="JI";
    a[cal("L")]["["]="JI";
    a[cal("L")]["]"]="JI";
    a[cal("M")]["z"]="@";
    a[cal("M")]["x"]="@";
    a[cal("M")]["."]="@";
    a[cal("M")][")"]="@";
    a[cal("M")]["<"]="@";
    a[cal("M")]["+"]="@";
    a[cal("M")]["-"]="@";
    a[cal("M")][";"]="@";
    a[cal("M")]["!"]="@";
    a[cal("M")]["/"]="/KM";
    a[cal("M")]["*"]="*KM";

    a[cal("M")]["}"]="@";
    a[cal("N")]["z"]="z";
    a[cal("N")]["x"]="x";
    a[cal("N")]["."]=".";
    a[cal("N")]["<"]="<";
    a[cal("N")]["!"]="!";

    p["A"]="program";
    p["B"]="compoundstmt";
    p["C"]="stmt";
    p["D"]="ifstmt";
    p["E"]="whilestmt";
    p["F"]="assgstmt";
    p["G"]="stmts";
    p["H"]="boolexpr";
    p["I"]="arithexprprime";
    p["J"]="multexpr";
    p["K"]="simpleexpr";
    p["L"]="arithexpr";
    p["M"]="multexprprime";
    p["N"]="boolop";
    p["!"]=">";
    p["["]="ID";
    p["]"]="NUM";
    p["."]="==";
    p["z"]=">=";
    p["x"]="<=";
    p["y"]="if";
    p["u"]="else";
    p["v"]="then";
    p["w"]="while";
}
#define PII pair<string,int>
vector<PII> ans;

int line;
int solve(string s,int &cur,int l,int d)
{
    //cout<<l<<" "<<d<<" "<<cur<<endl;
    int len=s.length();
    int i=l;
    while(1)
    {
        if (s[i]=='\n') line++,i++;
        else if (s[i]==' '||s[i]=='\t'||s[i]=='\r'||s[i]=='\v') i++;
        else break;
    }
    //cout<<i<<" "<<d<<" "<<cur<<endl;
    string x="";x+=s[i];
    if (s[i]=='I'&&s[i+1]=='D') x=a[cur]["["];//,puts("fuck");
    else if (s[i]=='>'&&s[i+1]=='=') x=a[cur]["z"];
    else if (s[i]=='<'&&s[i+1]=='=') x=a[cur]["x"];
    else if (s[i]=='='&&s[i+1]=='=') x=a[cur]["."];
    else if (s[i]=='>') x=a[cur]["!"];
    else if (s[i]=='i'&&s[i+1]=='f') x=a[cur]["y"];
    else if (s[i]=='t'&&s[i+1]=='h') x=a[cur]["v"];
    else if (s[i]=='e'&&s[i+1]=='l') x=a[cur]["u"];
    else if (s[i]=='w'&&s[i+1]=='h') x=a[cur]["w"];
    else if (s[i]=='N'&&s[i+1]=='U'&&s[i+2]=='M') x=a[cur]["]"];
    else x=a[cur][x];
    //cout<<s[i]<<" "<<s[i+1]<<" "<<s[i+2]<<" "<<a[cur]["["]<<endl;
    //cout<<x<<endl;
    //int zzz;cin>>zzz;
    for (int j=0;j<x.length();j++)
        if (x[j]>='A'&&x[j]<='Z')
        {
            //for (int k=1;k<=d;k++)
            //    putchar('\t');
            string y="";y+=x[j];
            //cout<<p[y]<<endl;
            ans.push_back(make_pair(p[y],d));
            Max=max(Max,d);
            cur=cal(y);
            i=solve(s,cur,i,d+1);
        }
        else if (x[j]=='@')
        {
            ans.push_back(make_pair("@",-d));
            /*for (int k=1;k<=d;k++)
                putchar('\t');
            puts("E");*/
        }
        else
        {
            //for (int k=1;k<=d;k++)
            //    putchar('\t');
            string y="";y+=x[j];
            if (x[j]=='!'||x[j]=='['||x[j]==']'||x[j]=='.'||x[j]=='z'||x[j]=='x'||x[j]=='y'||x[j]=='u'||x[j]=='v'||x[j]=='w') y=p[y];
            int flag=0;
            for (int k=0;k<y.length();k++)
            {
                while(1)
                {
                    if (s[i]=='\n') line++,i++;
                    else if (s[i]==' '||s[i]=='\n'||s[i]=='\t'||s[i]=='\r'||s[i]=='\v') i++;
                    else break;
                }
                if (s[i]!=y[k]) flag=1,i--;
                i++;
            }
            /*if (flag==1)
            {
                printf("语法错误,第%d行,缺少\"",line);
                cout<<y;
                printf("\"\n");
            }*/
            ans.push_back(make_pair(y,-d));
            Max=max(Max,d);
            //cout<<y<<endl;
        }
    return i;
}
int error(string s,int &cur,int l,int d)
{
    //cout<<l<<" "<<d<<" "<<cur<<endl;
    int len=s.length();
    int i=l;
    while(1)
    {
        if (s[i]=='\n') line++,i++;
        else if (s[i]==' '||s[i]=='\t'||s[i]=='\r'||s[i]=='\v') i++;
        else break;
    }
    //cout<<i<<" "<<d<<" "<<cur<<endl;
    string x="";x+=s[i];
    if (s[i]=='I'&&s[i+1]=='D') x=a[cur]["["];//,puts("fuck");
    else if (s[i]=='>'&&s[i+1]=='=') x=a[cur]["z"];
    else if (s[i]=='<'&&s[i+1]=='=') x=a[cur]["x"];
    else if (s[i]=='='&&s[i+1]=='=') x=a[cur]["."];
    else if (s[i]=='>') x=a[cur]["!"];
    else if (s[i]=='i'&&s[i+1]=='f') x=a[cur]["y"];
    else if (s[i]=='t'&&s[i+1]=='h') x=a[cur]["v"];
    else if (s[i]=='e'&&s[i+1]=='l') x=a[cur]["u"];
    else if (s[i]=='w'&&s[i+1]=='h') x=a[cur]["w"];
    else if (s[i]=='N'&&s[i+1]=='U'&&s[i+2]=='M') x=a[cur]["]"];
    else x=a[cur][x];
    //cout<<s[i]<<" "<<s[i+1]<<" "<<s[i+2]<<" "<<a[cur]["y"]<<endl;
    //cout<<x<<endl;
    //int zzz;cin>>zzz;
    for (int j=0;j<x.length();j++)
        if (x[j]>='A'&&x[j]<='Z')
        {
            /*for (int k=1;k<=d;k++)
                putchar('\t');*/
            string y="";y+=x[j];
            //cout<<p[y]<<endl;
            cur=cal(y);
            //cout<<cur<<endl;
            i=error(s,cur,i,d+1);
        }
        else if (x[j]=='@')
        {
            /* for (int k=1;k<=d;k++)
                 putchar('\t');
             puts("E");*/
        }
        else
        {
            /*for (int k=1;k<=d;k++)
                putchar('\t');*/
            string y="";y+=x[j];
            if (x[j]=='!'||x[j]=='['||x[j]==']'||x[j]=='.'||x[j]=='z'||x[j]=='x'||x[j]=='y'||x[j]=='u'||x[j]=='v'||x[j]=='w') y=p[y];
            int flag=0;
            for (int k=0;k<y.length();k++)
            {
                while(1)
                {
                    if (s[i]=='\n') line++,i++;
                    else if (s[i]==' '||s[i]=='\n'||s[i]=='\t'||s[i]=='\r'||s[i]=='\v') i++;
                    else break;
                }
                if (s[i]!=y[k]) flag=1,i--;
                i++;
            }
            if (flag==1)
            {
                printf("语法错误，第%d行，缺少\"",line);
                cout<<y;
                printf("\"\n");
            }
            //cout<<y<<endl;
        }
    return i;
}

void Analysis()
{
    string prog;
    read_prog(prog);
    /* 骚年们 请开始你们的表演 */
    /********* Begin *********/
    init();
    int len=prog.length();
    int cur=cal("A");line=0;
    for (int i=0;i<len;)
    {
        i=error(prog,cur,i,1);
    }
    //puts("program");
    ans.push_back(make_pair("program",0));
    cur=cal("A");
    Max=0;
    for (int i=0;i<len;)
    {
        i=solve(prog,cur,i,1);
    }

/*for (auto x:ans)
    cout<<x.second<<" "<<x.first<<endl;*/
    cout<<"program =>"<<endl;
    int n=ans.size();
    ans.push_back(make_pair("",0));
    int a[1000],b[1000];a[1]=0;int l=1;
    while(1)
    {
        int flag=-1;
        for (int i=l;i>=1;i--)
            if (ans[a[i]].second>=0) {flag=i;break;}
        if (flag==-1) break;
        int r=0;
        for (int i=1;i<flag;i++) b[++r]=a[i];
        int d1=abs(ans[a[flag]+1].second),d2=abs(ans[a[flag]].second);
        //cout<<d1<<" "<<d2<<" "<<a[flag]+1<<endl;
        for (int i=a[flag]+1;i<n;i++)
        {
            //cout<<i<<" "<<abs(ans[i].second)<<endl;
            if (abs(ans[i].second)<=d2) break;
            else if (abs(ans[i].second)==d1) b[++r]=i;
        }
        for (int i=flag+1;i<=l;i++)
            b[++r]=a[i];
        flag=-1;
        for (int i=r;i>=1;i--)
            if (ans[b[i]].second>=0) {flag=i;break;}
        if (flag==-1){
            l=0;
            string x="@";
            for (int i=1;i<=r;i++)
            {
                if (ans[b[i]].first==x) continue;
                //cout<<ans[b[i]].first<<" ";
                a[++l]=b[i];
            }
            cout<<ans[b[1]].first;
            for (int i=2;i<=l;i++)
            {
                cout<<" "<<ans[a[i]].first;
            }
            cout<<endl;
            break;
        }
        l=0;
        string x="@";
        for (int i=1;i<=r;i++)
        {
            if (ans[b[i]].first==x) continue;
            cout<<ans[b[i]].first<<" ";
            a[++l]=b[i];
        }
        cout<<"=>"<<endl;
        //int zzz;cin>>zzz;
    }
    /********* End *********/

}


/*
0 program
1 compoundstmt
-2 {
2 stmts
3 stmt
4 assgstmt
-5 ID
-5 =
5 arithexpr
6 multexpr
7 simpleexpr
-8 NUM
7 multexprprime
-8 @
6 arithexprprime
-7 @
-5 ;
3 stmts
-4 @
-2 }
*/

#endif //C_LR_PARSER_LRPARSERXJD_H
