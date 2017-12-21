#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("pas.ans","w",stdout);
	srand(time(0));
	int n=rand();
	cout<<(n^17)<<endl; 
	for(int i=1;i<n;i++){
		cout<<rand()<<' ';
	}
	cout<<(19260817^17)<<endl<<(2^17)<<endl;
	return 0;
}

