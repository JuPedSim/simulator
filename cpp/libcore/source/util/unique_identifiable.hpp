#pragma once

#include <atomic>

namespace jps
{
/// UniqueIdentifiable provides unique identifier functionality for objects of derive classes.
/// For using just derive like: `class Pedestrian : public UniqueIdentifiable<Pedestrian>`
/// The template parameter required for counting UIDs separately.
/// In this implementation unique refers to the object in memory of a derived class.
/// There must be no two different objects in memory with the same unique identifier.
/// UniqueIdentifiable is thread safe.
template <typename IdentifiedType>
class UniqueIdentifiable
{
    /// Static count for the next available unique identifier.
    inline static std::atomic<unsigned int> uid_counter{0};
    /// The actual unique identifier of the object
    unsigned int m_uid{uid_counter++};

public:
    UniqueIdentifiable() = default;

    /// A copy of a UniqueIdentifiable object should get a new UID
    UniqueIdentifiable(UniqueIdentifiable const & /*p_other*/) noexcept : m_uid{uid_counter++} {};
    UniqueIdentifiable & operator=(UniqueIdentifiable const & /*p_other*/) noexcept
    {
        m_uid = uid_counter++;
        return *this;
    }

    /// For moved objects the same UID is used.
    UniqueIdentifiable(UniqueIdentifiable && p_other) noexcept : m_uid{p_other.m_uid} {};
    UniqueIdentifiable & operator=(UniqueIdentifiable && p_other) noexcept
    {
        m_uid = p_other.m_uid;
        return *this;
    }


    unsigned int getUID() const noexcept { return m_uid; }
};
} // namespace jps
