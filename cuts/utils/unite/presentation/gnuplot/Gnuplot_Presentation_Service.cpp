// $Id$

#include "Gnuplot_Presentation_Service.h"

#if !defined (__CUTS_INLINE__)
#include "Gnuplot_Presentation_Service.inl"
#endif

#include "cuts/utils/unite/Dataset_Result.h"
#include "cuts/utils/unite/Unite_Test.h"
#include "ace/Get_Opt.h"
#include "ace/Service_Config.h"
#include "ace/streams.h"
#include "ace/Unbounded_Set.h"

struct get_group_name_item
{
public:
  get_group_name_item (ACE_CString & name,
                       const char * separator,
                       size_t count)
    : name_ (name),
      separator_ (separator),
      count_ (count)
  {

  }

  void operator () (const ACE_CString & name)
  {
    this->name_ += name.c_str ();

    if (this->count_ -- != 1)
      this->name_ += this->separator_;
  }

private:
  /// Output location of the group name.
  ACE_CString & name_;

  /// Separator between each item.
  const char * separator_;

  /// The current item.
  size_t curr_;

  /// The number of items in the group name.
  size_t count_;
};

//
// init
//
int CUTS_Gnuplot_Presentation_Service::init (int argc, char * argv [])
{
  const char * optstr = "o:";
  ACE_Get_Opt get_opt (argc, argv, optstr, 0);

  get_opt.long_option ("disable-group-title");

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "disable-group-title") == 0)
        this->has_group_titles_ = false;
      break;

    case 'o':
      this->output_ = get_opt.opt_arg ();
      break;
    }
  }

  return 0;
}

//
// handle_result
//
int CUTS_Gnuplot_Presentation_Service::
handle_result (CUTS_Dataset_Result & result)
{
  std::ofstream outfile;
  ACE_CString filename;

  typedef ACE_Unbounded_Set <ACE_CString> datasets_type;
  datasets_type datasets;

  ACE_CString curr_name, next_name;
  size_t index;

  if (result.has_groupings ())
  {
    for ( ; !result.done (); result.advance ())
    {
      // Make sure the output storage is empty.
      if (!next_name.empty ())
        next_name.clear ();

      // Get the name of the next group.
      std::for_each (result.get_group_name ().begin (),
                     result.get_group_name ().end (),
                     get_group_name_item (next_name,
                                          ".",
                                          result.get_group_name ().size ()));

      if (curr_name != next_name)
      {
        // Close the output file if it is already open.
        if (outfile.is_open ())
          outfile.close ();

        // Open a data file for the new group.
        filename = this->output_ + "/" + next_name + ".dat";
        outfile.open (filename.c_str ());

        if (outfile.is_open ())
        {
          // Save the filename for the dataset.
          datasets.insert (next_name);
        }
        else
        {
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - failed to open data file %s for writing\n",
                      filename.c_str ()));
        }

        // Save the name of the new group.
        curr_name = next_name;
        index = 1;
      }

      // Write the data to the file.
      outfile << (index ++) << ' ' << result.get_result () << std::endl;
    }
  }
  else
  {
    // Open the data file for writing.
    filename = this->output_ + "/" + "result.dat";
    outfile.open (filename.c_str ());

    if (outfile.is_open ())
      datasets.insert ("result");

    // Write the data to the data file.
    size_t index = 1;

    for ( ; !result.done (); result.advance ())
      outfile << (index ++) << " " << result.get_result () << std::endl;
  }

  // Prepare for the main file.
  if (outfile.is_open ())
    outfile.close ();

  // Construct the filename for the main file.
  filename = this->output_ + "/" +
             result.unit_test ()->name () + ".gnuplot";

  // Open the main file for writing.
  outfile.open (filename.c_str ());

  if (!outfile.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to open %s for writing\n",
                       filename.c_str ()),
                       -1);

  outfile << "set ylabel '"
          << result.unit_test ()->name ().c_str () << "'" << std::endl
          << std::endl
          << "plot ";

  datasets_type::CONST_ITERATOR iter (datasets);

  if (!iter.done ())
  {
    outfile << "'" << (*iter).c_str ()
            << ".dat' using 1:2 with lines";

    if (this->has_group_titles_)
      outfile << " title '"
              << (*iter).c_str () << "'";
    else
      outfile << " notitle";

    for (++ iter ; !iter.done (); ++ iter)
    {
      outfile << ", \\" << std::endl
              << "     '" << (*iter).c_str ()
              << ".dat' using 1:2 with lines";

      if (this->has_group_titles_)
        outfile << " title '"
                << (*iter).c_str () << "'";
      else
        outfile << " notitle";
    }
  }

  // Close the file from writing.
  outfile.close ();

  return 0;
}

///////////////////////////////////////////////////////////////////////////////
//

ACE_STATIC_SVC_DEFINE (CUTS_Gnuplot_Presentation_Service,
                       ACE_TEXT ("cuts.gnuplot"),
                       ACE_SVC_OBJ_T,
                       &ACE_SVC_NAME (CUTS_Gnuplot_Presentation_Service),
                       ACE_Service_Type::DELETE_THIS | ACE_Service_Type::DELETE_OBJ,
                       1)

ACE_FACTORY_DEFINE (CUTS_GNUPLOT_PRESENTATION_SERVICE,
                    CUTS_Gnuplot_Presentation_Service)
