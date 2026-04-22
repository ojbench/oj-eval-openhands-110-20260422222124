#include <bits/stdc++.h>
using namespace std;

static const int mdays_common[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

struct Date {
    int _year, _month, _day;

    static bool isLeap(int y){
        if(y%400==0) return true;
        if(y%100==0) return false;
        return y%4==0;
    }
    static int mdays(int y,int m){
        if(m==2) return mdays_common[2] + (isLeap(y)?1:0);
        return mdays_common[m];
    }
    static bool valid(int y,int m,int d){
        if(y<1900 || y>2030) return false;
        if(m<1 || m>12) return false;
        int md = mdays(y,m);
        if(d<1 || d>md) return false;
        return true;
    }

    Date(): _year(1900), _month(1), _day(1) {}
    Date(int y,int m,int d){
        if(valid(y,m,d)) { _year=y; _month=m; _day=d; }
        else { _year=1900; _month=1; _day=1; }
    }

    // convert to ordinal days since 1900-1-1 (day 0)
    static long long toOrdinal(const Date &dt){
        long long days=0;
        for(int y=1900;y<dt._year;++y){
            days += 365 + (isLeap(y)?1:0);
        }
        for(int m=1;m<dt._month;++m){
            days += mdays(dt._year,m);
        }
        days += dt._day - 1;
        return days;
    }
    static Date fromOrdinal(long long ord){
        // clamp within allowed range 1900-01-01 .. 2030-12-31
        long long minOrd = 0; // 1900-01-01
        // compute maxOrd for 2030-12-31
        Date tmp(2030,12,31);
        long long maxOrd = toOrdinal(tmp);
        if(ord<minOrd) ord=minOrd;
        if(ord>maxOrd) ord=maxOrd;
        int y=1900;
        while(true){
            long long ydays = 365 + (isLeap(y)?1:0);
            if(ord>=ydays){ ord-=ydays; ++y; }
            else break;
        }
        int m=1;
        while(true){
            int md = mdays(y,m);
            if(ord>=md){ ord-=md; ++m; }
            else break;
        }
        int d = (int)ord + 1;
        return Date(y,m,d);
    }

    // ++/-- and +,- with ints
    Date& operator++(){ // pre
        long long o = toOrdinal(*this);
        *this = fromOrdinal(o+1);
        return *this;
    }
    Date operator++(int){ // post
        Date old=*this;
        ++(*this);
        return old;
    }
    Date& operator--(){
        long long o = toOrdinal(*this);
        *this = fromOrdinal(o-1);
        return *this;
    }
    Date operator--(int){
        Date old=*this;
        --(*this);
        return old;
    }
    Date operator+(long long days) const{
        long long o = toOrdinal(*this);
        return fromOrdinal(o+days);
    }
    Date operator-(long long days) const{
        long long o = toOrdinal(*this);
        return fromOrdinal(o-days);
    }

    // date - date absolute difference
    long long operator-(const Date& other) const{
        long long a = toOrdinal(*this);
        long long b = toOrdinal(other);
        long long diff = a-b;
        if(diff<0) diff=-diff;
        return diff;
    }

    bool operator<(const Date& other) const{
        if(_year!=other._year) return _year<other._year;
        if(_month!=other._month) return _month<other._month;
        return _day<other._day;
    }
};

ostream& operator<<(ostream& os, const Date& d){
    os << d._year << '-' << d._month << '-' << d._day;
    return os;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int op; if(!(cin>>op)) return 0;
    int yy,mm,dd;
    if(op==1 || op==0){
        Date d0;
        Date d1(2000,2,29);
        Date d2(1900,2,29);
        cout<<d0<<"\n";
        cout<<d1<<"\n";
        cout<<d2<<"\n";
    }
    if(op==2 || op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        for(int i=0;i<5;++i) cout<<++d0<<"\n";
        for(int i=0;i<5;++i) cout<<d0++<<"\n";
        for(int i=0;i<5;++i) cout<<d0--<<"\n";
        for(int i=0;i<2;++i) cout<<--d0<<"\n";
        cout<<d0<<"\n";
    }
    if(op==3 || op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        cout<<(d0+100)<<"\n";
        cout<<(d0-1000)<<"\n";
    }
    if(op==4 || op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        Date d1(2020,12,21);
        cout<<(d0<d1)<<"\n";
    }
    if(op==5 || op==0){
        cin>>yy>>mm>>dd;
        Date d0(yy,mm,dd);
        Date d1(1912,6,23);
        cout<<(d0-d1)<<"\n";
    }
    return 0;
}
