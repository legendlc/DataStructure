#include<iostream> 
#include<istream>
#include<ostream>
#include<vector>
using namespace std;

typedef int coeType;
typedef int expType;
class Term;

void sortVec(vector<Term> &v);

class Term {
public:
	Term();
	friend bool cmp(const Term& a, const Term& b);
	friend istream& operator>>(istream& is, Term& term);
	friend ostream& operator<<(ostream& os, const Term& term);
	coeType coe;
	expType exp;
};

class Polynomial {
public:
	Polynomial();
	Polynomial(const Polynomial &p);
	~Polynomial();
	void getData(istream& is);
	void putData(ostream& os);
	friend Polynomial operator+(const Polynomial &a, const Polynomial &b);
	friend Polynomial operator*(const Polynomial &a, const Polynomial &b);
public:
	int _numNotZero;
	expType _maxOrder;
	coeType* pCoe;
	expType* pExpNotZero;
};

expType max(const expType &a, const expType &b) {
	return a > b ? a : b;
}

bool cmp(const Term& a, const Term& b) {
	if (a.exp > b.exp)
		return true;
	else
		return false;
}
istream& operator>>(istream& is, Term& term)
{
	is >> term.coe;
	is >> term.exp;
	return is;
}
ostream& operator<<(ostream& os, const Term& term) {
	os << term.coe;
	os << ' ';
	os << term.exp;
	return os;
}

Term::Term()
{
	coe = 0;
	exp = 0;
}



Polynomial::Polynomial()
{
	_numNotZero = 0;
	_maxOrder = 0;
	pCoe = 0;
	pExpNotZero = 0;
}

Polynomial::Polynomial(const Polynomial &p)
{
	this->_numNotZero = p._numNotZero;
	this->_maxOrder = p._maxOrder;
	if (this->pExpNotZero)
		delete pExpNotZero;
	this->pExpNotZero = new expType[_numNotZero];
	for (int i = 0; i < _numNotZero; i++) {
		this->pExpNotZero[i] = p.pExpNotZero[i];
	}
	if (this->pCoe)
		delete pCoe;
	this->pCoe = new coeType[_maxOrder + 1];
	for (int i = 0; i <= _maxOrder; i++) {
		this->pCoe[i] = p.pCoe[i];
	}
}

Polynomial::~Polynomial()
{
	if (pCoe)
		delete pCoe;
	if (pExpNotZero)
		delete pExpNotZero;
}

void Polynomial::getData(istream & is)
{
	is >> _numNotZero;
	if(_numNotZero == 0){
		pExpNotZero = new expType;
		pExpNotZero[0] = 0;
		pCoe = new coeType;
		pCoe[0] = 0;
	}
	else{
		pExpNotZero = new expType[_numNotZero];
		Term tempTerm;
		is >> tempTerm;
		pExpNotZero[0] = tempTerm.exp;
		_maxOrder = tempTerm.exp;
		pCoe = new coeType[_maxOrder + 1];
		for (int i = 0; i <= _maxOrder; i++) {
			pCoe[i] = 0;
		}
		pCoe[tempTerm.exp] = tempTerm.coe;
		for (int i = 1; i < _numNotZero; i++) {
			is >> tempTerm;
			pCoe[tempTerm.exp] = tempTerm.coe;
			pExpNotZero[i] = tempTerm.exp;
		}
	}
	
}

void Polynomial::putData(ostream & os)
{	
	if(_numNotZero == 0){
		cout << 0 << ' ' << 0;
		cout << endl;
	}
	else{
		for (int i = 0; i < _numNotZero; i++) {
			cout << pCoe[pExpNotZero[i]] << ' ' << pExpNotZero[i];
			if (i < _numNotZero - 1)
				cout << ' ';
			else
				cout << endl;
		}
	}
	
}

Polynomial operator+(const Polynomial &a, const Polynomial &b) {
	Polynomial sum;
	if (a._maxOrder > b._maxOrder) {
		sum._maxOrder = a._maxOrder;
		sum.pCoe = new coeType[sum._maxOrder + 1];
		for (int i = 0; i <= sum._maxOrder; i++) {
			sum.pCoe[i] = 0;
		}
		for (int i = 0; i < a._numNotZero; i++) {
			sum.pCoe[a.pExpNotZero[i]] += a.pCoe[a.pExpNotZero[i]];
		}
		for (int i = 0; i < b._numNotZero; i++) {
			sum.pCoe[b.pExpNotZero[i]] += b.pCoe[b.pExpNotZero[i]];
		}
	}
	else {
		sum._maxOrder = b._maxOrder;
		sum.pCoe = new coeType[sum._maxOrder + 1];
		for (int i = 0; i <= sum._maxOrder; i++) {
			sum.pCoe[i] = 0;
		}
		for (int i = 0; i < a._numNotZero; i++) {
			sum.pCoe[a.pExpNotZero[i]] += a.pCoe[a.pExpNotZero[i]];
		}
		for (int i = 0; i < b._numNotZero; i++) {
			sum.pCoe[b.pExpNotZero[i]] += b.pCoe[b.pExpNotZero[i]];
		}
	}
	for (int i = 0; i <= sum._maxOrder; i++) {
		if (sum.pCoe[i] != 0)
			sum._numNotZero++;
	}
	sum.pExpNotZero = new expType[sum._numNotZero];
	int cnt = 0;
	for (int i = sum._maxOrder; i >= 0; i--) {
		if (sum.pCoe[i] != 0) {
			sum.pExpNotZero[cnt] = i;
			cnt++;
		}
	}
	return sum;
}
Polynomial operator*(const Polynomial &a, const Polynomial &b) {
	Polynomial prod;
	prod._maxOrder = a._maxOrder + b._maxOrder;
	prod.pCoe = new coeType[prod._maxOrder + 1];
	for (int i = 0; i <= prod._maxOrder; i++) {
		prod.pCoe[i] = 0;
	}
	for (int i = 0; i < a._numNotZero; i++) {
		for (int j = 0; j < b._numNotZero; j++) {
			prod.pCoe[a.pExpNotZero[i] + b.pExpNotZero[j]] += a.pCoe[a.pExpNotZero[i]] * b.pCoe[b.pExpNotZero[j]];
		}
	}
	for (int i = 0; i <= prod._maxOrder; i++) {
		if (prod.pCoe[i] != 0)
			prod._numNotZero++;
	}
	prod.pExpNotZero = new expType[prod._numNotZero];
	int cnt = 0;
	for (int i = prod._maxOrder; i >= 0; i--) {
		if (prod.pCoe[i] != 0) {
			prod.pExpNotZero[cnt] = i;
			cnt++;
		}
	}
	return prod;
}

int main() {
	Polynomial a, b;
	a.getData(cin);
	b.getData(cin);
	Polynomial sum = a + b;
	Polynomial product = a * b;
	product.putData(cout);
	sum.putData(cout);

	return 0;
}
