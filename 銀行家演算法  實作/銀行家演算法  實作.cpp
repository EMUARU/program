#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#define S1 STRING1.str(""); STRING1.clear(); STRING1 << str;
#define S2 STRING2.str(""); STRING2.clear(); STRING2 << str;
#define cout std::cout
#define rq cout << '('; for (auto it(req.begin()); it != req.end(); it++) {cout << *it; if (it != --req.end()) cout << ',';}
#define sfq for (auto it(safeSeq.begin()); it != safeSeq.end(); it++) {cout << *it; if (it != --safeSeq.end()) cout << ',';}
#define wk for (auto it(work.begin()); it != work.end(); it++) {cout << *it; if (it != --work.end()) cout << ',';}

using namespace std;

vector< int > available, s_available, safeSeq, work, finish, del;
map< int, vector< int > > max, allocation, need, s_allocation, s_need;
vector< vector< int > > request, requeue;

pair< bool, bool > valid(vector< int > req)
{
	int g(req[0]), n(1), a(1);
	for (int i(1); i <= 5; i++)
	{
		if (req[i] > need[g][i - 1])
			n = 0;
		if (req[i] > available[i - 1])
			a = 0;
	}
	return make_pair(n, a);
}

bool safety(vector< int > req, bool ini)
{
	safeSeq.clear();
	s_available = available;
	s_allocation = allocation;
	s_need = need;
	for (int i(0); i < 5; i++)
	{
		s_available[i] -= req[i + 1];
		s_allocation[req[0]][i] += req[i + 1];
		s_need[req[0]][i] -= req[i + 1];
	}

	work = s_available;
	finish = vector< int >(s_need.size(), 0);

	if (!ini)
	{
		rq
			cout << "): WORK = (";
		wk
			cout << ")\n";
	}

	bool find, nof(0), safe(1);
	while (1)
	{
		for (int i(0); i < finish.size(); i++)
		{
			find = 0;
			if (finish[i] == 0)
			{
				find = 1;
				for (int j(0); j < 5; j++)
					if (s_need[i][j] > work[j])
						find = 0;
			}

			if (!find)
			{
				if (i == finish.size() - 1)
				{
					nof = 1;
					break;
				}
				continue;
			}
			else
			{
				for (int j(0); j < 5; j++)
					work[j] += s_allocation[i][j];

				if (!ini)
				{
					rq
						cout << "): gid " << i << " finish, WORK = (";
					wk
						cout << ")\n";
				}
				finish[i] = 1;
				safeSeq.push_back(i);
				break;
			}
		}

		if (nof)
			break;
	}

	for(auto it : finish)
		if (it == 0)
			return 0;

	return 1;
}

bool bankers(vector< int > req, bool wait)
{
	auto v = valid(req);

	if (!v.first)
	{
		rq
			cout << "): NEED error, request aborted\n";
		return 0;
	}
	else if (!v.second)
	{
		rq
			cout << "): NEED OK\n";
		rq
			cout << "): AVAILABLE error, request aborted\n";
		return 0;
	}
	else
	{
		rq
			cout << "): NEED OK\n";
		rq
			cout << "): AVAILABLE OK\n";
	}

	if (safety(req, 0))
	{
		rq
			cout << "): request granted, safe sequence = [";
		sfq
			cout << "]\n";

		for (int i(0); i < 5; i++)
		{
			available[i] -= req[i + 1];
			allocation[req[0]][i] += req[i + 1];
			need[req[0]][i] -= req[i + 1];
		}
		return 1;
	}
	else
	{
		rq
			cout << "): request not granted\n";
		if (!wait)
			requeue.push_back(req);
		return 0;
	}
}

int main(int argc, char* argv[])
{
	ifstream inFile(argv[1]);
	stringstream STRING1, STRING2;
	string str;
	char c;
	int i(0), n, m, s;

	while (getline(inFile, str, '\n'))
	{
		if (str[0] == '#')
		{
			i++; continue;
		}
		S1
			if (i == 1)
				while (getline(STRING1, str, ' '))
				{
					S2
						STRING2 >> n;
					available.push_back(n);
				}
			else if (i == 2)
			{
				getline(STRING1, str, ' ');
				S2
					STRING2 >> n;
				while (getline(STRING1, str, ' '))
				{
					S2
						STRING2 >> m;
					::max[n].push_back(m);
				}
			}
			else if (i == 3)
			{
				getline(STRING1, str, ' ');
				S2
					STRING2 >> n;
				while (getline(STRING1, str, ' '))
				{
					S2
						STRING2 >> m;
					allocation[n].push_back(m);
				}
			}
			else if (i == 4)
			{
				request.push_back(vector< int >());
				while (getline(STRING1, str, ' '))
				{
					S2
						if (!(str == "a" || str == "r"))
						{
							STRING2 >> n;
							request.back().push_back(n);
						}
						else
						{
							STRING2 >> c;
							request.back().push_back(c);
						}
				}
			}
	}

	need = ::max;
	for (auto it(need.begin()); it != need.end(); it++)
		for (int i(0); i < 5; i++)
			it->second[i] -= allocation[it->first][i];

	vector< int > iniReq{ 0, 0, 0, 0, 0, 0 };
	s = safety(iniReq, 1);
	if (s)
	{
		cout << "Initial state: safe, safe sequence = [";
		sfq
			cout << "]\n";
	}
	else
		cout << "Initial state : unsafe\n";

	for (auto it : request)
	{
		if (it.back() == 114)
		{
			bool r(1);
			n = it[0];
			it.pop_back();

			cout << '(';
			for (auto itt(it.begin()); itt != it.end(); itt++)
			{
				cout << *itt;
				if (itt != --it.end()) cout << ',';
			}
			cout << "): RELEASE ";
			it.erase(it.begin());

			for (int i(0); i < it.size(); i++)
				if (allocation[n][i] < it[i])
				{
					r = 0;
					break;
				}

			if (r)
			{
				for (int i(0); i < it.size(); i++)
				{
					allocation[n][i] -= it[i];
					available[i] += it[i];
				}
				cout << "granted";
			}
			else
				cout << "aborted";

			cout << ", AVAILABLE = (";
			for (auto itt(available.begin()); itt != available.end(); itt++)
			{
				cout << *itt;
				if (itt != --available.end()) cout << ',';
			}
			cout << ")\n";

			if (r)
			{
				del.clear();
				for (int i(0); i < requeue.size();i++)
				{
					m = bankers(requeue[i], 1);
					if (m)
						del.push_back(i);
				}
				for (int i(del.size() - 1); i >= 0; i--)
					requeue.erase(requeue.begin() + i);
			}
		}
		else
		{
			it.pop_back();
			bankers(it, 0);
		}
	}
}