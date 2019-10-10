#pragma once

template <typename T>
struct iterator
{
    iterator() = delete;
    iterator(
        const T *p_begin,
        const T *p_end)
        : begin(p_begin),
          end(p_end){};

private:
    const T *begin;
    const T *end;
};
