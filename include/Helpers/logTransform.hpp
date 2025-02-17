#pragma once

#include "logger.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"

namespace Helpers {
    using namespace UnityEngine;

    /**
     * @brief Logs the size and position of a RectTransform.
     *
     * @param transform The RectTransform to log.
     */
    inline void logTransform(RectTransform* transform) {
        auto currentSize = transform->get_sizeDelta();
        auto currentPosition = transform->get_localPosition();

        Logger.info("{} size: {}, {}", transform->name, currentSize.x, currentSize.y);
        Logger.info("{} position: {}, {}, {}", transform->name, currentPosition.x, currentPosition.y, currentPosition.z);
    }
}  // namespace Helpers
