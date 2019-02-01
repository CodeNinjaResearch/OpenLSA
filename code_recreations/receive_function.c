int LGJCbord::recv(LGJCbord *this)
{
  signed int characters_received; // eax@1
  signed int return_status; // ecx@1
  signed int data_start_index; // esi@2
  signed int received_array_index; // edx@2
  char checksum_calculator; // dl@7
  char checksum_received; // di@10

  memset((char *)this + 68, 0, 128);

  characters_received = _lgjSCI::recv(*((_lgjSCI **)this + 5), (char *)this + 68, 128);
  return_status = 1;
  if ( characters_received > 0 )
  {
    data_start_index = -1;
    received_array_index = 0;
    __asm
    {
      prefetcht0 byte ptr [edi]
      prefetcht0 byte ptr [ebx+84h]
    }

    while ( *((_BYTE *)this + received_array_index + 68) != 0xC0)
    {
      if ( ++received_array_index > 127 )
        goto TIMEOUT;
    }
    data_start_index = received_array_index;

TIMEOUT:

    return_status = 3;

    if ( data_start_index < characters_received && data_start_index != -1 )
    {
      checksum_calculator = 0;
      for ( int i = data_start_index + 1; i < data_start_index + 21 ; ++i )
        checksum_calculator ^= *((byte) this + i + 68);

      checksum_received = *((_BYTE *)this + data_start_index + 89);

      return_status = 4;

      if ( checksum_received == checksum_calculator )
      {
        return_status = 0;
        *((_BYTE *)this + 46) = *((_BYTE *)this + data_start_index + 68); // 0xC0
        *((_BYTE *)this + 47) = *((_BYTE *)this + data_start_index + 69); // 1
        *((_BYTE *)this + 48) = *((_BYTE *)this + data_start_index + 70); // 2
        *((_BYTE *)this + 49) = *((_BYTE *)this + data_start_index + 71); // 3
        *((_BYTE *)this + 50) = *((_BYTE *)this + data_start_index + 72); // 4
        *((_BYTE *)this + 51) = *((_BYTE *)this + data_start_index + 73); // 5
        *((_BYTE *)this + 52) = *((_BYTE *)this + data_start_index + 74); // 6
        *((_BYTE *)this + 53) = *((_BYTE *)this + data_start_index + 75); // 7
        *((_BYTE *)this + 54) = *((_BYTE *)this + data_start_index + 76); // 8
        *((_BYTE *)this + 55) = *((_BYTE *)this + data_start_index + 77); // 9
        *((_BYTE *)this + 56) = *((_BYTE *)this + data_start_index + 78); // 10
        *((_BYTE *)this + 57) = *((_BYTE *)this + data_start_index + 79); // 11
        *((_BYTE *)this + 58) = *((_BYTE *)this + data_start_index + 80); // 12
        *((_BYTE *)this + 59) = *((_BYTE *)this + data_start_index + 81); // 13
        *((_BYTE *)this + 60) = *((_BYTE *)this + data_start_index + 82); // 14
        *((_BYTE *)this + 61) = *((_BYTE *)this + data_start_index + 83); // 15
        *((_BYTE *)this + 62) = *((_BYTE *)this + data_start_index + 84); // 16
        *((_BYTE *)this + 63) = *((_BYTE *)this + data_start_index + 85); // 17
        *((_BYTE *)this + 64) = *((_BYTE *)this + data_start_index + 86); // 18
        *((_BYTE *)this + 65) = *((_BYTE *)this + data_start_index + 87); // 19
        *((_BYTE *)this + 66) = *((_BYTE *)this + data_start_index + 88); // 20
        *((_BYTE *)this + 67) = checksum_received; // Checksum
      }
    }
  }
  return return_status;
}