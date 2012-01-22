#include <iostream>
#include "Dmac_Vertical_Format.h"

//
// CUTS_Dmac_Vertical_Format
//
CUTS_Dmac_Vertical_Format::CUTS_Dmac_Vertical_Format (void)
{

}

//
// ~CUTS_Dmac_Vertical_Format
//
CUTS_Dmac_Vertical_Format::~CUTS_Dmac_Vertical_Format (void)
{

}

//
// tid
//
void CUTS_Dmac_Vertical_Format::tid (long tid)
{
  this->tid_ = tid;
}

//
// time_val
//
void CUTS_Dmac_Vertical_Format::time_val (long time_val)
{
  this->time_val_ = time_val;
}

//
// insert_word
//
void CUTS_Dmac_Vertical_Format::insert_word (std::string word)
{
  this->row_words_.push_back (word);
}

//
// populate
//
void CUTS_Dmac_Vertical_Format::populate
    (CUTS_DMAC_UTILS::sequence_details & word_index)
{
  CUTS_DMAC_UTILS::s_iter iter;

  // populate the vertical datalist

  for (iter = this->row_words_.begin ();
    iter != this->row_words_.end (); iter++)
  {
    int id;
    id =  word_index.find (*iter)->second;
    this->items_.push_back (id);
  }
}

//
// print_row_words
//
void CUTS_Dmac_Vertical_Format::print_row_words (std::ofstream & output)
{
  CUTS_DMAC_UTILS::s_iter iter;
  int i = 0;
  for (iter = this->row_words_.begin (); iter != this->row_words_.end ();
    iter++)
  {
    i++;
    output << this->tid_ << " " << i << " 1 " <<*iter << std::endl;
  }
}