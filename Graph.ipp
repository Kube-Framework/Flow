/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Flow graph
 */

#include "Graph.hpp"

template<typename WorkFunc>
    requires std::constructible_from<kF::Flow::Task::Work, WorkFunc>
inline kF::Flow::Task &kF::Flow::Graph::add(WorkFunc &&work) noexcept
{
    invalidateScheduleCache();

    return *_tasks.push(TaskPtr::Make(*this, std::forward<WorkFunc>(work)));
}

template<auto Function>
    requires std::constructible_from<kF::Flow::Task::Work, decltype(Function)>
inline kF::Flow::Task &kF::Flow::Graph::add(void) noexcept
{
    constexpr bool IsSwitchWork = std::is_convertible_v<decltype([] { return (*Function)(); }), Task::SwitchWork>;

    invalidateScheduleCache();

    std::conditional_t<IsSwitchWork, Task::SwitchWork, Task::StaticWork> work;
    work.prepare<Function>();
    return *_tasks.push(TaskPtr::Make(*this, std::move(work)));
}

template<auto MemberFunction, typename ClassType>
inline kF::Flow::Task &kF::Flow::Graph::add(ClassType * const instance) noexcept
{
    constexpr bool IsSwitchWork = std::is_convertible_v<decltype([](ClassType *ptr) { return (ptr->*MemberFunction)(); }), Task::SwitchWork>;

    invalidateScheduleCache();

    std::conditional_t<IsSwitchWork, Task::SwitchWork, Task::StaticWork> work;
    work.prepare<MemberFunction>(instance);
    return *_tasks.push(TaskPtr::Make(*this, std::move(work)));
}
