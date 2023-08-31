#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200001;

int n;
int segtree[4 * MAXN], a[MAXN];

void build(int l = 1, int r = n, int node = 1) {
    if (l == r) {
        segtree[node] = a[l];
        return;
    }
    
    int mid = (l + r) / 2;
    build(l, mid, node * 2);
    build(mid + 1, r, node * 2 + 1);
    segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
}

int queryupdate(int val, int idx, int l = 1, int r = n, int node = 1) {
    if (segtree[node] < val)
        return 0;

    if (l == r) {
        segtree[node] = 0;
        return l;
    }
    
    int mid = (l + r) / 2;
    int ocp = 0;
    
    if (segtree[node * 2] >= val)
        ocp = queryupdate(val, idx, l, mid, node * 2);
    
    if (ocp == 0 && segtree[node * 2 + 1] >= val)
        ocp = queryupdate(val, idx, mid + 1, r, node * 2 + 1);
    
    segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
    return ocp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q;
    cin >> n >> q;
    int arr[q];
    
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    
    build();
    
    while (q--) {
        int x;
        cin >> x;
        
        int ocp = queryupdate(x, 1);
        
        if (ocp > 0) {
            a[ocp] -= x;
            cout << ocp << " ";
        } else {
            cout << "- ";
        }
    }
    
    return 0;
}
