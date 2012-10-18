#include <iostream>
#include <string>
#include "RTIDDS_Smoke_Test_ComponentsC.h"

int main (int argc, char ** argv)
{
  try
  {
    SmokeStructType st;
    st.SmokeBoolean = true;
    st.SmokeChar = 'c';
    st.SmokeOctet = 05;
    st.SmokeString = "c";
    st.SmokeShort = 5;
    st.SmokeUShort = 5;
    st.SmokeLong = -68500L;
    st.SmokeULong = 68500L;
    st.SmokeLongLong = -5000000000LL;
    st.SmokeULongLong = 5000000000LL;
    st.SmokeFloat = 3.14F;
    st.SmokeDouble = 6.00;
    st.SmokeEnum = SmokeEnum2;

    Smoke up_base;
    SmokeEventUpcall up (up_base);
    up.SmokeBoolean (true);
    up.SmokeChar ('c');
    up.SmokeOctet (05);
    up.SmokeString ("c");
    up.SmokeShort (5);
    up.SmokeUShort (5);
    up.SmokeLong (-68500L);
    up.SmokeULong (68500L);
    up.SmokeLongLong (-5000000000LL);
    up.SmokeULongLong (5000000000LL);
    up.SmokeFloat (3.14F);
    up.SmokeDouble (6.00);
    up.SmokeEnum (SmokeEnum2);
    up.SmokeStruct (st);

    SmokeEventDowncall dn;
    dn.SmokeBoolean (true);
    dn.SmokeChar ('c');
    dn.SmokeOctet (05);
    dn.SmokeString ("c");
    dn.SmokeShort (5);
    dn.SmokeUShort (5);
    dn.SmokeLong (-68500L);
    dn.SmokeULong (68500L);
    dn.SmokeLongLong (-5000000000LL);
    dn.SmokeULongLong (5000000000LL);
    dn.SmokeFloat (3.14F);
    dn.SmokeDouble (6.00);
    dn.SmokeEnum (SmokeEnum2);
    dn.SmokeStruct (st);
    return 0;
  }
  catch (...)
  {
    return 1;
  }
}
