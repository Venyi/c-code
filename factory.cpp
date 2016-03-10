
#include <string>
#include <map>
#include <stdio.h>


template<class TopBase>
class ReflectClassFactory
{
    typedef TopBase* (*TypeCreateFun)();
    private:
    static std::map<std::string, TypeCreateFun> &GetRegTypes()
    {
        static std::map<std::string, TypeCreateFun> types;
        return types;
    }

    public:
    ReflectClassFactory(const char *cmd, TypeCreateFun create) 
    {
        GetRegTypes()[cmd] = create;
    }

    static TopBase *GetInstance(const std::string &cmd)
    {
        std::map<std::string, TypeCreateFun> &types = GetRegTypes();
        typeof(types.begin()) itr = types.find(cmd);
        if ( itr == types.end())
        {
            return NULL;
        }
        return itr->second();
        //return types[cmd]();
    }

#define DECLEAR_REFLECT_CLASS(topbase) \
    static topbase* GetInstance(); \
    static ReflectClassFactory<topbase> *pFactory;

#define IMPLEMENT_REFLECT_CLASS(topbase,classname) \
    topbase* classname::GetInstance(){return new classname;}  \
    ReflectClassFactory<topbase> *classname::pFactory = new ReflectClassFactory<topbase>(#classname,classname::GetInstance);

};


class Base
{
    public:
        virtual void Print(){printf("base haha\n");}
};

class A:public Base
{
    public:
        virtual void Print(){printf("haha\n");}

    public:
        DECLEAR_REFLECT_CLASS(Base)


};

IMPLEMENT_REFLECT_CLASS(Base,A)

class B:public Base
{
    public:
        void Print(){printf("B haha\n");}

    public:
        DECLEAR_REFLECT_CLASS(Base)

};
IMPLEMENT_REFLECT_CLASS(Base,B)

int main(void)
{
    A a;
    B b;

    a.Print();
    b.Print();

    Base *p = NULL;

    p = ReflectClassFactory<Base>::GetInstance("A");    

    p->Print();

    return 0;
}
