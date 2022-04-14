#pragma once

#include "custom-types/shared/macros.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/EventSystems/PointerEventData.hpp"
#include "GlobalNamespace/IVRPlatformHelper.hpp"

DECLARE_CLASS_CODEGEN(PlaylistManager, Scroller, UnityEngine::MonoBehaviour,

    private:
    bool addedDelegate = false, pointerHovered = false;

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(void, Init, UnityEngine::RectTransform* content);
    DECLARE_INSTANCE_METHOD(void, HandlePointerDidEnter, UnityEngine::EventSystems::PointerEventData* pointerEventData);
    DECLARE_INSTANCE_METHOD(void, HandlePointerDidExit, UnityEngine::EventSystems::PointerEventData* pointerEventData);
    DECLARE_INSTANCE_METHOD(void, HandleJoystickWasNotCenteredThisFrame, UnityEngine::Vector2 deltaPos);

    DECLARE_INSTANCE_METHOD(void, SetDestinationPos, float value);

    DECLARE_INSTANCE_FIELD(UnityEngine::RectTransform*, contentTransform);
    DECLARE_INSTANCE_FIELD(float, destinationPos);

    DECLARE_INSTANCE_FIELD(GlobalNamespace::IVRPlatformHelper*, platformHelper);
    DECLARE_STATIC_FIELD(float, scrollSpeed);
)
