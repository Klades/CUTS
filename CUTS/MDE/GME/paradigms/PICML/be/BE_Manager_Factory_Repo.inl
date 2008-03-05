// $Id$

//
// CUTS_BE_Manager_Factory_Repo
//
CUTS_INLINE
CUTS_BE_Manager_Factory_Repo::CUTS_BE_Manager_Factory_Repo (void)
{

}

//
// ~CUTS_BE_Manager_Factory_Repo
//
CUTS_INLINE
CUTS_BE_Manager_Factory_Repo::~CUTS_BE_Manager_Factory_Repo (void)
{
  this->unload_all ();
}

//
// factories
//
CUTS_INLINE
const CUTS_BE_Manager_Factory_Set &
CUTS_BE_Manager_Factory_Repo::factories (void) const
{
  return this->factories_;
}

//
// load
//
CUTS_INLINE
bool CUTS_BE_Manager_Factory_Repo::
load (const std::string & id, const std::string & module)
{
  CUTS_BE_Manager_Factory * factory = 0;
  return this->load (id, module, factory);
}
