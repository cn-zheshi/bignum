#include <string>
#include <deque>
#include <cctype>
#include <iostream>
int p(char a)
{
	if(a=='0')
		return 0;
	if(a=='1')
		return 1;
	if(a=='2')
		return 2;
	if(a=='3')
		return 3;
	if(a=='4')
		return 4;
	if(a=='5')
		return 5;
	if(a=='6')
		return 6;
	if(a=='7')
		return 7;
	if(a=='8')
		return 8;
	if(a=='9')
		return 9;
}
class bignum {
	friend bignum operator+(const bignum&,const bignum&);
	std::deque<int> de1;
	std::deque<int> de2;
	bool sign=true;
	char point='.';
public:
	bignum()
	{
		point=' ';
	}
	//template<typename T>bignum(T&& val)
	bignum(long double val)
	{
		std::string str=std::to_string(val);
		int count=0;
		if(!str.empty()) {
			if(!std::isalnum(str[0])) {
				if(str[0]=='-')
					sign=false;
				for(int i=1; i<str.size(); ++i) {
					if(!std::ispunct(str[i])&&count==0) {
						de1.push_front(p(str[i]));
					} else
						++count;
					if(count>1)
						de2.push_back(p(str[i]));
				}
			} else {
				for(int i=0; i<str.size(); ++i) {
					if(!std::ispunct(str[i])&&count==0) {
						de1.push_front(p(str[i]));
					} else
						++count;
					if(count>1)
						de2.push_back(p(str[i]));
				}
			}
		}
	}
	bignum(const bignum &ch)=default;
	~bignum()=default;
	bignum& operator=(const bignum&)=default;
	void print()
	{
		if(!(this->sign))
			std::cout<<"-";
		int i=(this->de1).size()-1;
		for(; i>=0; --i)
			std::cout<<(this->de1)[i];
		std::cout<<(this->point);
		for(int v=0; v<(this->de2).size(); ++v)
			std::cout<<(this->de2)[v];
		std::cout<<std::endl;
	}
};
bignum operator+(const bignum& a,const bignum& b)
{
	bignum c;
	if(((a.sign)&&(b.sign))||(!(a.sign)&&!(b.sign))) {
		if(!(a.sign)&&!(b.sign))
			c.sign=!(c.sign);
		int s=(a.de1).size()>(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
		int l=(a.de1).size()<(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
		for(int i=0; i<=l; ++i) {
			if(i<=s)
				(c.de1).push_back((a.de1)[i]+(b.de1)[i]);
			if(l==(a.de1).size()-1)
				if(i>s)
					(c.de1).push_back((a.de1)[i]);
			if(l==(b.de1).size()-1)
				if(i>s)
					(c.de1).push_back((b.de1)[i]);
		}
		for(int i=0; i<(b.de2).size(); ++i)
			(c.de2).push_back((a.de2)[i]+(b.de2)[i]);
		for(int i=(c.de2).size()-1; i>0; --i) {
			if(i!=0&&(c.de2)[i]>=10) {
				(c.de2)[i]-=10;
				++(c.de2)[i-1];
			}
			if((c.de2)[0]>=10) {
				(c.de2)[0]-=10;
				++(c.de1)[0];
			}
		}
		for(int i=0; i<(c.de1).size(); ++i) {
			if((c.de1)[i]>=10&&i!=(c.de1).size()-1) {
				(c.de1)[i]-=10;
				++(c.de1)[i+1];
			}
			if((c.de1)[i]>=10&&i==(c.de1).size()-1) {
				(c.de1)[i]-=10;
				(c.de1).push_back(1);
			}
		}
		return c;
	}
	else{
		if(a.sign){
			int s=(a.de1).size()>(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
			int l=(a.de1).size()<(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
			for(int i=0; i<=l; ++i) {
			if(i<=s)
				(c.de1).push_back((a.de1)[i]-(b.de1)[i]);
			if(l==(a.de1).size()-1)
				if(i>s)
					(c.de1).push_back((a.de1)[i]);
			if(l==(b.de1).size()-1)
				if(i>s)
					(c.de1).push_back(-(b.de1)[i]);
			}
			for(int i=0; i<(b.de2).size(); ++i)
				(c.de2).push_back((a.de2)[i]-(b.de2)[i]);
			if((c.de1)[(c.de1).size()-1]<0){
				c.sign=!(c.sign);
				for(int i=0; i<(b.de2).size(); ++i)
					(c.de2)[i]=-(c.de2)[i];
				for(int i=0; i<(c.de1).size(); ++i)
					(c.de1)[i]=-(c.de1)[i];
			}
			for(int i=(c.de2).size()-1; i>0; --i) {
				if(i!=0&&(c.de2)[i]<0) {
					(c.de2)[i]+=10;
					--(c.de2)[i-1];
				}
				if((c.de2)[0]<0) {
					(c.de2)[0]+=10;
					--(c.de1)[0];
				}
			}
			for(int i=0; i<(c.de1).size(); ++i) {
				if((c.de1)[i]<0&&i!=(c.de1).size()-1) {
					(c.de1)[i]+=10;
					--(c.de1)[i+1];
				}
			}
			return c;
		}
		else{
			int s=(a.de1).size()>(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
			int l=(a.de1).size()<(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
			for(int i=0; i<=l; ++i) {
			if(i<=s)
				(c.de1).push_back((b.de1)[i]-(a.de1)[i]);
			if(l==(a.de1).size()-1)
				if(i>s)
					(c.de1).push_back(-(a.de1)[i]);
			if(l==(b.de1).size()-1)
				if(i>s)
					(c.de1).push_back((b.de1)[i]);
			}
			for(int i=0; i<(b.de2).size(); ++i)
				(c.de2).push_back((b.de2)[i]-(a.de2)[i]);
			if((c.de1)[(c.de1).size()-1]<0){
				c.sign=!(c.sign);
				for(int i=0; i<(b.de2).size(); ++i)
					(c.de2)[i]=-(c.de2)[i];
				for(int i=0; i<(c.de1).size(); ++i)
					(c.de1)[i]=-(c.de1)[i];
			}
			for(int i=(c.de2).size()-1; i>0; --i) {
				if(i!=0&&(c.de2)[i]<0) {
					(c.de2)[i]+=10;
					--(c.de2)[i-1];
				}
				if((c.de2)[0]<0) {
					(c.de2)[0]+=10;
					--(c.de1)[0];
				}
			}
			for(int i=0; i<(c.de1).size(); ++i) {
				if((c.de1)[i]<0&&i!=(c.de1).size()-1) {
					(c.de1)[i]+=10;
					--(c.de1)[i+1];
				}
			}
			return c;
		}
	}
}
int main()
{
	bignum a=7987.768;
	bignum b=-361376.56743;
	bignum c=a;
	a.print();
	b.print();
	c=(a+b);
	c.print();
	return 0;
}
