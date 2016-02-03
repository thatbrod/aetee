#ifndef HEADER_AETEE_AXIOMS_FOR_EACH_H_INCLUDED
#define HEADER_AETEE_AXIOMS_FOR_EACH_H_INCLUDED
#include <tuple>
#include <utility>

namespace aetee {

namespace detail {

struct forEachFunctor {
    template <typename Tup, typename F>
    constexpr auto operator()(Tup&& tup, F&& fn) const
    {
        constexpr size_t N = std::tuple_size<std::decay_t<Tup>>::value;
        return impl(std::forward<Tup>(tup), std::forward<F>(fn), std::make_index_sequence<N>{});
    }

private:
    template <typename Tup, size_t... I, typename F>
    constexpr auto impl(Tup&& tup, F&& fn, std::index_sequence<I...>)
    {
        (fn(std::get<I>(std::forward<Tup>(tup))), ...);
        return fn;
    }
} /*struct forEachFunctor*/;

} /*namespace detail*/;

static constexpr auto for_each = detail::forEachFunctor{};

} /*namespace aetee*/;

#endif
