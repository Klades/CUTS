#define CUTS_INACTIVE_SUBSERVANT
#include "HelloWorld_Components_iCCMC.h"

#include "OpenSplice_HelloWorld_ComponentsC.h"

#include "cuts/iccm/arch/opensplice/servant/OpenSplice_Servant_T.h"
#include "cuts/iccm/arch/opensplice/servant/OpenSplice_EventConsumer_T.h"
#include "cuts/iccm/arch/opensplice/servant/OpenSplice_Publisher_T.h"
#include "cuts/iccm/arch/opensplice/servant/OpenSplice_Publisher_Table_T.h"
#include "HelloWorld_Components_svnt.h"

#include "HelloWorld_Components_stub_export.h"

#include "cuts/iccm/arch/chaos/servant/factory.h"

CHAOS_CONSUMER_FACTORY_IMPL (HELLOWORLD_COMPONENTS_STUB_Export, HelloReceiver_Servant, greeting_ospl, MessageEvent, iCCM::OpenSplice_EventConsumer_T);
CHAOS_CONSUMER_FACTORY_IMPL (HELLOWORLD_COMPONENTS_STUB_Export, HelloReceiver_Servant, greeting_ndds, MessageEvent, iCCM::OpenSplice_EventConsumer_T);
CHAOS_CONSUMER_FACTORY_IMPL (HELLOWORLD_COMPONENTS_STUB_Export, HelloReceiver_Servant, greeting_tcpip, MessageEvent, iCCM::OpenSplice_EventConsumer_T);
CHAOS_PUBLISHER_TABLE_FACTORY_IMPL (HELLOWORLD_COMPONENTS_STUB_Export, HelloSender_Servant, MessageEvent, iCCM::OpenSplice_Publisher_Table_T);

CHAOS_SERVANT_IMPL (HELLOWORLD_COMPONENTS_STUB_Export, HelloSender_Servant, OpenSplice, iCCM::OpenSplice_Servant_T, iCCM::OpenSplice_Servant);