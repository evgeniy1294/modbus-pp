#pragma once
#include <cstdint>


namespace modbus {
  
  enum Error {
    ERROR_NONE,                  ///< No error
    ERROR_FAILED,                ///< Operation failed
    ERROR_NO_BUFS,               ///< Insufficient buffers
    ERROR_BUSY,                  ///< Service is busy and could not service the operation 
    ERROR_INVALID_ARGS,          ///< Input arguments are invalid
    ERROR_ABORT,                 ///< Operation was aborted
    ERROR_NOT_IMPLEMENTED,       ///< Function or method is not implemented
    ERROR_INVALID_STATE,         ///< Cannot complete due to invalid state
    ERROR_NOT_FOUND,             ///< The requested item could not be found
    ERROR_ALREADY,               ///< The operation is already in progress
    ERROR_NOT_CAPABLE,           ///< Operation prevented by mode flags
    ERROR_RESPONSE_TIMEOUT,      ///< Response from remote device not received
    ERROR_DISABLED_FEATURE,      ///< A feature/functionality disabled by build-time configuration options.
    NUM_ERRORS,
    ERROR_GENERIC = 255,         ///< Generic error (should not use)
  };

} // namespace modbus
