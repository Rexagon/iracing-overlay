#pragma once

#define IMPL_PROPERTY(type, prop, setProp, propChanged, member) \
    type prop() const                                           \
    {                                                           \
        return member;                                          \
    }                                                           \
    void setProp(type value)                                    \
    {                                                           \
        if (value == member) {                                  \
            return;                                             \
        }                                                       \
        member = value;                                         \
        emit propChanged();                                     \
    }
