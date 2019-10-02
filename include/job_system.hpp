#pragma once

#include "map.hpp"

#include <future>
#include <mutex>

namespace komunis
{
template <typename Key, typename Value>
struct job_system
{
    // Use forwarding if possible
    template <typename F, typename... Args>
    void add_job(const F &f, Args... args) noexcept {
        // Launch async task
        // Make sure its thread-safe access into the map
    };

    Value get_copy(const Key &p_key) const noexcept
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.get_copy(p_key);
    };

    const Value &read_only(const Key &p_key) const noexcept
    {
        std::lock_guard<std::mutex> lock(mutex);
        return data.get_copy(p_key);
    };

private:
    struct Job
    {
        // Jobber
    };
    std::mutex mutex;
    komunis::vector<Job> jobs;
    komunis::map<Key, Value> data;
};
}; // namespace komunis
