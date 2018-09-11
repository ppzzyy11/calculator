#include<iostream>
#include<climits>
#include<fstream>
#include"stack.h"

using namespace std;

bool isValid(string& str);
bool isOperator(const char& ch);
bool isDigit(const char & ch);
bool Precedence(const char op1,const char op2);

long applyOp(long l1,long l2,char op);
long EvaluateString(const string expression)//return LONG_MIN means that /0
{
    stack<long> values;
    stack<char> ops;

    for(int i=0;i<expression.size();i++)
    {
        if(isDigit(expression[i]))
        {
            long l=0;
            while(i<expression.size()&&isDigit(expression[i]))
            {
                l=l*10+expression[i]-'0';
                i++;
            }
            values.push(l);
            i--;
        }else if(expression[i]=='(')
        {
            ops.push(expression[i]);
        } else if(expression[i]==')')
        {
            while(ops.top()!='(')
            {
                long l2=values.top();
                values.pop();
                long l1=values.top();
                values.pop();
                char op=ops.top();
                ops.pop();
                long res=applyOp(l1,l2,op);
                if(res==LONG_MIN)
                    return res;
                values.push(res);
            }
            ops.pop();
        }else if(isOperator(expression[i]))
        {
            while(!ops.empty()&&Precedence(expression[i],ops.top()))
            {
                long l2=values.top();
                values.pop();
                long l1=values.top();
                values.pop();
                char op=ops.top();
                ops.pop();
                long res=applyOp(l1,l2,op);
                if(res==LONG_MIN)
                    return res;
                values.push(res);
            }
            ops.push(expression[i]);
        }
    }
    while(!ops.empty())
    {
        long l2=values.top();
        values.pop();
        long l1=values.top();
        values.pop();
        char op=ops.top();
        ops.pop();
        long res=applyOp(l1,l2,op);
        if(res==LONG_MIN)
            return res;
        values.push(res);
    }
    return values.top();
}

int main(int argc,char** argv)
{
    if(argc<2)
    {
        cerr<<"too few arguments"<<endl;
        return 1;
    }
    string str;
    for(int i=6;argv[1][i]!='\0';i++)
    {
        str.push_back(argv[1][i]);
    }
    fstream in(str.c_str(),ios::in);
    while(getline(in,str))
    {
        string tmp=str;
        if(isValid(str)==false) continue;
        long res=EvaluateString(str);
        if(res==LONG_MIN) continue;
        cout<<tmp<<'='<<to_string(res)<<'\n';
    }

    return 0;
}

bool isOperator(const char& ch)
{
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/') return true;
    return false;
}

bool isDigit(const char& ch)
{
    return ch>='0'&&ch<='9';
}

bool isValid(string& str)
{
    //pathesis counts
    int cnt=0;
    for(int i=0;i<str.size();i++)
    {
        if(str[i]=='(')
        {
            if(i==str.size()-1||str[i+1]==')')
                return false;
            cnt++;
        }else if(str[i]==')')
        {
            cnt--;
        }
        if(cnt<0) return false;
    }
    if(cnt!=0) return false;

    //no continues () )(
    for(int i=0;i<str.size();i++)
    {
        if(str[i]=='('&&str[i+1]==')') return false;
        if(str[i]==')'&&str[i+1]=='(') return false;
    }

    //add leading 0 before negative number
    for(int i=0;i<str.size();i++)
    {
        if((str[i]=='-'||str[i]=='+')&&(i==0||str[i-1]=='('))
                str.insert(i,"0");
    }

    //no leadind operator
    for(int i=0;i<str.size();i++)
    {
        if(isOperator(str[i]))
        {
            if(i==0||str[i-1]=='(')
                return false;
        }
    }

    //no continues operator
    for(int i=0;i<str.size()-1;i++)
    {
        if(isOperator(str[i])&&isOperator(str[i+1]))
        {
            return false;
        }
    }








    return true;
}
bool Precedence(const char op1,const char op2)
{
    if(op2=='('||op2==')')
        return false;
    if((op1=='*'||op1=='/')&&(op2=='+'||op2=='-'))
        return false;
    else
        return true;
}

long applyOp(long l1,long l2,char op)
{
    switch (op)
    {
        case '-':
            return l1-l2;
            break;

        case '+':
            return l1+l2;
            break;

        case '*':
            return l1*l2;
            break;

        case '/':
            if(l2==0) return LONG_MIN;
            return l1/l2;
            break;
    }
    return LONG_MIN;
}
