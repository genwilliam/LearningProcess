def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        # 每轮将最大的数“冒泡”到末尾
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                # 交换相邻元素
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

# 数据
nums = [64, 34, 25, 12, 22, 11, 90]

print("排序前：", nums)

# 排序
sorted_nums = bubble_sort(nums.copy())

print("排序后：", sorted_nums)