// $Id$

#include <string>

//
// expand
//
template <typename IteratorT>
void CUTS_Property_Evaluator_List_Actor::
expand (IteratorT begin,
        IteratorT end,
        const CUTS_Property_Map & ,
        const CUTS_Property_Evaluator_Config &) const
{
  std::string name (begin, end);
  this->list_.insert (name.c_str ());
}
