
#include <iostream>
#define FACTOR 2
#define MIN_SIZE 2
template<typename T>
class Dynamic_Array
{
public:
	size_t size;
	size_t capacity;
	T*array;
	Dynamic_Array()
	{

		size = 0;
		capacity = MIN_SIZE;
		array = new T[capacity];
	}

	~Dynamic_Array()
	{
		for (int i = 0; i < size; i++)
		{
			this->array[i] = this->array[i + 1];
			delete array[i];
		}
		delete array;

		size = 0;
		capacity = MIN_SIZE;
	}
	int get_size()
	{
		return this->size;
	}
	void resize()
	{
		capacity = capacity * FACTOR;
		T *temp = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			temp[i] = this->array[i];
		}
		delete [] this->array;
		this->array = temp;
		
	}
	void add_element(T data)
	{
		if (size >= capacity)
		{
			resize();
		}
		size++;
		array[size - 1] = data;

	}
	T get(int index)
	{
		return array[index];
	}
	void replace_data(int index, T data)
	{
		this->array[index] = data;
	}
	void clear()
	{
		size = 0;
		delete[] array;
		capacity = MIN_SIZE;
		array = new T[capacity];
	}
	void display_array()
	{
		std::cout << "Rozmiar tablicy: " << size << " elementow\nMaksymalna pojemnosc: " << capacity << "\n";
		for (int i = 0; i < size; i++)
		{
			std::cout <<"Index: " <<i<<" "<<this->get(i) << "\n";
		}
	}
	void delete_first_element()
	{
		array[0] = array[size - 1];
		array[size - 1] = T();
		size--;
	}
	bool compare(int index1, int index2)
	{
		if (this->array[index1] < this->array[index2])
		{
			return true;
		}
		else
			return false;
	}
	
	
};
template<typename T>
class Binary_Heap
{	
	Dynamic_Array<T> *array;
public:
	Binary_Heap()
	{
		array = new Dynamic_Array<T>();
	}
	int get_parent_index(int index)
	{
		int parent_index = (index - 1) / 2;
		return parent_index;
	}
	int get_left_child_index(int index)
	{
		int left_child_index = (2 * index) + 1;
		return left_child_index;
	}
	int get_right_child_index(int index)
	{
		int right_child_index = (2 * index) + 2;
		return right_child_index;
	}
	void fix_heap_max_up(int index)
	{
		int parent_index;
		T tmp;

		if(index != 0) 
		{
			parent_index = get_parent_index(index);
			if (array->compare(parent_index,index) )
			{
				tmp = array->get(parent_index);
				array->replace_data(parent_index, array->get(index));
				array->replace_data(index, tmp);
				fix_heap_max_up(parent_index);
			}
		}
	}
	
	void fix_heap_max_down(int index)
	{
		int left_child_index;
		int right_child_index;
		T temp;
		if (index != array->get_size())
		{
			left_child_index = get_left_child_index(index);
			right_child_index = get_right_child_index(index);
			bool check_child = array->compare(left_child_index, right_child_index);
			if (check_child == true)
			{
				if (array->compare(index, right_child_index))
				{
					temp = array->get(index);
					array->replace_data(index, array->get(right_child_index));
					array->replace_data(right_child_index, temp);
					fix_heap_max_down(index);
				}
			}
			else
			{
				if (array->compare(index, left_child_index))
				{
					temp = array->get(index);
					array->replace_data(index, array->get(left_child_index));
					array->replace_data(left_child_index, temp);
					fix_heap_max_down(index);
				}
			}
			
		}
	}
	void delete_root()
	{
		array->delete_first_element();
		fix_heap_max_down(0);
	}
	
	void display()
	{
		array->display_array();
	}
	void insert(T data)
	{
		array->add_element(data);
		int index = array->get_size() - 1;
		fix_heap_max_up(index);
	}
	void clear()
	{
		array->clear();
		array = new Dynamic_Array<T>();

	}
};
int main()
{
	Binary_Heap <int>* bh= new Binary_Heap<int>();
	int tab [10]= { 8,2,13,111,86,14,33,63,11,68};
	for (int i = 0; i < 10; i++)
	{
		bh->insert(tab[i]);
	}
	bh->display();
	bh->delete_root();
	bh->display();
	bh->insert(130);
	bh->display();
	bh->clear();
	bh->insert(tab[5]);
	bh->display();
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
