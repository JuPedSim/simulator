#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

/// Grid2D Container for elements of type T
///
/// The Grid stores Elements of Type T in two dimensions in a hash map.
template <typename T>
class Grid2D
{
public:
    using index_type = std::int64_t;
    using value_type = T;

    class Grid2DRow
    {
        std::unordered_map<index_type, value_type> m_elements;

    public:
        auto operator[](index_type p_col) -> value_type & { return m_elements[p_col]; }
        auto get(index_type p_col) const -> value_type const &
        {
            auto it = m_elements.find(p_col);
            if(it != m_elements.end()) {
                return it->second;
            }
            return DUMMY_VALUE;
        }
    };

    Grid2D() = default;

    Grid2D(const Grid2D &)     = default;
    Grid2D(Grid2D &&) noexcept = default;

    auto operator=(const Grid2D &) -> Grid2D & = default;
    auto operator=(Grid2D &&) noexcept -> Grid2D & = default;

    ~Grid2D() = default;

    /// Returns the Grid2Row with index p_row
    ///
    /// If a Grid2DRow with index p_row does not exist, a new one is created.
    auto operator[](index_type p_row) -> Grid2DRow & { return m_rows[p_row]; }

    /// Returns a value_type const reference to the element at index p_row, p_col.
    ///
    /// If the element doesn't exist, the DUMMY_VALUE is returned.
    /// This can be used to iterate over empty grid cells in the neighborhood search.
    auto get(index_type p_row, index_type p_col) const -> value_type const &
    {
        auto it = m_rows.find(p_row);
        if(it != m_rows.end()) {
            return it->second.get(p_col);
        }
        return DUMMY_VALUE;
    }

    void clear() { m_rows.clear(); }

private:
    std::unordered_map<index_type, Grid2DRow> m_rows;
    inline static value_type const DUMMY_VALUE{};
};
