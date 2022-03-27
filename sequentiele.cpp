#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>


std::vector<int> find_prime_numbers(int n) {

  std::vector<int> zeef;

  for(int i = 2; i < n; i++) {
    zeef.push_back(i);
  }

  int k = 2;

  while(k * k <= n) {
    std::vector<int>::iterator it = std::find(zeef.begin(), zeef.end(), k * k);
    int index = std::distance(zeef.begin(), it);

    for(int i = index; i < n; i++) {
      if(zeef[i] % k == 0) {
        zeef[i] = 0;
      }
    }

    zeef.erase(std::remove(zeef.begin(), zeef.end(), 0), zeef.end());

    std::vector<int>::iterator it1 = std::find(zeef.begin(), zeef.end(), k);
    int k_index = std::distance(zeef.begin(), it1);

    k = zeef[k_index + 1];

  }

  return zeef;
}

int main() {

  int n = 1000;

  auto start = std::chrono::system_clock::now();
  std::vector<int> outcome = find_prime_numbers(n);
  auto stop = std::chrono::system_clock::now();

  auto duration = stop - start;
  typedef std::chrono::duration<float> float_seconds;
  auto secs = std::chrono::duration_cast<float_seconds>(duration);

  std::ofstream myFile;
  myFile.open("spreadsheet/sequentiele.csv", std::ios::app);
  myFile << secs.count() << "; " << outcome.size() << "; " << n << std::endl;
  myFile.close();

  std::cout << "total amount of numbers: " << n << std::endl;
  std::cout << "found prime numbers: " << outcome.size() << std::endl;
  std::cout << "Total time taken: " << secs.count() << std::endl;


  return 0;
}
