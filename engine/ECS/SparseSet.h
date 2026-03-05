#pragma once

#include <vector>
#include <cstdint>
#include <utility>

namespace engine {

constexpr uint32_t INVALID_INDEX = UINT32_MAX;

template<typename T>
class SparseSet
{
public:
    void add(uint32_t entityIndex, T component) {
        if (entityIndex >= m_sparse.size()) {
            m_sparse.resize(entityIndex + 1, INVALID_INDEX);
        }

        m_sparse[entityIndex] = static_cast<uint32_t>(m_denseEntities.size()); // Assign sparse index to next denseEntity index
        m_denseEntities.push_back(entityIndex);
        m_denseData.push_back(std::move(component));
    }

    void remove(uint32_t entityIndex) {
        // Swap-and-pop remove
        if (!contains(entityIndex)) return;

        uint32_t denseIndex = m_sparse[entityIndex];       // Index of element to be removed / swapped with end
        uint32_t lastEntityIndex = m_denseEntities.back(); // Index of Entity pointed to by last element in dense

        m_denseEntities[denseIndex] = lastEntityIndex;
        m_denseData[denseIndex] = std::move(m_denseData.back());

        m_sparse[lastEntityIndex] = denseIndex; // Update swapped dense index in sparse
        m_sparse[entityIndex] = INVALID_INDEX;  // Invalidate removed entity

        m_denseEntities.pop_back();
        m_denseData.pop_back();
    }

    bool contains(uint32_t entityIndex) const {
        return entityIndex < m_sparse.size() && m_sparse[entityIndex] != INVALID_INDEX; 
    }

    T& get(uint32_t entityIndex)
    {
        return m_denseData[m_sparse[entityIndex]];
    }

    const T& get(uint32_t entityIndex) const
    {
        return m_denseData[m_sparse[entityIndex]];
    }

    void clear() {
        m_sparse.clear();       
        m_denseEntities.clear();
        m_denseData.clear();    
    }

    size_t size() const  { return m_denseData.size(); }
    std::vector<T>& data() { return m_denseData; }
    const std::vector<T>& data() const  { return m_denseData; }
    const std::vector<uint32_t>& entities() const { return m_denseEntities; }

private:
    std::vector<uint32_t> m_sparse;        // entityIndex -> denseIndex
    std::vector<uint32_t> m_denseEntities; // denseIndex -> entityIndex
    std::vector<T>        m_denseData;     // denseIndex -> component data
};

} // namespace engine