#include <iostream>
#include <ctime>
using namespace std;

bool isPrime(long long);
int pali(int, int);

//code to solve problem 2 from projecteuler.net
long problem2(){
	long num = 1, num2 = 2, evens = 2;
	while (true)
	{
		num = num2 + num;
		num2 = num + num2;
		
		if (num > 4000000 || num2 > 4000000) break;

		if (num%2 == 0) evens += num;
		if (num2%2 == 0) evens += num2;
	}
	return evens;
}

//code to solve problem 3 from projecteuler.net
long problem3()
{
	long long test = 1, num = 600851475143, max = 0;

	while (test < sqrt(num))
	{
		if (num%test == 0)
		{
			if (isPrime(test))
			{
				if (test > max) max = test;
			}
		}

		test++;
	}

	return max;
}

bool isPrime(long long num)
{
	for (long i = 2; i <= sqrt(num); i++)
	{
		if (num%i == 0)
			return false;
	}

	return true;
}

bool isPrime(long long primes[], long long size, long num)
{
	for (int i = 0; i < size && (primes[i] <= sqrt(num)); i++)
	{
		if (num%primes[i] == 0) return false;
	}

	return true;
}

//code to solve problem 4 from projecteuler.net
//I figured that because the largest number will be >= 900009, the two numbers must be greater than 901 and 909 OR 903 and 903, as the last digits multiplied must equal 9
//Factors of 9 are 1, 3, and 9, so I tested all pairs between 900 and 999 with last digits of 1 and 9 OR 3 and 3
long problem4()
{
	int result1 = pali(999, 991); //largest possible 9/1 pair
	int result2 = pali(991, 999); //largest possible 1/9 pair

	if (result1 != 0) return result1;
	else if (result2 != 0) return result2;
	else return pali(993, 993);  //largest possible 3/3 pair
}

int pali(int num1, int num2)
{
	int result;

	while (num2 > 900)
	{
		result = num1*num2;

		if (result/100000 == result%10)
			if (result/10000%10 == result%100/10)
				if (result/1000%100 == result%1000/100)
					return result;

		num2 -= 10;
	}

	return 0;
}

//code to solve problem 5 from projecteuler.net
//232792560 - have to add up the primes of every number that can't currently be made somehow by the numbers already in the stack we're going to end up multiplying together
long problem5()
{
	int num = 2;
	long total = 1;

	while (num < 20)
	{
		if (total%num != 0)
		{
			if (isPrime(num))
				total *= num;
			else
			{
				for (int i = 2; i <= sqrt(num); i++)
				{
					if (num%i == 0)
					{
						total *= i;
						break;
					}
				}
			}
		}
		num++;
	}

	return total;
}

//code to solve problem 6 from projecteuler.net
long problem6()
{
	int sum = 0, ssum = 0;

	for (int i = 1; i <= 100; i++)
	{
		ssum += i;
		sum += i*i;
	}

	return ssum*ssum - sum;
}

//code to solve problem 7 from projecteuler.net
long problem7()
{
	long long * primes = new long long [200000];
   
    primes[0] = 2;
    primes[1] = 3;
   
    long num = 5;
   
    for (long i = 2; primes[i-1] < 2000000; i++)
    {
        while (!isPrime(primes, 200000, num))
        {
            num += 2;
        }
       
        primes[i] = num;
        num += 2;
    }
   
	long long datNum = primes[10000];
	delete primes;
    return datNum;
}

//code to solve problem 10 from projecteuler.net
long long problem10()
{
	long long * primes = new long long [200000];
   
    primes[0] = 2;
    primes[1] = 3;
   
    long long total = 0, num = 5;
   
    for (long i = 2; primes[i-1] < 2000000; i++)
    {
        while (!isPrime(primes, 200000, num))
        {
            num += 2;
        }
       
        primes[i] = num;
        num += 2;
    }
   
    for (long i = 0; primes[i] < 2000000; i++)
        total += primes[i];
   
	delete primes;
    return total;
}

struct Item{
	int weight;
	int value;
	int quantity;

	Item(int w, int v, int q){
		weight=w;
		value=v;
		quantity=q;
	}
};

