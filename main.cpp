#include <iostream>
#include <vector>


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

  std::vector<int> outcome = find_prime_numbers(1000);
  int global = 0;

  for(auto e : outcome) {
    global += 1;
  }

  std::cout << global;


  return 0;
}
