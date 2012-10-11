#include <iostream>
#include <string>
#include "TCPIP_Smoke_TestC.h"

int main ()
{
  try
  {
    SmokeStructType st;
    st.SmokeBoolean = true;
    st.SmokeChar = 'c';
    st.SmokeWChar = 'c';
    st.SmokeOctet = 05;
    st.SmokeString = "c";
    st.SmokeWString = L"c";
    st.SmokeShort = 5;
    st.SmokeUShort = 5;
    st.SmokeLong = -68500L;
    st.SmokeULong = 68500L;
    st.SmokeLongLong = -5000000000LL;
    st.SmokeULongLong = 5000000000LL;
    st.SmokeFloat = 3.14F;
    st.SmokeDouble = 6.00;
    st.SmokeEnum = SmokeEnum2;

    OBV_SmokeEvent ev;
    ev.SmokeBoolean (true);
    ev.SmokeChar ('c');
    ev.SmokeWChar ('c');
    ev.SmokeOctet (05);
    ev.SmokeString ("c");
    ev.SmokeWString (L"c");
    ev.SmokeShort (5);
    ev.SmokeUShort (5);
    ev.SmokeLong (-68500L);
    ev.SmokeULong (68500L);
    ev.SmokeLongLong (-5000000000LL);
    ev.SmokeULongLong (5000000000LL);
    ev.SmokeFloat (3.14F);
    ev.SmokeDouble (6.00);
    ev.SmokeEnum (SmokeEnum2);
    ev.SmokeStruct (st);
    return 0;
  }
  catch (...)
  {
    return 1;
  }
}
