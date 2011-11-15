// -*- C++ -*-
// $Id$

//
// CUTS_Static_Node_T
//
template <typename T>
CUTS_INLINE
CUTS_Static_Node_T <T>::CUTS_Static_Node_T (void)
: next_ (0),
  prev_ (0)
{

}

//
// CUTS_Static_Node_T
//
template <typename T>
CUTS_INLINE
CUTS_Static_Node_T <T>::
CUTS_Static_Node_T (const T & item,
                    CUTS_Static_Node_T <T> * next,
                    CUTS_Static_Node_T <T> * prev)
: item_ (item),
  next_ (next),
  prev_ (prev)
{

}

//
// CUTS_Static_Node_T
//
template <typename T>
CUTS_INLINE
CUTS_Static_Node_T <T>::~CUTS_Static_Node_T (void)
{

}
