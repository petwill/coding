/** template for query how many kinds of number between[a..b] in array[l..r] **/
//http://morris821028.github.io/2015/06/27/zj-b414/
//using  塊狀練表 
/** to do 
    off.init(n);
    for (int i = 1; i <= n; i++)
    off.A[i] = ??;
    for (int i = 0; i < m; i++) {
        off.q_add(l, r, a, b);
    }
    off.run();
    for (int i = 0; i < m; i++)
        printf("%d\n", off.ret[i]);
**/

const int MAXN = 500005; // max size of the array
const int MAXV = 500005; // max element of the array
const int MAXQ = 1000005;
const int MAXSQRTV = 512;
class Offline {
public:
    struct Event {
        static int PILE, belong[MAXV];
        int l, r, x, y, qid;
        Event(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0):
            l(a), r(b), x(c), y(d), qid(e) {}
        bool operator<(const Event &x) const {
            if (belong[l] != belong[x.l])
                return l < x.l;
            return r < x.r;
        }
    };
    int A[MAXN], N, qsize;
    Event event[MAXQ];
    int ret[MAXQ];
    void init(int N) {
        this->N = N, qsize = 0;
        memset(pile, 0, sizeof(pile));
        memset(val_count, 0, sizeof(val_count));
        val_PILE = Event::PILE = sqrt(N);
        for (int i = N; i >= 1; i--)
            val_belong[i] = Event::belong[i] = (i / Event::PILE );
    }
    void q_add(int l, int r, int a, int b) {
        event[qsize] = Event(l, r, a, b, qsize);
        qsize++;
    }
    void run() {
        sort(event, event+qsize);

        int l = 1, r = 0;
        for (int i = 0; i < qsize; i++) {
            while (r < event[i].r)	r++, update(A[r], 1);
            while (r > event[i].r)	update(A[r], -1), r--;
            while (l > event[i].l)	l--, update(A[l], 1);
            while (l < event[i].l)	update(A[l], -1), l++;
            ret[event[i].qid] = query(event[i].x, event[i].y);
        }
    }
private:
    // unrolled
    int pile[MAXSQRTV], val_count[MAXV], val_belong[MAXV], val_PILE;
    inline void update(int x, int val) {
        val_count[x] += val;
        if (val == -1 && val_count[x] == 0)
            pile[val_belong[x]]--;
        if (val == 1 && val_count[x] == 1)
            pile[val_belong[x]]++;
    }
    int query(int a, int b) {
        int ret = 0;
        if (val_belong[a] == val_belong[b]) {
            for (int i = a; i <= b; i++)
                ret += val_count[i] > 0;
            return ret;
        }
        for (int i = val_belong[a]+1; i < val_belong[b]; i++)
            ret += pile[i];
        for (int i = (val_belong[a]+1)*val_PILE-1; i >= a; i--)
            ret += val_count[i] > 0;
        for (int i = (val_belong[b])*val_PILE; i <= b; i++)
            ret += val_count[i] > 0;
        return ret;
    }
} off;
int Offline::Event::PILE = 16, Offline::Event::belong[MAXV];
/** end template **/
