#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int value;
} stack_data;

int Permutations(int *data, stack_data *stack, int n, int *all_perm) {
    int k, j;
    for (j = 0; j < n; ++j) {
        data[j] = j + 1;
        stack[j].index = -1;
    }
    k = 0; //k代表跑到第幾層
    int x = 0;
    while (k >= 0) {
        if (k >= n) {
            for (j = 0; j < n; ++j) {
//                printf("%d ", stack[j].value + 1);
                all_perm[x] = stack[j].value + 1;
                x++;
            }
//            printf("\n");
            if (--k >= 0) //回到上一層，要將資料還原
                data[stack[k].index] = stack[k].value;
            continue;
        }
        for (j = stack[k].index + 1; j < n && data[j] < 0; ++j);
        if (j >= n) {
            if (--k >= 0) //回到上一層，要將資料還原
                data[stack[k].index] = stack[k].value;
            continue;
        }
        if (stack[k].index >= 0)
            data[stack[k].index] = stack[k].value;
        stack[k].index = j;
        stack[k].value = data[j];
        data[j] = -data[j]; //取負值代表被選過
        if (++k < n) //到下一層，index從頭開始
            stack[k].index = -1;
    }
    return x;
}

int get_Permutations_num(int *data, stack_data *stack, int n) {
    int k, j;
    for (j = 0; j < n; ++j) {
        data[j] = j + 1;
        stack[j].index = -1;
    }
    k = 0; //k代表跑到第幾層
    int x = 0;
    while (k >= 0) {
        if (k >= n) {
            for (j = 0; j < n; ++j) {
                x++;
            }
            if (--k >= 0) //回到上一層，要將資料還原
                data[stack[k].index] = stack[k].value;
            continue;
        }
        for (j = stack[k].index + 1; j < n && data[j] < 0; ++j);
        if (j >= n) {
            if (--k >= 0) //回到上一層，要將資料還原
                data[stack[k].index] = stack[k].value;
            continue;
        }
        if (stack[k].index >= 0)
            data[stack[k].index] = stack[k].value;
        stack[k].index = j;
        stack[k].value = data[j];
        data[j] = -data[j]; //取負值代表被選過
        if (++k < n) //到下一層，index從頭開始
            stack[k].index = -1;
    }
    return x;
}

int main() {
    int n;
    int *a;
    scanf(" %d", &n);
    int nn = n - 1;
    a = (int *) malloc((sizeof(int) + sizeof(stack_data)) * nn);
    int x = get_Permutations_num(a, (stack_data *) (a + nn), nn);
    int all_perm[100000] = {0};
    Permutations(a, (stack_data *) (a + nn), nn, all_perm);

//    printf("%d\n", x);
//    for (int i = 0; i < x; i++) {
//        printf("%d ", all_perm[i]);
//    }
//    printf("\n");

    int all_perm_2[x / nn][n];
    int row = 0;
    for (int i = 0; i < x; i++) {
        all_perm_2[row][0] = 1;
        int j = i % nn;
        all_perm_2[row][j + 1] = all_perm[i];
        if (j == nn - 1) {
            row++;
        }
    }
//
//    printf("------------------------\n");
//    for (int i = 0; i < x / nn; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%d ", all_perm_2[i][j]);
//        }
//        printf("\n");
//    }
//
    int distance_table[10][10] = {0};
    int temp;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                scanf("%d", &temp);
            } else {
                scanf("%d", &distance_table[i - 1][j - 1]);
            }
        }
    }
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%d ", distance_table[i][j]);
//        }
//        printf("\n");
//    }
//
    int distance_array[x / nn];
    for (int i = 0; i < x / nn; i++) {
        int distance = 0;
        for (int j = 0; j < n - 1; j++) {
            distance += distance_table[all_perm_2[i][j] - 1][all_perm_2[i][j + 1] - 1];
        }
        distance_array[i] = distance;
//        printf("%d\n", distance);
    }
    // find min
    int location = 0;
    for (int c = 1; c < x / nn; c++) {
        if (distance_array[c] < distance_array[location])
            location = c;
    }
    printf("%d\n", distance_array[location]);

    for (int i = 0; i < x / nn; i++) {
        int distance = 0;
        for (int j = 0; j < n - 1; j++) {
            distance += distance_table[all_perm_2[i][j] - 1][all_perm_2[i][j + 1] - 1];
        }
        if (distance == distance_array[location]) {
            for (int k = 0; k < n; k++) {
                if (k < n - 1) {
                    printf("%d->", all_perm_2[i][k]);
                } else {
                    printf("%d", all_perm_2[i][k]);
                }
            }
            printf("\n");
        }
    }
//    print_distance_table(distance_table, n);







//    free(a);
    return 0;
}