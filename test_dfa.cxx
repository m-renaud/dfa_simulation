#include <iostream>
#include <iomanip>
#include <fstream>

#include "dfa_simulation.hxx"

int main()
{
  std::string line;

  // We want our states to be of type int and our transitions to be chars
  mrr::dfa<int,char> d;

  // Define the DFA representing the language of strings {a,b}*
  // that end with an 'a'

  // Add state 0 with 2 edges, also make it a final state
  d.add_state(0, {{'a',0},{'b',1}}, mrr::dfa_state::final);

  // Add state 1 with 2 edges, this state will be non-final
  d.add_state(1, {{'a',0},{'b',1}});

  // Set the start state for the DFA
  d.start_state(0);

  while(std::cin >> line)
    std::cout << std::boolalpha << d.simulate(line) << std::endl;


  // Write the DFA as a dot file
  std::ofstream dotfile("basic_sim.dot");
  d.dot(dotfile);

  return 0;
}
