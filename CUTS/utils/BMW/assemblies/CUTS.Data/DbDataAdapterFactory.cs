// -*- C# -*-

//=============================================================================
/**
 * @file        DbAdapterFactory.cs
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

using System;
using System.Data;

namespace CUTS.Data
{
  public interface IDbDataAdapterFactory
  {
    IDbDataAdapter CreateDbDataAdapter ();

    IDbDataAdapter CreateDbDataAdapter (IDbCommand select);
  }
}
