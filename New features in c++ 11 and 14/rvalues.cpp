#include <utility> // ��� std::move � std::forward

template<typename Function, typename ...Args>
auto apply(Function func, Args&&... args) -> decltype(func(std::forward<Args>(args)...)) {
	return func(std::forward<Args>(args)...);
}