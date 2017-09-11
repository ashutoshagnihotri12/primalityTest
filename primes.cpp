// This program generates the first N Prime Numbers
#include <iostream>
#include <vector>

class PrimeList{
public:
	PrimeList();

	// Returns the nth prime number
	// (primeList[0] is 2, primeList[1] is 3, etc.)
	unsigned long operator[](size_t nth);

private:
	std::vector<bool> sieve; //sieve[i] is true if i is prime
	std::vector<unsigned long> knownPrimes;

	void findMorePrimes();
};

PrimeList::PrimeList(){
	sieve.push_back(false); // 0 is not a prime
	sieve.push_back(false); // 1 is not a prime
	knownPrimes.push_back(2);
}

unsigned long PrimeList::operator[](size_t nth){
	while(nth >= knownPrimes.size()){
		findMorePrimes();
	}
	return knownPrimes[nth];
}

void PrimeList::findMorePrimes(){
	// Initiall, sieve is a vector where every element is assumed to be prime (sieve[i] = true). Then, we will set sieve[i] = false for all i where i is non-prime. Special cases for non-primes sieve[0] = false and sieve[1] = false were already established in teh contructor.

	// Enlarge the sieve by some arbitrary amount
	std::vector<bool>::size_type prevSieveSize = sieve.size();
	sieve.resize(4*prevSieveSize,/* is_prime=*/ true);

	// Strike out the composite numbers from the enlarged sieve
	for(std::vector<unsigned long>::iterator p = knownPrimes.begin();
		p!=knownPrimes.end();++p){
		for(std::vector<bool>::size_type multiple = (prevSieveSize/(*p))*(*p); multiple < sieve.size();
			multiple += (*p)){
			sieve[multiple] = false;
		}
	}

	// Harvest the newly discovered prime numbers
	for(std::vector<bool>::size_type i = prevSieveSize; i<sieve.size();++i){
		if(sieve[i]){
			knownPrimes.push_back(i);
		}
	}
}
int main(int argc, char const *argv[])
{
	PrimeList primes;
	std::cout << primes[0] << " should be 2" << std::endl;
	std::cout << primes[499] << " should be 3571" << std::endl;
	return 0;
}

// int main(int argc, char** argv) {
//     std::cout << "Have " << argc << " arguments:" << std::endl;
//     for (int i = 0; i < argc; ++i) {
//         std::cout << argv[i] << std::endl;
//     }
// }