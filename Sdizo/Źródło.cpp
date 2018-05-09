#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>

using namespace std;

long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

struct list
{
	int value;
	list* next;
	list* back;
};

struct lista
{
	int size;
	list *head;
	list *tail;
};

void searchList(lista *A, int _value)
{
	list *Tmp = A->head;

	while (1)
	{
		if (Tmp->value == _value)
		{
			cout << "\nznalazlem\n";
		}
		else
		{
			if (Tmp->next == NULL)
			{
				cout << "\n nie znalazlem\n";
				return;
			}
			Tmp = Tmp->next;
		}
	}
}

void initLista(lista *List)
{
	List->head = NULL;
	List->tail = NULL;
	List->size = NULL;
}

void initList(list *listt)
{
	listt->value = NULL;
	listt->back = NULL;
	listt->next = NULL;
}

void addOnFrontList(lista *node, int _value)
{
	if (node->size == 0)
	{
		list *newNode = (struct list*) malloc(sizeof(list));
		initList(newNode);
		node->head = newNode;
		node->tail = newNode;
		newNode->value = _value;
		node->size++;
		return;
	}
	else
	{
		list *newNode = (struct list*) malloc(sizeof(list));
		initList(newNode);
		node->head->back = newNode;
		newNode->value = _value;
		newNode->next = node->head;
		node->head = newNode;
		node->size++;
		return;
	}
}

void addOnBackList(lista *node, int _value)
{
	if (node->size == 0)
	{
		list *newNode = (struct list*) malloc(sizeof(list));
		initList(newNode);
		node->head = newNode;
		node->tail = newNode;
		newNode->value = _value;
		node->size++;
		return;
	}
	else
	{
		list *newNode = (struct list*) malloc(sizeof(list));
		initList(newNode);
		node->tail->next = newNode;
		newNode->value = _value;
		newNode->back = node->tail;
		node->tail = newNode;
		node->size++;
		return;
	}
}

void addOnIndexList(lista *node, int _value, int place)
{
	list *Tmp = node->head;
	if (place == 0)
	{
		addOnFrontList(node, _value);
		return;
	}
	else if (place == node->size)
	{
		addOnBackList(node, _value);
		return;
	}
	else if (place < 0 || place >= node->size)
	{
		return;
	}
	else
	{
		list *newNode = (struct list*) malloc(sizeof(list));
		initList(newNode);
		for (int i = 0; i <= node->size; i++)
		{
			if (i + 1 == place)
			{
				list *C = Tmp->next;
				newNode->value = _value;
				//newNode->next = Tmp;
				//newNode->back = Tmp->back;
				//Tmp->back = newNode;
				//Tmp->back->next = newNode;
				newNode->next = C;
				newNode->back = Tmp;
				C->back = newNode;
				Tmp->next = newNode;
				node->size++;
				return;
			}
			else
			{
				Tmp = Tmp->next;
			}
		}
	}
}

void deleteOnFrontList(lista *node)
{
	if (node->size == 0)
	{
		return;
	}
	else if (node->size == 1)
	{
		initLista(node);
	}
	else
	{
		node->head = node->head->next;
		node->head->back = NULL;
		node->size--;
	}
}

void deleteOnBackList(lista *node)
{
	if (node->size == 0)
	{
		return;
	}
	else if (node->size == 1)
	{
		initLista(node);
	}
	else
	{
		node->tail = node->tail->back;
		node->tail->next = NULL;
		node->size--;
	}
}

void deleteOnIndexList(lista *node, int place)
{
	list *Tmp = node->head;
	if (place == 0)
	{
		deleteOnFrontList(node);
		return;
	}
	else if (place == node->size - 1)
	{
		deleteOnBackList(node);
		return;
	}
	else if (place < 0 || place >= node->size)
	{
		return;
	}
	else
	{
		for (int i = 0; i < node->size; i++)
		{
			if (i == place)
			{
				Tmp->back->next = Tmp->next;
				Tmp->next->back = Tmp->back;
			}
			else
			{
				Tmp = Tmp->next;
			}
		}
		node->size--;
	}
}

