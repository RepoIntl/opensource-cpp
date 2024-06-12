#ifndef SOCPEGUARD_H
#define SOCPEGUARD_H

#include <iostream>

/**
 * @brief The ScopeGuard class
 * RAII 辅助类
 * @example
 * int *p = (int *)malloc(sizeof(int));
 * SCOPE_GUARD { free(p); };
 */
template <typename Function>
class ScopeGuard
{
    Function fun;
    bool active;

public:
    ScopeGuard(Function f) : fun(std::move(f)), active(true)
    {
    }
    ~ScopeGuard()
    {
        if (active)
        {
            fun();
        }
    }

    /**
     * @brief dismiss
     * 解除ScopeGuard的调用，常见于遇到异常的情况
     */
    void dismiss()
    {
        active = false;
    }

    ScopeGuard() = delete;
    ScopeGuard(const ScopeGuard &) = delete;
    ScopeGuard &operator=(const ScopeGuard &) = delete;
    ScopeGuard(ScopeGuard &&rhs) : fun(std::move(rhs.fun)), active(rhs.active)
    {
        rhs.dismiss();
    }
};

#ifdef __COUNTER__
#define MAKE_NAME(x) JOIN_WRAPPER(x, __COUNTER__)
#else
#define MAKE_NAME(x) JOIN_WRAPPER(x, __LINE__)
#endif
#define JOIN_WRAPPER(x, y) JOIN_IMPL(x, y)
#define JOIN_IMPL(x, y) x##y

#define SCOPE_GUARD ScopeGuard MAKE_NAME(USELESS_NAME) = [&]()

#endif
