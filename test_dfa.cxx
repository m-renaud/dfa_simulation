#include <iostream>
#include <iomanip>
#include <fstream>

#include "dfa_simulation.hxx"

int main()
{
  std::string line;
  mrr::dfa<int,char> d;

  d.add_state(0, {{'a',0},{'b',1}}, mrr::dfa_state::final);
  d.add_state(1, {{'a',0},{'b',1}});
  d.start_state(0);

  while(std::cin >> line)
    std::cout << std::boolalpha << d.simulate(line) << std::endl;


  // Write the DFA as a dot file
  std::ofstream dotfile("basic_sim.dot");
  d.dot(dotfile);
}
