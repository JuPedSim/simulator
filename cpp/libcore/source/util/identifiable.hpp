#pragma once

#include <atomic>

namespace jps
{
/// Identifiable provides identifier functionality for objects of derive classes.
/// For using just derive like: `class Pedestrian : public Identifiable<Pedestrian>`
/// The template parameter required for counting IDs separately.
/// Identifiable is thread safe.
template <typename IdentifiedType>
class Identifiable
{
    /// Static count for the next available unique identifier.
    inline static std::atomic<unsigned int> uid_counter{0};
    /// The actual unique identifier of the object
    unsigned int m_id{uid_counter++};

public:
    Identifiable() = default;

    /// Identified object should not be copied to avoid objects with same ID
    Identifiable(Identifiable const & /*p_other*/) = delete;
    auto operator=(Identifiable const & /*p_other*/) -> Identifiable & = delete;

    /// For moved objects the same UID is used.
    Identifiable(Identifiable && p_other) noexcept : m_id{p_other.m_id} {};
    auto operator=(Identifiable && p_other) noexcept -> Identifiable &
    {
        m_id = p_other.m_id;
        return *this;
    }


    auto getID() const noexcept -> unsigned int { return m_id; }
};
} // namespace jps