void showList(lista *node)
{
	if (node->size == 0)
	{
		std::cout << "\npusta lista\n";
		return;
	}
	list *Tmp = node->head;
	do
	{
		std::cout << Tmp->value;
		if (Tmp->next != NULL)
		{
			std::cout << "->";
		}
		Tmp = Tmp->next;
	} while (Tmp != NULL);
	std::cout << std::endl;
}

void openList(lista *node)
{
	ifstream In;
	In.open("Zapis.txt");
	int size;
	int Temp;
	In >> size;
	initLista(node);
	while (In)
	{
		In >> Temp;
		addOnBackList(node, Temp);
	}
	deleteOnBackList(node);
	if (node->size != size)
	{
		cout << "\n!!! ZLY ROZMIAR\n";
	}

	In.close();
}



struct Array
{
	int *data;
	int size;
};

void showArray(Array **Arr)
{
	if ((*Arr)->size == 0)
	{
		cout << "\nPusta tablica!\n";
		return;
	}
	cout << endl << " ";
	for (int i = 0; i<(*Arr)->size; i++)
	{
		cout << *(((*Arr)->data) + i) << " | ";
	}
	cout << endl;
}

void addOnFrontArray(Array **Arr, int val)
{
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size + 1) * sizeof((*Arr)->data));
	for (int i = (*Arr)->size; i >= 0; i--)
	{

		*(((*Arr)->data) + i + 1) = *(((*Arr)->data) + i);
	}
	(*(*Arr)->data) = val;
	(*Arr)->size++;
}

void addOnBackArray(Array **Arr, int val)
{
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size + 1) * sizeof((*Arr)->data));
	*(((*Arr)->data) + (*Arr)->size) = val;
	(*Arr)->size++;
}

void addOnIndexArray(Array **Arr, int index, int val)
{

	if (index > (*Arr)->size)
	{
		cout << "\nZly index!\n";
		return;
	}
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size + 1) * sizeof((*Arr)->data));
	for (int i = (*Arr)->size; i >= index; i--)
	{

		*(((*Arr)->data) + i + 1) = *(((*Arr)->data) + i);
	}
	*(((*Arr)->data) + index) = val;
	(*Arr)->size++;
}

void deleteOnFrontArray(Array **Arr)
{
	if ((*Arr)->size == 0)
	{
		return;
	}
	for (int i = 0; i < (*Arr)->size; i++)
	{
		*(((*Arr)->data) + i) = *(((*Arr)->data) + i + 1);
	}
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size - 1) * sizeof((*Arr)->data));
	(*Arr)->size--;
}

void deleteOnBackArray(Array **Arr)
{
	if ((*Arr)->size == 0)
	{
		return;
	}
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size - 1) * sizeof((*Arr)->data));
	(*Arr)->size--;
}

void deleteOnIndexArray(Array **Arr, int index)
{
	if ((*Arr)->size == 0)
	{
		return;
	}
	if (index > (*Arr)->size-1)
	{
		cout << "\nZly index!\n";
		return;
	}
	for (int i = index; i < (*Arr)->size; i++)
	{
		*(((*Arr)->data) + i) = *(((*Arr)->data) + i + 1);
	}
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size - 1) * sizeof((*Arr)->data));
	(*Arr)->size--;

}

void searchArray(Array **Arr, int val)
{
	bool found = false;
	if ((*Arr)->size == 0)
	{
		cout << "\nPusta tablica!\n";
		return;
	}
	cout << endl << " ";
	for (int i = 0; i<(*Arr)->size; i++)
	{
		if(val == *(((*Arr)->data) + i))
		{
			cout << "\nZnaleziono!\n";
			found = true;
		}
	}
	if (!found)
	{
		cout << "\nNie znaleziono!\n";
	}
}

