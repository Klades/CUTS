#include "RTIDDS_HelloWorld_ComponentsC.h"

#include "cuts/iccm/arch/rtidds/servant/RTIDDS_EventConsumer_T.h"
#include "cuts/iccm/arch/rtidds/servant/RTIDDS_Publisher_T.h"
#include "cuts/iccm/arch/rtidds/servant/RTIDDS_Publisher_Table_T.h"
#include "HelloWorld_Components_svnt.h"

#include "HelloWorld_Components_stub_export.h"

#include "cuts/iccm/arch/chaos/servant/factory.h"

CHAOS_CONSUMER_FACTORY_IMPL (HELLOWORLD_COMPONENTS_STUB_Export, HelloReceiver_Servant, MessageEvent, iCCM::RTIDDS_EventConsumer_T);
CHAOS_PUBLISHER_TABLE_FACTORY_IMPL (HELLOWORLD_COMPONENTS_STUB_Export, HelloSender_Servant, MessageEvent, iCCM::RTIDDS_Publisher_Table_T);