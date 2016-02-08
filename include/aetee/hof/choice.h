#ifndef HEADER_AETEE_COROLLARIES_CHOICE_H_INCLUDED
#define HEADER_AETEE_COROLLARIES_CHOICE_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/hof/curry.h>
#include <aetee/objects.h>

namespace aetee {

namespace detail {

struct choiceFunctor {
    template <typename Conditional, typename ABranch, typename BBranch>
    constexpr decltype(auto) operator()(Conditional c, ABranch a, BBranch b) const
    {
        return operator()(bool_c<c>, a, b);
    }

    template <typename BranchTaken, typename _>
    constexpr decltype(auto) operator()(bool_constant_t<true>, BranchTaken f, _) const
    {
        return f();
    }

    template <typename _, typename BranchTaken>
    constexpr decltype(auto) operator()(bool_constant_t<false>, _, BranchTaken f) const
    {
        return f();
    }

    template <typename F, typename A, typename B>
    static constexpr decltype(auto) transform(F f, A a, B b)
    {
        return transformer<F, A, B>{f, a, b};
    }

private:
    template <typename F, typename A = identityFunctor, typename B = identityFunctor>
    struct transformer {
        constexpr transformer(F f_, A a_ = {}, B b_ = {}) : f{f_}, a{a_}, b{b_} {};

        template <typename T>
        constexpr decltype(auto) operator()(T&& t)
        {
            return choiceFunctor{}(f(std::forward<T>(t)), curry(a, t), curry(b, t));
        }

        template <typename T>
        constexpr decltype(auto) operator()(T&& t) const
        {
            return choiceFunctor{}(f(std::forward<T>(t)), curry(a, t), curry(b, t));
        }

    private:
        F f;
        A a;
        B b;
    };

} /*struct choiceFunctor*/;

} /*namespace detail*/;

static constexpr auto choice = detail::choiceFunctor{};

} /*namespace aetee*/;

#endif
