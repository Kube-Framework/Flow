/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Flow allocator
 */

#pragma once

#include <Kube/Core/StaticSafeAllocator.hpp>

namespace kF::Flow
{
    /** @brief Allocator of the flow library */
    using FlowAllocator = Core::StaticSafeAllocator<"FlowAllocator">;
}