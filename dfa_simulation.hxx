#ifndef MRR_DFA_SIMULATION_HXX_
#define MRR_DFA_SIMULATION_HXX_

#include <unordered_map>
#include <unordered_set>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

enum class dfa_state {final, non_final};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename StateType, typename SymbolType>
struct dfa
{
  using state_type = StateType;
  using symbol_type = SymbolType;
  using transition_type = std::unordered_map<symbol_type,state_type>;
  using graph_type = std::unordered_map<state_type,transition_type>;

  void start_state(state_type const& s)
  {
    start = s;
  }

  void add_state(
    state_type const& state,
    transition_type const& transition,
    dfa_state is_final = dfa_state::non_final
  )
  {
    graph.insert(std::make_pair(state,transition));
    if (is_final == dfa_state::final)
	    final_states.insert(state);
  }

  template <typename Iter>
  bool simulate(Iter begin, Iter end)
  {
    state_type state = start;
    for (; begin != end; ++begin)
    {
      auto new_state = graph[state].find(*begin);
      if (new_state == graph[state].end())
        return false;
      state = new_state->second;
    }
    return final_states.find(state) != final_states.end();
  }

  std::ostream& dot(std::ostream& os)
  {
    os << "digraph\n"
       << "{\n"
       << "START [shape=point];\n"
       << "START -> " << start << ";\n\n"
    ;


    for (auto const& x : final_states)
      os << x << " [shape=doublecircle];\n";
    os << "node [shape=circle]\n";

    for (auto const& state : graph)
      for (auto const& transition : state.second)
        os << state.first << " -> " << transition.second
           << " [label=\"" << transition.first << "\"];\n"
        ;
    os << "}\n";

    return os;
  }

private:
  graph_type graph;
  state_type start;
  std::unordered_set<state_type> final_states;

}; // struct dfa



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#endif // #ifndef MRR_DFA_SIMULATION_HXX_
