#include "main.h"

class imp_res : public Restaurant
{
public:
	int counter;
	int counterQueue;
	customer *first;
	customer *X;
	customer *firstQueue;
	customer *lastQueue;
	customer *firstHistory;
	customer *lastHistory;
	customer *tempfirstHistory;
	customer *templastHistory;
	customer *copyHis;

public:
	imp_res()
	{
		counter = 0;
		counterQueue = 0;
	};

	customer *removeFirstQueue()
	{
		customer *del = firstQueue;
		firstQueue = firstQueue->next;
		del->next = nullptr;
		counterQueue--;
		return del;
	}

	customer *removeFirstHistory()
	{
		customer *del = firstHistory;
		firstHistory = firstHistory->next;
		del->next = nullptr;
		return del;
	}

	customer *removeCOPYFirstHistory()
	{
		customer *del = copyHis;
		copyHis = copyHis->next;
		del->next = nullptr;
		return del;
	}

	customer *copylist(customer *cus, int num)
	{
		customer *current = cus;
		customer *copy = new customer(current->name, current->energy, current->next, NULL);
		customer *const head = copy;
		current = current->next;
		for (int i = 1; i < counter - num; i++)
		{
			copy = copy->next = new customer(current->name, current->energy, NULL, NULL);
			current = current->next;
		}
		while (current != NULL)
		{
			copy = copy->next = new customer(current->name, current->energy, NULL, NULL);
			// copy = copy->next;
			current = current->next;
		}
		return head;
	}

	customer *find_RES(customer *cus)
	{
		int RES = abs(first->energy - cus->energy);
		customer *a = first;
		customer *result = a;
		int index = 0;
		while (index < counter)
		{
			if (abs(a->energy - cus->energy) > RES)
			{
				RES = abs(a->energy - cus->energy);
				result = a;
			}
			a = a->next;
			index++;
		}
		return result;
	}

	int find_max()
	{
		int max = abs(firstQueue->energy);
		customer *indexCus = firstQueue;
		customer *result = firstQueue;
		int index = 0;
		while (index < counterQueue && indexCus != nullptr)
		{
			if (abs(indexCus->energy) > max)
			{
				result = indexCus;
				max = abs(indexCus->energy);
			}
			index++;
			indexCus = indexCus->next;
		}

		customer *checkcus = firstQueue;
		int index2 = 1;

		while (result->energy != checkcus->energy && result->name != checkcus->name)
		{
			index2++;
			checkcus = checkcus->next;
		}
		return index2;
	}

