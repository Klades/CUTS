// $Id$

#include "TestArchive_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestArchive_i.inl"
#endif

#include "TestArchiveBrowser_i.h"
#include "TestRetriever_i.h"
#include "TestUploader_i.h"
#include "cuts/UUID.h"
#include <sstream>

//
// init
//
int CUTS_TestArchive_i::init (PortableServer::POA_ptr parent)
{
  CORBA::PolicyList policies (5);
  policies.length (5);

  policies[0] = parent->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
  policies[1] = parent->create_servant_retention_policy (PortableServer::RETAIN);
  policies[2] = parent->create_id_assignment_policy (PortableServer::USER_ID);
  policies[3] = parent->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
  policies[4] = parent->create_lifespan_policy (PortableServer::TRANSIENT);

  // Create the POA for the upload agents.
  this->upload_poa_ = parent->create_POA ("TestUploader",
                                          PortableServer::POAManager::_nil (),
                                          policies);

  PortableServer::POAManager_var mgr = this->upload_poa_->the_POAManager ();
  mgr->activate ();

  // Update the policy set.
  policies[2]->destroy ();
  policies[2] = parent->create_id_assignment_policy (PortableServer::SYSTEM_ID);

  // Create the POA for the test archive browser servants.
  this->browser_poa_ = parent->create_POA ("TestArchiveBrowser",
                                           PortableServer::POAManager::_nil (),
                                           policies);

  mgr = this->browser_poa_->the_POAManager ();
  mgr->activate ();

  // Create the POA for the test download servants.
  this->download_poa_ = parent->create_POA ("TestRetriever",
                                            PortableServer::POAManager::_nil (),
                                            policies);

  mgr = this->download_poa_->the_POAManager ();
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
begin_upload (const CUTS::TestProfile & result)
{
  // Extract the UUID of the test.
  ACE_Utils::UUID uuid;
  result.uuid >>= uuid;

  // Make sure the upload is not already taking place.
  if (this->uploads_.find (uuid) == 0)
    throw CUTS::TestArchive::UploadAlreadyActive ();

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
    throw CUTS::TestArchive::UploadFailed ();

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

//
// create_broswer
//
CUTS::TestArchiveBrowser_ptr
CUTS_TestArchive_i::create_broswer (CORBA::ULong size)
{
  // Allocate a new servant.
  CUTS_TestArchiveBrowser_i * servant = 0;

  ACE_NEW_THROW_EX (servant,
                    CUTS_TestArchiveBrowser_i (this->conn_, size),
                    CORBA::NO_MEMORY ());

  ACE_Auto_Ptr <CUTS_TestArchiveBrowser_i> auto_clean (servant);

  // Activate the servant.
  PortableServer::ObjectId_var oid =
    this->browser_poa_->activate_object (servant);

  // Return the servant to the client..
  ::CORBA::Object_var obj =
    this->browser_poa_->id_to_reference (oid.in ());

  CUTS::TestArchiveBrowser_var browser =
    CUTS::TestArchiveBrowser::_narrow (obj.in ());

  auto_clean.release ();
  return browser._retn ();
}

//
// destroy_browser
//
void CUTS_TestArchive_i::
destroy_browser (CUTS::TestArchiveBrowser_ptr browser)
{
  try
  {
    // Locate the servant.
    PortableServer::ServantBase_var servant_base =
      this->browser_poa_->reference_to_servant (browser);

    // Cast the servant base to an uploader agent.
    CUTS_TestArchiveBrowser_i * servant =
      dynamic_cast <CUTS_TestArchiveBrowser_i *> (servant_base.in ());

    // Deactivate the object.
    PortableServer::ObjectId_var oid = this->browser_poa_->servant_to_id (servant);
    this->browser_poa_->deactivate_object (oid.in ());

    // We can savely delete the servant.
    delete servant;
  }
  catch (const PortableServer::POA::ObjectNotActive &)
  {

  }
  catch (const PortableServer::POA::WrongAdapter &)
  {

  }
  catch (const PortableServer::POA::WrongPolicy &)
  {

  }
}

//
// begin_download
//
CUTS::TestRetriever_ptr CUTS_TestArchive_i::
begin_download (const CUTS::DownloadRequest & req)
{
  // Extract the UUID from the request.
  ACE_Utils::UUID uuid;
  req.uuid >>= uuid;

  // Allocate a new servant.
  CUTS_TestRetriever_i * servant = 0;

  ACE_NEW_THROW_EX (servant,
                    CUTS_TestRetriever_i (uuid, req.chunk_size),
                    CORBA::NO_MEMORY ());

  ACE_Auto_Ptr <CUTS_TestRetriever_i> auto_clean (servant);

  if (servant->open (this->opts_.upload_dir_) == 0)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - successfully opened test %s\n",
                uuid.to_string ()->c_str ()));
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to open test %s [%m]\n",
                uuid.to_string ()->c_str ()));

    throw CUTS::TestArchive::TestNotExist ();
  }

  // Activate the servant.
  PortableServer::ObjectId_var oid =
    this->download_poa_->activate_object (servant);

  // Return the servant to the client..
  ::CORBA::Object_var obj =
    this->download_poa_->id_to_reference (oid.in ());

  CUTS::TestRetriever_var retriever =
    CUTS::TestRetriever::_narrow (obj.in ());

  auto_clean.release ();
  return retriever._retn ();
}

//
// download_complete
//
void CUTS_TestArchive_i::
download_complete (const CUTS::TestRetriever_ptr retriever)
{
  try
  {
    // Locate the servant.
    PortableServer::ServantBase_var servant_base =
      this->download_poa_->reference_to_servant (retriever);

    // Cast the servant base to an uploader agent.
    CUTS_TestRetriever_i * servant =
      dynamic_cast <CUTS_TestRetriever_i *> (servant_base.in ());

    // Deactivate the object.
    PortableServer::ObjectId_var oid = this->download_poa_->servant_to_id (servant);
    this->download_poa_->deactivate_object (oid.in ());

    // Close the servant.
    servant->close ();

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - test %s download is complete\n",
                servant->uuid ().to_string ()->c_str ()));

    // We can savely delete the servant.
    delete servant;
  }
  catch (const PortableServer::POA::ObjectNotActive &)
  {

  }
  catch (const PortableServer::POA::WrongAdapter &)
  {

  }
  catch (const PortableServer::POA::WrongPolicy &)
  {

  }
}
