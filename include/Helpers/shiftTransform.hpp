#pragma once

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"

namespace Helpers {
    using namespace UnityEngine;

    /**
     * @brief Shifts the position of a RectTransform by a given Vector3.
     *
     * @param transform The RectTransform to shift.
     * @param shift The Vector3 representing the shift in position.
     */
    inline void shiftTransform(RectTransform* transform, Vector3 shift) {
        auto currentPosition = transform->get_localPosition();
        transform->set_localPosition(Vector3(currentPosition.x + shift.x, currentPosition.y + shift.y, currentPosition.z + shift.z));
    }
}
