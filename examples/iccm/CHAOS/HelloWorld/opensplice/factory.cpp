#include "OpenSplice_HelloWorld_ComponentsC.h"

#include "cuts/iccm/arch/opensplice/servant/OpenSplice_EventConsumer_T.h"
#include "cuts/iccm/arch/opensplice/servant/OpenSplice_Publisher_T.h"
#include "cuts/iccm/arch/opensplice/servant/OpenSplice_Publisher_Table_T.h"
#include "HelloWorld_Components_svnt.h"

#include "HelloWorld_Components_stub_export.h"

#include "cuts/iccm/arch/chaos/servant/factory.h"

CHAOS_CONSUMER_FACTORY_IMPL (HELLOWORLD_COMPONENTS_STUB_Export, HelloReceiver_Servant, MessageEvent, iCCM::OpenSplice_EventConsumer_T);
CHAOS_PUBLISHER_TABLE_FACTORY_IMPL (HELLOWORLD_COMPONENTS_STUB_Export, HelloSender_Servant, MessageEvent, iCCM::OpenSplice_Publisher_Table_T);