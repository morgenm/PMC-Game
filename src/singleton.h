/*
    Singleton
    This represents a Singleton container to contain other
    classes. Primarily used by the Engine abstraction base class.
*/

#pragma once

template<class T>
class Singleton {
public:
    T& Create();
private:
    T m_Single;
    bool m_IsSingleInit = false;
};

template<class T>
T& Singleton<T>::Create() {
    if(!m_IsSingleInit) {
        T single;
        m_Single = single;
        m_IsSingleInit = true;
    }

    return m_Single;
}
