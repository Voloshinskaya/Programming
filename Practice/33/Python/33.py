
def create(arr_size, arr_start = 0, arr_step = 0):
    return [i*arr_step + arr_start for i in range(arr_size)]

# метод сортировки вставками
def sort (arr):
    i = 1
    while i < len(arr):
        j=i
        while j > 0 and arr[j-1] > arr[j]:
            chg = arr[j - 1]
            arr[j - 1] = arr[j]
            arr[j] = chg
            j-= 1
        i+= 1
    return arr

_print = print
def print(arr):
    _print(arr)
    return arr

arr_size  = int(input())
arr_start = int(input())
arr_step  = int(input())
arr = create(arr_size, arr_start, arr_step)
arr = sort(arr)
print(arr)
