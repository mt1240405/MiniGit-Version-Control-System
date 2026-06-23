#pragma once

#include "Common.hpp"
#include "PointerIndexMap.hpp"

class FileVersion;

// ======================================================
// Binary Heap
// ======================================================

template <typename Comparator>
class BinaryHeap
{
private:
    vector<FileVersion *> heap;

    Comparator comparator;

    PointerIndexMap positionMap;

    void SwapNodes(
        int leftIndex,
        int rightIndex)
    {
        FileVersion *leftNode =
            heap[leftIndex];

        FileVersion *rightNode =
            heap[rightIndex];

        heap[leftIndex] = rightNode;
        heap[rightIndex] = leftNode;

        positionMap.Put(
            leftNode,
            rightIndex);

        positionMap.Put(
            rightNode,
            leftIndex);
    }

    void HeapifyUp(
        int index)
    {
        while (index > 0)
        {
            int parentIndex =
                (index - 1) / 2;

            if (!comparator(
                    heap[index],
                    heap[parentIndex]))
            {
                break;
            }

            SwapNodes(
                index,
                parentIndex);

            index = parentIndex;
        }
    }

    void HeapifyDown(
        int index)
    {
        int heapSize =
            static_cast<int>(heap.size());

        while (true)
        {
            int leftChild =
                2 * index + 1;

            int rightChild =
                2 * index + 2;

            int bestIndex =
                index;

            if (
                leftChild < heapSize &&
                comparator(
                    heap[leftChild],
                    heap[bestIndex]))
            {
                bestIndex = leftChild;
            }

            if (
                rightChild < heapSize &&
                comparator(
                    heap[rightChild],
                    heap[bestIndex]))
            {
                bestIndex = rightChild;
            }

            if (bestIndex == index)
            {
                break;
            }

            SwapNodes(
                index,
                bestIndex);

            index = bestIndex;
        }
    }

public:
    explicit BinaryHeap(
        int expectedSize = 1024)
        : positionMap(
              max(
                  16384,
                  expectedSize * 4))
    {
        heap.reserve(expectedSize);
    }

    void Push(
        FileVersion *file)
    {
        int index;

        if (
            positionMap.Get(
                file,
                index))
        {
            if (index < 0 || index > static_cast<int>(heap.size()))
                return;
            HeapifyUp(index);
            HeapifyDown(index);

            return;
        }

        heap.push_back(file);

        int newIndex =
            static_cast<int>(
                heap.size()) -
            1;

        positionMap.Put(
            file,
            newIndex);

        HeapifyUp(newIndex);
    }

    void Pop()
    {
        if (heap.empty())
        {
            return;
        }

        FileVersion *removed =
            heap[0];

        positionMap.Remove(
            removed);

        if (heap.size() == 1)
        {
            heap.pop_back();
            return;
        }

        heap[0] = heap.back();
        heap.pop_back();
        
        positionMap.Put(
            heap[0],
            0);

        HeapifyDown(0);
    }

    FileVersion *Top()
    {
        if (heap.empty())
        {
            return nullptr;
        }

        return heap[0];
    }

    bool Empty() const
    {
        return heap.empty();
    }

    int Size() const
    {
        return static_cast<int>(
            heap.size());
    }
};
