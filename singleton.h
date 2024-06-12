#ifndef SINGLETON_H
#define SINGLETON_H

/**
 * @brief The Singleton class 单例模式模板，静态局部变量实现
 * @example
 * class Test : public Singleton<Test>
 * {
 *     Test() = default;
 * public:
 *     friend class Singleton<Test>;
 * }
 */
template <typename T>
class Singleton
{
public:
    Singleton() = default;
    virtual ~Singleton() = default;
    Singleton(Singleton &&) = delete;
    Singleton(const Singleton &) = delete;
    void operator = (const Singleton &) = delete;

    static T* instance()
    {
        static T object;
        return &object;
    }
};

#endif // SINGLETON_H
