#pragma once

#include "error.hpp"


namespace modbus {

  class Result
  {
    public:
      // TODO: Use Node->ID after test
      std::uint8_t GetUnitId() { return 1; }
      virtual std::size_t Serialize ( std::uint8_t* pdu, std::size_t maxsz ) = 0;

    protected:
      virtual ~Result() = default;

    protected:
      void* _context;               ///< Pointer to Node
  };

}

