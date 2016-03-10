#include "stdio.h"
#include <string>

class CPrintfSomeString
{
    public:
        CPrintfSomeString()
            :_thing("something")
        {}

        ~CPrintfSomeString()
        {}

        int SetSomeThing(std::string& thing);

        int GetSomeThing(std::string& thing);

        int PrintSomeThing();
    private:
        std::string _thing;
};

int CPrintfSomeString::GetSomeThing(std::string& thing)
{
    thing = _thing;
    return 0;
}

int CPrintfSomeString::SetSomeThing(std::string& thing)
{
    _thing = thing;
    return 0;
}

int CPrintfSomeString::PrintSomeThing()
{
    printf("%s\n", _thing.c_str());
}

template<typename paramType, typename funType, typename classType>
int Handle(classType& className, funType fun, paramType& param)
{
    int iRet = 0;
    iRet = (className.*fun)(param);
}

int main()
{
    CPrintfSomeString someThing;
    std::string str;
    Handle(someThing, &CPrintfSomeString::GetSomeThing, str);
    printf("str:%s\n", str.c_str());

    str = "test";
    Handle(someThing, &CPrintfSomeString::SetSomeThing, str);
    printf("str:%s\n", str.c_str());

    someThing.PrintSomeThing();
}

