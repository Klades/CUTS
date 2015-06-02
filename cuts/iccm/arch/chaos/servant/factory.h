#define CHAOS_CONSUMER_FACTORY_IMPL(EXPORT,SERVANT,PORT,EVENT,TYPE_T) \
extern "C" \
EXPORT \
iCCM::EventConsumer * \
create_##SERVANT##_##PORT##_consumer (iCCM::CHAOS_Servant * servant) \
{ \
  SERVANT * svnt = dynamic_cast < SERVANT * > (servant); \
  return new TYPE_T < SERVANT, EVENT> (svnt, &SERVANT::push_##PORT##); \
} \
 \

#define CHAOS_PUBLISHER_FACTORY_IMPL(EXPORT,SERVANT,EVENT,TYPE_T) \
extern "C" \
EXPORT \
iCCM::Publisher * \
create_##SERVANT##_##EVENT##_publisher (void) \
{ \
  return new TYPE_T < ##EVENT## > (); \
} \
 \

#define CHAOS_PUBLISHER_TABLE_FACTORY_IMPL(EXPORT,SERVANT,EVENT,TYPE_T) \
extern "C" \
EXPORT \
iCCM::Publisher_Table * \
create_##SERVANT##_##EVENT##_publisher_table (void) \
{ \
  return new TYPE_T < ##EVENT## > (); \
} \
 \

#define CHAOS_SERVANT_IMPL(EXPORT,SERVANT,NAMESPACE,TYPE_T,TYPE) \
namespace NAMESPACE \
{ \
 \
class EXPORT SERVANT \
: public TYPE_T < void, void, void, void > \
{ \
 \
  typedef SERVANT self_type; \
 \
  public: \
  SERVANT (const char * name) \
  : TYPE_T < void, void, void, void > (name) {} \
 \
  virtual ~SERVANT (void){} \
 \
  virtual void _dispatch ( \
      TAO_ServerRequest & req, \
      TAO::Portable_Server::Servant_Upcall *servant_upcall) {} \
 \
  virtual const char* _interface_repository_id (void) const {return "ERROR";} \
}; \
} \
 \
extern "C" \
EXPORT \
iCCM::Servant * \
create_servant (const char * name) \
{ \
  return new NAMESPACE::SERVANT (name); \
}
