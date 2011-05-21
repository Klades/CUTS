//
// CUTS_Dmac_Sequence
//
CUTS_INLINE CUTS_Dmac_Sequence::CUTS_Dmac_Sequence (void)
: add_row_ (false),
  selected_ (false),
  row_count_ (0),
  max_row_words_ (0)
{

}

//
// ~CUTS_Dmac_Sequence
//
CUTS_INLINE CUTS_Dmac_Sequence::~CUTS_Dmac_Sequence (void)
{

}

//
// add_row
//
CUTS_INLINE bool CUTS_Dmac_Sequence::add_row (void)
{
  return this->add_row_;
}

//
// selected
//
CUTS_INLINE bool CUTS_Dmac_Sequence::selected (void)
{
  return this->selected_;
}

//
// row_count
//
CUTS_INLINE int CUTS_Dmac_Sequence::row_count (void)
{
  return this->row_count_;
}

//
// max_row_words
//
CUTS_INLINE int CUTS_Dmac_Sequence::max_row_words (void)
{
  return this->max_row_words_;
}

//
// row_ids
//
CUTS_INLINE CUTS_DMAC_UTILS::int_vector & CUTS_Dmac_Sequence::row_ids (void)
{
  return this->row_ids_;
}

//
// key_position_table
//
CUTS_INLINE CUTS_DMAC_UTILS::sequence_details & CUTS_Dmac_Sequence::key_position_table (void)
{
  return this->key_position_table_;
}

//
// add_row
//
CUTS_INLINE void CUTS_Dmac_Sequence::add_row (bool add_row)
{
  this->add_row_ = add_row;
}

//
// selected
//
CUTS_INLINE void CUTS_Dmac_Sequence::selected (bool selected)
{
  this->selected_ = selected;
}

//
// row_count
//
CUTS_INLINE void CUTS_Dmac_Sequence::row_count (int row_count)
{
  this->row_count_ = row_count;
}

//
// max_row_words
//
CUTS_INLINE void CUTS_Dmac_Sequence::max_row_words (int max_row_words)
{
  this->max_row_words_ = max_row_words;
}