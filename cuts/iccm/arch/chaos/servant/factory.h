#define CHAOS_CONSUMER_FACTORY_IMPL(EXPORT,SERVANT,EVENT,TYPE_T) \
EXPORT \
iCCM::EventConsumer * \
create_##SERVANT##_##EVENT##_consumer (SERVANT * svnt, \
                                      TYPE_T < SERVANT, ##EVENT## >::DESERIALIZE_METHOD callback) \
{ \
  return new TYPE_T < SERVANT, ##EVENT##> (svnt, callback); \
} \
 \

#define CHAOS_PUBLISHER_FACTORY_IMPL(EXPORT,SERVANT,EVENT,TYPE_T) \
EXPORT \
iCCM::Publisher * \
create_##SERVANT##_##EVENT##_publisher (void) \
{ \
  return new TYPE_T < ##EVENT## > (); \
} \
 \

#define CHAOS_PUBLISHER_TABLE_FACTORY_IMPL(EXPORT,SERVANT,EVENT,TYPE_T) \
EXPORT \
iCCM::Publisher_Table * \
create_##SERVANT##_##EVENT##_publisher_table (void) \
{ \
  return new TYPE_T < ##EVENT## > (); \
}