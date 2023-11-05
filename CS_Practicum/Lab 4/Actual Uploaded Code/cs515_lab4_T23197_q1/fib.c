#include<stdio.h>
#include<time.h>
#include<stdlib.h>
long long c[55];
long long fib_rec(int n)
{
	if(n==0 || n==1)
		return n;
	else
		return (fib_rec(n-1) + fib_rec(n-2));
}

long long fib_dp_caching(int n)
{
	if(n==0 || n==1)
	{
		c[n]=n;
		return c[n];
	}
	else
	{
	if(c[n]==-1)
		c[n] = fib_dp_caching(n-1) + fib_dp_caching(n-2);	
	return c[n];
	}
}

long long fib_dp_nocaching(int n)
{
	long long f1, f2, f3;
	int i;
	if(n==0)
	{
		f1 = 0;
		return f1;
	}
	if(n==1)
	{
		f2 = 1;
		return f2;
	}
	f1 = 0;
	f2 = 1;
	for(i=2 ; i<=n ; i++)
	{
		f3 = f1 + f2;
		f1 = f2;
		f2 = f3;
	}
	return f3;
}

int main(int argc, char* argv[])
{
	long long ans, ans1, ans2;
	int i;
	for(i = 0; i<55; i++)
		c[i] = -1;
	clock_t start, end, start1, end1, start2, end2;
	double cpu_time, cpu_time1, cpu_time2;
	int n = atoi(argv[1]);
	
	start = clock();
	ans = fib_rec(n-1);
	end = clock();
	cpu_time = ((double)(end - start)/CLOCKS_PER_SEC);

	start1 = clock();
	ans1 = fib_dp_caching(n-1);
	end1 = clock();
	cpu_time1 = ((double)(end1 - start1)/CLOCKS_PER_SEC);
	
	start2 = clock();
	ans2 = fib_dp_nocaching(n-1);
	end2 = clock();
	cpu_time2 = ((double)(end2 - start2)/CLOCKS_PER_SEC);
	printf("%lli %f %f %f", ans, cpu_time, cpu_time1, cpu_time2);

	printf("\n");
}

