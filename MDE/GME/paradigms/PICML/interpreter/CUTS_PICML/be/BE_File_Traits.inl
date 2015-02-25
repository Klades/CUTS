// $Id$

//
// CUTS_BE_File_Traits
//
CUTS_INLINE
CUTS_BE_File_Traits::CUTS_BE_File_Traits (void)
{

}

//
// close_file
//
CUTS_INLINE
void CUTS_BE_File_Traits::
close_file (const PICML::ComponentImplementationContainer_in container)
{
  this->out_.close ();
}
