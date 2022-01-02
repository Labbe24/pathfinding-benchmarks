#include <functional>

struct GridLocation {
    int x, y;
  
    friend bool operator<(const GridLocation& lhs, const GridLocation& rhs)
    {
        return (lhs.x == rhs.x);
    }

    friend bool operator==(const GridLocation& lhs, const GridLocation& rhs)
    {
        return (lhs.x == rhs.x && lhs.y == rhs.y);
    }

    friend bool operator!=(const GridLocation& lhs, const GridLocation& rhs)
    {
        return (lhs.x != rhs.x || lhs.y != rhs.y);
    }
};

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
    template <> struct hash<GridLocation> {
    std::size_t operator()(const GridLocation& id) const noexcept {
        // NOTE: better to use something like boost hash_combine
        return std::hash<int>()(id.x ^ (id.y << 16));
        }
    };
}

