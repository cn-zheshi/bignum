#include <string>
#include <deque>
#include <cctype>
#include <iostream>
// Bignum by @cn-zheshi
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
	friend bignum operator-(const bignum& a);
	friend bignum operator*(const bignum& a,const bignum& b);
	std::deque<int> de1;
	std::deque<int> de2;
	bool sign=true;
public:
	bignum()=default;
	//template<typename T>bignum(T&& val)
	bignum(long double val)
	{
		std::string str=std::to_string(val);
		int count=0;
		if(!str.empty()) {
			if(!std::isalnum(str[0])) {
				if(str[0]=='-')
					sign=false;
				for(std::size_t i=1; i<str.size(); ++i) {
					if(!std::ispunct(str[i])&&count==0) {
						de1.push_front(p(str[i]));
					} else
						++count;
						if(count>1)
							de2.push_back(p(str[i]));
				}
			} else {
				for(std::size_t i=0; i<str.size(); ++i) {
					if(!std::ispunct(str[i])&&count==0) {
						de1.push_front(p(str[i]));
					} else
						++count;
						if(count>1)
							de2.push_back(p(str[i]));
				}
			}
		}
	}/*
	bignum(const std::string& str)
	{
		int count=0;
		if(!str.empty()) {
			if(!std::isdigit(str[0])) {
				if(str[0]=='-')
					sign=false;
				for(std::size_t i=1; i<str.size(); ++i) {
					if(!std::ispunct(str[i])&&count==0) {
						de1.push_front(p(str[i]));
					} else
						++count;
						if(count>1)
							de2.push_back(p(str[i]));
				}
			} else {
				for(std::size_t i=0; i<str.size(); ++i) {
					if(!std::ispunct(str[i])&&count==0) {
						de1.push_front(p(str[i]));
					} else
						++count;
						if(count>1)
							de2.push_back(p(str[i]));
				}
			}
		}
	}*/
	bignum(const bignum &ch)=default;
	~bignum()=default;
	bignum& operator=(const bignum&)=default;
	void print()
	{
		if(!(this->sign))
			std::cout<<"-";
		std::deque<int> a=(this->de2);
		int count=0;
		while(count==0&&!a.empty()){
			count=1;
			if(a[a.size()-1]==0){
				a.pop_back();
				--count;
			}
		}
		for(std::size_t i=(this->de1).size()-1; i>=0; --i){
			std::cout<<(this->de1)[i];
			if(i==0)
				break;
		}
		if(!(this->de1).empty()&&!a.empty())
			std::cout<<".";
		for(std::size_t v=0; v<a.size(); ++v)
			std::cout<<a[v];
		std::cout<<std::endl;
	}
};
bignum operator+(const bignum& a,const bignum& b)
{
	bignum c;
	if(((a.sign)&&(b.sign))||(!(a.sign)&&!(b.sign))) {
		if(!(a.sign)&&!(b.sign))
			c.sign=!(c.sign);
		std::size_t s=(a.de1).size()>(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
		std::size_t l=(a.de1).size()<(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
		for(std::size_t i=0; i<=l; ++i) {
			if(i<=s)
				(c.de1).push_back((a.de1)[i]+(b.de1)[i]);
			if(l==(a.de1).size()-1)
				if(i>s)
					(c.de1).push_back((a.de1)[i]);
			if(l==(b.de1).size()-1)
				if(i>s)
					(c.de1).push_back((b.de1)[i]);
		}
		for(std::size_t i=0; i<(b.de2).size(); ++i)
			(c.de2).push_back((a.de2)[i]+(b.de2)[i]);
		for(std::size_t i=(c.de2).size()-1; i>0; --i) {
			if(i!=0&&(c.de2)[i]>=10) {
				(c.de2)[i]-=10;
				++(c.de2)[i-1];
			}
			if((c.de2)[0]>=10) {
				(c.de2)[0]-=10;
				++(c.de1)[0];
			}
		}
		for(std::size_t i=0; i<(c.de1).size(); ++i) {
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
			std::size_t s=(a.de1).size()>(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
			std::size_t l=(a.de1).size()<(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
			for(std::size_t i=0; i<=l; ++i) {
			if(i<=s)
				(c.de1).push_back((a.de1)[i]-(b.de1)[i]);
			if(l==(a.de1).size()-1)
				if(i>s)
					(c.de1).push_back((a.de1)[i]);
			if(l==(b.de1).size()-1)
				if(i>s)
					(c.de1).push_back(-(b.de1)[i]);
			}
			int count=0;
			while(count==0&&(c.de1).size()>1){
				count=1;
				if((c.de1)[(c.de1).size()-1]==0){
					c.de1.pop_back();
					--count;
				}
			}
			s=(a.de2).size()>(b.de2).size()?(b.de2).size()-1:(a.de2).size()-1;
			l=(a.de2).size()<(b.de2).size()?(b.de2).size()-1:(a.de2).size()-1;
			for(std::size_t i=0; i<l; ++i){
				if(i<=s)
					(c.de2).push_back((a.de2)[i]-(b.de2)[i]);
				if(l==a.de2.size()-1)
					if(i>s)
						c.de2.push_back((a.de2)[i]);
				if(l==b.de2.size()-1)
					if(i>s)
						c.de2.push_back(-(b.de2)[i]);
			}
			if((c.de1)[(c.de1).size()-1]<0){
				c.sign=!(c.sign);
				for(std::size_t i=0; i<(b.de2).size(); ++i)
					(c.de2)[i]=-(c.de2)[i];
				for(std::size_t i=0; i<(c.de1).size(); ++i)
					(c.de1)[i]=-(c.de1)[i];
			}
			if(c.de1.size()==1&&(c.de1)[0]==0){
				for(std::size_t v=0;v<c.de2.size();++v)
					if((c.de2)[v]<0){
						c.sign=!(c.sign);
						for(std::size_t i=0; i<(b.de2).size(); ++i)
							(c.de2)[i]=-(c.de2)[i];
						for(std::size_t i=0; i<(c.de1).size(); ++i)
							(c.de1)[i]=-(c.de1)[i];
						break;
					}
			}
			for(std::size_t i=(c.de2).size()-1; i>0; --i) {
				if(i!=0&&(c.de2)[i]<0) {
					(c.de2)[i]+=10;
					--(c.de2)[i-1];
				}
				if((c.de2)[0]<0) {
					(c.de2)[0]+=10;
					--(c.de1)[0];
				}
			}
			for(std::size_t i=0; i<(c.de1).size(); ++i) {
				if((c.de1)[i]<0&&i!=(c.de1).size()-1) {
					(c.de1)[i]+=10;
					--(c.de1)[i+1];
				}
			}
			return c;
		}
		else{
			std::size_t s=(a.de1).size()>(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
			std::size_t l=(a.de1).size()<(b.de1).size()?(b.de1).size()-1:(a.de1).size()-1;
			for(std::size_t i=0; i<=l; ++i) {
			if(i<=s)
				(c.de1).push_back((b.de1)[i]-(a.de1)[i]);
			if(l==(a.de1).size()-1)
				if(i>s)
					(c.de1).push_back(-(a.de1)[i]);
			if(l==(b.de1).size()-1)
				if(i>s)
					(c.de1).push_back((b.de1)[i]);
			}
			int count=0;
			while(count==0&&(c.de1).size()>1){
				count=1;
				if((c.de1)[(c.de1).size()-1]==0){
					c.de1.pop_back();
					--count;
				}
			}
			s=(a.de2).size()>(b.de2).size()?(b.de2).size()-1:(a.de2).size()-1;
			l=(a.de2).size()<(b.de2).size()?(b.de2).size()-1:(a.de2).size()-1;
			for(std::size_t i=0; i<l; ++i){
				if(i<=s)
					(c.de2).push_back((b.de2)[i]-(a.de2)[i]);
				if(l==a.de2.size()-1)
					if(i>s)
						c.de2.push_back(-(a.de2)[i]);
				if(l==b.de2.size()-1)
					if(i>s)
						c.de2.push_back((b.de2)[i]);
			}
			if((c.de1)[(c.de1).size()-1]<0){
				c.sign=!(c.sign);
				for(std::size_t i=0; i<(b.de2).size(); ++i)
					(c.de2)[i]=-(c.de2)[i];
				for(std::size_t i=0; i<(c.de1).size(); ++i)
					(c.de1)[i]=-(c.de1)[i];
			}
			if(c.de1.size()==1&&(c.de1)[0]==0){
				for(std::size_t v=0;v<c.de2.size();++v)
					if((c.de2)[v]<0){
						c.sign=!(c.sign);
						for(std::size_t i=0; i<(b.de2).size(); ++i)
							(c.de2)[i]=-(c.de2)[i];
						for(std::size_t i=0; i<(c.de1).size(); ++i)
							(c.de1)[i]=-(c.de1)[i];
						break;
					}
			}
			for(std::size_t i=(c.de2).size()-1; i>0; --i) {
				if(i!=0&&(c.de2)[i]<0) {
					(c.de2)[i]+=10;
					--(c.de2)[i-1];
				}
				if((c.de2)[0]<0) {
					(c.de2)[0]+=10;
					--(c.de1)[0];
				}
			}
			for(std::size_t i=0; i<(c.de1).size(); ++i) {
				if((c.de1)[i]<0&&i!=(c.de1).size()-1) {
					(c.de1)[i]+=10;
					--(c.de1)[i+1];
				}
			}
			return c;
		}
	}
}
bignum operator-(const bignum& a){
	bignum c=a;
	c.sign=!(a.sign);
	return c;
}
bignum operator-(const bignum& a,const bignum& b){
	bignum c=-b;
	return a+c;
}
bignum operator*(const bignum& a,const bignum& b){
	bignum c;
	std::deque<int> x(a.de1.size()+b.de1.size(),0);
	c.de1=x;
	std::deque<int> y(a.de2.size()+b.de2.size(),0);
	c.de2=y;
	if(!((a.sign&&b.sign)||(!a.sign&&!b.sign)))
		c.sign=false;
	for(std::size_t i=0;i<a.de1.size();++i){
		for(std::size_t v=0;v<b.de1.size();++v){
			(c.de1)[i+v]+=((a.de1)[i])*((b.de1)[v]);
		}
	}
	for(std::size_t i=0;i<a.de2.size();++i){
		for(std::size_t v=0;v<b.de2.size();++v){
			(c.de2)[i+v+1]+=((a.de2)[i])*((b.de2)[v]);
		}
	}
	for(std::size_t i=0;i<a.de1.size();++i){
		for(std::size_t v=0;v<b.de2.size();++v){
			if(i>v)
				(c.de1)[i-v-1]+=((a.de1)[i])*((b.de2)[v]);
			else
				(c.de2)[v-i]+=((a.de1)[i])*((b.de2)[v]);
		}
	}
	for(std::size_t i=0;i<a.de2.size();++i){
		for(std::size_t v=0;v<b.de1.size();++v){
			if(i>=v)
				(c.de2)[i-v]+=((a.de2)[i])*((b.de1)[v]);
			else
				(c.de1)[v-i-1]+=((a.de2)[i])*((b.de1)[v]);
		}
	}
	int count=0;
	while(count==0&&(c.de1).size()>1){
		count=1;
		if((c.de1)[(c.de1).size()-1]==0){
			c.de1.pop_back();
			--count;
		}
	}
	count=1;
	while(count!=0){
		count=0;
		for(std::size_t i=(c.de2).size()-1; i>0; --i) {
			if(i!=0&&(c.de2)[i]>=10) {
				(c.de2)[i]-=10;
				++(c.de2)[i-1];
				++count;
			}
			if((c.de2)[0]>=10) {
				(c.de2)[0]-=10;
				++(c.de1)[0];
				++count;
			}
		}
		for(std::size_t i=0; i<(c.de1).size(); ++i) {
			if((c.de1)[i]>=10&&i!=(c.de1).size()-1) {
				(c.de1)[i]-=10;
				++(c.de1)[i+1];
				++count;
			}
			if((c.de1)[i]>=10&&i==(c.de1).size()-1) {
				(c.de1)[i]-=10;
				(c.de1).push_back(1);
				++count;
			}
		}
	}
	return c;
}/*
bignum operator""x(const char* p)
{
	return bignum(p);
}*/