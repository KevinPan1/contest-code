#include <string.h>
#include <cstdio>
void answer(int S[], int D[]);
int tryCombination(int S[]);
int init();

int curr [5000] = { 0 }, corr [5000], last, current = 0, high, low, mid, cur, temp;
bool visited [5000] = { 0 }, flag = false;

void exploreCave(int N) {
    for (int i = 0; i < N; ++i) {
        high = N - 1;
        low = 0;
        last = tryCombination(curr);
        if (last == -1)
            break;
        while (low < high) {
            mid = low + (high - low) / 2;
            for (int j = low; j <= mid; ++j) {
                if (!visited[j])
                    curr[j] = !curr[j];
            }
            cur = tryCombination(curr);
            if (cur == -1) {
                flag = true;
                break;
            }
            if (((last == current) && (cur == current)) || ((last > current) && (cur > current)))
                low = mid + 1;
            else
                high = mid;
            last = cur;
        }
        if (flag)
            break;
        if (last > current) {
            corr[low] = current;
        } else {
            corr[low] = current;
            curr[low] = !curr[low];
        }
        current++;
        visited[low] = true;
    }
    for (int i = 0; i < N; ++i) {
        if (visited[i])
            continue;
        curr[i] = !curr[i];
        temp = tryCombination(curr);
        if (temp == -1)
            corr[i] = N - 1;
        else
            corr[i] = temp;
        curr[i] = !curr[i];
    }
    answer(curr, corr);
}
