// $Id$

#include "Property_Map_File.h"
#include "Property_Parser.h"
#include "boost/spirit/include/classic_file_iterator.hpp"
#include "ace/streams.h"

//
// CUTS_Property_Map_File
//
CUTS_Property_Map_File::CUTS_Property_Map_File (CUTS_Property_Map & map)
: prop_map_ (map)
{

}

//
// CUTS_Property_Map_File
//
CUTS_Property_Map_File::~CUTS_Property_Map_File (void)
{

}

//
// read
//
bool CUTS_Property_Map_File::read (const char * filename)
{
  typedef char char_t;
  typedef boost::spirit::classic::file_iterator <char_t> iterator_t;

  // Get an iterator to the beginning of the file.
  iterator_t begin (filename);

  if (!begin)
    return false;

  // Get an iterator to the end of the file.
  iterator_t end = begin.make_end ();

  // Parse the contents of the file.
  CUTS_Property_Parser parser (this->prop_map_);
  return parser.parse (begin, end);
}

//
// write
//
bool CUTS_Property_Map_File::write (const char * filename) const
{
  // Open the file for writing.
  std::ofstream file;
  file.open (filename);

  if (!file.is_open ())
    return false;

  // Write all the properties to the file.
  CUTS_Property_Map::iterator
    iter = this->prop_map_.begin (), iter_end = this->prop_map_.end ();

  for (; iter != iter_end; ++ iter)
    file << iter->key ().c_str () << "=" << iter->item ().c_str () << std::endl;

  // Close the file from writing.
  file.close ();

  return true;
}
