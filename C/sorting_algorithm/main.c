#include "sort.h"

#include <time.h>

#define TEST_SIZE 32768

#define USER_SIZE 100

typedef void (*sort_func_t)(item_t* arr, int n);

int order_cmp(const void* a, const void* b)
{
    return (*(item_t*)a) - (*(item_t*)b);
}

int reverse_cmp(const void* a, const void* b)
{
    return (*(item_t*)b) - (*(item_t*)a);
}

struct result
{
    double random_time;
    double order_time;
    double reverse_time;
    item_t* data;
};

static item_t random[TEST_SIZE], order[TEST_SIZE], reverse[TEST_SIZE];

void prepare_data()
{
    srand(time(NULL));
    for (int i = 0; i < TEST_SIZE; ++i)
    {
        random[i] = order[i] = reverse[i] = rand();
    }
    qsort(order, TEST_SIZE, sizeof(item_t), order_cmp);
    qsort(reverse, TEST_SIZE, sizeof(item_t), reverse_cmp);
}

struct result time_test(sort_func_t method)
{
    static item_t random_local[TEST_SIZE], order_local[TEST_SIZE], reverse_local[TEST_SIZE];
    // 生成数据
    for (int i = 0; i < TEST_SIZE; ++i)
    {
        random_local[i] = random[i];
        order_local[i] = order[i];
        reverse_local[i] = reverse[i];
    }

    clock_t start, end;
    struct result result;

    // 随机数据排序
    start = clock();
    method(random_local, TEST_SIZE);
    end = clock();
    result.random_time = (double)(end - start) / CLOCKS_PER_SEC;

    // 顺序数据排序
    start = clock();
    method(order_local, TEST_SIZE);
    end = clock();
    result.order_time = (double)(end - start) / CLOCKS_PER_SEC;

    // 逆序数据排序
    start = clock();
    method(reverse_local, TEST_SIZE);
    end = clock();
    result.reverse_time = (double)(end - start) / CLOCKS_PER_SEC;

    result.data = random_local;

    return result;
}

sort_func_t functions[] = {
    heap_sort, insertion_sort, merge_sort, quick_sort, radix_sort, selection_sort, shell_sort, bubble_sort};

const char* func_names[] = {
    "heap sort", "insertion sort", "merge sort", "quick sort", "radix sort", "selection sort", "shell sort", "bubble sort"};

void test_mode(void)
{
    printf("TEST_SIZE: %d\n", TEST_SIZE);
    printf("\t\trandom_time\torder_time\treverse_time\tdata\n");
    struct result result;

    prepare_data();
    for (int i = 0; i < sizeof(functions) / sizeof(sort_func_t); ++i)
    {
        result = time_test(functions[i]);
        printf("%s:\t%lfs\t%lfs\t%lfs\t", func_names[i], result.random_time, result.order_time, result.reverse_time);
        for (int i = 0; i < 10; i++)
        {
            printf("%d ", result.data[i]);
        }
        printf("...\n");
    }
    printf("Test finished.\n");
}

void user_mode(void)
{
    printf("Please select a sort algorithm:\n");
    for (int i = 0; i < sizeof(functions) / sizeof(sort_func_t); ++i)
    {
        printf("  %d: %s\n", i + 1, func_names[i]);
    }
    int ch;
    scanf("%d", &ch);
    sort_func_t func = functions[ch - 1];

    item_t arr[USER_SIZE];
    int n = 0;
    printf("Please input the integers (separated by spaces, no more than %d elements) and hit `Enter`:\n", USER_SIZE);
    while (n < USER_SIZE && scanf("%d", &arr[n]))
    {
        n++;
        if (getchar() == '\n')
        {
            break;
        }
    }

    func(arr, n);

    printf("\n");
    printf("The data after %sing is as follows:\n", func_names[ch - 1]);
    for (int i = 0; i < n; i++)
    {
        printf("%d : %d\n", i + 1, arr[i]);
    }
}

int main(void)
{
    printf("Please select:\n");
    printf("  1. Test mode. (default)\n");
    printf("  2. User mode.\n");

    char ch;
    scanf("%c", &ch);
    switch (ch)
    {
        case '1':
        case '\n':
            test_mode();
            break;
        case '2':
            user_mode();
            break;
        default:
            fprintf(stderr, "Invalid option.\n");
            break;
    }

    return 0;
}
