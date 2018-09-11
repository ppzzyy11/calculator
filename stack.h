#ifndef stack_h_
#define stack_h_

#include<iostream>
#include<vector>

using namespace std;
//st all ok
template<typename T>
class stack{
    private:
        vector<T> eles;

    public:
        int size(){return eles.size();}
        T top(){return eles.back();}
        void pop(){eles.pop_back();}
        void push(T t){eles.push_back(t);}
        bool empty(){return eles.size()==0;}
        void traversal()
        {
            for(int i=0;i<eles.size();i++)
            {
                cout<<eles[i]<<' ';
            }
            cout<<endl;
        }

};
#endif
