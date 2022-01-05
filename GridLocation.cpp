#include <functional>

class GridLocation {
    public:
        friend class Node;
        template<typename T, typename L> friend class GridGraph;

        // Constructors
        GridLocation();
        GridLocation(const int x, const int y);
        
        // Copy constructor
        GridLocation(const GridLocation& other);

        // Copy assignment operator
        GridLocation& operator=(const GridLocation& other);

        int getX() const;
        int getY() const;
    
        friend bool operator<(const GridLocation& lhs, const GridLocation& rhs)
        {
            return (lhs.x_ > rhs.x_ && lhs.y_ > rhs.y_);
        }

        friend bool operator==(const GridLocation& lhs, const GridLocation& rhs)
        {
            return (lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_);
        }

        friend bool operator!=(const GridLocation& lhs, const GridLocation& rhs)
        {
            return (lhs.x_ != rhs.x_ || lhs.y_ != rhs.y_);
        }

    private:
        int x_;
        int y_;
};

GridLocation::GridLocation(const int x, const int y)
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

int GridLocation::getX() const
{
    return x_;
}

int GridLocation::getY() const
{
    return y_;
}

/* Implement hash function to GridLocation into an unordered_set and add to std namespace */
namespace std {
    template <> struct hash<GridLocation> {
    std::size_t operator()(const GridLocation& id) const noexcept {
        return std::hash<int>()(id.getX() ^ (id.getY() << 16));
        }
    };
}

