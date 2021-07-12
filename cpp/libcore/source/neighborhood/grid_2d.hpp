#pragma once

#include <cstddef>
#include <vector>

template <typename T>
class Grid2D
{
private:
    template <typename element_type>
    using container_type = std::vector<element_type>;

public:
    using size_type          = std::size_t;
    using value_type         = T;
    using row_type           = container_type<value_type>;
    using row_container_type = container_type<row_type>;

    Grid2D(size_type p_num_rows, size_type p_num_columns) :
        m_rows(p_num_rows, row_type(p_num_columns))
    {
    }

    Grid2D(const Grid2D &)     = default;
    Grid2D(Grid2D &&) noexcept = default;

    auto operator=(const Grid2D &) -> Grid2D & = default;
    auto operator=(Grid2D &&) noexcept -> Grid2D & = default;

    ~Grid2D() = default;

    auto operator[](size_type p_row) const -> row_type const & { return m_rows[p_row]; }
    auto operator[](size_type p_row) -> row_type & { return m_rows[p_row]; }

    void clear()
    {
        for(auto & row : m_rows) {
            for(auto & elem : row) {
                elem.clear();
            }
        }
    }

    auto numRows() const -> size_type { return m_rows.size(); }
    auto numColumns() const -> size_type
    {
        if(m_rows.empty()) {
            return 0;
        }
        return m_rows.front().size();
    }


private:
    row_container_type m_rows;
};
