// $Id$

#include "TestArchive_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestArchive_i.inl"
#endif

#include "TestUploader_i.h"
#include "cuts/UUID.h"
#include <sstream>

//
// init
//
int CUTS_TestArchive_i::init (PortableServer::POA_ptr parent)
{
  // Create the POA for the upload agents.
  CORBA::PolicyList policies (5);
  policies.length (5);

  policies[0] = parent->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
  policies[1] = parent->create_servant_retention_policy (PortableServer::RETAIN);
  policies[2] = parent->create_id_assignment_policy (PortableServer::SYSTEM_ID);
  policies[3] = parent->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
  policies[4] = parent->create_lifespan_policy (PortableServer::TRANSIENT);

  this->upload_poa_ = parent->create_POA ("TestUploader",
                                          PortableServer::POAManager::_nil (),
                                          policies);

  PortableServer::POAManager_var mgr = this->upload_poa_->the_POAManager ();
  mgr->activate ();

  // Destroy the POA policies
  for (CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();

  // Finally, open a connection to the database.
  int retval = 0;

  try
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - opening connection to database\n"));

    this->conn_.connect (this->opts_.username_.c_str (),
                         this->opts_.password_.c_str (),
                         this->opts_.hostname_.c_str ());
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - failed to open connection to database [%s]\n",
                ex.message ().c_str ()));

    retval = -1;
  }

  return retval;
}

//
// begin_upload
//
CUTS::TestUploader_ptr CUTS_TestArchive_i::
begin_upload (const CUTS::TestResult & result)
{
  // Extract the UUID of the test.
  ACE_Utils::UUID uuid;
  result.uid >>= uuid;

  // Make sure the upload is not already taking place.
  if (this->uploads_.find (uuid) == 0)
    throw CUTS::UploadAlreadyActive ();

  // Allocate a new uploader agent for this test.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - creating a new upload agent for %s\n",
              uuid.to_string ()->c_str ()));

  CUTS_TestUploader_i * servant = 0;

  ACE_NEW_THROW_EX (servant,
                    CUTS_TestUploader_i (uuid, this->opts_.upload_dir_),
                    CORBA::NO_MEMORY ());

  ACE_Auto_Ptr <CUTS_TestUploader_i> auto_clean (servant);

  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - opening file to store test results for %s\n",
              servant->uuid ().to_string ()->c_str ()));

  // Verify the uploader is open.
  if (!servant->is_open ())
    throw CUTS::UploadFailed ();

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - activating the upload agent\n"));

  // Convert the UUID to a object id, which should be unique.
  PortableServer::ObjectId_var oid =
    PortableServer::string_to_ObjectId (uuid.to_string ()->c_str ());

  // Activate the uploader object using specified object id.
  this->upload_poa_->activate_object_with_id (oid.in (), servant);

  // Get a reference to the newly activate servant. Then, return the
  // reference to the client.
  ::CORBA::Object_var obj = this->upload_poa_->servant_to_reference (servant);
  CUTS::TestUploader_var uploader = CUTS::TestUploader::_narrow (obj.in ());

  auto_clean.release ();
  return uploader._retn ();
}

//
// upload_complete
//
void CUTS_TestArchive_i::upload_complete (CUTS::TestUploader_ptr uploader)
{
  // Locate the servant.
  PortableServer::ServantBase_var servant_base =
    this->upload_poa_->reference_to_servant (uploader);

  // Cast the servant base to an uploader agent.
  CUTS_TestUploader_i * servant =
    dynamic_cast <CUTS_TestUploader_i *> (servant_base.in ());

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - completing test results upload for %s\n",
              servant->uuid ().to_string ()->c_str ()));

  // Deactivate the object.
  PortableServer::ObjectId_var oid = this->upload_poa_->servant_to_id (servant);
  this->upload_poa_->deactivate_object (oid.in ());

  // Close the file from writing.
  servant->close (this->conn_);

  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - sucessfully uploaded test results for %s\n",
              servant->uuid ().to_string ()->c_str ()));

  // Remove the UUID from the upload list.
  this->uploads_.remove (servant->uuid ());

  // We can savely delete the servant.
  delete servant;
}
