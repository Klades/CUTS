// $Id$

#include "BE_Preprocessor_T.h"
#include "BE_Preprocessor_Handlers_T.h"

#include "boost/bind.hpp"

struct visit_all
{
public:
template <typename T>
void operator () (T & collection, PICML::Visitor * visitor) const
{
  for (auto item : collection)
    item->accept (visitor);
}
};

//
// CUTS_BE_Impl_Graph_Builder_T
//
template <typename T>
CUTS_BE_Impl_Graph_Builder_T <T>::
CUTS_BE_Impl_Graph_Builder_T (CUTS_BE_Impl_Graph & impl_graph,
                              CUTS_BE_IDL_Graph & idl_graph)
: impl_graph_ (impl_graph),
  idl_graph_ (idl_graph),
  curr_impl_ (0)
{

}

//
// ~CUTS_BE_Impl_Graph_Builder_T
//
template <typename T>
CUTS_BE_Impl_Graph_Builder_T <T>::~CUTS_BE_Impl_Graph_Builder_T (void)
{

}

//
// visit_ComponentImplementationContainer
//
template <typename T>
void CUTS_BE_Impl_Graph_Builder_T <T>::
visit_ComponentImplementationContainer (PICML::ComponentImplementationContainer_in container)
{
  // Get all the monolithic implemenations in this <container>.
  visit_all () (container->get_MonolithicImplementations (), this);
}

//
// visit_MonolithicImplementation
//
template <typename T>
void CUTS_BE_Impl_Graph_Builder_T <T>::
visit_MonolithicImplementation (PICML::MonolithicImplementation_in monoimpl)
{
  // Determine if we should preprocess the implementation. If
  // the element is preprocessed, then we will also include
  // the implementation in the listing.
  CUTS_BE_Preprocessor_Preprocess_Impl_T <T> preprocess;

  if (preprocess.generate (monoimpl))
  {
    // Locate the implementation in the graph. Also, set the container for
    // the implementation.
    this->impl_graph_.find (monoimpl->name (), this->curr_impl_);
    this->curr_impl_->container_ = PICML::ComponentImplementation::_narrow (monoimpl->parent ());

    // Visit the component that is being implemented.
    if (monoimpl->has_src_of_Implements ())
    {
      PICML::Implements implements = monoimpl->src_of_Implements ();
      PICML::ComponentRef ref = implements->dst_ComponentRef ();
      if (!ref->Component_is_nil ())
        ref->refers_to_Component ()->accept (this);
    }

    visit_all () (monoimpl->src_of_MonolithprimaryArtifact (), this);
  }
}

//
// visit_ComponentImplementationArtifact
//
template <typename T>
void CUTS_BE_Impl_Graph_Builder_T <T>::
visit_ComponentImplementationArtifact (PICML::ComponentImplementationArtifact_in cia)
{
  this->curr_impl_->exec_artifact_ = cia->refers_to_ImplementationArtifact ();
}

//
// visit_ComponentServantArtifact
//
template <typename T>
void CUTS_BE_Impl_Graph_Builder_T <T>::
visit_ComponentServantArtifact (PICML::ComponentServantArtifact_in csa)
{
  this->curr_impl_->svnt_artifact_ = csa->refers_to_ImplementationArtifact ();
}

//
// visit_Component
//
template <typename T>
void CUTS_BE_Impl_Graph_Builder_T <T>::
visit_Component (PICML::Component_in component)
{
  // Let's locate the parent file of this <component>.
  GAME::Mga::Object parent = component->parent ();

  while (parent->meta ()->name () != PICML::File::impl_type::metaname)
    parent = parent->parent ();

  // Save te file for later.
  PICML::File file = PICML::File::_narrow (parent);
  this->curr_impl_->impl_interface_ = file;

  // We are going to preprocess this file as well.
  CUTS_BE_IDL_Graph_Builder builder (this->idl_graph_);
  file->accept (&builder);

  // We need to locate this file in the graph.
  const CUTS_BE_IDL_Node * idl_node = 0;
  if (!this->idl_graph_.find (file->name (), idl_node))
    return;

  this->curr_impl_->references_.insert (idl_node);

  // Now, let's continue with the preprocessing by visiting all
  // the workers that are defined in this component. This is
  // necessary since to properly generate the implementation
  // code and project files.
  visit_all () (component->get_WorkerTypes (), this);
}

//
// visit_WorkerType
//
template <typename T>
void CUTS_BE_Impl_Graph_Builder_T <T>::
visit_WorkerType (PICML::WorkerType_in worker_type)
{
  if (!worker_type->Worker_is_nil ())
    worker_type->refers_to_Worker ()->accept (this);
}

//
// visit_Worker
//
template <typename T>
void CUTS_BE_Impl_Graph_Builder_T <T>::
visit_Worker (PICML::Worker_in worker)
{
  // We need to locate the parent file for this worker. This may
  // mean iterating over muliple packages before finding the file.
  CUTS_BE_Preprocessor_Worker_T <T> preprocessor;
  preprocessor.generate (this->curr_impl_, worker);

  GAME::Mga::Object parent = worker->parent ();

  while (parent->meta ()->name () != PICML::WorkerFile::impl_type::metaname)
    parent = parent->parent ();

  parent->accept (this);
}

//
// visit_WorkerFile
//
template <typename T>
void CUTS_BE_Impl_Graph_Builder_T <T>::
visit_WorkerFile (PICML::WorkerFile_in file)
{
  // Add the name of the worker to the collection of
  // include files for this node.
  CUTS_BE_Preprocessor_WorkerFile_T <T> preprocessor;
  preprocessor.generate (this->curr_impl_, file);

  // Add the location of this worker, if the string is not
  // empty, to the collection of include directories.
  std::string location = file->Location ();

  // Visit the library hosting the file.
  PICML::WorkerLibrary library = file->parent_WorkerLibrary ();
  library->accept (this);
}

//
// visit_WorkerFile
//
template <typename T>
void CUTS_BE_Impl_Graph_Builder_T <T>::
visit_WorkerLibrary (PICML::WorkerLibrary_in library)
{
  // Add the name of the library to the collection of
  // import libraries for this node.
  CUTS_BE_Preprocessor_WorkerLibrary_T <T> preprocessor;
  preprocessor.generate (this->curr_impl_, library);
}

//
// visit_MonolithprimaryArtifact
//
template <typename T>
void CUTS_BE_Impl_Graph_Builder_T <T>::
visit_MonolithprimaryArtifact (PICML::MonolithprimaryArtifact_in primary)
{
  PICML::ImplementationArtifactReference ref = primary->dst_ImplementationArtifactReference ();

  if (!ref->ImplementationArtifact_is_nil ())
    this->curr_impl_->artifacts_.insert (ref->refers_to_ImplementationArtifact ());

  primary->accept (this);
}
