// $Id$

#if !defined (__CUTS_INLINE__)
#include "BE_Assembly_Generator_T.inl"
#endif

//
// Visit_ComponentAssembly
//
template <typename T>
void CUTS_BE_Assembly_Generator_T <T>::
Visit_ComponentAssembly (const PICML::ComponentAssembly & assembly)
{
  CUTS_BE_ComponentAssembly_Begin_T <T>::generate (assembly);

  typedef std::vector <PICML::Component> Component_Set;
  Component_Set components = assembly.Component_children ();

  CUTS_BE::visit <T> (components,
    boost::bind (&Component_Set::value_type::Accept, _1, boost::ref (*this)));

  // Begin the generation of connection information.
  CUTS_BE_ComponentAssembly_Connections_Begin_T <T>::generate (assembly);

  // Get all the point-to-point connections and visit them.
  typedef std::vector <PICML::emit> emit_Set;
  emit_Set emits = assembly.emit_children ();

  CUTS_BE::visit <T> (emits,
    boost::bind (&emit_Set::value_type::Accept, _1, boost::ref (*this)));

  // Get all the one-to-many connections and visit them.
  typedef std::vector <PICML::PublishConnector> PublishConnector_Set;
  PublishConnector_Set connectors = assembly.PublishConnector_children ();

  CUTS_BE::visit <T> (connectors,
    boost::bind (&PublishConnector_Set::value_type::Accept, _1, boost::ref (*this)));

  // End the generation of the connection information.
  CUTS_BE_ComponentAssembly_Connections_End_T <T>::generate (assembly);

  // End the generation of assembly information.
  CUTS_BE_ComponentAssembly_End_T <T>::generate (assembly);
}

//
// Visit_Component
//
template <typename T>
void CUTS_BE_Assembly_Generator_T <T>::
Visit_Component (const PICML::Component & component)
{
  CUTS_BE_Component_Instance_T <T>::generate (component);
}

//
// Visit_emit
//
template <typename T>
void CUTS_BE_Assembly_Generator_T <T>::
Visit_emit (const PICML::emit & e)
{
  CUTS_BE_emit_T <T>::generate (e);
}

//
// Visit_PublishConnector
//
template <typename T>
void CUTS_BE_Assembly_Generator_T <T>::
Visit_PublishConnector (const PICML::PublishConnector & connector)
{
  CUTS_BE_PublishConnector_T <T>::generate (connector);
}
