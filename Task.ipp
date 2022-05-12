/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Flow task
 */

#include "Task.hpp"

inline kF::Flow::Task::Work::~Work(void) noexcept
{
    switch (type) {
    case WorkType::Static:
        staticWork.~StaticWork();
        break;
    case WorkType::Switch:
        switchWork.~SwitchWork();
        break;
    case WorkType::Graph:
        graphWork.~GraphWork();
        break;
    default:
        break;
    }
}

template<typename Type>
inline kF::Flow::Task::Work::Work(Type &&value) noexcept
{
    static_assert(std::is_constructible_v<StaticWork, Type> || std::is_constructible_v<GraphWork, Type>,
        "Flow::Task::Work: Invalid work type");

    if constexpr (std::is_constructible_v<SwitchWork, Type>) {
        type = WorkType::Switch;
        new (&switchWork) SwitchWork(std::forward<Type>(value));
    } else if constexpr (std::is_constructible_v<StaticWork, Type>) {
        type = WorkType::Static;
        new (&staticWork) StaticWork(std::forward<Type>(value));
    } else if constexpr (std::is_constructible_v<GraphWork, Type>) {
        type = WorkType::Graph;
        new (&graphWork) GraphWork(std::forward<Type>(value));
    }
}