#include <queue>


namespace PQ
{
    /* Basically a wrapper for the std::priority_queue */
    template<typename T, typename P>
    class PriorityQueue
    {
        typedef std::pair<P, T> element;

        public:

            bool empty() const {
                return elements_.empty();
            }

            void put(T element, P priority) {
            elements_.emplace(priority, element);
            }
            
            T get() {
                T best_element = elements_.top().second;
                elements_.pop();
                return best_element;
            }
        
        private:

            std::priority_queue<element, std::vector<element>, std::greater<element>> elements_;
    };
}