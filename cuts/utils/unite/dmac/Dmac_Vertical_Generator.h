#ifndef _CUTS_DMAC_VERTICAL_APP_H_
#define _CUTS_DMAC_VERTICAL_APP_H_

#include <iostream>
#include "ace/SString.h"
#include "Dmac_Vertical_Format.h"
#include <algorithm>
#include <sstream>


/**
 * @class CUTS_Dmac_Vertical_Generator
 *
 * Convert the dataset to a vertical format
 */
class CUTS_Dmac_Vertical_Generator
{
public:

  /// Type definitions
  typedef std::vector <CUTS_Dmac_Vertical_Format *> vertical_list_t;

  typedef std::vector <CUTS_Dmac_Vertical_Format *>::iterator v_iter;

  /// Default constructor
  CUTS_Dmac_Vertical_Generator (std::string & delims);

  /// Destructor
  ~CUTS_Dmac_Vertical_Generator (void);

  // Convert oto vertical format
  virtual int generate (ACE_CString & db_file, int round) = 0;

  // Tokenize words
  void tokenize (const std::string & str,
                 std::set <std::string> & tokens,
                 std::string & delimiters,
                 CUTS_Dmac_Vertical_Format * format);

protected:
  // Delimitters
  std::string & delims_;

};


/**
 * @class CUTS_Dmac_DB_Vertical_Generator
 *
 * Convert the dataset in a database to a vertical format
 */
class CUTS_Dmac_DB_Vertical_Generator : public CUTS_Dmac_Vertical_Generator
{
public:

  /// Default constructor
  CUTS_Dmac_DB_Vertical_Generator (std::string & delims);

  /// Destructor
  ~CUTS_Dmac_DB_Vertical_Generator (void);

  /// Convert to vertical format using a dataset in a database
  virtual int generate (ACE_CString & db_file, int round);

};


/**
 * @class CUTS_Dmac_File_Vertical_Generator
 *
 * Convert the dataset in a database to a vertical format
 */
class CUTS_Dmac_File_Vertical_Generator : public CUTS_Dmac_Vertical_Generator
{
public:

  /// Default constructor
  CUTS_Dmac_File_Vertical_Generator (std::string & delims);

  /// Destructor
  ~CUTS_Dmac_File_Vertical_Generator (void);

  /// convert to vertical format using a dataset in a file
  virtual int generate (ACE_CString & db_file, int round);

  /// Number of rows in the dataset.
  long row_count_;

};

#endif  // !defined _CUTS_DMAC_VERTICAL_APP_H_