void saveArray(Array **Arr)
{
	ofstream Out;
	Out.open("ZapisTablica.txt");
	if ((*Arr)->size == 0) 
	{
		Out << "Pusta!";
		return;
	}
	Out << (*Arr)->size << endl;
	for (int i = 0; i < (*Arr)->size; i++)
	{
		Out << *(((*Arr)->data) + i) << endl;
	}
	Out.close();
}

void openArray(Array **Arr)
{
	ifstream In;
	int i = 0;
	int temp = 0;
	In.open("ZapisTablica.txt");
	In >> temp;
	while (In)
	{
		In >> temp;
		addOnBackArray(Arr, temp);
	}
	In.close();
	deleteOnBackArray(Arr);
}

void randArray(Array **Arr, int index)
{
	for (int i = 0; i < index; i++)
	{
		int _Tmp = rand() % 100;
		addOnBackArray(Arr, _Tmp);
	}
}


struct binar
{
	int *Tab;
	int Size;
};

void showBinary(string sp, string sn, int v, binar *head)
{
	string cr, cl, cp;
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	string s;

	if (v < head->Size)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		showBinary(s + cp, cr, 2 * v + 2, head);

		s = s.substr(0, sp.length() - 2);

		cout << s << sn << head->Tab[v] << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		showBinary(s + cp, cl, 2 * v + 1, head);
	}
}

void reBuild(binar *head, int s)
{
	int pos = s - 1;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}
	pos = s;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}
	pos = s - 1;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}
	pos = s;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}
	pos = s - 2;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}
	pos = s;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}

}

void addToBinar(binar *head, int _Value)
{
	head->Tab = (int*)realloc(head->Tab, (head->Size + 1) * sizeof(int));
	head->Size++;
	head->Tab[head->Size - 1] = _Value;
	head->Tab[head->Size] = NULL;
	reBuild(head, head->Size);
}

void emptyBinar(binar *head)
{
	head->Size = 0;
	head->Tab = NULL;
}

void deleteBinaryIndex(binar *head, int index)
{
	if (head->Size == 0)
	{
		return;
	}
	for (int i = 0; i < head->Size; i++)
	{
		if (i == index)
		{
			for (int q = i; q < head->Size - 1; q++)
			{
				head->Tab[q] = head->Tab[q + 1];
			}
			break;
		}
	}
	head->Size--;
	head->Tab[head->Size] = NULL;
	reBuild(head, index);
}

void saveBinary(binar *head)
{
	ofstream Out;
	Out.open("ZapisBinary.txt");
	for (int i = 0; i < head->Size; i++)
	{
		Out << head->Tab[i] << endl;
	}
	Out.close();
}

void openBinary(binar *head)
{
	emptyBinar(head);
	ifstream In;
	In.open("ZapisBinary.txt");
	int Temp = 0;
	int count = 0;
	while (In)
	{
		In >> Temp;
		addToBinar(head, Temp);
		count++;
	}
	head->Size = count-1;
	In.close();
}

void searchBinary(binar *head, int val)
{

	for (int i = 0; i < head->Size; i++)
	{
		if (head->Tab[i] == val)
		{
			cout << "\nZnalaziono!\n";
			i = head->Size;
			return;
		}
	}
}

void randBinary(binar *head, int _Value)
{
	int _Tmp;
	head->Tab = (int*)realloc(head->Tab, (_Value) * sizeof(int));
	head->Size = _Value;
	for (int i = 0; i < _Value; i++)
	{
		_Tmp = rand() % 100;
		head->Tab[i] = _Tmp;
		reBuild(head, i);
	}
}

