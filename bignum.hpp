#pragma once
#include <string>
#include <deque>
#include <cctype>
#include <ostream>
#include <stdexcept>
// Bignum by @cn-zheshi
namespace zheshi {
	class bignum {
		static int p(char);
		// Operators declaration
		friend std::ostream& operator<<(std::ostream&,const bignum&);
		friend const bignum operator+(const bignum&,const bignum&);
		friend const bignum operator-(const bignum&);
		friend const bignum operator*(const bignum&,const bignum&);
		friend const bignum operator/(const bignum&,const bignum&);
		friend const bignum operator-(const bignum&,const bignum&);
		friend bool operator==(const bignum& a,const bignum& b);
		friend bool operator>=(const bignum& a,const bignum& b);
		friend bool operator<(const bignum& a,const bignum& b);
		friend bool operator>(const bignum& a,const bignum& b);
		friend bool operator<=(const bignum& a,const bignum& b);
		friend bool operator!=(const bignum& a,const bignum& b);
		friend const bignum operator%(const bignum& a,const bignum& b);
		friend const bignum operator^(const bignum& a,const bignum& b);
		std::deque<int> de1;
		std::deque<int> de2;
		bool sign=true;
	public:
		bignum(const bignum&)=default;
		bignum(bignum&&) noexcept=default;
		~bignum()=default;
		explicit bignum(const std::string&);
		bignum(long double val):bignum(std::to_string(val)) {}
		bignum():bignum("0") {}
		bignum& operator=(const bignum&)=default;
	};
	bignum::bignum(const std::string& str)
	{
		int count=0;
		if(!str.empty()) {
			if(!std::isalnum(str[0])) {
				if(str[0]=='-')
					sign=false;
				for(std::size_t i=1; i<str.size(); ++i) {
					if(!std::ispunct(str[i])&&count==0) {
						de1.push_front(p(str[i]));
					}
					else {
						++count;
						if(count>1)
							de2.push_back(p(str[i]));
					}
				}
			}
			else {
				for(std::size_t i=0; i<str.size(); ++i) {
					if(!std::ispunct(str[i])&&count==0) {
						de1.push_front(p(str[i]));
					}
					else {
						++count;
						if(count>1)
							de2.push_back(p(str[i]));
					}
				}
			}
		}
		count=0;
		while(count==0&&!de2.empty()) {
			count=1;
			if(de2[de2.size()-1]==0) {
				de2.pop_back();
				--count;
			}
		}
	}
	int bignum::p(char a)
	{
		switch(a) {
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		}
	}
	std::ostream& operator<<(std::ostream& out,const bignum& a)
	{
		if(!(a.sign))
			out<<"-";
		for(auto it=a.de1.rbegin(); it!=a.de1.rend(); ++it)
			out<<*it;
		if(!a.de1.empty()&&!a.de2.empty())
			out<<".";
		if(!a.de2.empty())
			for(auto& it:a.de2)
				out<<it;
		return out;
	}
	const bignum operator+(const bignum& a,const bignum& b)
	{
		if(a.de1.empty()||b.de1.empty())
			throw std::logic_error("Error");
		if(b.de1.size()==1&&b.de1[0]==0&&b.de2.empty())
			return a;
		if(a.de1.size()==1&&a.de1[0]==0&&a.de2.empty())
			return b;
		bignum c;
		c.de1.clear();
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
			if(!(a.de2.empty()||b.de2.empty())) {
				l=(a.de2).size()<(b.de2).size()?(b.de2).size():(a.de2).size();
				std::deque<int> ls1=a.de2;
				std::deque<int> ls2=b.de2;
				while(ls2.size()<l+1) {
					ls2.push_back(0);
				}
				while(ls1.size()<l+1) {
					ls1.push_back(0);
				}
				for(std::size_t i=0; i<l; ++i) {
					(c.de2).push_back((ls2)[i]+(ls1)[i]);
				}
			}
			else {
				if(a.de2.empty()&&!b.de2.empty())
					for(std::size_t i=0; i<b.de2.size(); ++i) {
						c.de2.push_back(b.de2[i]);
					}
				if(b.de2.empty()&&!a.de2.empty())
					for(std::size_t i=0; i<a.de2.size(); ++i) {
						c.de2.push_back(a.de2[i]);
					}
				if(b.de2.empty()&&a.de2.empty())
					c.de2= {0};
			}
			for(std::size_t i=(c.de2).size()-1; i>0; --i) {
				if(i!=0&&(c.de2)[i]>=10) {
					(c.de2)[i]-=10;
					++(c.de2)[i-1];
				}
			}
			if(!c.de2.empty())
				while((c.de2)[0]>=10) {
					(c.de2)[0]-=10;
					++(c.de1)[0];
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
			int count=0;
			while(count==0&&!c.de2.empty()) {
				count=1;
				if((c.de2)[c.de2.size()-1]==0) {
					c.de2.pop_back();
					--count;
				}
			}
			return c;
		}
		else {
			if(a.sign) {
				if(b.de1.size()==1&&b.de1[0]==0&&b.de2.empty())
					return a;
				if(a.de1.size()==1&&a.de1[0]==0&&a.de2.empty())
					return b;
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
				while(count==0&&(c.de1).size()>1) {
					count=1;
					if((c.de1)[(c.de1).size()-1]==0) {
						c.de1.pop_back();
						--count;
					}
				}
				if(!(a.de2.empty()||b.de2.empty())) {
					l=(a.de2).size()<(b.de2).size()?(b.de2).size():(a.de2).size();
					std::deque<int> ls1=a.de2;
					std::deque<int> ls2=b.de2;
					while(ls2.size()<l+1) {
						ls2.push_back(0);
					}
					while(ls1.size()<l+1) {
						ls1.push_back(0);
					}
					for(std::size_t i=0; i<l; ++i) {
						(c.de2).push_back((ls1)[i]-(ls2)[i]);
					}
				}
				else {
					if(a.de2.empty()&&!b.de2.empty())
						for(std::size_t i=0; i<b.de2.size(); ++i) {
							c.de2.push_back(-b.de2[i]);
						}
					if(b.de2.empty()&&!a.de2.empty())
						for(std::size_t i=0; i<a.de2.size(); ++i) {
							c.de2.push_back(a.de2[i]);
						}
					if(b.de2.empty()&&a.de2.empty())
						c.de2= {0};
				}
				if((c.de1)[(c.de1).size()-1]<0) {
					c.sign=!(c.sign);
					for(std::size_t i=0; i<(b.de2).size(); ++i)
						(c.de2)[i]=-(c.de2)[i];
					for(std::size_t i=0; i<(c.de1).size(); ++i)
						(c.de1)[i]=-(c.de1)[i];
				}
				if(c.de1.size()==1&&(c.de1)[0]==0) {
					for(std::size_t v=0; v<c.de2.size(); ++v) {
						if((c.de2)[v]<0) {
							c.sign=!(c.sign);
							for(std::size_t i=0; i<(b.de2).size(); ++i)
								(c.de2)[i]=-(c.de2)[i];
							for(std::size_t i=0; i<(c.de1).size(); ++i)
								(c.de1)[i]=-(c.de1)[i];
							break;
						}
						else {
							if((c.de2)[v]>0)
								break;
						}
					}
				}
				for(std::size_t i=(c.de2).size()-1; i>0; --i) {
					if(i!=0&&(c.de2)[i]<0) {
						(c.de2)[i]+=10;
						--(c.de2)[i-1];
					}
				}
				while((c.de2)[0]<0) {
					(c.de2)[0]+=10;
					--(c.de1)[0];
				}
				for(std::size_t i=0; i<(c.de1).size(); ++i) {
					if((c.de1)[i]<0&&i!=(c.de1).size()-1) {
						(c.de1)[i]+=10;
						--(c.de1)[i+1];
					}
				}
				count=0;
				while(count==0&&!c.de2.empty()) {
					count=1;
					if((c.de2)[c.de2.size()-1]==0) {
						c.de2.pop_back();
						--count;
					}
				}
				return c;
			}
			else
				return b+a;
		}
	}
	const bignum operator-(const bignum& a)
	{
		if(a.de1.empty())
			throw std::logic_error("Error");
		bignum c=a;
		c.sign=!(a.sign);
		return c;
	}
	const bignum operator-(const bignum& a,const bignum& b)
	{
		if(a.de1.empty()||b.de1.empty())
			throw std::logic_error("Error");
		bignum c=-b;
		return a+c;
	}
	const bignum operator*(const bignum& a,const bignum& b)
	{
		if(a.de1.empty()||b.de1.empty())
			throw std::logic_error("Error");
		if((a.de1.size()==1&&a.de2.empty()&&(a.de1)[0]==0)||(b.de1.size()==1&&b.de2.empty()&&(b.de1)[0]==0))
			return 0;
		bignum c;
		c.de1.clear();
		if(a.de2.empty()&&b.de2.empty()) {
			bignum d;
			bignum e;
			c=0;
			if(a.sign)
				d=a;
			else
				d=-a;
			if(b.sign)
				e=b;
			else
				e=-b;
			while(e.sign&&!(e.de1.size()==1&&e.de1[0]==0)) {
				c=c+d;
				e=e-1;
			}
			if(!((a.sign&&b.sign)||(!a.sign&&!b.sign)))
				c.sign=!c.sign;
			return c;
		}
		std::deque<int> x(a.de1.size()+b.de1.size(),0);
		c.de1=x;
		std::deque<int> y(a.de2.size()+b.de2.size(),0);
		c.de2=y;
		if(!((a.sign&&b.sign)||(!a.sign&&!b.sign)))
			c.sign=false;
		for(std::size_t i=0; i<a.de1.size(); ++i) {
			for(std::size_t v=0; v<b.de1.size(); ++v) {
				(c.de1)[i+v]+=((a.de1)[i])*((b.de1)[v]);
			}
		}
		for(std::size_t i=0; i<a.de2.size(); ++i) {
			for(std::size_t v=0; v<b.de2.size(); ++v) {
				(c.de2)[i+v+1]+=((a.de2)[i])*((b.de2)[v]);
			}
		}
		for(std::size_t i=0; i<a.de1.size(); ++i) {
			for(std::size_t v=0; v<b.de2.size(); ++v) {
				if(i>v)
					(c.de1)[i-v-1]+=((a.de1)[i])*((b.de2)[v]);
				else
					(c.de2)[v-i]+=((a.de1)[i])*((b.de2)[v]);
			}
		}
		for(std::size_t i=0; i<a.de2.size(); ++i) {
			for(std::size_t v=0; v<b.de1.size(); ++v) {
				if(i>=v)
					(c.de2)[i-v]+=((a.de2)[i])*((b.de1)[v]);
				else
					(c.de1)[v-i-1]+=((a.de2)[i])*((b.de1)[v]);
			}
		}
		int count=0;
		while(count==0&&(c.de1).size()>1) {
			count=1;
			if((c.de1)[(c.de1).size()-1]==0) {
				c.de1.pop_back();
				--count;
			}
		}
		count=0;
		while(count==0&&!c.de2.empty()) {
			count=1;
			if((c.de2)[c.de2.size()-1]==0) {
				c.de2.pop_back();
				--count;
			}
		}
		count=1;
		while(count!=0) {
			count=0;
			for(std::size_t i=(c.de2).size()-1; i>0; --i) {
				if(i!=0&&(c.de2)[i]>=10) {
					(c.de2)[i]-=10;
					++(c.de2)[i-1];
					++count;
				}
			}
			if(!c.de2.empty())
				if((c.de2)[0]>=10) {
					(c.de2)[0]-=10;
					++(c.de1)[0];
					++count;
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
	}
	const bignum operator/(const bignum& a,const bignum& b)
	{
		if(a.de1.empty()||b.de1.empty())
			throw std::logic_error("Error");
		bignum c=0;
		bignum e;
		bignum f;
		bignum d=1;
		if(a.sign)
			e=a;
		else
			e=-a;
		if(b.sign)
			f=b;
		else
			f=-b;
		if(b.de1.size()==1&&b.de1[0]==0&&b.de2.empty())
			throw std::logic_error("Error");
		while(!(e-(f*d)).sign)
			d=0.1*d;
		while(((e-(f*d)).sign)) {
			e=e-(f*d);
			c=c+d;
			if((e-(f*d)).de1.size()==1&&(e-(f*d)).de1[0]==0&&(e-(f*d)).de2.empty()) {
				c=c+d;
				break;
			}
			if((!(e-(f*d)).sign)&&d.de2.size()<8)
				d=0.1*d;
		}
		if(!((a.sign&&b.sign)||(!a.sign&&!b.sign)))
			c.sign=!c.sign;
		return c;
	}
	bool operator==(const bignum& a,const bignum& b){
		if(((a.sign&&b.sign)||(!a.sign&&!b.sign))&&a.de1==b.de1&&a.de2==b.de2)
			return true;
		else
			return false;
	}
	bool operator>=(const bignum& a,const bignum& b){
		if((a-b).sign)
			return true;
		else
			return false;
	}
	bool operator<(const bignum& a,const bignum& b){
		if(!(a>=b))
			return true;
		else
			return false;
	}
	bool operator>(const bignum& a,const bignum& b){
		if(a>=b&&(!(a==b)))
			return true;
		else
			return false;
	}
	bool operator<=(const bignum& a,const bignum& b){
		if((!(a>=b))||a==b)
			return true;
		else
			return false;
	}
	bool operator!=(const bignum& a,const bignum& b){
		if(a==b)
			return false;
		else
			return true;
	}
	const bignum operator%(const bignum& a,const bignum& b){
		bignum c=a/b;
		if(!c.de2.empty())
			c.de2.clear();
		c=a-(b*c);
		return c;
	}
	const bignum operator^(const bignum& a,const bignum& b){
		if(a.de1.empty()||b.de1.empty())
			throw std::logic_error("Error");
		bignum c=b;
		bignum d=1;
		if(!c.de2.empty()){
			if(c.de2[0]<5)
				c.de2.clear();
			else{
				c.de2.clear();
				++c.de1[0];
			}
		}
		while(c>0){
			d=d*a;
			c=c-1;
		}
		return d;
	}
}
zheshi::bignum operator""_bignum(const char* p)
{
	return zheshi::bignum(p);
}