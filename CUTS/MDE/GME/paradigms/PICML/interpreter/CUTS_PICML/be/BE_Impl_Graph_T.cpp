// $Id$

#include "BE_Preprocessor_T.h"
#include "BE_Preprocessor_Handlers_T.h"
#include "CoWorkEr_Cache.h"

// UDM headers
#include "Uml.h"

// BOOST headers
#include "boost/bind.hpp"

#define PREPROCESSOR_SINGLETON(T) \
  ACE_Singleton <CUTS_BE_Preprocessor_T <T>, ACE_Null_Mutex>::instance ()

//
// CUTS_BE_Impl_Graph
//
template <typename T>
CUTS_BE_Impl_Graph_T <T>::CUTS_BE_Impl_Graph_T (void)
: current_impl_ (0)
{

}

//
// ~CUTS_BE_Impl_Graph
//
template <typename T>
CUTS_BE_Impl_Graph_T <T>::~CUTS_BE_Impl_Graph_T (void)
{

}

//
// Visit_ComponentImplementationContainer
//
template <typename T>
void CUTS_BE_Impl_Graph_T <T>::
Visit_ComponentImplementationContainer (
const PICML::ComponentImplementationContainer & container)
{
  // Get all the monolithic implemenations in this <container>.
  typedef std::vector <PICML::MonolithicImplementation> MonoImpl_Set;
  MonoImpl_Set monoimpls = container.MonolithicImplementation_kind_children ();

  // Visit all the monolithic implementations.
  std::for_each (monoimpls.begin (),
                 monoimpls.end (),
                 boost::bind (&MonoImpl_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_MonolithicImplementation
//
template <typename T>
void CUTS_BE_Impl_Graph_T <T>::
Visit_MonolithicImplementation (const PICML::MonolithicImplementation & monoimpl)
{
  // Determine if we should preprocess the implementation. If
  // the element is preprocessed, then we will also include
  // the implementation in the listing.
  CUTS_BE_Preprocessor_Preprocess_Impl_T <T> preprocess;

  if (preprocess.generate (monoimpl))
  {
    // Locate the implementation in the graph. Also, set the container for
    // the implementation.
    this->find (monoimpl.name (), this->current_impl_);

    this->current_impl_->container_ =
      PICML::ComponentImplementationContainer::Cast (monoimpl.parent ());

    // Visit the component that is being implemented.
    PICML::Implements implements = monoimpl.dstImplements ();

    if (implements != Udm::null)
    {
      PICML::ComponentRef ref = implements.dstImplements_end ();
      PICML::Component component = ref.ref ();

      if (component != Udm::null)
        component.Accept (*this);
    }

    typedef std::set <PICML::MonolithprimaryArtifact> PrimaryArtifact_Set;
    PrimaryArtifact_Set primaries = monoimpl.dstMonolithprimaryArtifact ();

    std::for_each (primaries.begin (),
                   primaries.end (),
                   boost::bind (&PrimaryArtifact_Set::value_type::Accept,
                                _1,
                                boost::ref (*this)));
  }
}

//
// Visit_ComponentImplementationArtifact
//
template <typename T>
void CUTS_BE_Impl_Graph_T <T>::
Visit_ComponentImplementationArtifact (const PICML::ComponentImplementationArtifact & cia)
{
  this->current_impl_->exec_artifact_ = cia.ref ();
}

//
// Visit_ComponentServantArtifact
//
template <typename T>
void CUTS_BE_Impl_Graph_T <T>::
Visit_ComponentServantArtifact (const PICML::ComponentServantArtifact & csa)
{
  this->current_impl_->svnt_artifact_ = csa.ref ();
}

//
// Visit_Component
//
template <typename T>
void CUTS_BE_Impl_Graph_T <T>::
Visit_Component (const PICML::Component & component)
{
  // Maybe this component we are generating is a proxy-enabled
  // component. If this is the case, we need to save this info
  // the generators.
  this->current_impl_->is_proxy_ =
   CUTS_CoWorkEr_Cache::instance ()->is_coworker (component);

  // Let's locate the parent file of this <component>.
  PICML::MgaObject parent = component.parent ();

  while (parent.type () != PICML::File::meta)
    parent = PICML::MgaObject::Cast (parent.parent ());

  // Save te file for later.
  PICML::File file = PICML::File::Cast (parent);
  this->current_impl_->impl_interface_ = file;

  // We are going to preprocess this file as well.
  const CUTS_BE_IDL_Node * idl_node = 0;
  PREPROCESSOR_SINGLETON (T)->preprocess (file, idl_node);

  // Add the preprocessed file to the reference set.
  this->current_impl_->references_.insert (idl_node);

  // Now, let's continue with the preprocessing by visiting all
  // the workers that are defined in this component. This is
  // necessary since to properly generate the implementation
  // code and project files.
  typedef std::vector <PICML::WorkerType> WorkerType_Set;
  WorkerType_Set workers = component.WorkerType_kind_children ();

  std::for_each (workers.begin (),
                 workers.end (),
                 boost::bind (&WorkerType_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_WorkerType
//
template <typename T>
void CUTS_BE_Impl_Graph_T <T>::
Visit_WorkerType (const PICML::WorkerType & worker_type)
{
  PICML::Worker worker = worker_type.ref ();

  if (worker != Udm::null)
    worker.Accept (*this);
}

//
// Visit_Worker
//
template <typename T>
void CUTS_BE_Impl_Graph_T <T>::
Visit_Worker (const PICML::Worker & worker)
{
  // We need to locate the parent file for this worker. This may
  // mean iterating over muliple packages before finding the file.
  CUTS_BE_Preprocessor_Worker_T <T> preprocessor;
  preprocessor.generate (this->current_impl_, worker);

  PICML::MgaObject parent = worker.parent ();

  while (parent.type () != PICML::WorkerFile::meta)
    parent = PICML::MgaObject::Cast (parent.parent ());

  PICML::WorkerFile::Cast (parent).Accept (*this);
}

//
// Visit_WorkerFile
//
template <typename T>
void CUTS_BE_Impl_Graph_T <T>::
Visit_WorkerFile (const PICML::WorkerFile & file)
{
  // Add the name of the worker to the collection of
  // include files for this node.
  CUTS_BE_Preprocessor_WorkerFile_T <T> preprocessor;
  preprocessor.generate (this->current_impl_, file);

  // Add the location of this worker, if the string is not
  // empty, to the collection of include directories.
  std::string location = file.Location ();

  // Visit the library hosting the file.
  PICML::WorkerLibrary library = file.WorkerLibrary_parent ();
  library.Accept (*this);
}

//
// Visit_WorkerFile
//
template <typename T>
void CUTS_BE_Impl_Graph_T <T>::
Visit_WorkerLibrary (const PICML::WorkerLibrary & library)
{
  // Add the name of the library to the collection of
  // import libraries for this node.
  CUTS_BE_Preprocessor_WorkerLibrary_T <T> preprocessor;
  preprocessor.generate (this->current_impl_, library);
}

//
// Visit_MonolithprimaryArtifact
//
template <typename T>
void CUTS_BE_Impl_Graph_T <T>::
Visit_MonolithprimaryArtifact (const PICML::MonolithprimaryArtifact & primary)
{
  PICML::ImplementationArtifactReference ref = primary.dstMonolithprimaryArtifact_end ();
  PICML::ImplementationArtifact artifact = ref.ref ();

  if (artifact != Udm::null)
    this->current_impl_->artifacts_.insert (artifact);

  if (PICML::ComponentImplementationArtifact::meta == ref.type ())
    PICML::ComponentImplementationArtifact::Cast (ref).Accept (*this);
  else if (PICML::ComponentServantArtifact::meta == ref.type ())
    PICML::ComponentServantArtifact::Cast (ref).Accept (*this);
}
