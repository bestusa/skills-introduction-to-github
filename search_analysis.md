# Search Algorithms: Step Counts, Pseudocode, and Complexity

## 1) Linear search steps for key 8 in `[2, 4, 6, 8, 10, 12, 13]`

Linear search checks elements from left to right:

1. Compare with 2 (not equal)
2. Compare with 4 (not equal)
3. Compare with 6 (not equal)
4. Compare with 8 (found)

**Answer: 4 steps.**

## 2) Binary search steps for key 8 in `[2, 4, 6, 8, 10, 12, 13]`

For 7 elements, the middle index is 3, whose value is 8.

1. Compare middle element 8 with key 8 (found)

**Answer: 1 step.**

## 3) Maximum binary-search steps for array size 100,000

The maximum number of iterations is:

- `ceil(log2(100000)) = 17`

(Equivalent common bound: `floor(log2(N)) + 1`, also 17 for `N = 100000`.)

**Answer: 17 steps (iterations).**

---

## 4) Theoretical explanation (Big-O) for linear vs binary search

- **Linear search:** in the worst case, it may inspect every element once.  
  So operations grow proportionally with `N`:
  - Worst case: `N` comparisons
  - Average case: about `N/2`
  - Complexity: **`O(N)`**

- **Binary search:** each comparison halves the remaining search interval.  
  After `k` steps, remaining size is about `N / 2^k`.  
  Stop when this becomes 1, so `2^k ≈ N`, hence `k ≈ log2(N)`.
  - Worst case: about `log2(N)` iterations
  - Complexity: **`O(log N)`**

For `N = 100000`, `log2(N)` is about 16.6, so at most about 17 iterations.

---

## 5) Randomized search pseudocode (without repetition)

Dataset: vector `A` of `N = 100000` distinct values.

```text
RANDOMIZED_SEARCH_NO_REPETITION(A, key):
    n <- length(A)
    indices <- [0, 1, 2, ..., n - 1]

    // Randomly permute indices (Fisher-Yates shuffle)
    for i <- n - 1 down to 1:
        j <- random integer in [0, i]
        swap(indices[i], indices[j])

    comparisons <- 0
    for t <- 0 to n - 1:
        idx <- indices[t]
        comparisons <- comparisons + 1
        if A[idx] == key:
            return (found = true, index = idx, comparisons = comparisons)

    return (found = false, index = -1, comparisons = comparisons)
```

### Complexity of randomized search (without repetition)

- **Best case:** key is first checked item: **`O(1)`**
- **Average case:** expected position is around middle of random order: **`O(N)`**
- **Worst case:** key is last checked (or absent): **`O(N)`**

Even with randomization, each element is examined at most once, so asymptotically it is linear.

---

## 6) Comparison: randomized vs linear vs binary

### Time complexity

- **Linear:** best `O(1)`, average `O(N)`, worst `O(N)`
- **Binary:** best `O(1)`, average/worst `O(log N)`
- **Randomized (no repetition):** best `O(1)`, average `O(N)`, worst `O(N)`

### Data requirements

- **Linear:** no ordering required
- **Binary:** requires sorted/random-access data
- **Randomized:** no ordering required

### Practical efficiency

- **Binary search** is usually fastest on large sorted arrays due to logarithmic growth.
- **Linear search** is simple and often fine for small arrays or one-off scans.
- **Randomized search** does not improve asymptotic complexity over linear search and adds randomization overhead (index permutation/shuffling).

### When to prefer each

- Prefer **binary search** when data is sorted (or can be maintained sorted) and frequent lookups are needed.
- Prefer **linear search** for very small data, quick prototypes, or unsorted collections when simplicity is most important.
- Prefer **randomized search** mainly in special contexts (for example, to avoid deterministic access patterns); it is usually not the most efficient default for standard lookup tasks.
