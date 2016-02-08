#ifndef HEADER_AETEE_AXIOMS_COMPOSE_H_INCLUDED
#define HEADER_AETEE_AXIOMS_COMPOSE_H_INCLUDED
#include <aetee/objects.h>
#include <aetee/hof/fold.h>
#include <utility>

namespace aetee {

namespace detail {

template <typename F, typename G>
struct compositionFunctor {
    template <typename... A>
    constexpr auto operator()(A&&... a)
    {
        return f(g(std::forward<A>(a)...));
    }

    template <typename... A>
    constexpr auto operator()(A&&... a) const
    {
        return f(g(std::forward<A>(a)...));
    }

private:
    F f;
    G g;
} /*struct compositionFunctor*/;

struct composeFunctor {
    template <typename F, typename G>
    constexpr auto operator()(F&& f, G&& g) const
    {
        return compositionFunctor<F, G>{std::forward<F>(f), std::forward<G>(g)};
    }
} /*struct composeFunctor*/;

} /*namespace detail*/;

static constexpr auto composition = detail::composeFunctor{};

} /*namespace aetee*/;

#endif
