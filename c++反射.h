/* 
 * File:   ReflectClassFactory.h
 * Author: stephyang
 * 反射类工厂
 * Created on 2010年5月12日, 上午9:22
 */

#ifndef _REFLECTCLASSFACTORY_H
#define	_REFLECTCLASSFACTORY_H
#include <string>
#include <map>
#include <iostream>

namespace tencent_itil
{

    template<class TopBase>
    class ReflectClassFactory
    {
        typedef TopBase* (*TypeCreateFun)();
    private:
        static std::map<std::string, ReflectClassFactory*>& GetRegTypes()
        {
            static std::map<std::string, ReflectClassFactory*> types;
            return types;
        }
        const char* _typeName;
        TypeCreateFun _typeCreate;

    public:
        ReflectClassFactory(const char* name, TypeCreateFun create) :
        _typeName(name), _typeCreate(create)
        {
            GetRegTypes()[name] = this;
        }

        static TopBase *GetInstance(const std::string &typeName)
        {
            std::map<std::string, ReflectClassFactory*>& types = GetRegTypes();
            if (types.find(typeName) == types.end())
            {
                return NULL;
            }
            return types[typeName]->_typeCreate();
        }
    };

    //使用该宏定义于类声明中  topbase为基类类名
    #define DECLEAR_REFLECT_CLASS(topbase) \
	static topbase* GetInstance(); \
	static ReflectClassFactory<topbase> *pFactory;

    //使用该宏定义与类实现中 topbase为基类类名  classname为该类的类名
    #define IMPLEMENT_REFLECT_CLASS(topbase, classname) \
	topbase* classname::GetInstance(){return new classname;} \
	ReflectClassFactory<topbase> *classname::pFactory = new ReflectClassFactory<topbase>(#classname, classname::GetInstance);
}


#endif	/* _REFLECTCLASSFACTORY_H */

