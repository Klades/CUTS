// $Id$

//
// CUTS_Activation_Record_Endpoint
//
CUTS_INLINE
CUTS_Activation_Record_Endpoint::CUTS_Activation_Record_Endpoint (void)
: id_ (CUTS_UNKNOWN_ID)
{

}

//
// CUTS_Activation_Record_Endpoint
//
CUTS_INLINE
CUTS_Activation_Record_Endpoint::
CUTS_Activation_Record_Endpoint (int id,
                                 const ACE_Time_Value & toc,
                                 size_t data_size)
: CUTS_Endpoint_Data (toc, data_size),
  id_ (id)
{

}


//
// CUTS_Activation_Record_Endpoint
//
CUTS_INLINE
CUTS_Activation_Record_Endpoint::
CUTS_Activation_Record_Endpoint (const CUTS_Activation_Record_Endpoint & src)
: CUTS_Endpoint_Data (src),
  id_ (src.id_)
{

}

//
// ~CUTS_Activation_Record_Endpoint
//
CUTS_INLINE
CUTS_Activation_Record_Endpoint::~CUTS_Activation_Record_Endpoint (void)
{

}

//
// id
//
CUTS_INLINE
int CUTS_Activation_Record_Endpoint::id (void) const
{
  return this->id_;
}