	int shellSort(int n)
	{
		int nswap = 0;

		for (int gap = n / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < n; i += 1)
			{
				customer *temp1 = movecus(i);
				int j = i;
				customer *temp2 = movecus(j);
				customer *temp3 = movecus(j - gap);
				for (j; j >= gap && temp3->energy > temp1->energy; j -= gap)
				{
					int entemp = temp2->energy;
					string strtemp = temp2->name;

					temp2->energy = temp3->energy;
					temp2->name = temp3->name;

					temp3->energy = entemp;
					temp3->name = strtemp;

					nswap++;

					temp2 = movecus(j);
					temp3 = movecus(j - gap);
				}

				int entemp = temp2->energy;
				string strtemp = temp2->name;

				temp2->energy = temp1->energy;
				temp2->name = temp1->name;

				temp1->energy = entemp;
				temp1->name = strtemp;

				nswap++;
			}
		}
		return nswap;
	}

	customer *movecus(int n)
	{
		int i = 0;
		customer *result = nullptr;
		customer *index = firstQueue;
		while (i < n && index->next != nullptr)
		{
			i++;
			index = index->next;
		}
		result = index;
		return result;
	}

	bool checkname(customer *cus)
	{
		customer *a = first;
		int index = 0;
		while (index < counter)
		{
			if (a->name == cus->name)
				return false;
			a = a->next;
			index++;
		}
		return true;
	}

	void logicRED(customer *cusInput)
	{
		customer *cus = new customer(cusInput->name, cusInput->energy, nullptr, nullptr);
		if (cus->energy == 0)
		{
			return;
		}
		else
		{
			if (counter == 0)
			{
				first = cus;
				counter++;
			}
			else
			{
				if (counter == 1)
				{
					if (!checkname(cus))
					{
						return;
					}
					else
					{
						first->next = cus;
						first->prev = cus;
						cus->next = first;
						cus->prev = first;
						counter++;
					}
				}
				else if (counter < MAXSIZE / 2)
				{
					if (!checkname(cus))
					{
						return;
					}
					else
					{
						if (cus->energy >= X->energy)
						{
							customer *N = X->next;
							X->next = cus;
							cus->prev = X;
							cus->next = N;
							N->prev = cus;
							X = X->next;
							counter++;
						}
						else
						{
							customer *N = X->prev;
							X->prev = cus;
							cus->next = X;
							cus->prev = N;
							N->next = cus;
							X = X->prev;
							counter++;
						}
					}
				}
				else if (counter < MAXSIZE)
				{
					if (!(checkname(cus)))
					{
						return;
					}
					else
					{
						X = find_RES(cus);
						int RES = cus->energy - X->energy;
						if (RES >= 0)
						{
							customer *N = X->next;
							X->next = cus;
							cus->prev = X;
							cus->next = N;
							N->prev = cus;
							X = X->next;
							counter++;
						}
						else
						{
							customer *N = X->prev;
							X->prev = cus;
							cus->next = X;
							cus->prev = N;
							N->next = cus;
							X = X->prev;
							counter++;
						}
					}
				}
				else if (counter == MAXSIZE && counterQueue == 0)
				{
					if (!checkname(cus))
					{
						return;
					}
					else
					{
						lastQueue = cus;
						firstQueue = cus;
						counterQueue = 1;
					}
				}
				else
				{
					if (!checkname(cus))
					{
						return;
					}
					else
					{
						if (counterQueue == MAXSIZE)
						{
							return;
						}
						else
						{
							lastQueue->next = cus;
							lastQueue = cus;
							counterQueue++;
						}
					}
				}
			}
		}
		customer *histemp = new customer(cusInput->name, cusInput->energy, nullptr, nullptr);
		if (counter == 1)
		{
			firstHistory = histemp;
			lastHistory = histemp;
		}
		else
		{
			lastHistory->next = histemp;
			lastHistory = histemp;
		}
		return;
	}

	void RED(string name, int energy)
	{
		// cout << name << " " << energy << endl;
		customer *cus = new customer(name, energy, nullptr, nullptr);
		logicRED(cus);
	}

	void BLUE(int num)
	{
		if (counter > 0)
		{
			if (num >= counter)
			{
				const int index = counterQueue;
				first = nullptr;
				counter = 0;
				if (counterQueue <= MAXSIZE)
				{
					for (int i = 0; i < index; i++)
					{
						customer *templ = removeFirstQueue();
						logicRED(templ);
					}
				}
			}
			else if (num < counter && counterQueue > 0)
			{
				const int index2 = counter;
				for (int i = 0; i < num; i++)
				{
					customer *del = removeFirstHistory();
					counter--;
					delete del;
				}
				first = nullptr;
				counter = 0;
				copyHis = copylist(firstHistory, index2 - num);
				firstHistory = nullptr;
				for (int j = 0; j < index2 - num; j++)
				{
					customer *templ = removeCOPYFirstHistory();
					logicRED(templ);
				}
				int inputCus_countineu = min(num, counterQueue);
				for (int k = 0; k < inputCus_countineu; k++)
				{
					customer *templ = removeFirstQueue();
					logicRED(templ);
				}
			}
			else
			{
				const int index2 = counter;
				for (int i = 0; i < num; i++)
				{
					customer *del = removeFirstHistory();
					counter--;
					delete del;
				}
				first = nullptr;
				counter = 0;
				copyHis = copylist(firstHistory, index2 - num);
				firstHistory = nullptr;
				for (int j = 0; j < index2 - num; j++)
				{
					customer *templ = removeCOPYFirstHistory();
					logicRED(templ);
				}
			}
		}
	}

	void PURPLE()
	{
		cout << "PURPLE" << endl;
		// int index = find_max();
		// shellSort(3);
	}

	void REVERSAL()
	{
		cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
	{
		cout << "light " << num << endl;
	}
	void SHOW()
	{
		cout << "--------------danh sach trong ban--------------" << endl;
		customer *a = first;
		int max = 1;
		while (max <= counter)
		{
			cout << a->name << " " << a->energy << endl;
			a = a->next;
			max++;
		}
		cout << "--------------danh sach trong queue-------------" << endl;
		customer *b = firstQueue;
		int mx = 1;
		while (b != nullptr)
		{
			cout << b->name << " " << b->energy << endl;
			b = b->next;
			mx++;
		}
		cout << "--------------danh sach trong history-------------" << endl;
		customer *c = firstHistory;
		int m = 1;
		while (c != nullptr)
		{
			cout << c->name << " " << c->energy << endl;
			c = c->next;
			m++;
		}
	}
};

// template <typename E, typename Comp>
// void inssort2(E A[], int n, int incr)
// {
// 	for (int i = incr; i < n; i += incr)
// 		for (int j = i; (j >= incr) &&
// 						(Comp::prior(A[j], A[j - incr]));
// 			 j -= incr)
// 			swap(A, j, j - incr);
// }
// template <typename E, typename Comp>
// void shellsort(E A[], int n)
// {									   // Shellsort
// 	for (int i = n / 2; i > 2; i /= 2) // For each increment
// 		for (int j = 0; j < i; j++)	   // Sort each sublist
// 			inssort2<E, Comp>(&A[j], n - j, i);
// 	inssort2<E, Comp>(A, n, 1);
// }
