#ifndef FACTORY
#define FACTORY

#include <qdebug.h>

#include <string>
#include <map>
#include <functional>

using namespace std;

template <typename T, typename K = std::string>
class Factory
{
public:

    typedef T type_value;

    template <typename N>
    struct register_h
    {
        register_h(const K& key)
        {
            Factory::instance()->m_creators[key] = []{ return new N; };
			qDebug()<<QString::fromStdString(key);
        }
    };


    static auto instance() -> Factory<T, K>*
    {
        static Factory<T, K> f;
        return &f;
    }

    auto creat(const K& key) -> T*
    {
        T* re = NULL;
        auto ite = m_creators.find(key);
        if (ite != m_creators.end()) {
            re = (ite->second)();
        }
        return re;
    }

    static auto produce(const K& key) -> T*
    {
        return Factory::instance()->creat(key);
    }

private:
    Factory() {}
    Factory(const Factory&) = delete;
    Factory(Factory&&) = delete;
    Factory& operator =(const Factory&) = delete;
    std::map<K, std::function<T*()>> m_creators;
};


#define CLASS_NAME(CLASS) #CLASS



#endif // FACTORY

