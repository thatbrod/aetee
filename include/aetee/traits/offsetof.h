#ifndef HEADER_AETEE_TRAITS_OFFSETOF_H_INCLUDED
#define HEADER_AETEE_TRAITS_OFFSETOF_H_INCLUDED
#include <aetee/int_c.h>
#include <aetee/type_c.h>
#include <array>

namespace aetee {

namespace detail {

struct offsetOfFunctor {

    template <typename... T, size_t I = sizeof...(T)>
    constexpr auto operator()(type_sequence_t<T...> ts, idx_constant_t<I> i = {}) const
    {
        return int_constant_c<std::ptrdiff_t, impl(ts, i)>;
    }

private:

    template <typename... T, size_t I>
    static constexpr std::ptrdiff_t impl(type_sequence_t<T...>, idx_constant_t<I>)
    {
        constexpr std::array<size_t, sizeof...(T)> szs{sizeof(T)...};
        constexpr std::array<size_t, sizeof...(T) +1> als{ alignof(T)..., std::max({alignof(T)...}) };
        std::ptrdiff_t result{0};
        for (size_t i = 0; i != I; ++i) {
            result = ((result + szs[i] + als[i+1] - 1) / als[i+1]) * als[i+1];
        }
        return result;
    }

} /*struct offsetOfFunctor*/;

} /*namespace detail*/;

static constexpr auto offsetof_ = detail::tupifyFunctor{};

} /*namespace aetee*/;

#endif