int main()
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	cout << "\n1. Lista\n2. Tablica\n3. Kopiec binarny\nWybieram:";
	int answer, N, I;

	cin>>answer;
	lista *B = (struct lista*) malloc(sizeof(lista));
	initLista(B);
	Array* tab;
	tab = (Array*)malloc(0 * sizeof(Array));
	tab->size = 0;
	tab->data = (int*)malloc(0 * sizeof(int));
	struct binar *A = (struct binar*) malloc(sizeof(struct binar));
	emptyBinar(A);

	switch (answer)
	{
	case 1:
		do
		{
			cout << "\n1. Wyswietl liste\n3. Dodaj element na poczatku listy\n4. Dodaj element na koncu listy\n5. Dodaj element do listy o indeksie\n";
			cout << "6. Usun element na poczatku listy\n7. Usun element na koncu listy\n8. Usun element listy o indeksie\n10. Otworz z pliku\n11. Szukaj w liscie\n12. Wyjscie\nWybieram:";
			cin>>answer;
			system("CLS");
			switch (answer)
			{
			

			case 1:
				system("CLS");
				start = read_QPC();
				showList(B);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 3:
				cout << "Podaj wartosc nowego elementu listy=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				addOnFrontList(B, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 4:
				cout << "Podaj wartosc nowego elementu listy=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				addOnBackList(B, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 5:
				cout << "Podaj wartosc nowego elementu listy=";
				cin >> N;
				cout << "\nPodaj wartosc indexu=";
				cin >> I;
				system("CLS");
				start = read_QPC();
				addOnIndexList(B, N, I);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 6:
				system("CLS");
				start = read_QPC();
				deleteOnFrontList(B);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 7:
				system("CLS");
				start = read_QPC();
				deleteOnBackList(B);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 8:
				cout << "\nPodaj wartosc indexu=";
				cin >> I;				
				system("CLS");
				start = read_QPC(); deleteOnIndexList(B, I);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;


			case 10:
				system("CLS");
				start = read_QPC();
				openList(B);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 11:
				cout << "\nPodaj wartosc szukanej=";
				cin >> I;
				system("CLS");
				start = read_QPC();
				searchList(B, I);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			default:
				cout << "\nZly wybor\n";
			}
		} while (answer!=12);
		break;

	case 2:
		
		do
		{
			cout << "\n1. Wyswietl Tablice\n2. Wygeneruj losowa Tablice o rozmiarze N\n3. Dodaj element na poczatku Tablicy\n4. Dodaj element na koncu Tablicy\n5. Dodaj element do Tablicy o indeksie\n";
			cout << "6. Usun element na poczatku Tablicy\n7. Usun element na koncu Tablicy\n8. Usun element Tablicy o indeksie\n9. Zapisz do pliku\n10. Otworz z pliku\n11. Szukaj w Tablicy\n12. Wyjscie\nWybieram:";
			cin >> answer;
			switch (answer)
			{
			case 2:
				tab = (Array*)malloc(0 * sizeof(Array));
				tab->size = 0;
				tab->data = (int*)malloc(0 * sizeof(int));
				cout << "Podaj rozmiar Tablicy N=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				randArray(&tab, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;
				system("pause");
				system("CLS");
				cin.get();
				break;

			case 1:
				system("CLS");
				start = read_QPC();
				showArray(&tab);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 3:
				cout << "Podaj wartosc nowego elementu Tablicy=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				addOnFrontArray(&tab, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 4:
				cout << "Podaj wartosc nowego elementu Tablicy=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				addOnBackArray(&tab, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 5:
				cout << "Podaj wartosc nowego elementu Tablicy=";
				cin >> N;
				cout << "\nPodaj wartosc indexu=";
				cin >> I;
				system("CLS");
				start = read_QPC();
				addOnIndexArray(&tab, I, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 6:
				system("CLS");
				start = read_QPC();
				deleteOnFrontArray(&tab);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 7:
				system("CLS");
				start = read_QPC();
				deleteOnBackArray(&tab);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 8:
				cout << "\nPodaj wartosc indexu=";
				cin >> I;
				system("CLS");
				start = read_QPC();
				deleteOnIndexArray(&tab, I);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 9:
				system("CLS");
				start = read_QPC();
				saveArray(&tab);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;


			case 10:
				system("CLS");
				start = read_QPC();
				openArray(&tab);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 11:
				cout << "\nPodaj wartosc szukanej=";
				cin >> I;
				system("CLS");
				start = read_QPC();
				searchArray(&tab, I);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			default:
				cout << "\nZly wybor\n";
			}
		} while (answer != 12);
		break;

	case 3:
		do
		{
			cout << "\n1. Pokaz kopiec\n";
			cout << "2. Dodaj do kopca\n";
			cout << "3. Usun z kopca\n";
			cout << "4. Zapisz\n";
			cout << "5. Otworz\n";
			cout << "6. Wyszukaj\n";
			cout << "7. Rand Binar\n";
			cout << "8. Wyjscie\nWybieram:";

			cin >> answer;
			switch (answer)
			{
			case 2:
				cout << "Podaj wartosc nowego elementu Kopca=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				addToBinar(A, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 1:
				system("CLS");
				start = read_QPC();
				showBinary("", "", 0, A);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 3:
				cout << "Podaj wartosc indeksu=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				deleteBinaryIndex(A, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 4:
				system("CLS");
				start = read_QPC();
				saveBinary(A);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 5:
				system("CLS");
				start = read_QPC();
				openBinary(A);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 6:
				cout << "Podaj szukana wartosc=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				searchBinary(A, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 7:
				cout << "Podaj rozmiar kopca N=";
				cin >> N;
				system("CLS");
				int _Tmp;
				start = read_QPC();
				/*emptyBinar(A);
				for (int i = 0; i < N; i++)
				{
					_Tmp = rand() % 100;
					addToBinar(A, _Tmp);
				}*/
				randBinary(A, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;
				system("pause");
				system("CLS");
				cin.get();
				break;
			default:
				cout << "\nZly wybor\n";
			}
		} while (answer != 8);
		break;

	default:
		cout << "Zly wybor\n";
	}





		




						
	/*struct binar *A = (struct binar*) malloc(sizeof(struct binar));
	emptyBinar(A);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, 6);
	addToBinar(A, rand() % 98);
	saveBinary(A);
	showBinary("", "", 0, A);
	openBinary(A);
	showBinary("", "", 0, A);
	searchBinary(A,6);
	addToBinar(A, 5);
	showBinary("", "", 0, A);*/


	/*Array* tab;
	tab = (Array*)malloc(0 * sizeof(Array));
	tab->size = 0;
	tab->data = (int*)malloc(0 * sizeof(int));
	showArray(&tab);
	addOnFrontArray(&tab, 1);
	addOnFrontArray(&tab, 4);
	addOnFrontArray(&tab, 7);
	addOnFrontArray(&tab, 8);
	addOnFrontArray(&tab, 4);
	showArray(&tab);
	addOnBackArray(&tab, 99);
	showArray(&tab);
	addOnIndexArray(&tab, 7, 21);
	showArray(&tab);
	deleteOnFrontArray(&tab);
	showArray(&tab);
	deleteOnBackArray(&tab);
	showArray(&tab);
	deleteOnIndexArray(&tab,1);
	showArray(&tab);
	searchArray(&tab, 0);
	saveArray(&tab);
	tab->data = (int*)malloc(0 * sizeof(int));
	tab->size = 0;
	showArray(&tab);
	openArray(&tab);
	showArray(&tab);
	tab->size = 0;
	tab->data = (int*)malloc(0 * sizeof(int));
	randArray(&tab, 10);
	showArray(&tab);*/






	//list *lista = (struct list*) malloc(sizeof(list));
	//lista->back = NULL;
	//lista->next = NULL;
	//lista->value = 9;
	//addOnBackList(lista, 99);
	//addOnFrontList(lista, 88);
	//randList(lista, 20);
	//showList(lista);




	cin.get();
	return 0;
}