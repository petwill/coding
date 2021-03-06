#include <bits/stdc++.h>
using namespace std;

struct Treap{
    Treap *l, *r;
    int pri, key, val;
    Treap(int _val, int _key):
        val(_val), key(_key), l(NULL), r(NULL), pri(rand()){}
};

/// We assure that key value in A treap is greater than that in treap B
Treap *merge( Treap *a, Treap *b){
    if(a==NULL || b==NULL) return (!a) ? b : a;
    if(a->pri > b->pri){
        a->r = merge(a->r, b);
        return a;
    }else{
        b->l = merge(a, b->l);
        return b;
    }
}
void split(Treap *t, int k, Treap *&a, Treap *&b){
    if( !t ) a = b = NULL;
    else if( t->key <= k){
        a = t;
        split(t->r, k, a->r, b);
    }else{
        b = t;
        split(t->l, k, a, b->l);
    }
}
Treap* insert( Treap *t, int k, int _val){
    Treap *tl, *tr;
    split(t, k, tl, tr);
    return merge(tl, merge(new Treap(_val, k) , tr));
}
Treap* remove( Treap* t, int k){
    Treap *tl, *tr;
    split(t, k-1, tl, t);
    split(t, k, t, tr);
    return merge(tl, tr);
}
int main(){

    return 0;
}
