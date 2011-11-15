// -*- C++ -*-

#include "eisa/EISA_EINodeS.h"

class EINode_Channel_i :
  public POA_EISA::EINode_Channel
{
public:
  EINode_Channel_i (void);

  virtual ~EINode_Channel_i (void);

  virtual void register_einode (const EISA::EINodeRegistration &);

  virtual void unregister_einode (const EISA::UUID &);

  virtual void register_metadata (const EISA::CharStream &);

  virtual void send_data (const EISA::BinaryStream &);
};
