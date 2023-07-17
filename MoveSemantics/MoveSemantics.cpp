#include <iostream>

class String
{
public:
	String() = default;
	String(const char* string)
	{
		printf("Created!\n");
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
	}
	// Ñopy constructor
	String(const String& other)
	{
		printf("Copied!\n");
		m_Size = other.m_Size;
		m_Data = new char[m_Size]; // allocate memory on the heap
		memcpy(m_Data, other.m_Data, m_Size);
	}
	// Move constructor
	String(String&& other) noexcept // for temporary object, for rvalue
	{
		printf("Moved!\n");
		m_Size = other.m_Size;
		m_Data = other.m_Data;
		other.m_Size = 0;
		other.m_Data = nullptr; // reconfigurate the pointer of old object
	}
	// Assignment operator
	String& operator=(String&& other) noexcept
	{
		printf("Moved!\n");
		if (this != &other)
		{
			delete[] m_Data;
			m_Size = other.m_Size;
			m_Data = other.m_Data;
			other.m_Size = 0;
			other.m_Data = nullptr; // reconfigurate the pointer of old object
		}
		return *this;
	}
	~String()
	{
		printf("Destroyed!\n");
		delete m_Data;
	}
	void Print()
	{
		for (uint32_t i = 0; i < m_Size; i++)
			printf("%c", m_Data[i]);
		printf("\n");
	}
private:
	char* m_Data;
	uint32_t m_Size;
};

class Entity
{
public:
	Entity(const String& name) // for lvalue
		: m_Name(name)         // initializer list
	{

	}
	Entity(String&& name) // for rvalue
	  //: m_Name((String&&)name)
		: m_Name(std::move(name))  // transform to rvalue
	{

	}
	void PrintName()
	{
		m_Name.Print();
	}
private:
	String m_Name;
};

int main()
{
	//Entity entity(String("Message"));
	//Entity entity("Message"); // Message is a temporary object, it's not assigned to anything (rvalue)
	//entity.PrintName();

	String apple = "Apple";
	String dest;
	//String dest = std::move(apple); // move constructor

	std::cout << "Apple: ";
	apple.Print();
	std::cout << "Dest: ";
	dest.Print();

	dest = std::move(apple);         // assignment operator
	                                 // std::move(...) convert an object (lvalue) to temporary object (rvalue)

	std::cout << "Apple: ";
	apple.Print();
	std::cout << "Dest: ";
	dest.Print();

	//String string = "Hello";
	//String dest = (String&&)string;
	//String dest((String&&)string);
	//String dest(std::move(string)); // moving this string into this destination
	//String dest = std::move(string);

	//dest = std::move(string);
	//dest = std::move(dest);
}