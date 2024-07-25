#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>


namespace string_my
{
	class string
	{
	public:
		typedef char* iterator;

		string()
			:_s(new char[1])
			,_capacity(1)
			,_size(0)
		{

		}

		string(const char* s1)
			:_s( new char[strlen(s1)+1])
			,_capacity(strlen(s1)+1)
			,_size(strlen(s1))
		{
			strcpy(_s, s1);
		}

		string(string& s1)
			:_s(new char[strlen(s1._s)+1])
			,_capacity(s1._capacity)
			,_size(s1._size)
		{
			strcpy(_s, s1._s);
		}

		iterator begin()
		{
			return _s;
		}

		iterator end()
		{
			return _s + _size;//刚好在\0得位置
		}

		void reserve(int size)
		{
			if (size > _capacity)
			{
				char* tmp = new char[size + 1];
				if (tmp == nullptr)
				{
					exit(-1);
				}
				strcpy(tmp, _s);
				delete[] _s;
				_s = tmp;
				_capacity = size;
			}	
		}

		int size()
		{
			return strlen(_s);
		}

		void resize(int n,char s1='\0')
		{
			if (n > _size)
			{
				if (n > _capacity)
				{
					reserve(n);
				}
				for (int i = _size; i <= _capacity; i++)
				{
					_s[i] = '\0';
				}
			}
			else if (n < _size)
			{
				std::cout << "不能比原本得size还小" << std::endl;
			}
		}
		
		void push_back(char a)//一个字符一个字符得加
		{
			*this += a;
		}

		void insert(iterator pos,const char* s1)
		{
			char tmp1 = *pos;
			reserve(_size + strlen(s1));
			pos = std::find(this->begin(), this->end(), tmp1);
			char* tmp = new char[_size - (pos - this->begin())+1];
			strcpy(tmp, pos);
			strcpy(pos, s1);
			strcpy(pos + strlen(s1), tmp);
			delete[] tmp;
			_size = this->size();
		}

		void erase(iterator pos)
		{
			char* tmp = new char[_size - (pos - this->begin())];
			strcpy(tmp, pos+1);
			strcpy(pos, tmp);
			_size--;
			delete[] tmp;

		}

		friend std::ostream& operator <<(std::ostream& cout, string& s1)
		{
			std::cout << s1._s << " " << s1._size <<" "<< s1._capacity;
			return std::cout;
		}

		string& operator = (string& s1)
		{
			reserve(s1._size);
			strcpy(_s, s1._s);
			_size = s1._size;
			_capacity = s1._capacity;
			return *this;
		}

		void operator+=(const char *s1)
		{
			reserve(_size + strlen(s1));
			iterator tmp = this->end();
			strcpy(tmp, s1);
			_size = strlen(_s);
		}

		void operator+=(const char s1)
		{
			reserve(_size+1);
			iterator tmp = this->end();
			*tmp = s1;
			*(tmp+1) = '\0';
			_size = strlen(_s);
		}

		~string()
		{
			delete[] _s;
			_s = nullptr;
			_size = 0;
			_capacity = 0;
		}
	
	private:
		char* _s;
		int _size;
		int _capacity;
	};
}