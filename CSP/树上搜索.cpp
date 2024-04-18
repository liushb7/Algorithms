#include<bits/stdc++.h>
using namespace std;
struct node{
	int value;
	int parent;
	vector<int>child;
}a[2005],b[2005];

int n,m;
long long w[2005];

long long addsum(int i)//求节点i以及其后代节点的权重之和 
{
	long long ans=a[i].value;
	for(int j=0;j<a[i].child.size();j++)
	{
		ans+=addsum(a[i].child[j]);
	}
	return ans;
}

bool ischild(int i,int k)
{
	if(i==k)return true;
	for(int j=0;j<a[i].child.size();j++)
	{
		if(ischild(a[i].child[j],k))
		return true;
	}
	return false;
} 

void solve(int i,long long total)
{
	w[i]=abs(2*addsum(i)-total);
	for(int j=0;j<a[i].child.size();j++)
	{
	    solve(a[i].child[j],total);
	}
}

int find(int i)//找出i以及后代节点中w值 最小的节点编号，若两者w值相同选最小的 
{
	int minn=i;
	for(int j=0;j<a[i].child.size();j++)
	{
		int tmp=find(a[i].child[j]);
		if(w[tmp]<w[minn] ||((w[tmp]==w[minn])&&(minn>tmp)))
		{
			minn=tmp;
		}
	}
	return minn;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>b[i].value;
	}
	for(int i=2;i<=n;i++)
	{
		cin>>b[i].parent;
		b[b[i].parent].child.push_back(i);
	}
	int p,q;
	while(m--)
	{
		int root=1;
		cin>>q;
		memset(w,0,sizeof(w)); 
		for(int i=1;i<=n;i++)
		{
			a[i].value=b[i].value;
			if(i>1)a[i].parent=b[i].parent;
			a[i].child=b[i].child;
		}
		while(a[root].child.size()!=0)
		{
		long long total=addsum(root);
		
		//求差值最小的节点编号
		solve(root,total);
	    
		int tmp=find(root);
		cout<<tmp<<" ";
		if(ischild(tmp,q))//若q是tmp的节点及后代节点 以tmp作为根节点 
		{
			root=tmp;
		}
		else//移除tmp以及其后代节点 
		{
			int index=a[tmp].parent;
			for(int i=0;i<a[index].child.size();i++)
			{
				if(a[index].child[i]==tmp)
				{
					a[index].child.erase(a[index].child.begin()+i);
					break;
				}
			}
		}
		}
		cout<<endl;
	}
	return 0;
} 