// $Id$

//
// CUTS_Component_Instance
//
CUTS_INLINE
CUTS_Component_Instance::
CUTS_Component_Instance (const CUTS_Component_Assembly & assembly,
                         ports_type ports)
: assembly_ (assembly),
  ports_ (ports)
{

}


//
// ~CUTS_Component_Instance
//
CUTS_INLINE
CUTS_Component_Instance::~CUTS_Component_Instance (void)
{

}

//
// assembly
//
CUTS_INLINE
const CUTS_Component_Assembly &
CUTS_Component_Instance::assembly (void) const
{
  return this->assembly_;
}
