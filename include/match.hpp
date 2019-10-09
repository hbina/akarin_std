#include <variant>

namespace ktl
{
template <typename... Ts>
struct pattern
{
    std::variant<Ts...> value;
};
} // namespace ktl