//the regular knapsack problem, with one knapsack, and assuming there is only one of each item
int fillKnapsackRegular(Item items[], int numItems, int remainingCapacity, int curItem){
	if(curItem>numItems)
		return 0;
	int includedValue=0, notIncludedValue=0;

	if(items[curItem].weight <= remainingCapacity) //if it fits
		includedValue = items[curItem].value + fillKnapsackRegular(items, numItems, remainingCapacity-items[curItem].weight, curItem+1); //put it in
	notIncludedValue = 0 + fillKnapsackRegular(items, numItems, remainingCapacity, curItem+1); //don't put it in

	return max(includedValue, notIncludedValue);
}

//adapt the knapsack problem to work with two knapsacks
//you will have to try putting each item in knapsack 1, knapsack 2, or neither
int fillTwoKnapsacks(Item items[], int numItems, int rcap1, int rcap2, int curItem)
{
	if(curItem>numItems)
		return 0;
	int includedValue1 = 0, includedValue2 = 0, notInc1 = 0, notInc2 = 0;

	if (items[curItem].weight <= rcap1) //if it fits
		includedValue1 = items[curItem].value + fillTwoKnapsacks(items, numItems, rcap1-items[curItem].weight, rcap2, curItem+1); //put it in
	else if (items[curItem].weight <= rcap2)
		includedValue1 = items[curItem].value + fillTwoKnapsacks(items, numItems, rcap1, rcap2-items[curItem].weight, curItem+1);
	notInc1 = 0 + fillTwoKnapsacks(items, numItems, rcap1, rcap2, curItem+1);
	
	
	if (items[curItem].weight <= rcap2) //if it fits
		includedValue2 = items[curItem].value + fillTwoKnapsacks(items, numItems, rcap1, rcap2-items[curItem].weight, curItem+1);
	else if (items[curItem].weight <= rcap1)
		includedValue2 = items[curItem].value + fillTwoKnapsacks(items, numItems, rcap1-items[curItem].weight, rcap2, curItem+1); //put it in
	notInc2 = 0 + fillTwoKnapsacks(items, numItems, rcap1, rcap2, curItem+1);

	return max(notInc2, max(includedValue2, max(includedValue1, notInc1)));
}

//adapt the knapsack problem to work with a quantity
//you will have to try including none, 1, 2, 3, … quantity of the items and choose the best
int fillKnapsackQty(Item items[], int numItems, int capacity, int curItem)
{
	if (curItem > numItems || capacity == 0) return 0;

	int inc = 0, notInc = 0;

	if (items[curItem].quantity == 0) curItem++;

	if (items[curItem].quantity-- > 0)
	{
		if (items[curItem].weight <= capacity)
			inc = items[curItem].value + fillKnapsackQty(items, numItems, capacity-items[curItem].weight, curItem);
		
		notInc = 0 + fillKnapsackQty(items, numItems, capacity, curItem);
	}

	return max(inc, notInc);
}

int main(){

	clock_t begin, end;
	long timeSpent;
	long long returnValue;

	cout<<"\n\n---------Part 1---------\n";

	for(int i=2; i<=7; i++){
		begin=clock();
		if(i==2)
			returnValue=problem2();
		if(i==3)
			returnValue=problem3();
		if(i==4)
			returnValue=problem4();
		if(i==5)
			returnValue=problem5();
		if(i==6)
			returnValue=problem6();
		if(i==7)
			returnValue=problem7();
		end=clock();
		timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
		cout<<"Problem "<<i<<" returned "<<returnValue<<" and took "<<timeSpent<<" seconds.\n";
	}

	begin=clock();
	returnValue=problem10();
	end=clock();
	timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout<<"Problem 10 returned "<<returnValue<<" and took "<<timeSpent<<" seconds.\n";


	cout<<"\n\n---------Part 2---------\n";

	Item items[6]={Item(20, 1000000, 3), Item(30, 1200000, 2), Item(10, 250000, 1), Item(1, 22400, 5), Item(2, 20000, 4), Item(1, 384, 50)};
	
	cout<<"Regular: with a 40 lb knapsack\n";
	cout<<"\tThe most money that we can make off with is $"<<fillKnapsackRegular(items, 6, 40, 0)<<endl;
	
	cout<<"Two Knapsacks: with a 30 lb knapsack and a 25 lb knapsack\n";
	cout<<"\tThe most money that we can make off with is $"<<fillTwoKnapsacks(items, 6, 30, 25, 0)<<endl;

	cout<<"Qty Knapsack: considering quantity and given a 40 lb knapsack\n";
	cout<<"\tThe most money that we can make off with is $"<<fillKnapsackQty(items, 6, 40, 0)<<endl;

	cout<<endl<<endl;
	return 0;
}