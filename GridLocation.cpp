#include <functional>

class GridLocation {
    public:
        friend class Node;
        template<typename T, typename L> friend class GridGraph;

        GridLocation(unsigned int x, unsigned int y);
        GridLocation();

        GridLocation(const GridLocation& other);
        GridLocation& operator=(const GridLocation& other);

        void setX(unsigned int x);
        void setY(unsigned int y);

        unsigned int getX() const;
        unsigned int getY() const;
    
        friend bool operator<(const GridLocation& lhs, const GridLocation& rhs)
        {
            return (lhs.getX() == rhs.getX());
        }

        friend bool operator==(const GridLocation& lhs, const GridLocation& rhs)
        {
            return (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY());
        }

        friend bool operator!=(const GridLocation& lhs, const GridLocation& rhs)
        {
            return (lhs.getX() != rhs.getX() || lhs.getY() != rhs.getY());
        }       

    private:
        unsigned int x_;
        unsigned int y_;
};

GridLocation::GridLocation(unsigned int x, unsigned int y)
:x_(x), y_(y)
{}

GridLocation::GridLocation()
{}

GridLocation::GridLocation(const GridLocation& other)
{
    this->x_ = other.x_;
    this->y_ = other.y_;
}

GridLocation& GridLocation::operator=(const GridLocation& other)
{
    this->x_ = other.x_;
    this->y_ = other.y_;
    return *this;
}

void GridLocation::setX(unsigned int x)
{
    x_ = x;
}

void GridLocation::setY(unsigned int y)
{
    y_ = y;
}

unsigned int GridLocation::getX() const
{
    return x_;
}

unsigned int GridLocation::getY() const
{
    return y_;
}

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
    template <> struct hash<GridLocation> {
    std::size_t operator()(const GridLocation& id) const noexcept {
        // NOTE: better to use something like boost hash_combine
        return std::hash<int>()(id.getX() ^ (id.getY() << 16));
        }
    };
}

