/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Flow task
 */

#include "Task.hpp"

using namespace kF;

Flow::Task::~Task(void) noexcept
{
}

Flow::Task &Flow::Task::before(Task &other) noexcept
{
    _linkedTo.push(&other);
    other._linkedFrom.push(this);
    return *this;
}

Flow::Task &Flow::Task::after(Task &other) noexcept
{
    _linkedFrom.push(&other);
    other._linkedTo.push(this);
    return *this;
}
